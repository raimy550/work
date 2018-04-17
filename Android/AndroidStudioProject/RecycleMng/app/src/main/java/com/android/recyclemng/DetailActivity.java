package com.android.recyclemng;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.List;

/**
 * Created by raimy on 2018-03-27.
 */

public class DetailActivity extends Activity implements View.OnClickListener{
    private TextView mTvContentGridNo, mTvContentGridCount,
            mTvContentGridUsed, mTvContentGridAddr;

    private Logic mLogic;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);
        InitView();
        Init();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_clean:
                mLogic.DoLogicClean();
                break;
            case R.id.tv_back:
                finish();
                break;
        }
    }

    private void InitView(){
        Button btn = (Button) findViewById(R.id.btn_clean);
        btn.setOnClickListener(this);
        btn = (Button) findViewById(R.id.btn_locate);
        btn.setOnClickListener(this);

        mTvContentGridNo = (TextView) findViewById(R.id.tv_gridno_content);
        mTvContentGridCount = (TextView) findViewById(R.id.tv_gridcount_content);
        mTvContentGridUsed = (TextView) findViewById(R.id.tv_gridused_content);
        mTvContentGridAddr = (TextView) findViewById(R.id.tv_gridaddr_content);
        LinearLayout tv = (LinearLayout) findViewById(R.id.tv_back);
        tv.setOnClickListener(this);


        Bundle bundle = getIntent().getExtras();
        GridInfo info = (GridInfo) bundle.getSerializable("GridData");
        UpdateViewGridInfo(info);
    }

    private void Init(){
        mLogic = Logic.ObjCreater.GetInstance();
    }

    private void UpdateViewGridInfo(GridInfo gridsInfo){
            mTvContentGridNo.setText(gridsInfo.getNumber());
            mTvContentGridCount.setText(gridsInfo.getBoxCount());
            mTvContentGridUsed.setText(gridsInfo.getUsedCount());
            mTvContentGridAddr.setText(gridsInfo.getAddress());

    }
}
