package com.example.peripheraltest;

import java.util.List;

import org.apache.http.conn.params.ConnConnectionParamBean;

//import com.peripheral.printer.PrinterApi;
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
import android.os.IBinder;
import android.printservice.PrintService;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener{
	//private PrinterApi mPrinterApi;
	private static final String TAG="MainActivity";
	private int mTestType;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
//		mPrinterApi = PrinterApi.GetInstance();
		
		InitView();
		
	}

	private void InitView(){
		Button Btn = (Button)findViewById(R.id.btn_test_serial);
		Btn.setOnClickListener(this);
		
		Btn = (Button)findViewById(R.id.btn_test_usb);
		Btn.setOnClickListener(this);
		
		Btn = (Button)findViewById(R.id.btn_test_net);
		Btn.setOnClickListener(this);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.btn_test_serial:
			TestSerial();
			break;
		case R.id.btn_test_usb:
			TestUsb();
			break;
		case R.id.btn_test_net:
			TestNet();
			break;
			
		default:
			break;
		}
		
		Intent intent = new Intent(this, ApiTestActivity.class);
		intent.putExtra("commuType", mTestType);
		startActivity(intent);
	}
	
	
	private void TestSerial(){
		mTestType = PrinterUtils.COMMU_SERIAL;
//	 	final Intent intent = new Intent(this, PrinterLoaclService.class);
//	 	bindService(intent, conn, Service.BIND_AUTO_CREATE);
	}
	
	private void TestUsb(){
		mTestType = PrinterUtils.COMMU_USB;
//		final Intent intent = new Intent(this, PrinterLoaclService.class);
//	 	bindService(intent, conn, Service.BIND_AUTO_CREATE);
	}
	
	private void TestNet(){
		mTestType = PrinterUtils.COMMU_NET;
//		final Intent intent = new Intent(this, PrinterLoaclService.class);
//	 	bindService(intent, conn, Service.BIND_AUTO_CREATE);
	}
}
