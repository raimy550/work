package com.android.clothingrecycle;

import android.app.ProgressDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.clothingrecycle.Data.DoorState;
import com.android.raimy.utils.MyTimer;
import com.android.raimy.utils.ToastHelper;
import com.android.raimy.utils.ui.framework.InterfaceUi;
import com.android.raimy.utils.ui.framework.UiHandler;

import java.io.Serializable;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class MainActivity extends AppCompatActivity implements View.OnClickListener,
        LogicParam.LogicCallBack, MyTimer.ITimerCallBack, InterfaceUi, UiHandler.HandleUiCallBack{

    private Logic mLogic;
    private ImageView mIVQuickMark;
    private UiHandler mUIHandler;
    private ProgressDialog mProgressDlg;
    private MyTimer mQrTimer;
    private TextView mTvContent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        InitLogic();
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

    @Override
    public void OnUiCallBack(Serializable logicParam) {
        LogicParam param = (LogicParam)(logicParam);
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

    @Override
    public void InitView(){
        Button btn = (Button) findViewById(R.id.btn_interfacetest);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_make_qucode);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_reset);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_stretch);
        btn.setOnClickListener(this);


        mTvContent = (TextView) findViewById(R.id.tv_content);
        mProgressDlg = new ProgressDialog(this);
        mProgressDlg.setTitle("正在加载中");
        mIVQuickMark = (ImageView)findViewById(R.id.iv_quickmark);
        int nSize = mLogic.GetEmptyGridSize();
        mTvContent.setText(getResources().getString(R.string.content_scan)+"(空箱："+nSize+"个)");
        ShowProgressDlg();
    }

    @Override
    public void UnInitView() {

    }

    @Override
    public boolean InitLogic() {
        mUIHandler = new UiHandler(this);
        mQrTimer = new MyTimer(this, 300, 4000);
        mLogic = Logic.ObjCreater.GetInstance();
        mLogic.Init(getApplicationContext(), this);

        return true;
    }

    @Override
    public void UnInitLogic() {

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
            case R.id.btn_stretch:
                ShowDetail();
                break;
            default:
                break;
        }
    }

    private void ShowDetail(){
        DetailPopupWindow popupWindow = new DetailPopupWindow(this);
        popupWindow.Show();
    }

    @Override
    public void OnLogicCallBack(LogicParam param) {
       mUIHandler.SendMessage(param);
    }
}
