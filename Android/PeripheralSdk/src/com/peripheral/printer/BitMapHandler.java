/**
 * 
 */
package com.peripheral.printer;

import java.util.Arrays;

import com.raimy.utils.BitMapHelper;
import com.raimy.utils.LogHelper;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Path;

/**
 * @author raimy
 *
 */
public class BitMapHandler {
	private String mPath;
	private int mWidth, mHeight;
	private int mRows, mCols;
	private byte[] mPrintBmpData;
	private byte[] mPrinterBmpDataRow;
	

	public BitMapHandler(String path){
		mPath = path;
		mPrintBmpData = null;
		mPrinterBmpDataRow = null;
	}
	
	public Boolean Change2PrinterBmp(){
		Boolean bRet=true;
		Bitmap bmp = null;
		bmp = BitmapFactory.decodeFile(mPath);
		
		if (bmp==null) {
			LogHelper.logE(getClass().getSimpleName(), "load bmp "+ mPath + "error!");
			return false;
		}
		
		mWidth = bmp.getWidth();
		mHeight = bmp.getHeight();
		
		mRows = (mHeight+23)/24;
		mCols = mWidth;
		
		mPrintBmpData = BitMapHelper.pic2PxPoint(bmp);
		
		mPrinterBmpDataRow = new byte[mCols*3];
		
		return bRet;
	}
	
	public byte[] GetPrinterBmpData(int row){
		if (mRows<row || mPrintBmpData==null || mPrinterBmpDataRow==null) {
			return null;
		}
		Arrays.fill(mPrinterBmpDataRow, (byte)0);
		System.arraycopy(mPrintBmpData, row*(mCols*3), mPrinterBmpDataRow, 0, mCols*3);
		
		return mPrinterBmpDataRow;
	}
	
	public int GetRows(){
		return mRows;
	}
	
	public int GetCols(){
		return mCols;
	}
	
}
