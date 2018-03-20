/**
 * 
 */
package com.peripheral.printer.adapter;

import java.util.List;

import android.content.Context;
import android.content.IntentSender.SendIntentException;
import android.graphics.PorterDuff;

import com.peripheral.printer.BitMapHandler;
import com.peripheral.printer.IInnerOpCallBack;
import com.peripheral.printer.PrinterManager;
import com.peripheral.printer.PrinterManager.PrinterEntry;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.api.PrinterUtils;
import com.peripheral.printer.commu.CommuBase;
import com.raimy.utils.LogHelper;
import com.raimy.utils.StringHelper;

/**
 * @author raimy
 *
 */
public abstract class PrinterAdapterBase implements IInnerOpCallBack {
	protected int mCommuType;
	protected CommuBase mCommu;
	protected Context  mContext;
	protected IInnerOpCallBack mCallBack;
	protected ReadThread mReadThread;
	protected boolean mIsConnected;
	/**
	 * 
	 */
	public PrinterAdapterBase(Context context, int commuType, IInnerOpCallBack callBack) {
		// TODO Auto-generated constructor stub
		mContext = context;
		mCallBack = callBack;
		mCommuType = commuType;
		mIsConnected = false;
	}

	//public abstract void Search(PrinterParam param);
	//public abstract List<PrinterSearchEntry> GetSearchData();
	protected abstract void WriteImp(String data);
	protected abstract void WriteImp(byte[] data);
	protected abstract byte[] ReadImp();
	protected abstract boolean ConnectImp(PrinterParam param);
	protected abstract void DisConnectImp(PrinterParam param);
	
	public abstract List<PrinterSearchEntry> GetDeviceList();
	
	/*
	 * 修改回调函数
	 */
	public final void SetCallBack(IInnerOpCallBack callBack){
		mCallBack = callBack;
	}
	
	public final void SetReadThread(ReadThread readThread){
		mReadThread = readThread;
	}
	
	public final void Write(String data){
		if (!IsConnected()) {
			return;
		}
		WriteImp(data);
	}
	public final void Write(byte[] data){
		if (!IsConnected()) {
			return;
		}
		WriteImp(data);
	}
	public final byte[] Read(){
		if (!IsConnected()) {
			return null;
		}
		
		byte[] rec = ReadImp();	
		return rec;
	}
	
	public boolean IsConnected(){
		return mIsConnected;
	}
	
	public final boolean Connect(PrinterParam param){
		if (IsConnected()) {
			LogHelper.logI(getClass().getSimpleName(), "already connected");
			return false;
		}
		boolean bRet = ConnectImp(param);
		if (bRet) {			
			mReadThread = new ReadThread(this, this);
			mReadThread.start();
			LogHelper.logI(getClass().getSimpleName(), "ReadThread ID = "+mReadThread.getId());
		}		
		
		mIsConnected = bRet;
		return bRet;
	}
	
	public final void DisConnect(PrinterParam param){
		if (!IsConnected()) {
			LogHelper.logI(getClass().getSimpleName(), "already Disconnected");
			return;
		}
		DisConnectImp(param);
		if (mReadThread!=null) {
			mReadThread.interrupt();
			mReadThread=null;
		}
		
		mIsConnected = false;
	}
	
	/**
	 *内部回调，传入OperatorThread，ReadThread， 比如连接，读取数据 需要线程操作
	 */
	@Override
	public void OnCallBackFunc(PrinterParam Param) {
		// TODO Auto-generated method stub
		mCallBack.OnCallBackFunc(Param);
	}
	
	public final int GetCommuType(){
		return mCommuType;
	}
	
	protected void SendCmdPrintBmp(int cols){
		byte[] cmd = new byte[5];
		cmd[0]=0x1b;
		cmd[1]=0x2a;
		cmd[2]=33;
		cmd[3]=(byte)(cols%256);
		cmd[4]=(byte)(cols/256);
		mCommu.Write(cmd);
		
	}
	
	protected void SendCmdPageGoBmp(int line){
		byte[] cmd = new byte[3];
		cmd[0]=0x1B;
		cmd[1]=0x4A;
		cmd[2]=(byte)line; 
		mCommu.Write(cmd);
		
	}
	
	protected void SendCmdPageCut(){
		byte[] cmd = new byte[4];
		cmd[0]=0x1d;
		cmd[1]=0x56;
		cmd[2]=0x42;//m
		cmd[3]=0x00;
		mCommu.Write(cmd);
		
	}
	
	public boolean PrintBmp(PrinterParam param){
		
		boolean bRet = false;
		
		if (!IsConnected()) {
			return bRet;
		}
		
		BitMapHandler bmpHandler = new BitMapHandler(param.mStrParam1);
		bmpHandler.Change2PrinterBmp();
		
		int rows = bmpHandler.GetRows();
		int cols = bmpHandler.GetCols();
		byte[] rowData=null;
		
		for (int i = 0; i < rows; i++) {
			rowData = bmpHandler.GetPrinterBmpData(i);
			
			//发送打印位图指令
			SendCmdPrintBmp(cols);
			//发送位图数据
			bRet = mCommu.Write(rowData);
			//走纸24点行
			SendCmdPageGoBmp(24);	
		}
		//切纸
		//SendCmdPageCut();
		
		return bRet;
		
	}
	
}
