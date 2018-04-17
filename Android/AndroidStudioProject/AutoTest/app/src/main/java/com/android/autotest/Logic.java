package com.android.autotest;

import android.content.Context;
import android.media.MediaPlayer;

import com.android.autotest.threads.TestSerialThread;
import com.android.autotest.utils.AlertDlg;
import com.android.autotest.utils.TestEntry;
import com.android.autotest.utils.TestUtils;
import com.android.autotest.utils.LogicParam;
import com.raimy.utils.AbstractSingleton;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import phoenix.peripherals.CashDrawerManager;

/**
 * Created by raimy on 2018-04-10.
 */

public class Logic implements  IAsyncCallBack{
    private Context mAppContext;
    private LogicParam.LogicCallBack mLogicCallBack;
    private List<TestEntry> mTestList;
    private MediaPlayer mediaPlayer;

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
        mLogicCallBack = callBack;
        mTestList = new ArrayList<>();
        InitTestList();

    }

    private void InitTestList(){
        TestEntry entry = new TestEntry(TestUtils.TEST_SERIAL);
        entry.ident = TestUtils.Serial2_Ident;
        entry.baudrate = TestUtils.Serial_BaudRate;
        mTestList.add(entry);

        entry = new TestEntry(TestUtils.TEST_SERIAL);
        entry.baudrate = TestUtils.Serial_BaudRate;
        entry.ident = TestUtils.Serial3_Ident;
        mTestList.add(entry);

        entry = new TestEntry(TestUtils.TEST_SERIAL);
        entry.baudrate = TestUtils.Serial_BaudRate;
        entry.ident = TestUtils.Serial4_Ident;
        mTestList.add(entry);

        mTestList.add(new TestEntry(TestUtils.TEST_CRASH));

        mTestList.add(new TestEntry(TestUtils.TEST_TRUMPET));

        mTestList.add(new TestEntry(TestUtils.TEST_HEADSET));

        mTestList.add(new TestEntry(TestUtils.TEST_USB, TestUtils.Usb2_Ident));
        mTestList.add(new TestEntry(TestUtils.TEST_USB, TestUtils.Usb3_Ident));
        mTestList.add(new TestEntry(TestUtils.TEST_USB, TestUtils.Usb4_Ident));
        mTestList.add(new TestEntry(TestUtils.TEST_USB, TestUtils.Usb5_Ident));

    }

    public void UnInit(){
        mAppContext = null;
        mLogicCallBack = null;
    }

    public void DoLogicStartTest(){
        DoLogicReset();
        DoTest(TestUtils.TEST_SERIAL);
    }

    private void DoLogicTestNext(int testType){
        if(testType == TestUtils.TEST_SERIAL){
            DoTest(TestUtils.TEST_USB);
        }else if(testType == TestUtils.TEST_USB){
            DoTest(TestUtils.TEST_CRASH);
        }else if(testType == TestUtils.TEST_CRASH){
            DoTest(TestUtils.TEST_TRUMPET);
        }else if(testType == TestUtils.TEST_TRUMPET){
            DoTest(TestUtils.TEST_HEADSET);
        }else if(testType == TestUtils.TEST_HEADSET){
            DoTestOver();
        }
    }

    private void DoTest(int type){
        DoLogicCallBack(TestUtils.GetLogicType(type), LogicParam.EState.State_Start, null);

        switch(type){
            case TestUtils.TEST_SERIAL:
                DoTestSerial();
            break;
            case TestUtils.TEST_USB:
                DoTestUsb();
                break;
            case TestUtils.TEST_CRASH:
                DoTestCrash();
                break;
            case TestUtils.TEST_TRUMPET:
                DoTestTrumpet();
                break;
            case TestUtils.TEST_HEADSET:
                DoTestHeadSet();
                break;
            default:
                break;
        }
    }

    private void DoTestOver(){
        boolean bRet = IsAllTestedOk();
        DoLogicCallBack(LogicParam.ELogicType.ETest_AllResult, LogicParam.EState.State_Over,
                bRet? LogicParam.EResult.Result_Suc : LogicParam.EResult.Result_Fail);
    }

    private void DoTestSerial(){
        for (int i=0; i<mTestList.size();i++){
            TestEntry entry = new TestEntry(mTestList.get(i));

            if(entry.testType == TestUtils.TEST_SERIAL){
                new TestSerialThread(mAppContext, this, entry).start();
            }
        }
    }

    private void DoTestUsb(){
        boolean bSucess=false;
        for (int i=0; i<mTestList.size();i++){
            TestEntry entry = mTestList.get(i);
            if(entry.testType == TestUtils.TEST_USB){
                boolean bRet = TestUsb(entry.ident);
                if(bRet==false){
                    bSucess = false;
                }
                entry.testState = bRet? TestUtils.TEST_STATE_SUC : TestUtils.TEST_STATE_FAIL;
                LogicParam Param = new LogicParam(LogicParam.ELogicType.ETest_USB);
                Param.mStrParam1 = entry.ident;
                Param.testState = LogicParam.EState.State_Tesing;
                Param.result = bRet? LogicParam.EResult.Result_Suc : LogicParam.EResult.Result_Fail;
                mLogicCallBack.OnLogicCallBack(Param);
            }
        }

        LogicParam.EResult result = bSucess? LogicParam.EResult.Result_Suc : LogicParam.EResult.Result_Fail;
        DoLogicCallBack(LogicParam.ELogicType.ETest_USB, LogicParam.EState.State_Over, result);

//        if(bSucess){
            DoLogicTestNext(TestUtils.TEST_USB);
//        }
    }

    private void DoTestCrash(){
        CashDrawerManager cashDrawerManager = new CashDrawerManager();
        cashDrawerManager.openCashDrawer();
    }

    private void DoTestTrumpet(){
        mediaPlayer = MediaPlayer.create(mAppContext, R.raw.aaa);
        mediaPlayer.setLooping(true);
        mediaPlayer.start();
    }

    private void DoTestHeadSet(){
    }

    private void DoLogicCallBack(LogicParam.ELogicType type, LogicParam.EState state, LogicParam.EResult result){
        LogicParam Param = new LogicParam(type,state, result);
        mLogicCallBack.OnLogicCallBack(Param);

//        if(result == LogicParam.EResult.Result_Fail){
//            DoLogicReset();
//            Param.logicType = LogicParam.ELogicType.ETest_AllResult;
//            mLogicCallBack.OnLogicCallBack(Param);
//        }
    }

    private boolean TestUsb(String path){
        boolean bRet = false;
        File file = new File(path+"/"+TestUtils.Usb_Test_file);
        if(!file.exists()){
            try {
                if(file.createNewFile()){
                    FileOutputStream outStream = new FileOutputStream(file);
                    outStream.write(TestUtils.Usb_Test_Str.getBytes());
                    outStream.flush();
                    outStream.close();

                    FileInputStream inStream = new FileInputStream(file);
                    byte buf[] = new byte[128];
                    int nLen = inStream.read(buf);
                    buf[nLen] = '\0';
                    String str = new String(buf);
                    if(TestUtils.Usb_Test_Str.equals(str)){
                        bRet = true;
                    }
                    inStream.close();

                    file.delete();

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return bRet;
    }


    @Override

    public synchronized void OnAsyncCallBack(TestEntry Param) {

        LogicParam Param1 = null;
        if(Param.testType == TestUtils.TEST_SERIAL){
            SetTestState(Param);
            Param1 = new LogicParam(LogicParam.ELogicType.ETest_Serial);
            Param1.mStrParam1 = Param.ident;
            Param1.result = Param.testState==TestUtils.TEST_STATE_SUC?
                    LogicParam.EResult.Result_Suc : LogicParam.EResult.Result_Fail;

            if(IsTested(TestUtils.TEST_SERIAL)){
                Param1.testState = LogicParam.EState.State_Tesing;
                mLogicCallBack.OnLogicCallBack(Param1);

                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                Param1.testState = LogicParam.EState.State_Over;
                if(!IsTestOk(TestUtils.TEST_SERIAL)){
                    Param1.result = LogicParam.EResult.Result_Fail;
                }
                mLogicCallBack.OnLogicCallBack(Param1);

//                if( Param1.result == LogicParam.EResult.Result_Suc){
                    DoLogicTestNext(TestUtils.TEST_SERIAL);
//                }
            }else{
                Param1.testState = LogicParam.EState.State_Tesing;
                mLogicCallBack.OnLogicCallBack(Param1);
            }

        }

    }

    private boolean IsTested(int testType){
        boolean bRet=true;
        for (int i = 0; i < mTestList.size(); i++) {
            TestEntry entry = mTestList.get(i);
            if(entry.testType == testType){
                if(entry.testState == TestUtils.TEST_STATE_NOT){
                    bRet = false;
                    break;
                }
            }
        }
        return bRet;
    }

    private boolean IsTestOk(int testType){
        boolean bRet=true;
        for (int i = 0; i < mTestList.size(); i++) {
            TestEntry entry = mTestList.get(i);
            if(entry.testType == testType){
                if(entry.testState != TestUtils.TEST_STATE_SUC){
                    bRet = false;
                    break;
                }
            }
        }
        return bRet;
    }

    private boolean IsAllTestedOk(){
        boolean bRet=true;
        for (int i = 0; i < mTestList.size(); i++) {
            TestEntry entry = mTestList.get(i);
            if(entry.testState != TestUtils.TEST_STATE_SUC){
                bRet = false;
                break;
            }
        }
        return bRet;
    }

    private void ResteTestOpts(){
        for (int i = 0; i < mTestList.size(); i++) {
             mTestList.get(i).testState = TestUtils.TEST_STATE_NOT;
        }
    }

    private void SetTestState(TestEntry param){
        for (int i = 0; i < mTestList.size(); i++) {
            TestEntry entry = mTestList.get(i);
            if(entry.testType == param.testType && entry.ident.equals(param.ident)){
                entry.testState = param.testState;
                break;
            }
        }
    }

    private void DoLogicReset(){
        ResteTestOpts();
        if(mediaPlayer!=null){
            mediaPlayer.stop();
            mediaPlayer.release();
            mediaPlayer = null;
        }
    }

    public void DoLogicDlgResponse(int type, int res){
        LogicParam.EResult result;
        result = res==AlertDlg.RET_YES ? LogicParam.EResult.Result_Suc : LogicParam.EResult.Result_Fail;
        DoLogicCallBack(TestUtils.GetLogicType(type), LogicParam.EState.State_Over, result);

        if(res == AlertDlg.RET_YES){
            DoLogicTestNext(type);
        }else{
            DoLogicReset();
//            DoLogicCallBack(LogicParam.ELogicType.ETest_AllResult, LogicParam.EState.State_Over,
//                    LogicParam.EResult.Result_Fail);
        }

    }
}
