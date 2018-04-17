package com.android.autotest.threads;

import android.content.Context;

import com.android.autotest.IAsyncCallBack;
import com.android.autotest.utils.TestEntry;
import com.raimy.utils.MyTimer;
import com.raimy.utils.comm.CommuSerial;

/**
 * Created by raimy on 2018-04-11.
 */

public class TestUsbThread extends Thread implements MyTimer.ITimerCallBack{
    private Context mContext;
    private MyTimer mTimer;
    private IAsyncCallBack mAsyncCallBack;

    @Override
    public void OnTimerCallBack() {

    }

    public TestUsbThread(Context context, IAsyncCallBack iAsyncCallBack, TestEntry entry){
        mContext = context;
        mAsyncCallBack = iAsyncCallBack;
        mTimer = new MyTimer(this, 2000, 2000);
    }

    @Override
    public void run() {
        super.run();
    }

    @Override
    public synchronized void start() {
        super.start();
    }
}
