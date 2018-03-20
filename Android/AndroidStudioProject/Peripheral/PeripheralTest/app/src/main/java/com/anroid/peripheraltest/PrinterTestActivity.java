package com.anroid.peripheraltest;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.widget.Button;

/**
 * Created by raimy on 2018-01-04.
 */

public class PrinterTestActivity extends Activity implements View.OnClickListener{
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.printer_activity);
        InitView();
    }

    private void InitView(){
        Button btn = (Button) findViewById(R.id.btn_test_net);
        btn.setOnClickListener(this);

        btn = (Button) findViewById(R.id.btn_test_serial);
        btn.setOnClickListener(this);

        btn = (Button) findViewById(R.id.btn_test_usb);
        btn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.btn_test_serial:
                Logic.GetInstance().DoPrintTestSerial();
                break;
            case R.id.btn_test_usb:
                Logic.GetInstance().DoPrintTestUsb();
                break;
            case R.id.btn_test_net:
                Logic.GetInstance().DoPrintTestNet();
                break;
            default:
            break;
        }
    }
}
