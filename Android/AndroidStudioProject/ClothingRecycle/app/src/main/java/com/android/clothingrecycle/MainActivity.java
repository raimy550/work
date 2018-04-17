package com.android.clothingrecycle;

import android.app.ProgressDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.hardware.camera2.params.Face;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.clothingrecycle.Data.DoorState;
import com.raimy.utils.MyTimer;
import com.raimy.utils.ToastHelper;

import java.io.InputStream;
import java.text.Format;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class MainActivity extends AppCompatActivity implements View.OnClickListener,
        LogicParam.LogicCallBack, MyTimer.ITimerCallBack{

    private Logic mLogic;
    private ImageView mIVQuickMark;
    private Handler mUIHandler;
    private ProgressDialog mProgressDlg;
    private MyTimer mQrTimer;
    private TextView mTvContent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Init();
        InitView();
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        Logic.ObjCreater.GetInstance().UnInit();
    }

    @Override
    public void OnTimerCallBack() {
        mQrTimer.stopTimer();
        mProgressDlg.dismiss();
    }

    public class HandlerCallBack implements  Handler.Callback{

        @Override
        public boolean handleMessage(Message msg) {
            LogicParam param = (LogicParam)msg.getData().getSerializable("LogicParam");
            switch (param.logicType){
                case DownloadQRCodes:
                    DoParamDownloadQRCodes(param);
                    break;
                case DoorStateChange:
                    DoParamDoorStateChange(param);
                    break;
                case GridStateFull:
                    DoParamGridStateFull(param);
                    break;
                case GetEmptyGridFail:
                    ToastHelper.showToast(MainActivity.this, "获取空箱子失败");
                    DismissProgressDlg();
                    break;
                case GetNextEmptyGridQr:
                    ShowProgressDlg();
                    break;
                case GridCleaning:
                    mIVQuickMark.setImageBitmap(null);
                    mTvContent.setText(R.string.content_cleaning);
                    break;
                case GridCleanOver:
                    UpdateGridUsedContent();
                    break;
                default:
                    break;
            }
            return false;
        }
    }

    private void DoParamGridStateFull(LogicParam param) {
        mIVQuickMark.setImageBitmap(null);
        mTvContent.setText(R.string.content_gridfull);
        ToastHelper.showToast(this, "箱子已经满!");
    }

    private void DoParamDoorStateChange(LogicParam param) {
        Set entrys = param.retMap.entrySet();
        Iterator it = entrys.iterator();
        while (it.hasNext()){
            Map.Entry entry = (Map.Entry) it.next();
            int key = (Integer) entry.getKey();
            int value = (Integer) entry.getValue();
            String strConent="";
            if(value == DoorState.Door_state_close){
                strConent = String.format("<<%d>> 门打开!",key+1);
            }else if(value == DoorState.Door_state_open){
                strConent = String.format("<<%d>> 门关闭!", key+1);
            }else if(value == DoorState.Door_state_cleaning){
                strConent = String.format("<<%d>> 门清理中!清理完成后请关门！",key+1);
            }
            ToastHelper.showToast(this, strConent);
        }

        UpdateGridUsedContent();

    }

    private void DoParamDownloadQRCodes(LogicParam param){
       DismissProgressDlg();
        Bitmap bmp;
//        InputStream bmpStream;
//
//        BitmapFactory.Options factory = new BitmapFactory.Options();
//        factory.inJustDecodeBounds = true;
//        bmpStream = mLogic.GetQrCodeStream();
//        bmp = BitmapFactory.decodeStream(bmpStream, null, factory);
//
//        int dh = mIVQuickMark.getMeasuredHeight();
//        int dw = mIVQuickMark.getMeasuredWidth();
//        int hRatio = (int)Math.ceil(factory.outHeight / (float)dh);
//        int wRatio = (int)Math.ceil(factory.outWidth / (float)dw);
//        if(hRatio >  1 || wRatio > 1){
//            if(hRatio > wRatio){
//                factory.inSampleSize = hRatio;
//            }else{
//                factory.inSampleSize = wRatio;
//            }
//        }
//
//        factory.inJustDecodeBounds = false;
       bmp = mLogic.getmQrCode();
        mIVQuickMark.setImageBitmap(bmp);
    }

    private void UpdateGridUsedContent(){
        int nSize  = mLogic.GetEmptyGridSize();
        if(nSize!=0){
            String strRet = getResources().getString(R.string.content_scan)+"(空箱："+nSize+"个)";
            mTvContent.setText(strRet);
        }

    }

    private void Init(){
        mUIHandler = new Handler(new HandlerCallBack());
        mQrTimer = new MyTimer(this, 300, 4000);
        mLogic = Logic.ObjCreater.GetInstance();
        mLogic.Init(getApplicationContext(), this);


    }

    private void InitView(){
        Button btn = (Button) findViewById(R.id.btn_interfacetest);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_make_qucode);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_reset);
        btn.setOnClickListener(this);
        mTvContent = (TextView) findViewById(R.id.tv_content);
        mProgressDlg = new ProgressDialog(this);
        mProgressDlg.setTitle("正在加载中");
        mIVQuickMark = (ImageView)findViewById(R.id.iv_quickmark);
        int nSize = mLogic.GetEmptyGridSize();
        mTvContent.setText(getResources().getString(R.string.content_scan)+"(空箱："+nSize+"个)");
        ShowProgressDlg();
    }

    private void ShowProgressDlg(){
        mQrTimer.startTimer();
        mProgressDlg.show();
    }

    private void DismissProgressDlg(){
        mQrTimer.stopTimer();
        mProgressDlg.dismiss();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_interfacetest:
                startActivity(new Intent(this, InterfaceActivity.class));
                break;
            case R.id.btn_make_qucode:
                break;
            case R.id.btn_reset:
                mLogic.DoLogicReset();
                break;
            default:
                break;
        }
    }

    @Override
    public void OnLogicCallBack(LogicParam param) {
        Message msg = new Message();
        Bundle bundle = new Bundle();
        bundle.putSerializable("LogicParam", param);
        msg.setData(bundle);
        mUIHandler.sendMessage(msg);

    }
}
