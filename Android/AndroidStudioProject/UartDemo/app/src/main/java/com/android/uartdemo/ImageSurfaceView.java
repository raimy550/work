package com.android.uartdemo;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Rect;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.LinearLayout;

import java.util.ArrayList;
import java.util.List;


public class ImageSurfaceView extends SurfaceView implements SurfaceHolder.Callback{
    private int imgId = -1;
    private List<String> mList            =    null;
    private SurfaceHolder         mSurfaceHolder     =     null;
    private static Matrix matrix             =     new Matrix();
    private int mwidth, mhight;

    public ImageSurfaceView(Context context, int width, int hight) {
        super(context);
        mList = new ArrayList<String>();
        mList.add("/data/1.jpg");
        mList.add("/data/2.bmp");
        mList.add("/data/3.bmp");
        mList.add("/data/4.bmp");

        mSurfaceHolder = getHolder();
        mSurfaceHolder.addCallback(this);
        mwidth = width;
        mhight = hight;
        LinearLayout.LayoutParams gpioDirBtnParams = new LinearLayout.LayoutParams(width, hight);
        gpioDirBtnParams.setMargins(100, 0, 0, 0);
        setLayoutParams(gpioDirBtnParams);
        setVisibility(INVISIBLE);
    }
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width,    int height) {}

    public void update(int id) {
        drawImg(id - 1);
    }
    //图像创建时
    @Override
    public void surfaceCreated(SurfaceHolder holder) {
    }
    //视图销毁时
    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }
    //画图方法
    private void drawImg(int id){
        Canvas canvas = mSurfaceHolder.lockCanvas();
        if(canvas == null || mSurfaceHolder == null){
            return;
        }
        Bitmap bitmap  = null;
        switch (id) {
            case 0:
                bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a1);
                break;
            case 1:
                bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a2);
                break;
            case 2:
                bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a3);
                break;
            case 3:
                bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.a4);
                break;
        }
        try{

            if(bitmap!=null){
                //画布宽和高
                int height = mhight;//getHeight();
                int width  = mwidth; //getWidth();
                //生成合适的图像
                bitmap = getReduceBitmap(bitmap,mwidth,mhight);

                Paint paint = new Paint();
                paint.setAntiAlias(true);
                paint.setStyle(Style.FILL);
                //清屏
                paint.setColor(Color.BLACK);
                canvas.drawRect(new Rect(0, 0, mwidth,mhight), paint);
                //Log.d("ImageSurfaceView_IMG",path);
                //画图
                canvas.drawBitmap(bitmap, matrix, paint);
            }
            //解锁显示
            mSurfaceHolder.unlockCanvasAndPost(canvas);
        }catch(Exception ex){
            Log.e("ImageSurfaceView",ex.getMessage());
            return;
        }finally{
            //资源回收
            if(bitmap!=null){
                bitmap.recycle();
            }
        }
    }
    //缩放图片
    private Bitmap getReduceBitmap(Bitmap bitmap ,int w,int h){
        int     width     =     bitmap.getWidth();
        int     hight     =     bitmap.getHeight();
        Matrix     matrix     =     new Matrix();
        float     wScake     =     ((float)w/width);
        float     hScake     =     ((float)h/hight);
        matrix.postScale(wScake, hScake);
        return Bitmap.createBitmap(bitmap, 0,0,width,hight,matrix,true);
    }

}