package com.android.recyclemng;

import android.content.Context;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.serializer.ContextValueFilter;
import com.android.recyclemng.Http.HttpManager;
import com.raimy.utils.AbstractSingleton;
import com.raimy.utils.MyTimer;
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.Response;

import java.io.IOException;
import java.util.List;

/**
 * Created by raimy on 2018-03-26.
 */

public class Logic implements  Callback, MyTimer.ITimerCallBack{
    private HttpManager mHttpManager;
    private final static String UUID= "OSU4FWmXO88AyFnKc3JlBw";
    private String mCabinnetNumber;
    private LogicParam.LogicCallBack mLogicCallBack;
    private Context mAppContext;
    private List<GridInfo> mGridsInfo;
    private MyTimer mGetGriTimer;

    public List<GridInfo> getmGridsInfo() {
        return mGridsInfo;
    }

    public static AbstractSingleton<Logic> ObjCreater = new AbstractSingleton<Logic>() {
        @Override
        protected Logic NewObject() {
            return new Logic();
        }
    };

    public void Init(Context appContext, LogicParam.LogicCallBack callBack){
        mAppContext = appContext;
        mLogicCallBack = callBack;
        mHttpManager = new HttpManager(this);
        mCabinnetNumber = "abc0001";

        mGetGriTimer = new MyTimer(this, 1000, 2000);
        mGetGriTimer.startTimer();

    }

    public void UnInit(){
        mGetGriTimer.stopTimer();
    }

    public void DoLogicGetCabinetsByUUid(){
        mHttpManager.HttpSyncGetCabinetsByUUid(UUID, mCabinnetNumber);
    }

    @Override
    public void onFailure(Request request, IOException e) {

    }

    @Override
    public void onResponse(Response response) throws IOException {
        boolean result = response.code()>=200 && response.code()<300;
        if(response.toString().contains(HttpManager.Url_cabinetsByUUid)
                && result ) {
            String strBody = response.body().string();
            JSONObject jobj =  JSONObject.parseObject(strBody);
            String strItems = jobj.getString("items");
            mGridsInfo = JSON.parseArray(strItems, GridInfo.class);
            mLogicCallBack.OnLogicCallBack(LogicParam.Update_GridInfo);
        }
    }

    public void DoLogicClean(){
        mHttpManager.HttpCleanGrid(mCabinnetNumber);
    }

    @Override
    public void OnTimerCallBack() {
        DoLogicGetCabinetsByUUid();
    }
}
