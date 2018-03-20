/**
 * 
 */
package com.peripheral.printer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.api.PrinterUtils;

import android.annotation.SuppressLint;
import android.content.Context;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;

/**
 * @author raimy
 *
 */
public class UsbDeviceFinder {
	private UsbManager mUsbManager;
	private Context mContext;
	
	public UsbDeviceFinder(Context context){
		mContext = context;
		mUsbManager = (UsbManager)mContext.getSystemService(Context.USB_SERVICE);
	}
	
	@SuppressLint("NewApi")
	public List<PrinterSearchEntry> GetDevices(){
		List<PrinterSearchEntry> list= new ArrayList<PrinterSearchEntry>();
		
		HashMap<String, UsbDevice> devList = mUsbManager.getDeviceList();
    	Iterator<UsbDevice> devIter = devList.values().iterator();
    	while(devIter.hasNext()){
    		UsbDevice device = devIter.next();  
    		if (IsPrinterUsbDevice(device)) {
    			PrinterSearchEntry entry = new PrinterSearchEntry(PrinterUtils.COMMU_USB);
        		entry.VendorID = device.getVendorId();
        		entry.ProductID = device.getProductId();
        		entry.mName = device.getProductName();
        		entry.mIdent = String.format("Usb%d-%d", entry.VendorID, entry.ProductID);	
        		list.add(entry);
			}
    		
    	}
    	return list;
	}
	
	private boolean IsPrinterUsbDevice(UsbDevice usbDevice){
		boolean bRet = false;
		 int interfaceCount = usbDevice.getInterfaceCount();
         for (int interfaceIndex = 0; interfaceIndex < interfaceCount; interfaceIndex++) {
             UsbInterface usbInterface = usbDevice.getInterface(interfaceIndex);
             if (UsbConstants.USB_CLASS_PRINTER == usbInterface.getInterfaceClass()){
            	 bRet = true;
            	 break;
             }
         }
		
		return bRet;
	}
	
	
}
