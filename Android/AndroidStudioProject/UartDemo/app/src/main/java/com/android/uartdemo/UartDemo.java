package com.android.uartdemo;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import android.os.Bundle;
import android.os.Environment;
import android.os.HandlerThread;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.os.Handler;

import com.smatek.uart.UartComm;
import com.android.uartdemo.SerialPortPreferences;

public class UartDemo extends Activity {
    private Button btn_send;
    private Button rs485Btn;
    final static String TAG = "SendHex";
    private EditText ed_hex;
    private TextView tvMsg, tvUartSetting;
    private UartComm UC;
    final int MSG_UPDATE_MSG = 1;
    private String recv_msg;
    private Handler mRecvHandler=null;

    HandlerThread thread;
    private String uartDevice;
    private int baudrate;
    private int parityCheck;

    private boolean mRunning = false;
    private boolean mNeedSendData = false;
    private 	int[] mSendBuf = new int[256];
    private int mSendDataLen;
    private final int MSG_UPDATE = 1;
    private boolean mIsRS485 = false;
    private int uart_fd;


    Handler mUIHandler = new Handler(){
        public void handleMessage(android.os.Message msg) {
            switch(msg.what){
                case MSG_UPDATE:
                    //更新界面
                    tvMsg.setText(recv_msg);
                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_uart_demo);
        UC = new UartComm();
        ed_hex = (EditText) findViewById(R.id.editHex);
        tvMsg = (TextView)findViewById(R.id.tvMsgRecv);
        tvUartSetting = (TextView)findViewById(R.id.tvUartSetting);
        rs485Btn = (Button) findViewById(R.id.rs485Btn);
        rs485Btn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(UartDemo.this,  Rs485Loop.class));
            }
        });

        final Button buttonSetup = (Button)findViewById(R.id.ButtonSetup);
        buttonSetup.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                startActivity(new Intent(UartDemo.this,  SerialPortPreferences.class));
            }
        });

        final Button buttonEnableCfg = (Button)findViewById(R.id.EnableCfg);
        buttonEnableCfg.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                CfgIO("/sys/class/gpio_sw/PE12/data", 0);
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                CfgIO("/sys/class/gpio_sw/PE12/data", 1);
            }
        });

        //获取CheckBox实例
        CheckBox cb = (CheckBox)this.findViewById(R.id.cb);
        //绑定监听器
        cb.setOnCheckedChangeListener(new OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton arg0, boolean isChecked) {
                if(isChecked) {
                    mIsRS485 = true;
                } else {
                    mIsRS485 = false;
                }
            }
        });
		/* Create a receiving thread */

        thread = new HandlerThread("UartRecvThread");
        thread.start();//创建一个HandlerThread并启动它
        mRecvHandler = new Handler(thread.getLooper());//使用HandlerThread的looper对象创建Handler，如果使用默认的构造方法，很有可能阻塞UI线程



        btn_send = (Button) findViewById(R.id.btnSend);
        btn_send.requestFocus();
        btn_send.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                int i;

                String hex = ed_hex.getText().toString();
                if ("".equals(hex) ) {
                    return;
                }
                String[] hexArray = hex.split(" ");


                for(i=0; i<hexArray.length; i++) {
                    mSendBuf[i] = hexStringToInt(hexArray[i]);
                }
                mSendDataLen = hexArray.length;
                tvMsg.setText("");

                mNeedSendData = true;

            }});
    }
    /**
     * Convert hex string to byte[]
     * @param hexString the hex string
     * @return byte[]
     */
    public static int  hexStringToInt(String hexString) {
        if (hexString == null || hexString.equals("")) {
            return 0xff;
        }
        hexString = hexString.toUpperCase();
        char[] hexChars = hexString.toCharArray();
        if(hexString.length() == 1)
            return charToInt(hexChars[0]);
        else if(hexString.length() == 2)
            return  (int) (charToInt(hexChars[0]) << 4 | charToInt(hexChars[1]));
        else
            return 0xff;
    }
    /**
     * Convert char to byte
     * @param c char
     * @return byte
     */
    private static int charToInt(char c) {
        return  "0123456789ABCDEF".indexOf(c);
    }

    //实现耗时操作的线程
    Runnable mRecvRunnable = new Runnable() {
        @Override
        public void run() {
            while(mRunning){
                int size;
                int[] buffer = new int[256];
                if(mNeedSendData == true) {
                    //set RS485 to send data mode
                    if(mIsRS485)
                        UC.setRS485WriteRead(0);
                    Log.d(TAG, "will send data " + mSendDataLen);
                    UC.send(uart_fd, mSendBuf, mSendDataLen);
                    mNeedSendData = false;
                    //set RS485 to receive data mode by default.
                    if(mIsRS485)
                        UC.setRS485WriteRead(1);
                } else {
                    if(mIsRS485)
                        UC.setRS485WriteRead(1);
                    size = UC.recv(uart_fd, buffer, 256);
                    if(size != 0) {
                        recv_msg = "";
                        for(int i=0; i<size; i++) {
                            recv_msg += Integer.toHexString(((int)buffer[i])&0xff);
                            recv_msg += "  ";
                        }
                        //	Log.i(TAG, "recv " + recv_msg);
                        mUIHandler.sendEmptyMessage(MSG_UPDATE);
                    } //end if(size != 0)
                } //end else
            } //end while
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
    @Override
    protected void onResume() {
        super.onResume();
        String str;
        SharedPreferences sp = getSharedPreferences("com.android.uartdemo_preferences", MODE_PRIVATE);
        uartDevice = sp.getString("DEVICE", "");
        baudrate = Integer.decode(sp.getString("BAUDRATE", "-1"));
        String odd_even =  sp.getString("PARITY_CHECK", "none");
        if(odd_even.equals("Odd"))
            parityCheck = 1;
        else if(odd_even.equals("Even"))
            parityCheck = 2;
        else
            parityCheck = 0;
        if(!uartDevice.equals("") && (baudrate != -1)) {
            str = "uart: " + uartDevice + "    baudrate :  " + baudrate + " parity check: " + odd_even;
            uart_fd = UC.uartInit(uartDevice);
            UC.setOpt(uart_fd, baudrate, 8, parityCheck, 1);
            //只有设置过串口后才会进入读取线程
            mRunning = true;
            mRecvHandler.post(mRecvRunnable);//将线程post到Handler中
            Log.i(TAG, "fd " + uart_fd + " parameter " + str);
        } else
            str = "串口还没有设置";
        tvUartSetting.setText(str);


    }
    @Override
    protected void onPause() {
        super.onPause();
        Log.v(TAG, "onPause");
        mRunning = false;
        mRecvHandler.removeCallbacks(mRecvRunnable);
        UC.uartDestroy(uart_fd);
        uart_fd = -1;
    }

    private int CfgIO(String path, int level) {
        int tmp;
        File file = new File(path);
        if(!file.exists()) {
            return 0;
        }
        try {
            BufferedWriter out = new BufferedWriter(new FileWriter(path), 32);
            try {
                if(level == 0)
                    out.write("0");
                else
                    out.write("1");
            }
            finally {
                out.close();
            }
            return 1;
        }
        catch (IOException e) {
            Log.e(TAG, "IOException when write " + path);
            return 0;
        }
    }
}