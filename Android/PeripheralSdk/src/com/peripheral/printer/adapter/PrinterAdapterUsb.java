/**
 * 
 */
package com.peripheral.printer.adapter;

import java.util.List;

import android.content.Context;

import com.peripheral.printer.IInnerOpCallBack;
import com.peripheral.printer.UsbDeviceFinder;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.commu.CommuBase;
import com.peripheral.printer.commu.CommuUsb;

/**
 * @author raimy
 *
 */
public class PrinterAdapterUsb extends PrinterAdapterBase{
	UsbDeviceFinder mDeviceFinder;
	/**
	 * @param context
	 * @param callBack
	 */
	public PrinterAdapterUsb(Context context, int commuType, IInnerOpCallBack callBack) {
		super(context, commuType, callBack);
		// TODO Auto-generated constructor stub
		mDeviceFinder = new UsbDeviceFinder(context);
	}

	@Override
	public boolean ConnectImp(PrinterParam param) {
		// TODO Auto-generated method stub
		if (mCommu==null) {
			mCommu = new CommuUsb(mContext, param.mIntParam1, param.mIntParam2);
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
		return mDeviceFinder.GetDevices();
	}

	@Override
	public void WriteImp(String data) {
		// TODO Auto-generated method stub
		mCommu.Write(data);
	}

	@Override
	public byte[] ReadImp() {
		// TODO Auto-generated method stub
		return mCommu.Read();
	}

	@Override
	public void WriteImp(byte[] data) {
		// TODO Auto-generated method stub
		mCommu.Write(data);
	}

}
