package com.android.clothingrecycle;

import java.io.Serializable;
import java.util.Map;

/**业务参数，供界面与logic使用
 * Created by raimy on 2018-03-22.
 */

public class LogicParam implements Serializable{
    public enum ELogicType{
        RegisterCabinet,//注册服务器
        GetCabinetQRCodes,//获取二维码
        DownloadQRCodes,//下载二维码
        DoorStateChange,//门状态改变
        GridStateFull,//箱子已满
        GetEmptyGridFail,//获取空箱失败
        GetNextEmptyGridQr,//获取下一个空箱二维码
        GridCleaning,//柜子清理当中
        GridCleanOver//柜子清理完成
    }

    public enum EResult{
        Result_Suc, Result_Fail
    }

    /**
     * 界面回调接口
     */
    interface LogicCallBack{
        void OnLogicCallBack(LogicParam param);
    }

    ELogicType logicType;
    EResult result;

    public Map<Integer, Integer> retMap;

    public LogicParam(){

    }

    public LogicParam(ELogicType logicType, EResult result){
        this.logicType = logicType;
        this.result = result;
    }

    public LogicParam(ELogicType logicType){
        this.logicType = logicType;
    }
}
