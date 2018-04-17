package com.raimy.utils.ui.framework;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import com.android.autotest.utils.LogicParam;

/**
 * Created by raimy on 2018-04-10.
 * 此对象在主线程中创建
 */

public class UiHandler implements Handler.Callback{
    private Handler uiHandler;
    private HandleUiCallBack mUiCallBack;
    public UiHandler(){
    }

    public void Init(HandleUiCallBack callBack){
        uiHandler = new Handler(this);
        mUiCallBack = callBack;
    }

    public interface HandleUiCallBack{
        void OnUiCallBack(LogicParam param);
    }

    @Override
    public boolean handleMessage(Message msg) {
        HandleLogic(msg);
        return false;
    }

    private void HandleLogic(Message msg){
        LogicParam param = (LogicParam)msg.getData().getSerializable("LogicParam");
        mUiCallBack.OnUiCallBack(param);
    }


    public void SendMessage(LogicParam param){
        Message msg = new Message();
        Bundle bundle = new Bundle();
        bundle.putSerializable("LogicParam", param);
        msg.setData(bundle);
        uiHandler.sendMessage(msg);
    }
}
