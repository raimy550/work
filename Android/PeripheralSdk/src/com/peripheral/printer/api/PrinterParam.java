/**
 * 
 */
package com.peripheral.printer.api;

import com.peripheral.printer.PrinterManager;

/**
 * @author raimy
 * 打印机回调参数，打印机传入参数
 */
public class PrinterParam{	
//公共
	public int mOpType; //操作类型
	
	public int mCommuType;//通信类型
	public String mName;//名称
	public String mIdent;//唯一标识
	//字符串参数
	public String mStrParam1;//连接操作：设备标识
	public String mStrParam2;
	public String mStrParam3;
	//整形参数	
	public int    mIntParam1;//连接操作：串口波特率，网口端口
	public int    mIntParam2;
	public int    mIntParam3;
	
//出参
	public int mOutResult;
	public int mOutErrCode;
	
	public PrinterParam(){
		mName = "";
		mIdent = "";
		
		mOutResult=PrinterUtils.Result_Suc;
	}
	
	public PrinterParam(int commuType){
		mCommuType = commuType;
		mName = "";
		mIdent = "";
		mOutResult=PrinterUtils.Result_Suc;
	}
	
	public PrinterParam(int commuType, String ident, int opType, int result, int errCode){
		mCommuType = commuType;
		mIdent = ident;
		mOpType = opType;
		mOutResult=result;
		mOutErrCode = errCode;
	}
	
	public PrinterParam(PrinterParam param){
		mCommuType = param.mCommuType;
		mName = param.mName;
		mIdent = param.mIdent;
		mOpType = param.mOpType;

		mStrParam1 = param.mStrParam1;
		mStrParam2 = param.mStrParam2;
		mStrParam3 = param.mStrParam3;

		mIntParam1 = param.mIntParam1;
		mIntParam2 = param.mIntParam2;
		mIntParam3 = param.mIntParam3;
	}
}
