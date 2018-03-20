/**
 * 
 */
package com.peripheral.printer.adapter;

import android.util.Log;

import com.peripheral.printer.IInnerOpCallBack;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterUtils;
import com.raimy.utils.LogHelper;

/**
 * @author raimy
 *
 */
public class ReadThread extends Thread{
	private PrinterAdapterBase mAdapter;
	private IInnerOpCallBack mCallBack;
	private boolean isInterrupted=false;
	
	public ReadThread(PrinterAdapterBase adapter,IInnerOpCallBack callBack){
		mAdapter = adapter;
		mCallBack = callBack;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
		LogHelper.logI(getClass().getSimpleName(), "readThread------Run");
		byte[] data = null;
		while (!isInterrupted) {
			data = mAdapter.Read();
			HandleData(data);
			try {
				Thread.sleep(200);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		LogHelper.logI(getClass().getSimpleName(), "readThread------exit");
	}

	@Override
	public void interrupt() {
		// TODO Auto-generated method stub
		isInterrupted = true;
		super.interrupt();
	}
	
	public void HandleData(byte[] data){
		if (data!=null) {
			String strData = new String(data);
			PrinterParam param = new PrinterParam();
			param.mCommuType = mAdapter.GetCommuType();
			param.mOpType = PrinterUtils.BackData_Data;
			param.mStrParam1 = strData;
			mCallBack.OnCallBackFunc(param);
		}
	}
	
}
