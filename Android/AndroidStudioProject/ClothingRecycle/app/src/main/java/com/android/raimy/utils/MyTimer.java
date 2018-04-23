package com.android.raimy.utils;

import java.util.Timer;
import java.util.TimerTask;

import android.content.Context;

public class MyTimer {
	
	private Timer mTimer;
	private TimerTask mTimerTask;
	private long mDelay,mPeriod;
	private ITimerCallBack mTimerCallBack; 
	
	public interface ITimerCallBack{
		public void OnTimerCallBack();
	}
	
	public MyTimer(ITimerCallBack timerCallBack, long delay, long period){
		mDelay = delay;
		mPeriod = period;
		mTimerCallBack = timerCallBack;
	}
	
	public void startTimer(){
		if (mTimer==null && mTimerTask==null) {
			mTimer = new Timer();
			mTimerTask = new TimerTask() {
				
				@Override
				public void run() {
					if (mTimerCallBack!=null) {
						mTimerCallBack.OnTimerCallBack();
					}
				}
			};
			
			mTimer.schedule(mTimerTask, mDelay, mPeriod);
		}	
	}
	
	public void stopTimer(){
		 if (mTimer != null) {  
	            mTimer.cancel();  
	            mTimer = null;  
	        }  
	  
	        if (mTimerTask != null) {  
	            mTimerTask.cancel();  
	            mTimerTask = null;  
	        }   
	}
	
	
}
