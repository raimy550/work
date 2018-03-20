/**
 * 
 */
package com.peripheral.printer.api;

import com.peripheral.printer.SearchPrinterThread;

/**
 * @author raimy
 *
 */
public class PrinterSearchEntry {
	public int mCommuType;//通信类型
	public String mName;//名称
	public String mIdent;//唯一标识
	public int Baudrate;//串口波特率
	public int VendorID;//供应商ID
	public int ProductID;//产品ID
	public byte mHasDev;//是否有设备 0：无，1有，2未搜索
	public Boolean mIsConnected;//是否连接
	
	public SearchPrinterThread mSearchThread;
	
	public PrinterSearchEntry(int commType){
		mCommuType = commType;
		mHasDev = 2;
		mIdent ="";
		mName = "";
	}
	
	public PrinterSearchEntry(PrinterSearchEntry entry){
		mCommuType = entry.mCommuType;
		Baudrate = entry.Baudrate;
		mHasDev = entry.mHasDev;;
		mIdent = entry.mIdent;
		mName = entry.mName;
		VendorID = entry.VendorID;
		ProductID = entry.ProductID;
		mIsConnected = entry.mIsConnected;
		mSearchThread = entry.mSearchThread;
	}
}
