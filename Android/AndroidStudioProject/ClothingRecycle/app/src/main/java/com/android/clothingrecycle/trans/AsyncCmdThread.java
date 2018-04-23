package com.android.clothingrecycle.trans;

/**
 * Created by raimy on 2018-03-22.
 */

public class AsyncCmdThread extends  Thread{
    private ITrans mTrans;
    private TransManager.ICallBack mCallBack;
    private boolean mbRunning;
    public AsyncCmdThread(ITrans trans, TransManager.ICallBack callBack){
        mTrans = trans;
        mCallBack = callBack;
        mbRunning = true;
    }

    public void stopRunning(){
        mbRunning = false;
    }

    @Override
    public void run() {
        super.run();
        TransParam param = null;

        while (mbRunning){
            param = TransManager.ObjCreater.GetInstance().PullCmd();
            int[] retInfo = null;
            boolean bCallBack = true;
            if(param!=null){
                switch (param.cmd){
                    case Cmd_Open_Dor:
                        retInfo = new int[5];
                        mTrans.OpenDoor(param.paramInt1, param.paramInt2, retInfo);
                        break;
                    case Cmd_Get_AllDoorsStates:
                        retInfo = new int[7];
                        mTrans.GetDoorsStates(param.paramInt1, retInfo);
                        break;
                    default:
                        bCallBack=false;
                        break;
                }
            }else{
                bCallBack = false;
            }

            if(bCallBack){
                TransParam tParam = new TransParam(param);
                tParam.result = TransParam.eResult.Result_Suc;
                tParam.retInfo = retInfo;
                mCallBack.OnTransCallBack(tParam);
            }

            try {
                Thread.sleep(300);
            }catch (InterruptedException e){
            }

        }
    }
}
