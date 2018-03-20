/**
 * 
 */
package com.peripheral.printer.adapter;

import java.util.List;

import android.content.Context;
import com.peripheral.printer.IInnerOpCallBack;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.commu.CommuBase;
import com.peripheral.printer.commu.CommuNet;
import com.raimy.utils.StringHelper;

/**
 * @author raimy
 *
 */
public class PrinterAdapterNet extends PrinterAdapterBase{

	
	/**
	 * @param context
	 * @param callBack
	 */
	public PrinterAdapterNet(Context context, int commuType, IInnerOpCallBack callBack) {
		super(context,commuType, callBack);
		// TODO Auto-generated constructor stub
	}

	@Override
	public boolean ConnectImp(PrinterParam param) {
		// TODO Auto-generated method stub
		if (mCommu==null) {
			mCommu = new CommuNet(param.mStrParam1, param.mIntParam1);
		}
		return mCommu.Connect();
	}

	@Override
	public void DisConnectImp(PrinterParam param) {
		// TODO Auto-generated method stub
		if (mCommu!=null) {
			mCommu.DisConnect();
		}
	}

	@Override
	public List<PrinterSearchEntry> GetDeviceList() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void WriteImp(String data) {
		// TODO Auto-generated method stub
		mCommu.Write(data);
	}

	@Override
	public byte[] ReadImp() {
		// TODO Auto-generated method stub		
		byte[] rec=null;
		rec = mCommu.Read();
		return rec;
	}

	@Override
	public void WriteImp(byte[] data) {
		// TODO Auto-generated method stub
		mCommu.Write(data);
	}

}
