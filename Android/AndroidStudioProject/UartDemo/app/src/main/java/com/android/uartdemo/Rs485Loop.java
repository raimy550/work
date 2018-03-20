package com.android.uartdemo;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RadioGroup;
import com.smatek.uart.UartComm;

/**
 * Created by tangly on 16-7-29.
 */
public class Rs485Loop extends Activity implements View.OnClickListener{
    private final int GUIUPDATEOPEN = 1, GUIUPDATESTATUS = 2;
    private Button loopBtn[];
    private LinearLayout loop1, loop2;
    private RadioGroup boardAddrCtrl;
    private int boardAddr;
    private boolean mloop;

    ImageSurfaceView imageSurfaceView;

    private Button startBtn, stopBtn, pauseBtn;
    private boolean start = false, stop = true, pause = false, startLED = false;
    UartComm.Rs485 rs485;
    private int sig_door = -1;

    private int[] doorStatus = new int[7];
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.rs485loop);
        loop1 = (LinearLayout) findViewById(R.id.loopBtn1);
        loop2 = (LinearLayout) findViewById(R.id.loopBtn2);
        loopBtn = new Button[24];

        rs485 = new UartComm().new Rs485();
        rs485.rs485Init();
        LinearLayout.LayoutParams gpioDirBtnParams = new LinearLayout.LayoutParams(70, 60);
        gpioDirBtnParams.setMargins(5, 0, 0, 0);

        LinearLayout linearLayout = (LinearLayout) findViewById(R.id.baorAddrChoose);
        imageSurfaceView = new ImageSurfaceView(this, 100, 80);
        linearLayout.addView(imageSurfaceView);

        boardAddrCtrl = (RadioGroup) findViewById(R.id.RadioGroup);
        boardAddrCtrl.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                start = pause =false;
                stop = true;
                imageSurfaceView.setVisibility(View.VISIBLE);
                switch (checkedId) {
                    case R.id.RadioButton1:
                        boardAddr = 1;
                        imageSurfaceView.update(boardAddr);
                        break;
                    case R.id.RadioButton2:
                        boardAddr = 2;
                        imageSurfaceView.update(boardAddr);
                        break;
                    case R.id.RadioButton3:
                        boardAddr = 3;
                        imageSurfaceView.update(boardAddr);
                        break;
                    case R.id.RadioButton4:
                        boardAddr = 4;
                        imageSurfaceView.update(boardAddr);
                        break;
                }
            }
        });
        for (int i = 0; i < loopBtn.length; i++) {
            loopBtn[i] = new Button(this);
            loopBtn[i].setLayoutParams(gpioDirBtnParams);
            loopBtn[i].setText("门"  + (i + 1));
            loopBtn[i].setOnClickListener(this);
            if(i < 12)
                loop1.addView(loopBtn[i]);
            else
                loop2.addView(loopBtn[i]);
        }

        startBtn = (Button) findViewById(R.id.start);
        startBtn.setOnClickListener(this);
        startBtn.setBackgroundColor(Color.BLUE);
        stopBtn = (Button) findViewById(R.id.stop);
        stopBtn.setOnClickListener(this);
        pauseBtn = (Button) findViewById(R.id.pause);
        pauseBtn.setOnClickListener(this);
        mloop = true;
        new Rs485StatusTask().start();
        new Rs485OpenTask().start();
        new Rs485SSigDoorTask().start();
    }

    private void getDoorStatusFromArray(int[] array, boolean[] doorStatus) {
        for (int i = 0; i < 3; i++) {
            int state = (int)array[4 - i];
            int t = 1;
            for (int j = 0; j < 8; j++) {
                int doorIndex = i * 8 + j;
                if ( (t & state) >0 ) {
                    doorStatus[doorIndex] = true;
                } else {
                    doorStatus[doorIndex] = false;
                }
                t *= 2;
            }
        }
    }

    @Override
    public void onClick(View v) {
        for (int i = 0; i < loopBtn.length; i++) {
            if (v == loopBtn[i]) {
                sig_door = i+1;
                return;
            }
        }
        int id = v.getId();
        switch (id) {
            case R.id.start:
                start = true;
                stop = pause = false;
                break;
            case R.id.stop:
                stop = true;
                start = pause = false;
                break;
            case R.id.pause:
                if (!pause) {
                    start = stop = false;
                    pause = true;
                    pauseBtn.setText("　恢复　");
                } else {
                    stop = pause = false;
                    start = true;
                    pauseBtn.setText("　暂停　");
                }
                break;
        }
    }

    private Handler myHandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case GUIUPDATEOPEN:
                    startLED = !startLED;
                    startBtn.setBackgroundColor(startLED ? Color.YELLOW:Color.BLUE);
                    break;
                case GUIUPDATESTATUS:
                    boolean[] status = new boolean[24];
                    getDoorStatusFromArray(doorStatus,status);
                    for (int i = 0; i < status.length; i++)
                        loopBtn[i].setBackgroundColor(status[i] ? Color.YELLOW : Color.GREEN);
                    break;
            }
            super.handleMessage(msg);
        }
    };
    class Rs485StatusTask extends Thread {
        @Override
        public void run() {
            while (mloop) {
                try {
                    Thread.sleep(400);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                if (boardAddr <= 0 || !start)
                    continue;
                synchronized (Rs485Loop.this) {
                    rs485.rs485GetDoorState(boardAddr, 0, doorStatus);
                }
                Message message = new Message();
                message.what = GUIUPDATESTATUS;
                myHandler.sendMessage(message);
            }
        }
    }
    class Rs485SSigDoorTask extends Thread {
        @Override
        public void run() {
            while (mloop) {
                try {
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                if (boardAddr <= 0)
                    continue;
                if (sig_door > 0 && sig_door <= 24) {
                    int info[] = new int[5];
                    synchronized (Rs485Loop.this) {
                        rs485.rs485OpenGrid(boardAddr, sig_door, info);
                        sig_door = -1;
                    }
                    Message message = new Message();
                    message.what = GUIUPDATESTATUS;
                    myHandler.sendMessage(message);
                }
            }
        }
    }

    class Rs485OpenTask extends Thread{
        @Override
        public void run() {
            int[] info = new int[5];
            while (mloop) {
                if (boardAddr <= 0)
                    continue;
                for (int i = 0; i < 24; i++) {
                    if(pause) {
                        i--;
                        continue;
                    }
                    if (stop)
                        break;
                    if (start) {
                        synchronized (Rs485Loop.this) {
                            rs485.rs485OpenGrid(boardAddr, i + 1, info);
                        }
                        try {
                            Thread.sleep(500);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        Message message = new Message();
                        message.what = GUIUPDATEOPEN;
                        myHandler.sendMessage(message);
                    }
                }
            }
        }
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
    }

    @Override
    protected void onResume() {
        start = true;
        stop = pause = false;
        super.onResume();
    }

    @Override
    protected void onPause() {
        start = stop = false;
        pause = true;
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        start = pause = false;
        stop = true;
        mloop = false;
        super.onDestroy();
    }
}
