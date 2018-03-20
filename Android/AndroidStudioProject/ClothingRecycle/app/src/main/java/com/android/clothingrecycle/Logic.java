package com.android.clothingrecycle;

import android.content.Context;

import com.android.clothingrecycle.trans.ITrans;
import com.android.clothingrecycle.trans.Trans485;
import com.raimy.utils.AbstractSingleton;

/**
 * Created by raimy on 2018-03-15.
 */

public class Logic{
    private Context mAppContext;
    private ITrans mTrans;
    private final static String TAG = "Logic";

    public static AbstractSingleton<Logic> ObjCreater = new AbstractSingleton<Logic>() {
        @Override
        protected Logic NewObject() {
            return new Logic();
        }
    };

    private Logic(){
        mTrans = new Trans485();
    }

    public void Init(Context appContext){
        mAppContext = appContext;
    }

    public void UnInit() {
        mAppContext = null;
    }



}
