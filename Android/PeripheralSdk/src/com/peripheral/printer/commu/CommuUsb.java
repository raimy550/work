/**
 * 
 */
package com.peripheral.printer.commu;

import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.security.acl.Permission;
import java.util.HashMap;
import java.util.Iterator;

import com.raimy.utils.LogHelper;

import android.R.string;
import android.annotation.SuppressLint;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.database.CursorJoiner.Result;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;

/**
 * @author raimy
 *
 */
public class CommuUsb extends CommuBase{
	private Context mContext;
	private UsbManager mUsbManager;
	private UsbDevice mUsbDevice;
	private UsbInterface mUsbInterface;
	private UsbDeviceConnection mUsbDeviceConnection;
	private UsbEndpoint mUsbEndpointIn;
    private UsbEndpoint mUsbEndpointOut;
    private Integer mVenderId, mProductId;
    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
	
	
	public CommuUsb(Context context, int nVenderId, int nProductId){
		mVenderId = nVenderId;
		mProductId = nProductId;
		mContext = context;
		mUsbManager = (UsbManager)mContext.getSystemService(Context.USB_SERVICE);
		
	}
	
	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#Write(java.lang.String)
	 */
	@Override
	public boolean Write(String data) {
		// TODO Auto-generated method stub
		boolean bRet = false;
		byte[] byData = null;
		byData = data.getBytes(Charset.forName("GBK"));
		int nRet = mUsbDeviceConnection.bulkTransfer(mUsbEndpointOut, byData, byData.length, 0);
		if (nRet>=0) {
			LogHelper.logI(getClass().getName(), "---write sucess");
			bRet = true;
		}else{
			LogHelper.logI(getClass().getName(), "---write fail");
			bRet = false;
		}
		
		return bRet;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#Connect()
	 */
	@Override
	public boolean Connect() {
		// TODO Auto-generated method stub
		boolean bRet=false;
		if (FindUsbDevice()) {
			if (mUsbManager.hasPermission(mUsbDevice)) {
					bRet = OpenDevice();
			}else{
				PendingIntent pdIntent = PendingIntent.getBroadcast(mContext, 
						0, new Intent(ACTION_USB_PERMISSION), 0);
				mUsbManager.requestPermission(mUsbDevice, pdIntent);
			}
		}
		return bRet;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#DisConnect()
	 */
	@Override
	public boolean DisConnect() {
		// TODO Auto-generated method stub
		if (mUsbDeviceConnection != null) {
			mUsbDeviceConnection.releaseInterface(mUsbInterface);
			mUsbDeviceConnection.close();
			mUsbDeviceConnection = null;
		}
		
		 mUsbEndpointIn = null;
	     mUsbEndpointOut = null;
		return true;
	}
	
	/**
     * 分配端点，IN | OUT，即输入输出；可以通过判断
     */
	private boolean OpenDevice() {
		boolean bRet=false;
    	 int interfaceCount = mUsbDevice.getInterfaceCount();
         for (int interfaceIndex = 0; interfaceIndex < interfaceCount; interfaceIndex++) {
             UsbInterface usbInterface = mUsbDevice.getInterface(interfaceIndex);
//             if ((UsbConstants.USB_CLASS_CDC_DATA != usbInterface.getInterfaceClass())
//                     && (UsbConstants.USB_CLASS_COMM != usbInterface.getInterfaceClass())) {
//                 continue;
//             }
             if (UsbConstants.USB_CLASS_PRINTER != usbInterface.getInterfaceClass()){
            	 continue;
             }
              

             for (int i = 0; i < usbInterface.getEndpointCount(); i++) {
                 UsbEndpoint ep = usbInterface.getEndpoint(i);
                 if (ep.getType() == UsbConstants.USB_ENDPOINT_XFER_BULK) {
                     if (ep.getDirection() == UsbConstants.USB_DIR_OUT) {
                    	 mUsbEndpointOut = ep;
                     } else if(ep.getDirection() == UsbConstants.USB_DIR_IN) {
                         mUsbEndpointIn = ep;
                     }
                 }
             }
             
             if ((null == mUsbEndpointIn) || (null == mUsbEndpointOut)) {
                 mUsbEndpointIn = null;
                 mUsbEndpointOut = null;
                 mUsbInterface = null;
             } else {
                 mUsbInterface = usbInterface;
                 mUsbDeviceConnection = mUsbManager.openDevice(mUsbDevice);
                 bRet=true;
                 break;
             }
         }
         return bRet;
    }

	private boolean FindUsbDevice(){
		boolean bRet = false;
    	HashMap<String, UsbDevice> devList = mUsbManager.getDeviceList();
    	Iterator<UsbDevice> devIter = devList.values().iterator();
    	while(devIter.hasNext()){
    		UsbDevice device = devIter.next();
    		if (device.getVendorId() == mVenderId && device.getProductId() == mProductId) {
    			mUsbDevice = device; 
    			bRet=true;
    			break;
    		}
    	}
    	return bRet;
    }

	@Override
	public boolean Write(byte[] data) {
		// TODO Auto-generated method stub
		Boolean bRet = false;
		int nRet = mUsbDeviceConnection.bulkTransfer(mUsbEndpointOut, data, data.length, 0);
		if (nRet>=0) {
			LogHelper.logI(getClass().getName(), "---write sucess");
			bRet = true;
		}else{
			LogHelper.logI(getClass().getName(), "---write fail");
			bRet = false;
		}
		
		return bRet;
	}

	@Override
	public byte[] Read() {
		// TODO Auto-generated method stub
		byte[] byteRead= new byte[1024];
		byte[] byteRet = null;
		int nRet = mUsbDeviceConnection.bulkTransfer(mUsbEndpointIn, byteRead, byteRead.length, 3000);
		if (nRet>=0) {
			LogHelper.logI(getClass().getName(), "---read sucess");
			byteRet = new byte[nRet];
			System.arraycopy(byteRead, 0, byteRet, 0, nRet);
		}else{
			LogHelper.logI(getClass().getName(), "---read  fail");
		}
		
		return byteRet;
	}
}
