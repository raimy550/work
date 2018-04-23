package com.android.clothingrecycle;

import android.content.Context;
import android.graphics.drawable.ColorDrawable;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.PopupWindow;
import android.widget.TextView;

/**
 * Created by raimy on 2018-04-19.
 */

public class DetailPopupWindow implements View.OnClickListener{
    private PopupWindow mPopupWindow;
    private Context mContext;
    private View mContentView;
    private Logic mLogic;
    private TextView mTvTotalValue, mTvUsedValue, mTvEmptyValue;

    public DetailPopupWindow(Context context){
        mContext = context;
        Init();
        InitView();
    }

    private void UpdateContent(){
        mTvTotalValue.setText(Integer.toString(mLogic.GetTotalGridSize()));
        mTvUsedValue.setText(Integer.toString(mLogic.GetUsedGridSize()));
        mTvEmptyValue.setText(Integer.toString(mLogic.GetEmptyGridSize()));
    }

    private void InitView(){
        mTvTotalValue = (TextView) mContentView.findViewById(R.id.tv_total_value);
        mTvUsedValue = (TextView) mContentView.findViewById(R.id.tv_used_value);
        mTvEmptyValue = (TextView) mContentView.findViewById(R.id.tv_empty_value);

        Button btn = (Button) mContentView.findViewById(R.id.btn_clean);
        btn.setOnClickListener(this);

        UpdateContent();
    }

    private void Init(){
        mLogic = Logic.ObjCreater.GetInstance();

        mContentView = LayoutInflater.from(mContext).inflate(R.layout.popupwindow_detail, null);
        mPopupWindow = new PopupWindow(mContentView,
                WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.MATCH_PARENT, true);

        mPopupWindow.setTouchable(true);
    // 如果不设置PopupWindow的背景，有些版本就会出现一个问题：无论是点击外部区域还是Back键都无法dismiss弹框
        mPopupWindow.setBackgroundDrawable(new ColorDrawable(mContext.getResources().getColor(R.color.popupwindow)));

    // 设置好参数之后再show
     //mPopupWindow.showAsDropDown(mContentView);
    }

    public  void Show(){
        //mPopupWindow.showAtLocation();
        //mPopupWindow.showAsDropDown(mContentView);
        mPopupWindow.showAtLocation(mContentView, Gravity.RIGHT, 0, 20);
    }

    @Override
    public void onClick(View v) {
        if(v.getId() == R.id.btn_clean){
            mLogic.DoLogicCleanGrid();
        }

    }
}
