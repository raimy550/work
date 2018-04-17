package com.android.sp4418testtool;

/**
 * 
 */


import android.util.Log;

/**
 * @author Administrator
 *
 */
public class LogHelper {
	
	private static boolean DEBUG = false;
	private static boolean INFO = false;
	private static boolean ERROR = true;
	private static boolean TEST = false;
	
	private static long smStartTime = 0;
	
	public static long startCalculateTime(){
		return smStartTime = System.currentTimeMillis();
	}
	
	public static long stopCalculateTime(){
		
		long lSum = System.currentTimeMillis() - smStartTime;
		smStartTime = System.currentTimeMillis();
		return lSum;
	}
	
	public static void logD(String tag, String msg) {
		if (DEBUG) {
			Log.d(tag,"Debug:" + msg);
		}
	}
	
	public static void logE(String tag, String msg){
		if(ERROR)
		 Log.e(tag, "Error:"+msg);
	}
	
	public static void logI(String tag, String msg){
		if(INFO)
		 Log.i(tag, "Info:"+msg);
	}
	
	public static void logT(String tag, String msg){
		if(TEST)
		 Log.i(tag, "Test"+msg);
	}
	
}
