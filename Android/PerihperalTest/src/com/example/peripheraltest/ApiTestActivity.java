package com.example.peripheraltest;

import java.io.IOException;
import java.util.List;

import com.peripheral.printer.api.IPrinterCallBack;
import com.peripheral.printer.api.PrinterLoaclService;
import com.peripheral.printer.api.PrinterParam;
import com.peripheral.printer.api.PrinterSearchEntry;
import com.peripheral.printer.api.PrinterUtils;

import android.app.Activity;
import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Environment;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ApiTestActivity extends Activity implements OnClickListener, IPrinterCallBack{
	private int mCommType;
	private PrinterLoaclService mPrinterLoaclService=null;
	private ServiceConnection conn;
	private static final String TAG="ApiTestActivity";

	/* (non-Javadoc)
	 * @see android.app.Activity#onCreate(android.os.Bundle)
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_api);
		mCommType = getIntent().getIntExtra("commuType", 0);
		
		conn = new ServiceConnection() {

			@Override
			public void onServiceConnected(ComponentName name, IBinder service) {
				// TODO Auto-generated method stub
				Log.i(TAG, "----------onServiceConnected");
				if (mPrinterLoaclService==null) {
					PrinterLoaclService.PrinterLocalBinder binder = 
							(PrinterLoaclService.PrinterLocalBinder)service;
					mPrinterLoaclService = binder.GetService();
					mPrinterLoaclService.RegistCallBack(ApiTestActivity.this);
				}
			}

			@Override
			public void onServiceDisconnected(ComponentName name) {
				// TODO Auto-generated method stub
				mPrinterLoaclService = null;
			}
			
		};
		
		InitView();
		
		StartPrinterService();
			
	}
	
	private void StartPrinterService(){
		
	 	final Intent intent = new Intent(this, PrinterLoaclService.class);
	 	bindService(intent, conn, Service.BIND_AUTO_CREATE);
		
	}
	
	private void InitView(){
		Button btn = (Button)findViewById(R.id.btn_connect);
		btn.setOnClickListener(this);
		
		btn = (Button)findViewById(R.id.btn_disconnect);
		btn.setOnClickListener(this);
		
		btn = (Button)findViewById(R.id.btn_search);
		btn.setOnClickListener(this);
		
		btn = (Button)findViewById(R.id.btn_getinfo);
		btn.setOnClickListener(this);
		
		btn = (Button)findViewById(R.id.btn_printbmp);
		btn.setOnClickListener(this);
		
		btn = (Button)findViewById(R.id.btn_exit);
		btn.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		PrinterParam param = new PrinterParam(mCommType);
		if (mCommType == PrinterUtils.COMMU_SERIAL) {
			param.mIdent = "/dev/ttyAMA2";
		}else if (mCommType == PrinterUtils.COMMU_USB) {
			param.mIdent = "Usb1110-2056";
		}else if (mCommType == PrinterUtils.COMMU_NET) {
			param.mIdent = PrinterUtils.NET_IP_ADDR;
		}
		
		
		switch (v.getId()) {
		case R.id.btn_connect:
			param.mCommuType = mCommType;
			param.mOpType = PrinterUtils.OpType_Connect;
			if (mCommType == PrinterUtils.COMMU_SERIAL) {
				param.mStrParam1 = "/dev/ttyAMA2";
				param.mIntParam1 = 115200;
			}else if (mCommType == PrinterUtils.COMMU_USB) {
				param.mIntParam1= 1110;//1155;//34918;//1137;
				param.mIntParam2 = 2056;//41061;//256;//85;
			}else if (mCommType == PrinterUtils.COMMU_NET) {
				param.mStrParam1 = PrinterUtils.NET_IP_ADDR;
				param.mIntParam1 = PrinterUtils.NET_PORT;
			}
			mPrinterLoaclService.Operate(param);
			break;
		case R.id.btn_disconnect:
			param.mOpType = PrinterUtils.OpType_DisConnect;
			mPrinterLoaclService.Operate(param);		
			break;
		case R.id.btn_search:
			param.mOpType = PrinterUtils.OpType_Search;
			mPrinterLoaclService.Operate(param);
			break;
		case R.id.btn_getinfo:
			param.mOpType = PrinterUtils.OpType_GetInfo;
			mPrinterLoaclService.Operate(param);
			break;
		case R.id.btn_printbmp:
			String path = Environment.getExternalStorageDirectory().toString();
			path = path + "/Pictures/screenShot.bmp";
			param.mOpType = PrinterUtils.OpType_PrintBmp;
			param.mStrParam1 = path;
			mPrinterLoaclService.Operate(param);
			break;
		case R.id.btn_exit:
			finish();
			break;

		default:
			break;
		}
		
	}

	/* (non-Javadoc)
	 * @see android.app.Activity#onDestroy()
	 */
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		mPrinterLoaclService.UnRegistCallBack(this);
		unbindService(conn);
	}

	@Override
	public void OnCallBackFunc(PrinterParam Param) {
		// TODO Auto-generated method stub
		Log.i(TAG, "----------OnCallBackFunc");
		if (Param.mOpType == PrinterUtils.OpType_Search) {
			PrinterParam param = null;
			if (Param.mCommuType == PrinterUtils.COMMU_SERIAL) {
				param = new PrinterParam(PrinterUtils.COMMU_SERIAL);
			}else if (Param.mCommuType == PrinterUtils.COMMU_USB) {
				param = new PrinterParam(PrinterUtils.COMMU_USB);
			}
			
			List<PrinterSearchEntry> dataEntries = mPrinterLoaclService.GetSearchList(param);
			for (int i = 0; i < dataEntries.size(); i++) {
				Log.i(TAG, "------"+dataEntries.get(i).mIdent);
			}
		}else{
			Log.i(TAG, "CallBack-----OpType:"
		+Param.mOpType+", ident:"+Param.mIdent+",result:"+Param.mOutResult+", errcode:"+Param.mOutErrCode);
		}
	}
	
}
