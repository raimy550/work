/**
 * 
 */
package com.android.raimy.utils;

import android.util.Log;

/**
 * @author Administrator
 *
 */
public class LogHelper {
	
	private static boolean DEBUG = true;
	private static boolean INFO = true;
	private static boolean ERROR = true;
	private static boolean TEST = true;
	private static final String TAG="<raimy>";
	
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
			Log.d(tag,TAG+"Debug:" + msg);
		}
	}
	
	public static void logE(String tag, String msg){
		if(ERROR)
		 Log.e(tag, TAG+"Error:"+msg);
	}
	
	public static void logI(String tag, String msg){
		if(INFO)
		 Log.i(tag, TAG+"Info:"+msg);
	}
	
	public static void logT(String tag, String msg){
		if(TEST)
		 Log.i(tag, TAG+"Test"+msg);
	}
	
}
