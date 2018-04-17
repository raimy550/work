package com.android.autotest.utils;

import java.io.Serializable;

/**业务参数，供界面与logic使用
 * Created by raimy on 2018-03-22.
 */

public class LogicParam implements Serializable {

    public enum ELogicType{
        ETest_Serial,//串口测试
        ETest_USB,//串口测试
        ETest_Crash,//钱箱测试开始
        ETest_Trumpet,//喇叭测试开始
        ETest_Headset,//耳机测试开始
        ETest_AllResult//所有测试结束
    }

    public enum EResult{
        Result_Suc, Result_Fail
    }

    public enum EState{
        State_None, State_Start, State_Tesing, State_Over
    }

    /**
     * 界面回调接口
     */
    public interface LogicCallBack{
        void OnLogicCallBack(LogicParam param);
    }

    public ELogicType logicType;
    public EResult result;
    public String mStrParam1;
    public EState testState;

    public LogicParam(){

    }

    public LogicParam(ELogicType logicType, EResult result){
        this.logicType = logicType;
        this.result = result;
        mStrParam1 = "";
        testState = EState.State_None;
    }
    public LogicParam(ELogicType logicType, EState state, EResult result){
        this.logicType = logicType;
        this.result = result;
        mStrParam1 = "";
        testState = state;
    }

    public LogicParam(ELogicType logicType){
        this.logicType = logicType;
        mStrParam1 = "";
        result = EResult.Result_Suc;
        testState = EState.State_None;
    }

    public LogicParam(LogicParam param){
        logicType = param.logicType;
        result = param.result;
        mStrParam1 = param.mStrParam1;
        testState = param.testState;
    }
}
