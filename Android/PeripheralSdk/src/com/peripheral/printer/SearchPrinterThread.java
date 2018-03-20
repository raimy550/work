/**
 * 
 */
package com.peripheral.printer;
import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;
import android.util.Log;

import com.peripheral.printer.adapter.PrinterAdapterBase;
import com.peripheral.printer.adapter.ReadThread;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.api.PrinterUtils;
import com.raimy.utils.LogHelper;
import com.raimy.utils.StringHelper;

/**
 * @author raimy
 *
 */
public class SearchPrinterThread extends Thread implements IInnerOpCallBack{
	private PrinterParam mParam;
	private Context mContext;
	private IInnerOpCallBack mCallBack;//PrinterManager回调
	private PrinterAdapterBase mAdapter;
	
	private Timer mTimer=null;
	private TimerTask mTimerTask=null;
	private Boolean mReaded;
	
	public SearchPrinterThread(Context context, IInnerOpCallBack callBack, PrinterAdapterBase adapter, 
			PrinterParam param){
		mParam = param;
		mContext = context;
		mCallBack = callBack;
		mAdapter = adapter;
		mReaded = false;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
		Log.i(getClass().getSimpleName(), "SearchPrinterThread----run");
		mAdapter.SetCallBack(this);// 转换adapter的回调
		PrinterParam param = new PrinterParam(mParam);
		param.mOpType = PrinterUtils.OpType_Connect;
		if(mAdapter.Connect(param)){
			mAdapter.Write(PrinterCmd.CMD_GetPrinterState());
			startTimer();
		}else{
			mAdapter.DisConnect(param);
			PrinterParam param1 = new PrinterParam(mParam);
			param.mOutResult = PrinterUtils.Result_Fail;
			mCallBack.OnCallBackFunc(param1);
		}
		
		Log.i(getClass().getSimpleName(), "SearchPrinterThread----Exit");
	}

	@Override
	public synchronized void start() {
		// TODO Auto-generated method stub
		super.start();
	}
	
	private void startTimer(){
		mTimer = new Timer();
		mTimerTask = new TimerTask() {
			
			@Override
			public void run() {
				if (!mReaded) {
					
					PrinterParam param = new PrinterParam();
					param.mOpType = PrinterUtils.OpType_Search;
					param.mCommuType = mParam.mCommuType;
					param.mIdent = mParam.mIdent;
					param.mOutResult = PrinterUtils.Result_Fail;
					
					mCallBack.OnCallBackFunc(param);
					mAdapter.DisConnect(mParam);
					stopTimer();
				}
			}
		};
		
		mTimer.schedule(mTimerTask, 3000, 3000);
	}
	
	private void stopTimer(){
		 if (mTimer != null) {  
	            mTimer.cancel();  
	            mTimer = null;  
	        }  
	  
	        if (mTimerTask != null) {  
	            mTimerTask.cancel();  
	            mTimerTask = null;  
	        }   
	}

	@Override
	public void OnCallBackFunc(PrinterParam Param) {
		// TODO Auto-generated method stub
		if (Param.mOpType == PrinterUtils.BackData_Data) {
			mReaded = true;
			stopTimer();
			PrinterParam param1 = new PrinterParam(mParam);
			param1.mOpType = PrinterUtils.OpType_DisConnect;
			mAdapter.DisConnect(param1);
			
			PrinterParam param = new PrinterParam();
			param.mOpType = PrinterUtils.OpType_Search;
			param.mCommuType = mParam.mCommuType;
			param.mIdent = mParam.mIdent;
			mCallBack.OnCallBackFunc(param);
		}
	}
	
	public void StopSearch(){
		stopTimer();
	}
	
}
