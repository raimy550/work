/**
 * 
 */
package com.peripheral.printer.commu;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.nio.charset.Charset;

import com.raimy.utils.LogHelper;
import com.raimy.utils.StringHelper;

import android.R.integer;
import android.annotation.SuppressLint;

/**
 * @author raimy
 *
 */
public class CommuNet extends CommuBase{
	public final int Net_ReceiveTimeout = 1500;
	private String mNetIp;
	private Integer mNetPort;
	private Socket mSocket;
	public byte[] mOutBytes;
	
	public CommuNet(String strIp, int netPort){
		mNetIp = strIp;
		mNetPort=netPort;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#Write(java.lang.String)
	 */
	
	@Override
	public boolean Write(String data) {
		// TODO Auto-generated method stub
		try {
			mOutBytes = data.getBytes(Charset.forName("GBK"));
			OutputStream stream = mSocket.getOutputStream();
			stream.write(mOutBytes);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		return true;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#Connect()
	 */
	@Override
	public boolean Connect() {
		// TODO Auto-generated method stub
		Boolean ret = true;
		try {
			if (mSocket!=null){
				mSocket.close();
				mSocket=null;
			}
			mSocket = new Socket();
			
			SocketAddress addr = new InetSocketAddress(mNetIp, mNetPort);
			mSocket.connect(addr);
			mSocket.setSoTimeout(Net_ReceiveTimeout);
			LogHelper.logI(getClass().getSimpleName(), "Connect sucess");
			
		} catch (Exception e) {
			// TODO: handle exception
			LogHelper.logE(getClass().getSimpleName(), "Connect fail");
			e.printStackTrace();
			ret = false;
		}
		return ret;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#DisConnect()
	 */
	@Override
	public boolean DisConnect(){
		// TODO Auto-generated method stub
		if (mSocket!=null){
			try {
				mSocket.close();
				mSocket=null;
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
		}
		return true;
	}

	@Override
	public boolean Write(byte[] data) {
		// TODO Auto-generated method stub
		try {
			OutputStream stream = mSocket.getOutputStream();
			stream.write(data);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		return true;
	}

	@Override
	public byte[] Read() {
		// TODO Auto-generated method stub
		byte[] buffer = new byte[1024];
		byte[] byRet = null;
		int nRead;
		try {
			InputStream stream = mSocket.getInputStream();
			nRead = stream.read(buffer);
			if (nRead>0) {
				byRet = new byte[nRead];
				LogHelper.logI(getClass().getSimpleName(), "Read:"+StringHelper.bytesToHexString(byRet));
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			return byRet;
		}
		return byRet;
	}

}
