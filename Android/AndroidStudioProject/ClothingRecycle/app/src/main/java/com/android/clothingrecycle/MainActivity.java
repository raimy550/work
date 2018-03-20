package com.android.clothingrecycle;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private Logic mLogic;
    private ImageView mIVQuickMark;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Init();
        InitView();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Logic.ObjCreater.GetInstance().UnInit();;
    }

    private void Init(){
        mLogic = Logic.ObjCreater.GetInstance();
        mLogic.Init(getApplicationContext());
    }

    private void InitView(){
        Button btn = (Button) findViewById(R.id.btn_interfacetest);
        btn.setClickable(true);
        btn.setOnClickListener(this);

        mIVQuickMark = (ImageView)findViewById(R.id.iv_quickmark);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_interfacetest:
                startActivity(new Intent(this, InterfaceActivity.class));
                break;
            default:
                break;
        }
    }
}
