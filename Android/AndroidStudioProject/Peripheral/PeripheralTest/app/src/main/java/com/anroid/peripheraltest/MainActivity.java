package com.anroid.peripheraltest;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        InitView();
        Logic.GetInstance().Init(getApplicationContext());
    }

    private void InitView(){
        Button btn;
        btn = (Button)findViewById(R.id.btn_printer);
        btn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
       switch(v.getId()){
           case R.id.btn_printer:
               startActivity(new Intent().setClass(this, PrinterTestActivity.class));
           break;
           default:
           break;
       }
    }
}
