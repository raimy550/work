package com.android.autotest.utils;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.icu.text.DateFormat;
import android.icu.text.MessageFormat;
import android.view.ViewGroup;

/**
 * Created by raimy on 2018-04-11.
 */

public class AlertDlg {
    private AlertDialog mDlg;
    private AlertDialog.Builder mBuilder;
    private String mStrMsg;
    private int mMsgId;
    private Context mContext;
    private IAlertDlgCallBack mAlertDlgCallBack;
    private int mType ;
    private int mBtnCount;

    public final static int Btn_One= 1;
    public final static int Btn_Two= 2;
    public final static int Btn_Three= 3;

    public final static int RET_NO=0;
    public final static int RET_YES=1;
    public final static int RET_CANCLE=2;

    public AlertDlg(Context context, IAlertDlgCallBack iAlertDlgCallBack){
        mContext = context;
        mAlertDlgCallBack = iAlertDlgCallBack;
        mStrMsg = "";
    }

    public interface IAlertDlgCallBack{
        public void OnAlertDlgCallBack(int type, int result);
    }

    public AlertDlg SetOpts(int nType, String strMsg, int btnCount){
        mType = nType;
        mStrMsg = strMsg;
        mBtnCount = btnCount;
        return this;
    }

    public AlertDlg SetOpts(int nType, int msgId, int btnCount){
        mType = nType;
        mMsgId = msgId;
        mBtnCount = btnCount;
        return this;
    }

    public void Show(){
        mBuilder = new AlertDialog.Builder(mContext);
        if(!mStrMsg.equals("")){
            mBuilder.setMessage(mStrMsg);
        }else{
            mBuilder.setMessage(mMsgId);
        }

        if(mBtnCount == Btn_One || mBtnCount == Btn_Three ){
            mBuilder.setNeutralButton("取消", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    mAlertDlgCallBack.OnAlertDlgCallBack(mType, RET_CANCLE);
                    mDlg.dismiss();
                }
            });
        }

        if(mBtnCount == Btn_Two || mBtnCount == Btn_Three){
            mBuilder.setPositiveButton("成功", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    mAlertDlgCallBack.OnAlertDlgCallBack(mType, RET_YES);
                    mDlg.dismiss();
                }
            });
            mBuilder.setNegativeButton("失败", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    mAlertDlgCallBack.OnAlertDlgCallBack(mType, RET_NO);
                    mDlg.dismiss();
                }
            });
        }
        mDlg = mBuilder.create();
        mDlg.show();
        mDlg.getWindow().setLayout(500, ViewGroup.LayoutParams.WRAP_CONTENT);
    }



}
