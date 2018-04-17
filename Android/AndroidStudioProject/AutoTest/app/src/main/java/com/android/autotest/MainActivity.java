package com.android.autotest;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.android.autotest.utils.AlertDlg;
import com.android.autotest.utils.TestUtils;
import com.android.autotest.utils.LogicParam;
import com.raimy.utils.ui.framework.UiHandler;
import com.raimy.utils.ui.framework.InterfaceUi;

public class MainActivity extends AppCompatActivity implements LogicParam.LogicCallBack,
        InterfaceUi,UiHandler.HandleUiCallBack, View.OnClickListener, AlertDlg.IAlertDlgCallBack{
    private Logic mLogic;
    private UiHandler mUiHandler;
    private TextView mTvTestSerail;
    private TextView mTvTestUsb;

    private TextView mTvTestTrumpet;
    private TextView mTvTestHeadSet;
    private TextView mTvTestCrash;
    private TextView mTvInfo, mTvDetail;
    private AlertDlg mAlertDlg;

    @Override
    protected void onPostResume() {
        super.onPostResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        UnInitLogic();
        UnInitView();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        InitView();
        InitLogic();
    }

    @Override
    public void InitView() {
        Button btn = (Button) findViewById(R.id.bt_start);
        btn.setOnClickListener(this);
        mTvTestSerail = (TextView) findViewById(R.id.tv_test_serial);
        mTvTestUsb = (TextView) findViewById(R.id.tv_test_Usb);
        mTvTestCrash = (TextView) findViewById(R.id.tv_test_crash);
        mTvTestTrumpet = (TextView) findViewById(R.id.tv_test_trumpet);
        mTvTestHeadSet = (TextView) findViewById(R.id.tv_test_headset);
        mTvInfo = (TextView) findViewById(R.id.tv_info);
        mTvDetail = (TextView) findViewById(R.id.tv_detail);

        mAlertDlg = new AlertDlg(this, this);
    }

    @Override
    public void UnInitView() {

    }

    @Override
    public boolean InitLogic() {
        mUiHandler = new UiHandler();
        mUiHandler.Init(this);
        mLogic = Logic.ObjCreater.GetInstance();
        mLogic.Init(getApplicationContext(), this);
        return true;
    }

    @Override
    public void UnInitLogic() {
        mLogic.UnInit();
    }

    @Override
    public void OnLogicCallBack(LogicParam param) {
        mUiHandler.SendMessage(param);
    }

    @Override
    public void OnAlertDlgCallBack(int type, int result) {
        mLogic.DoLogicDlgResponse(type, result);
    }

    @Override
    public void OnUiCallBack(LogicParam param) {
        switch(param.logicType){
            case ETest_Serial:
                DoUiTestSerial(param);
                break;
            case ETest_Crash:
                DoUiTestCrash(param);
                break;
            case ETest_USB:
                DoUiTestUsb(param);
                break;
            case ETest_Trumpet:
                DoUiTestTrumpet(param);
                break;
            case ETest_Headset:
                DoUiTestHeadset(param);
                break;
            case ETest_AllResult:
                DoUiAllResult(param);
                break;
            default:
                break;
        }
    }

    private void DoUiTestTrumpet(LogicParam param){
        if(param.testState == LogicParam.EState.State_Start){
            AddTextToDetail(R.string.detail_trumpet);
            SetTestingOp(LogicParam.ELogicType.ETest_Trumpet);
            mAlertDlg.SetOpts(TestUtils.TEST_TRUMPET, R.string.dlg_trumpet, AlertDlg.Btn_Two).Show();
        }else if(param.testState == LogicParam.EState.State_Tesing){

        }else if(param.testState == LogicParam.EState.State_Over){
            if(param.result == LogicParam.EResult.Result_Suc){
                AddTextToDetail(R.string.info_suc);
            }else{
                AddTextToDetail(R.string.info_fail);
            }
        }
    }

    private void DoUiTestHeadset(LogicParam param){
        if(param.testState == LogicParam.EState.State_Start){
            AddTextToDetail(R.string.detail_headset);
            SetTestingOp(LogicParam.ELogicType.ETest_Headset);
            mAlertDlg.SetOpts(TestUtils.TEST_HEADSET, R.string.dlg_headset, AlertDlg.Btn_Two).Show();
        }else if(param.testState == LogicParam.EState.State_Tesing){

        }else if(param.testState == LogicParam.EState.State_Over){
            if(param.result == LogicParam.EResult.Result_Suc){
                AddTextToDetail(R.string.info_suc);
            }else{
                AddTextToDetail(R.string.info_fail);
            }
        }
    }

    private void DoUiAllResult(LogicParam param){
        if(param.result == LogicParam.EResult.Result_Suc){
            mTvInfo.setText(R.string.info_suc);
        }else{
            mTvInfo.setText(R.string.info_fail);
        }
    }

    private void DoUiTestUsb(LogicParam param){
        if(param.testState == LogicParam.EState.State_Start){
            AddTextToDetail(getString(R.string.detail_usb));
            SetTestingOp(LogicParam.ELogicType.ETest_USB);
        }else if(param.testState == LogicParam.EState.State_Tesing){
            if(param.result == LogicParam.EResult.Result_Fail){
                AddTextToDetail(param.mStrParam1+TestUtils.Pad  +"fail");
                mTvInfo.setText(R.string.info_fail);
            }else{
                AddTextToDetail(param.mStrParam1+TestUtils.Pad  +"Suc");
            }
        }else if(param.testState == LogicParam.EState.State_Over){
            if(param.result == LogicParam.EResult.Result_Suc){
                AddTextToDetail(R.string.info_suc);
            }else{
                AddTextToDetail(R.string.info_fail);
            }
        }
    }

    private void DoUiTestCrash(LogicParam param){
        if(param.testState == LogicParam.EState.State_Start){
            AddTextToDetail(R.string.detail_crash);
            SetTestingOp(LogicParam.ELogicType.ETest_Crash);
            mAlertDlg.SetOpts(TestUtils.TEST_CRASH, R.string.dlg_crash, AlertDlg.Btn_Two).Show();
        }else if(param.testState == LogicParam.EState.State_Tesing){

        }else if(param.testState == LogicParam.EState.State_Over){
            if(param.result == LogicParam.EResult.Result_Suc){
                AddTextToDetail(R.string.info_suc);
            }else{
                AddTextToDetail(R.string.info_fail);
            }
        }
    }

    private void DoUiTestSerial(LogicParam param){
        if(param.testState == LogicParam.EState.State_Start){
            AddTextToDetail(getString(R.string.detail_serial));
            SetTestingOp(LogicParam.ELogicType.ETest_Serial);
        }else if(param.testState == LogicParam.EState.State_Tesing){
            if(param.result == LogicParam.EResult.Result_Fail){
                AddTextToDetail(param.mStrParam1+TestUtils.Pad  +"fail");
                mTvInfo.setText(R.string.info_fail);
            }else{
                AddTextToDetail(param.mStrParam1+TestUtils.Pad  +"Suc");
            }
        }else if(param.testState == LogicParam.EState.State_Over){
            if(param.result == LogicParam.EResult.Result_Suc){
                AddTextToDetail(R.string.info_suc);
            }else{
                AddTextToDetail(R.string.info_fail);
            }
        }


    }

    private void AddTextToDetail(int resId){
        String str = getResources().getString(resId);
        AddTextToDetail(str);
    }

    private void AddTextToDetail(String str){
        mTvDetail.append(str+"\n");
        int offset=mTvDetail.getLineCount()*mTvDetail.getLineHeight();
        if(offset>mTvDetail.getHeight()){
            mTvDetail.scrollTo(0,offset-mTvDetail.getHeight());
        }
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.bt_start:
            DoStartTest();
            break;
            default:
            break;
        }
    }

    private void DoStartTest(){
        ResetUi();
        mTvInfo.setText(R.string.info_testing);
        mLogic.DoLogicStartTest();
    }

    private void SetTestingOp(LogicParam.ELogicType type){
        switch(type){
            case ETest_Serial:
                mTvTestSerail.setTextColor(getResources().getColor(R.color.color_testing));
            break;
            case ETest_USB:
                mTvTestUsb.setTextColor(getResources().getColor(R.color.color_testing));
                break;
            case ETest_Crash:
                mTvTestCrash.setTextColor(getResources().getColor(R.color.color_testing));
                break;
            case ETest_Trumpet:
                mTvTestTrumpet.setTextColor(getResources().getColor(R.color.color_testing));
                break;
            case ETest_Headset:
                mTvTestHeadSet.setTextColor(getResources().getColor(R.color.color_testing));
                break;

            default:
            break;
        }
    }

    private void ResetUi(){
        mTvDetail.setText("");
        mTvTestSerail.setTextColor(getResources().getColor(R.color.color_test));
        mTvTestUsb.setTextColor(getResources().getColor(R.color.color_test));
        mTvTestCrash.setTextColor(getResources().getColor(R.color.color_test));
        mTvTestTrumpet.setTextColor(getResources().getColor(R.color.color_test));
        mTvTestHeadSet.setTextColor(getResources().getColor(R.color.color_test));



    }
}
