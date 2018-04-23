package com.android.clothingrecycle.trans;

/**
 * Created by raimy on 2018-03-22.
 */

public class TransParam {
    public enum eCmd{
        Cmd_None, Cmd_Open_Dor, Cmd_Open_All, Cmd_Get_DoorState, Cmd_Get_AllDoorsStates, Cmd_Get_Connected_Board_Addr
    }
    public enum eResult{
        Result_Suc, Result_Fail
        }

    public eCmd cmd;
    public eResult result;
    public int paramInt1;
    public int paramInt2;

    public int[] retInfo;

    public TransParam(){
        cmd = eCmd.Cmd_None;
        result = eResult.Result_Suc;
        retInfo = null;
    }

    public TransParam(eCmd cmd, int param1, int param2){
        this.cmd = cmd;
        paramInt1 = param1;
        paramInt2 = param2;
        result = eResult.Result_Suc;
        retInfo = null;
    }

    public TransParam(TransParam param){
        cmd = param.cmd;
        result = param.result;
        paramInt1 = param.paramInt1;
        paramInt2 = param.paramInt2;
        retInfo = param.retInfo;
    }
}
