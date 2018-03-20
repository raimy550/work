package com.anroid.peripheraltest;

import android.content.Context;

/**
 * Created by raimy on 2018-01-04.
 */

public class Logic {
    private Context mContext;
    private static Logic sTheMe;

    public static Logic GetInstance(){
        if(sTheMe==null){
            synchronized (Logic.class){
                sTheMe = new Logic();
            }
        }
        return sTheMe;
    }

    private Logic(){
    }


    public void Init(Context context){
        mContext = context;
    }

    public void DoPrintTestNet(){

    }

    public void DoPrintTestSerial(){

    }

    public void DoPrintTestUsb(){

    }
}
