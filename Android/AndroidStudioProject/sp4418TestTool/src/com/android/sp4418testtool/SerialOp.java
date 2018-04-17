package com.android.sp4418testtool;

/**
 * 
 */

import java.io.IOException;
import java.nio.ByteBuffer;

import android.content.Context;
import android.hardware.ISerialManager;
import android.hardware.SerialPort;
import android.os.ParcelFileDescriptor;
import android.os.RemoteException;
import android.util.Log;
import android.os.ServiceManager;

/**
 * @author Administrator
 * 串口功能
 */
public class SerialOp{
	
	private SerialPort mSp = null;
	private static String TAG="SerialOp";
	
	
	/**
	 * 打开串口
	 * @param devPath 设备标识符路径 
	 * @param baudRate  波特率
	 */
	public boolean openSerialPort(String devPath, int baudRate){
		boolean bRet = false;
		try {
			ISerialManager serialService = ISerialManager.Stub.asInterface(ServiceManager.getService(Context.SERIAL_SERVICE));
			ParcelFileDescriptor pfd = serialService.openSerialPort(devPath);
            if (pfd != null) {
            	mSp = new SerialPort(devPath);
            	mSp.open(pfd, baudRate);  
            	bRet = true;
            } else {
                LogHelper.logE(TAG , "Could not open serial port: " + devPath);
            }
		} catch (RemoteException e) {
			LogHelper.logE(TAG, "exception in SerialOp.openSerialPort"+e);
		} catch (IOException e) {
			LogHelper.logE(TAG , "Could not open serial port: " + devPath);
		}
		
		return bRet;
	}
	
	public void closeSerialPort(){
		//
	}
	
	public int readData(ByteBuffer buffer){
		int nRet = 0;
		try {
			nRet = mSp.read(buffer);
		} catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		return nRet;
	}
	
	public void writeData(ByteBuffer buffer,int len){
		try {
			mSp.write(buffer,len);
		} catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
}
