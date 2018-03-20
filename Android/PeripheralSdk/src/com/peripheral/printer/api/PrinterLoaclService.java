/**
 * 
 */
package com.peripheral.printer.api;

import java.util.List;

import com.peripheral.printer.PrinterManager;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;

/**
 * @author raimy
 *
 */
/**
 * @author raimy
 *
 */
/**
 * @author raimy
 *
 */
public class PrinterLoaclService extends Service{
	
	private PrinterLocalBinder mBinder=new PrinterLocalBinder();
	
	public class PrinterLocalBinder extends Binder{
		public PrinterLoaclService GetService(){
			return PrinterLoaclService.this;
		}
	}
	
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return mBinder;
	}

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		Init();
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// TODO Auto-generated method stub
		return super.onStartCommand(intent, flags, startId);
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		UnInit();
	}

	@Override
	public boolean onUnbind(Intent intent) {
		// TODO Auto-generated method stub
		return super.onUnbind(intent);
	}
	
	// 功能接口
	
	/**初始化
	 * @param callBack:回调接口
	 */
	public void Init(){
		PrinterManager.GetInstance().Init(getApplicationContext());
	}
	
	/**反初始化
	 * @param callBack
	 */
	public void UnInit(){
		PrinterManager.GetInstance().UnInit();
	}
	
	/**操作命令
	 * @param param
	 */
	public void Operate(PrinterParam param){
		PrinterManager.GetInstance().Operate(param);
	}
	
	public List<PrinterSearchEntry> GetSearchList(PrinterParam param){
		return PrinterManager.GetInstance().GetSearchList(param);
	}
	
	/**注册回调
	 * @param callBack
	 */
	public void RegistCallBack(IPrinterCallBack callBack){
		PrinterManager.GetInstance().RegistCallBack(callBack);
	}
	
	
	/**反注册回调
	 * @param callBack
	 */
	public void UnRegistCallBack(IPrinterCallBack callBack){
		PrinterManager.GetInstance().UnRegistCallBack(callBack);
	}
	

	
	

}
