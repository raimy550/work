package com.android.raimy.utils.ui.framework;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import java.io.Serializable;

/**
 * Created by raimy on 2018-04-10.
 * 此对象在主线程中初始化
 */

public class UiHandler implements Handler.Callback{
    private Handler uiHandler;
    private HandleUiCallBack mUiCallBack;

    public UiHandler(HandleUiCallBack callBack){
        Init(callBack);
    }

    private void Init(HandleUiCallBack callBack){
        uiHandler = new Handler(this);
        mUiCallBack = callBack;
    }

    public interface HandleUiCallBack{
        void OnUiCallBack(Serializable logicParam);
    }

    @Override
    public boolean handleMessage(Message msg) {
        HandleLogic(msg);
        return false;
    }

    private void HandleLogic(Message msg){
        Serializable param = msg.getData().getSerializable("LogicParam");
        mUiCallBack.OnUiCallBack(param);
    }


    public void SendMessage(Serializable param){
        Message msg = new Message();
        Bundle bundle = new Bundle();
        bundle.putSerializable("LogicParam", param);
        msg.setData(bundle);
        uiHandler.sendMessage(msg);
    }
}
