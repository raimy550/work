package com.example.peripheraltest;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.widget.Toast;

public class SafeToast {
	private Handler mToastHandler;
	private Context mContext;
	private static SafeToast  sTheMe;
	
	private SafeToast(){
		new Thread(new Runnable() {
			public void run() {
				Looper.prepare();
				mToastHandler = new Handler(){
					@Override
					public void handleMessage(Message msg) {
						// TODO Auto-generated method stub
						super.handleMessage(msg);
						Bundle b = msg.getData();
						String str=b.getString("toast");
						int showType = b.getInt("showType");
						Toast.makeText(mContext, str, showType).show();
					}
					
				};
				Looper.loop();
			}
		}).start();
	}
	
	public static SafeToast GetInstance(){
		if (sTheMe==null) {
			synchronized (SafeToast.class) {
				sTheMe = new SafeToast();
			}	
		}
		return sTheMe;
	}
	
	public void Show(Context context, String str, int showType){
		mContext = context;
		Message msg= mToastHandler.obtainMessage();
		Bundle bundle = new Bundle();
		bundle.putString("toast", str);
		bundle.putInt("showType", showType);
		msg.setData(bundle);
		msg.sendToTarget();
	}
	
	public void Show(Context context, int resId, int showType){
		mContext = context;
		String str = context.getResources().getString(resId);
		Message msg= mToastHandler.obtainMessage();
		Bundle bundle = new Bundle();
		bundle.putString("toast", str);
		bundle.putInt("showType", showType);
		msg.setData(bundle);
		msg.sendToTarget();
	}
	
}
