package com.android.clothingrecycle;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.widget.Toast;

import com.alibaba.fastjson.JSONObject;
import com.android.clothingrecycle.Data.DataManager;
import com.android.clothingrecycle.Data.DoorState;
import com.android.clothingrecycle.Data.GridData;
import com.android.clothingrecycle.Http.HttpManager;
import com.android.clothingrecycle.tasks.TaskCleaningOpenGrid;
import com.android.clothingrecycle.tasks.TaskManager;
import com.android.clothingrecycle.trans.TransManager;
import com.android.clothingrecycle.trans.TransParam;
import com.android.raimy.utils.AbstractSingleton;
import com.android.raimy.utils.LogHelper;
import com.android.raimy.utils.Module.task.TaskBase;
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.Response;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import cn.jpush.android.api.JPushInterface;

/**
 * Created by raimy on 2018-03-15.
 */

public class Logic implements com.squareup.okhttp.Callback, TransManager.ICallBack{
    private Context mAppContext;
    private TransManager mTransManager;
    private DataManager mDataManager;
    private HttpManager mHttpManager;
    private final static String TAG = "Logic";
    private String mJpushRegistrationID;
    private String mCabinnetNumber;
    private Bitmap mQrCode;
    private InputStream mQrCodeStream;
    private LogicParam.LogicCallBack mLogicCallBack;
    private TaskManager mTaskManager;

    public Bitmap getmQrCode() {
        return mQrCode;
    }

    public InputStream GetQrCodeStream(){
        return mQrCodeStream;
    }

    public static AbstractSingleton<Logic> ObjCreater = new AbstractSingleton<Logic>() {
        @Override
        protected Logic NewObject() {
            return new Logic();
        }
    };

    private Logic(){
    }

    public void Init(Context appContext, LogicParam.LogicCallBack callBack){
        mAppContext = appContext;
        mCabinnetNumber = "abc0001";
        mLogicCallBack = callBack;
        mDataManager = DataManager.ObjCreater.GetInstance();
        mTransManager = TransManager.ObjCreater.GetInstance();
        mHttpManager = new HttpManager(this);
        mDataManager.Init(appContext);
        mTaskManager = new TaskManager(mAppContext);
        mTaskManager.Init();
        mTaskManager.StartTasks();

        InitJPush(appContext);
        InitTrans(appContext);
        InitHttp();
    }

    private void InitJPush(Context context){
        JPushInterface.setDebugMode(true);
        JPushInterface.init(mAppContext);
        mJpushRegistrationID = JPushInterface.getRegistrationID(context);
        if(mJpushRegistrationID.isEmpty()){
            Toast.makeText(context, "JPush 初始化失败， 获取ID失败", Toast.LENGTH_SHORT).show();
        }
    }

    private void InitTrans(Context context){
        mTransManager = TransManager.ObjCreater.GetInstance();
        mTransManager.Init(context, this);
    }

    private void InitHttp(){
        mHttpManager.HttpRegisterCabinet(mCabinnetNumber, mJpushRegistrationID,
                mDataManager.GetGridCount(), mDataManager.GetGridUsedCount());

       DoHttpGetQRCode();
    }

    private void DoHttpGetQRCode(){
        int nGrid = mDataManager.GetEmptyGrid();
        if(nGrid != -1) {
            mHttpManager.HttpGetQRCode(mCabinnetNumber, nGrid);
        }else{
            mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GridStateFull));
        }
    }

    public void UnInit() {
        mAppContext = null;
        mTransManager.UnInit();
    }


    @Override
    public void onFailure(Request request, IOException e) {
        LogHelper.logI(TAG, "===onFailure"+request.toString());
    }

    @Override
    public void onResponse(Response response) throws IOException {
        LogHelper.logD(TAG, "===onResponse: "+response.toString());
        boolean result = response.code()>=200 && response.code()<300;
        if(response.toString().contains(HttpManager.Url_registerCabinet)
                && result ){
        }else if(response.toString().contains(HttpManager.Url_openCabinetQRCodes)
                && result){
            JSONObject jobject = JSONObject.parseObject(response.body().string());
            String strQRUrl = jobject.getString(HttpManager.Rsp_openCabinetQRCodes_Key_QRUrl);
            mHttpManager.HttpDownloadQrCode(strQRUrl, new DownLoadQRCallBack());
        }
    }

    private void DoStateChangedWhileCleaning(boolean[] bStates, Map<Integer, Integer> retInfo){
        Set entrys = retInfo.entrySet();
        Iterator it = entrys.iterator();

        while (it.hasNext()) {
            Map.Entry entry = (Map.Entry) it.next();
            int key = (Integer) entry.getKey();
            int value = (Integer) entry.getValue();
            int curState = DoorState.Door_state_None;

            if (value == DoorState.Door_state_close) {//如果是关闭，则新状态为开
                curState =  DoorState.Door_state_open;
                mDataManager.UpdateDoorState(key,curState);
            } else if (value == DoorState.Door_state_open) {//如果是打开，则新状态为关闭
                curState =  DoorState.Door_state_close;
                mDataManager.UpdateDoorState(key, curState);
                mDataManager.UpdateGridData(key, GridData.State_Empty);
            }

            mTaskManager.DoGridDoorStateChange(key, curState);
            if(mDataManager.IsAllGridEmpty() && mDataManager.IsAllDoorsClosed()){
                //箱子都关闭，上传状态,退出清理模式
                mDataManager.SetCleaning(false);
                mHttpManager.HttpUploadGridStatus(mCabinnetNumber,
                        mDataManager.GetGridCount(),
                        mDataManager.GetGridUsedCount());
                mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GridCleanOver));
                mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GetNextEmptyGridQr));
                DoHttpGetQRCode();
            }else{
                mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GridCleaning));
            }


        }
    }

    private void DoStateChangedNotCleaning(boolean[] bStates, Map<Integer, Integer> retInfo){
        Set entrys = retInfo.entrySet();
        Iterator it = entrys.iterator();

        while (it.hasNext()) {
            Map.Entry entry = (Map.Entry) it.next();
            int key = (Integer) entry.getKey();
            int value = (Integer) entry.getValue();
            if (value == DoorState.Door_state_open) {//如果是打开，则新状态为关闭
                mDataManager.UpdateGridData(key, GridData.State_Not_Empty);
                mDataManager.UpdateDoorState(key, DoorState.Door_state_close);
                mHttpManager.HttpUploadGridStatus(mCabinnetNumber,
                        mDataManager.GetGridCount(),
                        mDataManager.GetGridUsedCount());//箱门关闭，上传柜子状态

                if (-1 == mDataManager.GetEmptyGrid()) {
                    LogicParam lParam = new LogicParam();
                    lParam.logicType = LogicParam.ELogicType.GridStateFull;
                    mLogicCallBack.OnLogicCallBack(lParam);
                }
                mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GetNextEmptyGridQr));
                DoHttpGetQRCode();
            }else{
                mDataManager.UpdateDoorState(key, DoorState.Door_state_open);
            }
        }

        LogicParam lParam = new LogicParam();
        lParam.logicType = LogicParam.ELogicType.DoorStateChange;
        lParam.retMap = retInfo;
        mLogicCallBack.OnLogicCallBack(lParam);
    }

    @Override
    public void OnTransCallBack(TransParam param) {
        switch(param.cmd) {
            case Cmd_Get_AllDoorsStates: {
                boolean bStatus[] = new boolean[24];
                Map<Integer, Integer> retInfo = new HashMap<Integer, Integer>();
                TransManager.getDoorStatusFromArray(param.retInfo, bStatus);
                if (mDataManager.GetChangedDoors(bStatus, retInfo)) {//箱子状态改变
                    if (mDataManager.IsCleaning()) {
                        DoStateChangedWhileCleaning(bStatus, retInfo);
                    } else {
                        DoStateChangedNotCleaning(bStatus, retInfo);
                    }
                }
                }
                break;
                default:
                    break;
        }
    }

    public class DownLoadQRCallBack implements Callback{
        @Override
        public void onFailure(Request request, IOException e) {

        }

        @Override
        public void onResponse(Response response) throws IOException {
            InputStream inputStream = response.body().byteStream();
            mQrCode = BitmapFactory.decodeStream(inputStream);
            mLogicCallBack.OnLogicCallBack(new
                    LogicParam(LogicParam.ELogicType.DownloadQRCodes, LogicParam.EResult.Result_Suc));
        }
    }

    public void DoLogicReset(){
        mTaskManager.CleanTasks();
        mDataManager.ResetData();
        mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GridCleanOver));
        DoHttpGetQRCode();
    }
    //{"boxNumber":"7","type":"openOne","cabinetNumber":"abc0001"}
    public void DoLogicJPushMsg(String strMsg){
        JSONObject jobj = (JSONObject)JSONObject.parse(strMsg);
        String type = jobj.getString("type");
        if("openOne".equals(type)){
            String num = jobj.getString("boxNumber");
            int openNum = Integer.parseInt(num);
            if(openNum != -1) {
               // mTransManager.PushCmd(new TransParam(TransParam.eCmd.Cmd_Open_Dor, 1, openNum));
                TaskBase task = new TaskCleaningOpenGrid(openNum, mTaskManager);
                mTaskManager.AddTask(task);
            }
        }else if("openAll".equals(type)){
            Logic.ObjCreater.GetInstance().DoLogicCleanGrid();
        }

    }

    public void DoLogicCleanGrid(){

        if(mDataManager.IsAllGridEmpty()){
            return;
        }

        mDataManager.SetCleaning(true);
        //mDataManager.ResetData();

        mLogicCallBack.OnLogicCallBack(new LogicParam(LogicParam.ELogicType.GridCleaning));


        Map<Integer, Integer> map = mDataManager.GetGridStates();
        Set entrys = map.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry)it.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer)entry.getValue();
           // mTransManager.PushCmd(new TransParam(TransParam.eCmd.Cmd_Open_Dor, 1, key+1));
            if(value == GridData.State_Not_Empty){
                TaskBase task = new TaskCleaningOpenGrid(key, mTaskManager);
                mTaskManager.AddTask(task);
            }
        }
    }

    public int GetEmptyGridSize(){
        return mDataManager.GetEmptyGridSize();
    }

    public int GetTotalGridSize(){
        return mDataManager.GetGridCount();
    }

    public int GetUsedGridSize(){
        return mDataManager.GetGridUsedCount();
    }
}
