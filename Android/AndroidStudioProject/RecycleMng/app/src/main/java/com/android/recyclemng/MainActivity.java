package com.android.recyclemng;

import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.text.Format;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements AdapterView.OnItemClickListener, View.OnClickListener, LogicParam.LogicCallBack{
    private Logic mLogic;
    private Handler mUIHandler;
    private ListView mLvGrids;
    private List<GridInfo> mGridData;


    private BaseAdapter mGridAdater = new BaseAdapter() {
        @Override
        public int getCount() {
           return mGridData.size();
        }

        @Override
        public Object getItem(int position) {
            return mGridData.get(position);
        }

        @Override
        public long getItemId(int position) {
            return 0;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if(convertView==null){
                convertView = View.inflate(MainActivity.this, R.layout.grid_item, null);
            }
            TextView tv;
            GridInfo grid = mGridData.get(position);
            tv = (TextView) convertView.findViewById(R.id.tv_gridNo);
            tv.setText(grid.getNumber());
            tv = (TextView) convertView.findViewById(R.id.tv_gridAddr);
            tv.setText(grid.getAddress());

            tv = (TextView) convertView.findViewById(R.id.tv_gridUsed);
            tv.setText("已用/总数:"+grid.getUsedCount()+"/"+grid.getBoxCount());

            tv = (TextView) convertView.findViewById(R.id.tv_gridempty_rate);
            int rate = Integer.parseInt(grid.getUsedCount())*100
                    /Integer.parseInt(grid.getBoxCount());
            tv.setText("使用率:"+rate+"%");

            return convertView;
        }
    };

    @Override
    protected void onResume() {
        super.onResume();
        mLogic.DoLogicGetCabinetsByUUid();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Init();
        InitView();

    }

    private void Init(){
        mLogic = Logic.ObjCreater.GetInstance();
        mLogic.Init(getApplicationContext(), this);

        mUIHandler = new Handler(new HandlerCallBack());

        mGridData = new ArrayList<GridInfo>();


    }

    @Override
    public void OnLogicCallBack(int eType) {
        Message msg = new Message();
        msg.what = eType;
        mUIHandler.sendMessage(msg);
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Intent intent = new Intent();
        intent.setClass(this, DetailActivity.class);
        Bundle bundle = new Bundle();
        GridInfo griddata = mGridData.get(position);
        bundle.putSerializable("GridData", griddata);
        intent.putExtras(bundle);
        startActivity(intent);
    }

    public class HandlerCallBack implements  Handler.Callback{
        @Override
        public boolean handleMessage(Message msg) {
            switch(msg.what){
                case LogicParam.Update_GridInfo:
                    DoUpdateGridInfo();
                break;
                default:
                break;
            }
            return false;
        }
    }

    private void InitView(){
        mLvGrids = (ListView) findViewById(R.id.lv_grids);
        mLvGrids.setAdapter(mGridAdater);
        mLvGrids.setOnItemClickListener(this);
    }

    private void DoUpdateGridInfo(){
        mGridData = new ArrayList<GridInfo>(mLogic.getmGridsInfo());
        mGridAdater.notifyDataSetChanged();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mLogic.UnInit();
    }

    @Override
    public void onClick(View v) {

    }
}
