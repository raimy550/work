package com.android.sp4418testtool;

import java.nio.ByteBuffer;

import phoenix.peripherals.CashDrawerManager;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener{

	private static final String SERIAL_1 = "/dev/ttyAMA2";
	private static final String SERIAL_2 = "/dev/ttyAMA3";
	private static final String SERIAL_3 = "/dev/ttyAMA4";
	
	
	private static final int SERIAL_SUCCESS = 0;
	private static final int SERIAL_FAILED = 1;
	
	
	private byte[] bytes = new byte[]{0x01, 0x02, 0x03};
	
	private TextView tv_serial1;
	private TextView tv_serial2;
	private TextView tv_serial3;
	
	private Button btn_cashbox;
	
	private SerialOp mSerialOp = new SerialOp();
	
	private boolean bThreadRun = false;
	
	private Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			String serial = (String) msg.obj;
			switch (msg.what) {
			case SERIAL_SUCCESS:
				if (serial.equalsIgnoreCase(SERIAL_1)) {
					startSerialTest(SERIAL_2);
					tv_serial1.setText(R.string.test_success);
				} else if (serial.equalsIgnoreCase(SERIAL_2)) {
					startSerialTest(SERIAL_3);
					tv_serial2.setText(R.string.test_success);
				} else {
					tv_serial3.setText(R.string.test_success);
					CashDrawerManager cashDrawerManager = new CashDrawerManager();
					cashDrawerManager.openCashDrawer();
				}
				break;
			case SERIAL_FAILED:
				if (serial.equalsIgnoreCase(SERIAL_1)) {
					tv_serial1.setText(R.string.test_failed);
				} else if (serial.equalsIgnoreCase(SERIAL_2)) {
					tv_serial2.setText(R.string.test_failed);
				} else {
					tv_serial3.setText(R.string.test_failed);
				}
				break;

			default:
				break;
			}
		}
	};
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        tv_serial1 = (TextView) findViewById(R.id.tv_serial1);
        tv_serial2 = (TextView) findViewById(R.id.tv_serial2);
        tv_serial3 = (TextView) findViewById(R.id.tv_serial3);
        
        btn_cashbox = (Button) findViewById(R.id.btn_cashbox);
        btn_cashbox.setOnClickListener(this);
        
        startSerialTest(SERIAL_1);
    }
    
    private void startSerialTest(final String serial) {
    	boolean bopen = mSerialOp.openSerialPort(serial, 115200);
        if (bopen) {
        	bThreadRun = true;
        	startReceiveThread(serial);
        	mHandler.postDelayed(new Runnable() {
    			
    			public void run() {
    				// TODO Auto-generated method stub
    				if (bThreadRun) {
    					mHandler.obtainMessage(SERIAL_FAILED, serial).sendToTarget();
    				}
    			}
    		}, 3*1000);
        	mSerialOp.writeData(ByteBuffer.wrap(bytes), bytes.length);
        } else {
			mHandler.obtainMessage(SERIAL_FAILED, serial).sendToTarget();
		}
    }
    
    private void startReceiveThread(final String serial){
    	new Thread(new Runnable() {
			
    		@Override
			public void run() {
				
				ByteBuffer buffer = ByteBuffer.wrap(new byte[512]);
				int len = 0;
					
				if ((len = mSerialOp.readData(buffer)) != 0) {
					byte[] recBytes = new byte[len];
					System.arraycopy(buffer.array(), 0, recBytes, 0, len);
						
					if (recBytes[0] == bytes[0] && recBytes[1] == bytes[1] && recBytes[2] == bytes[2]) {
						mHandler.obtainMessage(SERIAL_SUCCESS, serial).sendToTarget();
					} else {
						mHandler.obtainMessage(SERIAL_FAILED, serial).sendToTarget();
					}
					
					bThreadRun = false;
				}
			}
		}).start();
    }

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.btn_cashbox:
			//startSerialTest(SERIAL_1);
			btn_cashbox.setEnabled(false);
			StartTestAudio();
			break;

		default:
			break;
		}
	}
	
	private void StartTestAudio(){
		MediaPlayer mediaPlayer = MediaPlayer.create(this, R.raw.aaa);
		mediaPlayer.setLooping(true);
		mediaPlayer.start();
		
		
	}
}
