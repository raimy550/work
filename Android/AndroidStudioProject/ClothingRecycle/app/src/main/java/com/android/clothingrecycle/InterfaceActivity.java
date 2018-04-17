package com.android.clothingrecycle;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class InterfaceActivity extends AppCompatActivity implements View.OnClickListener{
    Logic mLogic;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_interface);
        Init();
        InitView();
    }

    private void Init(){
        mLogic = Logic.ObjCreater.GetInstance();
    }

    private void InitView(){
        Button btn = (Button) findViewById(R.id.btn_openall);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_openone);
        btn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.btn_openall:
                //mLogic.DoTestOpenAll();
            break;
            case R.id.btn_openone:
                //mLogic.DoTestOpenOne();
                break;
            default:
            break;
        }
    }
}
