package com.android.autotest.threads;


import android.content.Context;

import com.android.autotest.IAsyncCallBack;
import com.android.autotest.utils.TestEntry;
import com.android.autotest.utils.TestUtils;
import com.raimy.utils.MyTimer;
import com.android.autotest.comm.CommuSerial;

/**
 * Created by raimy on 2018-04-10.
 */

public class TestSerialThread extends  Thread implements MyTimer.ITimerCallBack{
    private IAsyncCallBack mAsyncCallBack;
    private TestEntry mEntry;
    private CommuSerial mSerial;
    private Context mContext;
    private MyTimer mTimer;

    @Override
    public void run() {
        super.run();
        if(mSerial.Connect()){
           mSerial.Write(TestUtils.STR_TEST);
           byte[] buf =  mSerial.Read();
            if(buf!=null){
                String str = new String(buf);
                if(TestUtils.STR_TEST.equals(str)){
                    mEntry.testState = TestUtils.TEST_STATE_SUC;
                    mAsyncCallBack.OnAsyncCallBack(mEntry);
                }
            }

        }
    }

    @Override
    public synchronized void start() {
        mTimer.startTimer();
        super.start();
    }

    public TestSerialThread(Context context, IAsyncCallBack iAsyncCallBack, TestEntry entry){
        mContext = context;
        mAsyncCallBack = iAsyncCallBack;
        mEntry = entry;
        mSerial = new CommuSerial(context, entry.ident, entry.baudrate);
        mTimer = new MyTimer(this, 2000, 2000);
    }

    @Override
    public void OnTimerCallBack() {
        mTimer.stopTimer();
        mSerial.DisConnect();
        mEntry.testState = TestUtils.TEST_STATE_FAIL;
        mAsyncCallBack.OnAsyncCallBack(mEntry);
    }
}
