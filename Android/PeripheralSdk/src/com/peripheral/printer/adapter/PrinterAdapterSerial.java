/**
 * 
 */
package com.peripheral.printer.adapter;

import java.util.ArrayList;
import java.util.List;

import android.R.string;
import android.content.Context;
import android_serialport_api.SerialPortFinder;

import com.peripheral.printer.IInnerOpCallBack;
import com.peripheral.printer.PrinterManager.PrinterEntry;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.api.PrinterUtils;
import com.peripheral.printer.commu.CommuBase;
import com.peripheral.printer.commu.CommuSerial;
import com.raimy.utils.CustMutex;
import com.raimy.utils.LogHelper;
import com.raimy.utils.StringHelper;

/**
 * @author raimy
 *
 */
public class PrinterAdapterSerial extends PrinterAdapterBase{
	private SerialPortFinder mSerialPortFinder;
	private String mIdent;
	private int mBaudrate;


	public PrinterAdapterSerial(Context context, int commuType, IInnerOpCallBack callBack) {
		// TODO Auto-generated constructor stub
		super(context,commuType,  callBack);
		mSerialPortFinder = new SerialPortFinder();
	}

	@Override
	public boolean ConnectImp(PrinterParam param) {
		// TODO Auto-generated method stub
		if (mCommu==null) {
			mCommu = new CommuSerial(mContext, param.mStrParam1, param.mIntParam1);
		}
		mIdent = new String(param.mIdent);
		mBaudrate = param.mIntParam1;
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
		List<PrinterSearchEntry> list = new ArrayList<PrinterSearchEntry>();
		
		String[] paths = mSerialPortFinder.getAllDevicesPath();
		for (int i = 0; i < paths.length; i++) {
			PrinterSearchEntry entry = new PrinterSearchEntry(PrinterUtils.COMMU_SERIAL);
			entry.mIdent = paths[i];
			entry.Baudrate = PrinterUtils.SERIAL_BAUDRAT;
			list.add(entry);
		}
		return list;
	}

	@Override
	public void WriteImp(String data) {
		// TODO Auto-generated method stub
		mCommu.Write(data);
		
	}

	@Override
	public byte[] ReadImp() {
		// TODO Auto-generated method stub
		byte[] data = mCommu.Read();
		if (data!=null) {
			LogHelper.logI(getClass().getSimpleName(), mIdent+":"+mBaudrate+"-----read data: "+StringHelper.bytesToHexString(data));
		}
		return data;
	}

	@Override
	public void WriteImp(byte[] data) {
		// TODO Auto-generated method stub
		mCommu.Write(data);
	}

}
