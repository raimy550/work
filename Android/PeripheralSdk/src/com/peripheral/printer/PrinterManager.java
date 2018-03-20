/**
 * 
 */
package com.peripheral.printer;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import android.content.Context;
import android.util.Log;

import com.peripheral.printer.adapter.PrinterAdapterBase;
import com.peripheral.printer.adapter.PrinterAdapterNet;
import com.peripheral.printer.adapter.PrinterAdapterSerial;
import com.peripheral.printer.adapter.PrinterAdapterUsb;
import com.peripheral.printer.api.IPrinterCallBack;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.api.PrinterUtils;
import com.raimy.utils.CustMutex;
import com.raimy.utils.LogHelper;

/**
 * @author raimy
 *
 */
public class PrinterManager implements IInnerOpCallBack{
	private static PrinterManager sTheMe;
	private List<IPrinterCallBack> mCallBacks;
	private List<PrinterEntry> mPrinters;
	private List<PrinterSearchEntry> mSearchEntries;
	private List<PrinterParam> mHandleOps;
	private Thread mHandlerThread;
	private Context mContext;
	private CustMutex mMutex;
	private CustMutex mPrintersMutex;
	private CustMutex mSearchMutex;
	private CustMutex mHandleMutex;
	
	/**当前正在使用的打印机
	 * @author raimy
	 *
	 */
	public class PrinterEntry{
		public int nCommuType;//通信类型
		public String strName;//名称
		public String strIdent;//唯一标识
		public Boolean bConnected;//是否已连接
		//public CommuBase commu;
		public PrinterAdapterBase adapter;
		
		public PrinterEntry(PrinterParam param, PrinterAdapterBase adapter){
			nCommuType = param.mCommuType;
			strName = param.mName;
			strIdent = param.mIdent;
			bConnected=false;
			this.adapter = adapter;
		}
	}
	
	
	
	private PrinterManager(){
	}
	
	public static PrinterManager GetInstance(){
		if (null==sTheMe){
			synchronized (PrinterManager.class) {
				sTheMe= new PrinterManager();
			}
		}
		return sTheMe;
	}
	
	
	
	public void Init(Context context){
		mContext = context;
		mCallBacks = new ArrayList<IPrinterCallBack>();
		mPrinters = new ArrayList<PrinterEntry>();
		mSearchEntries = new ArrayList<PrinterSearchEntry>();
		mHandleOps = new ArrayList<PrinterParam>();
		mMutex = new CustMutex();
		mPrintersMutex = new CustMutex();
		mSearchMutex = new CustMutex();
		mHandleMutex = new CustMutex();
		
		mHandlerThread = new HandleThread();
		LogHelper.logI(getClass().getSimpleName(), "HandlerThread ID = "+mHandlerThread.getId());
		mHandlerThread.start();
	}
	
	public void UnInit(){
		
	}
	
	private void RegistCallBackLock(IPrinterCallBack callBack){
		mMutex.lock();
		mCallBacks.add(callBack);
		mMutex.unlock();
	}
	
	public void RegistCallBack(IPrinterCallBack callBack){
		RegistCallBackLock(callBack);
	}
	
	private void UnRegistCallBackLock(IPrinterCallBack callBack){
		mMutex.lock();
		Iterator<IPrinterCallBack> it = mCallBacks.iterator();
		IPrinterCallBack tmpCallBack;
		while(it.hasNext()){
			tmpCallBack = it.next();
		    if(tmpCallBack == callBack){
		        it.remove();
		        break;
		    }
		}
		mMutex.unlock();
	}
	
	public void UnRegistCallBack(IPrinterCallBack callBack){
		UnRegistCallBackLock(callBack);
	}
	
	
	private PrinterParam GetOp(){
		PrinterParam param = null;
		mHandleMutex.lock();
		if(mHandleOps.size()>0){
			param = new PrinterParam(mHandleOps.get(0));
			mHandleOps.remove(0);	
		}
		mHandleMutex.unlock();
		return param;
	}
	
	private void AddOpLock(PrinterParam param){
		mHandleMutex.lock();
		mHandleOps.add(param);
		mHandleMutex.unlock();
	}
	
	class HandleThread extends Thread{
		private Boolean isInterrupted = false;
		@Override
		public void run() {
			// TODO Auto-generated method stub
			super.run();
			Log.i(getClass().getSimpleName(), "HandleThread------Run");
			PrinterParam param=null;
			while (!isInterrupted) {
				
				param = GetOp();
				if (param!=null) {
					HandleOp(param);
				}
				try {
					Thread.sleep(500);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			Log.i(getClass().getSimpleName(), "HandleThread------exit");
			
		}
		
		@Override
		public void interrupt() {
			// TODO Auto-generated method stub
			isInterrupted = true;
			super.interrupt();
		}
		
	}
	
	private void HandleOp(PrinterParam param){
		switch (param.mOpType) {
		case PrinterUtils.OpType_Connect:
			DoOpConnect(param); 
			break;
		case PrinterUtils.OpType_PrintBmp:
			DoOpPrintBmp(param);
			break;			
		case PrinterUtils.OpType_Search:
			DoOpSearch(param);
			break;	
		case PrinterUtils.OpType_StopSearch:
			DoOpStopSearch(param);
			break;
		case PrinterUtils.OpType_DisConnect:
			DoOpDisConnect(param); 
			break;
		case PrinterUtils.OpType_GetInfo:
			DoOpGetInfo(param);
			break;	
		default:
			break;
		}
	}
	
	public void Operate(PrinterParam param){
		AddOpLock(param);
	}
	
	private void DoOpConnect(PrinterParam param){
		PrinterEntry entry = AddPrinterLock(param);
		Boolean bRet = entry.adapter.Connect(param);
		
		if (bRet && param.mOpType == PrinterUtils.OpType_Connect ) {//连接成功，更新打印机列表对应的打印机状态
			Boolean bConnected = param.mOutResult==PrinterUtils.Result_Suc? true : false;
			SetPrinterConnectedLock(param, bConnected);
		}
		
		PrinterParam param1 = new PrinterParam(param);
		if (!bRet && entry.adapter.IsConnected()) {
			param1.mOutErrCode = PrinterUtils.Err_Already_Connected;
		}
		param1.mOutResult = bRet? PrinterUtils.Result_Suc:PrinterUtils.Result_Fail;
		DoCallBacks(param1);
	}
	
	private void DoOpDisConnect(PrinterParam param){
		RemovePrinterLock(param);
	}
	
	private void DoOpPrintBmp(PrinterParam param){
		PrinterEntry entry = AddPrinterLock(param);
		Boolean bRet = entry.adapter.PrintBmp(param);
		
		PrinterParam param1 = new PrinterParam(param);
		param1.mOutResult = bRet? PrinterUtils.Result_Suc : PrinterUtils.Result_Fail;
		DoCallBacks(param1);
	}
	
	
	private PrinterAdapterBase GetPrinterAdapter(int commType){
		PrinterAdapterBase adapter=null;
		if (commType == PrinterUtils.COMMU_SERIAL) {
			adapter = new PrinterAdapterSerial(mContext,commType, this);
		}else if (commType == PrinterUtils.COMMU_USB) {
			adapter = new PrinterAdapterUsb(mContext, commType,this);
		}else if (commType == PrinterUtils.COMMU_NET) {
			adapter = new PrinterAdapterNet(mContext,commType, this);
		}
		return adapter;
	}
	
	private void DoOpStopSearchLock(PrinterParam param){		
		if (!IsAllSearchedLock()) {
			mSearchMutex.lock();
			for (int i = 0; i < mSearchEntries.size(); i++) {
				mSearchEntries.get(i).mSearchThread.StopSearch();
			}
			mSearchEntries.clear();
			mSearchMutex.unlock();
		}
		
		PrinterParam param2 = new PrinterParam(param);
		param.mCommuType = GetSearchingTypeLock();
		param2.mOutResult = PrinterUtils.Result_Suc;
		DoCallBacks(param2);
	}
	
	private void DoOpStopSearch(PrinterParam param){
		DoOpStopSearchLock(param);
	}	
	
	
	
	private void DoOpSearch(PrinterParam param){
			// TODO Auto-generated method stub
			
			if (!IsAllSearchedLock()) {
				int nCommuType = GetSearchingTypeLock();
				PrinterParam param2 = new PrinterParam(nCommuType, "", 
						PrinterUtils.OpType_Search, PrinterUtils.Result_Fail, PrinterUtils.Err_Searching);
				DoCallBacks(param2);
				return;
			}
		
		    PrinterAdapterBase adapterBase = null;
		    PrinterEntry entry = AddPrinterLock(param);
		    adapterBase = entry.adapter;
		    
		    List<PrinterSearchEntry> strDevices = adapterBase.GetDeviceList();
			if (strDevices==null) {
				return;
			}
		    
		    mSearchMutex.lock();
		    mSearchEntries.clear();
			
			for (int i = 0; i < strDevices.size(); i++) {
				PrinterSearchEntry searchEntry = new PrinterSearchEntry(strDevices.get(i));
				mSearchEntries.add(searchEntry);
				//break;//test
			}
			
			SearchPrinterThread searchPrinterThread=null;
			PrinterParam param1=null;
			
			for (int i = 0; i < mSearchEntries.size(); i++) {
				param1 = new PrinterParam();
				param1.mCommuType = param.mCommuType;
				param1.mIdent = mSearchEntries.get(i).mIdent;
				param1.mStrParam1 = mSearchEntries.get(i).mIdent;
				
				if (param.mCommuType == PrinterUtils.COMMU_SERIAL) {
					param1.mIntParam1 = mSearchEntries.get(i).Baudrate;
				}else if (param.mCommuType == PrinterUtils.COMMU_USB) {
					param1.mIntParam1 = mSearchEntries.get(i).VendorID;
					param1.mIntParam2 = mSearchEntries.get(i).ProductID;
				}
				
				
				adapterBase = GetPrinterAdapter(param1.mCommuType);
				searchPrinterThread = new SearchPrinterThread(mContext, this, adapterBase, param1);
				mSearchEntries.get(i).mSearchThread = searchPrinterThread; 
				searchPrinterThread.start();
				LogHelper.logI(getClass().getSimpleName(), "searchPrinterThread ID = "+searchPrinterThread.getId());
			}
			mSearchMutex.unlock();
			
			if (searchPrinterThread == null) {
				PrinterParam pra = new PrinterParam(param);
				pra.mOutResult = PrinterUtils.Result_Fail;
				pra.mOutErrCode = PrinterUtils.Err_No_Device;
				DoCallBacks(pra);
			}
	}
	
	private void DoOpGetInfo(PrinterParam param){
		PrinterAdapterBase adapterBase = null;
	    PrinterEntry entry = AddPrinterLock(param);
	    adapterBase = entry.adapter;
		    
	    String strDataString = "123456789\n";
	    adapterBase.Write(strDataString);
	    
//	    adapterBase.Write(PrinterCmd.CMD_GetPrinterState());
//	    byte[] data = new byte[3];
//	    data[0] = (byte)10;
//	    data[1] = (byte)4;
//	    data[2] = (byte)1;
//	    
//	    adapterBase.Write(data);
//	    try {
//			Thread.sleep(500);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//	    
//    	adapterBase.Read();
	    
	    
	}
	
	private Boolean IsAllSearchedLock(){
		Boolean bRet=true;
		mSearchMutex.lock();
		for (int i = 0; i < mSearchEntries.size(); i++) {
			bRet = mSearchEntries.get(i).mHasDev!=2;
			if (bRet==false) {
				break;
			}
		}
		mSearchMutex.unlock();
		return bRet;
	}
	
	private int GetSearchingTypeLock(){
		int nType=0;
		mSearchMutex.lock();
		if (mSearchEntries.size()>0) {
			nType = mSearchEntries.get(0).mCommuType;
		}
		mSearchMutex.unlock();
		
		return nType;
	}
	
	private void SetSearchedLock(PrinterParam Param){
		mSearchMutex.lock();
		for (int i = 0; i < mSearchEntries.size(); i++) {
			if (Param.mIdent.equalsIgnoreCase(mSearchEntries.get(i).mIdent)) {
				mSearchEntries.get(i).mHasDev = (byte)(Param.mOutResult==PrinterUtils.Result_Suc?1:0);
				break;
			}
		}
		mSearchMutex.unlock();
	}
	
	
	private void DoCallBacks(PrinterParam param){
		mMutex.lock();
		for (int i = 0; i < mCallBacks.size(); i++) {
			IPrinterCallBack callBack = mCallBacks.get(i);
			if (null!=callBack) {
				try {
					callBack.OnCallBackFunc(param);
				} catch (Exception e) {
					// TODO: handle exception
					e.printStackTrace();
				}
				
			}
		}
		mMutex.unlock();
	}
	
	private PrinterEntry GetPrinterLock(PrinterParam param){
		PrinterEntry ret = null;
		mPrintersMutex.lock();
		PrinterEntry entry; 
		for (int i = 0; i < mPrinters.size(); i++) {
			entry = mPrinters.get(i);
			if (entry.strIdent.equalsIgnoreCase(param.mIdent)) {
				ret = entry;
				break;
			}
		}
		mPrintersMutex.unlock();
		return ret;
	}
	
	private PrinterEntry AddPrinterLock(PrinterParam param){
		PrinterAdapterBase adapter=null;
		PrinterEntry retEntry=null;
		
		retEntry = GetPrinterLock(param);
		if (retEntry == null) {
			adapter = GetPrinterAdapter(param.mCommuType);
			
			if (adapter!=null) {
					retEntry = new PrinterEntry(param, adapter);
					mPrintersMutex.lock();
					mPrinters.add(retEntry);
					mPrintersMutex.unlock();
					LogHelper.logI(getClass().getSimpleName(), "---add printer"+param.mIdent);
			}
		}else {
			LogHelper.logI(getClass().getSimpleName(), "---printer allready exist: "+param.mIdent);
		}
		return retEntry;
		
	}
	
	
	
	private void RemovePrinterLock(PrinterParam param){
		mPrintersMutex.lock();
		Iterator<PrinterEntry> it = mPrinters.iterator();
		PrinterEntry entry;
		Boolean bCallBack = false;
		while(it.hasNext()){
			entry = it.next();
		    if(param.mIdent.equalsIgnoreCase(entry.strIdent)){
		    	if (entry.adapter != null) {
		    		entry.adapter.DisConnect(param);
		    		bCallBack = true;
			    	entry.adapter = null;
			    	LogHelper.logI(getClass().getSimpleName(), "remove---printer ident:"+param.mIdent);
				}
		        it.remove();
		    }
		}
		mPrintersMutex.unlock();
		
		PrinterParam param1 = new PrinterParam(param);
		param1.mOutResult = bCallBack? PrinterUtils.Result_Suc:PrinterUtils.Result_Fail;
		if (!bCallBack) {
			param1.mOutErrCode = PrinterUtils.Err_No_Device;
		}
		DoCallBacks(param1);
		
	}

	private void SetPrinterConnectedLock(PrinterParam param, Boolean bConnected){
		mPrintersMutex.lock();
		for (int i = 0; i < mPrinters.size(); i++) {
			if (param.mIdent.equals( mPrinters.get(i).strIdent)) {
				mPrinters.get(i).bConnected = bConnected;
				break;
			}
		}
		mPrintersMutex.unlock();
	}
	
	@Override
	public void OnCallBackFunc(PrinterParam Param) {
		// TODO Auto-generated method stub
		if (Param.mOpType == PrinterUtils.OpType_Search) {
			SetSearchedLock(Param);
			if (IsAllSearchedLock()) {
				PrinterParam Param1 = new PrinterParam();
				Param1.mCommuType = Param.mCommuType;
				Param1.mOpType = Param.mOpType;
				
				DoCallBacks(Param1);
			}
		}
	}
	
	private List<PrinterSearchEntry> GetSearchListLock(PrinterParam param){
		List<PrinterSearchEntry> retlist = new ArrayList<PrinterSearchEntry>();
		PrinterSearchEntry entry;
		if (param.mCommuType != GetSearchingTypeLock()) {
					return retlist;
		}
		
		mSearchMutex.lock();
		for (int i = 0; i < mSearchEntries.size(); i++) {
			entry = mSearchEntries.get(i);
			if (param.mCommuType == PrinterUtils.COMMU_USB) {
				retlist.add(entry);
			}else if (entry.mHasDev==1) {
				retlist.add(entry);
			}
			
		}
		mSearchMutex.unlock();
		return retlist;
	}
	
	public List<PrinterSearchEntry> GetSearchList(PrinterParam param){
		return GetSearchListLock(param);
	}
	
}
