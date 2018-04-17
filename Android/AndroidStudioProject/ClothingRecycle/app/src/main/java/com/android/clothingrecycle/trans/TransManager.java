package com.android.clothingrecycle.trans;

import android.content.Context;

import com.raimy.utils.AbstractSingleton;
import com.raimy.utils.CustMutex;
import com.raimy.utils.MyTimer;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by raimy on 2018-03-22.
 */

public class TransManager implements MyTimer.ITimerCallBack{
    private Context mContext;
    private ITrans mTrans;
    private ICallBack mCallBack;
    private List<TransParam> mListCmds;
    private CustMutex mMutexCmds;
    private AsyncCmdThread mAsyncCmdThread;
    private MyTimer mMyTimer;

    public static AbstractSingleton<TransManager> ObjCreater = new AbstractSingleton<TransManager>() {
        @Override
        protected TransManager NewObject() {
            return new TransManager();
        }
    };

    @Override
    public void OnTimerCallBack() {
        PushCmd(new TransParam(TransParam.eCmd.Cmd_Get_AllDoorsStates, 1, 0));
    }

    public interface ICallBack{
        void OnCallBack(TransParam param);
    }

    private TransManager(){
    }

    public void Init(Context context, ICallBack callBack){
        mContext = context;
        mCallBack = callBack;
        mMutexCmds = new CustMutex();
        mListCmds = new ArrayList<TransParam>();
        mTrans = new Trans485();
        mTrans.Init();

        mAsyncCmdThread = new AsyncCmdThread(mTrans, mCallBack);
        mAsyncCmdThread.start();

        mMyTimer = new MyTimer(this, 1000, 3000);
        mMyTimer.startTimer();

    }

    public void UnInit(){
        mTrans.UnInit();
        mAsyncCmdThread.stopRunning();
        mMyTimer.stopTimer();
    }

    public void PushCmd(TransParam param){
        mMutexCmds.lock();
        mListCmds.add(param);
        mMutexCmds.unlock();
    }

    public TransParam PullCmd(){
        TransParam param = null;
        mMutexCmds.lock();
        if(mListCmds.size()>0){
            param = new TransParam(mListCmds.get(0));
            mListCmds.remove(0);
        }
        mMutexCmds.unlock();

        return param;
    }

    public static void getDoorStatusFromArray(int[] array, boolean[] doorStatus) {
        for (int i = 0; i < 3; i++) {
            int state = (int)array[4 - i];
            int t = 1;
            for (int j = 0; j < 8; j++) {
                int doorIndex = i * 8 + j;
                if ( (t & state) >0 ) {
                    doorStatus[doorIndex] = true;
                } else {
                    doorStatus[doorIndex] = false;
                }
                t *= 2;
            }
        }
    }

}
