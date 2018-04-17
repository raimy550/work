/**
 * 
 */
package com.raimy.utils.comm;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;

import com.raimy.utils.LogHelper;


import android.R.string;
import android.annotation.SuppressLint;
import android.content.Context;
import android.util.Log;
//import com.android.platform.utils.SerialOp;
import android_serialport_api.SerialPort;

/**
 * @author raimy
 *
 */
public class CommuSerial extends CommuBase{
	private static final String TAG = "CommuSerial";

	private String mDevPath;
	private Integer mBaudRate;
	private SerialPort mSerialPort;
	private Context mContext;
	
	/**
	 * @param devPath 串口名
	 * @param baudRate 波特率
	 */
	public CommuSerial(Context context, String devPath, int baudRate){
		mDevPath = devPath;
		mBaudRate = baudRate;
		mContext = context;
		init(context);
	}

	/* (non-Javadoc)
	 * 0
	 * @0see com.android.peripheralsdk.printer.CommuBase#Write(java.lang.String)
	 */
	@Override
	public boolean Write(String data) {
		// TODO Auto-generated method stub
	    data = data + "\n";
	    ByteBuffer buffer = null;
		buffer = ByteBuffer.wrap(data.getBytes(Charset.forName("GBK")));
		mSerialPort.write(buffer.array());
		return true;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#Connect()
	 */
	@Override
	public boolean Connect() {
		// TODO Auto-generated method stub
		Boolean bRet = false;
		mSerialPort = new SerialPort(mContext.getFilesDir() + "/armeabi/"+"libserial_port.so");
		try {
			LogHelper.logI(getClass().getSimpleName(), "Connect path:"+mDevPath+", baudrate:"+mBaudRate);
			bRet = mSerialPort.Connect(new File(mDevPath), mBaudRate, 0);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return bRet;
	}

	/* (non-Javadoc)
	 * @see com.android.peripheralsdk.printer.CommuBase#DisConnect()
	 */
	@Override
	public boolean DisConnect() {
		// TODO Auto-generated method stub
		mSerialPort.close();
		return true;
	}
	
	public boolean init(Context context)
    { 
		
        initAssetsFile(context,"armeabi");
        return true;
    }

    private void initAssetsFile(Context context,String dir)
    {     
        boolean needCopy = false;

        // 创建data/data目录
        File file = context.getFilesDir();
        String path = file.toString() + "/"+dir+"/";

        // 遍历assets目录下所有的文件，是否在data/data目录下都已经存在
        try {
            String[] fileNames = context.getAssets().list(dir);
            for (int i = 0; fileNames != null && i < fileNames.length; i++) {
                if (!new File(path + fileNames[i]).exists()) {
                    needCopy = true;
                    break;
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

        if (needCopy) {
            copyFilesFassets(context, dir, path);
        }
    }

    //将旧目录中的文件全部复制到新目录
    private void copyFilesFassets(Context context, String oldPath, String newPath) {
        
        LogHelper.logI(getClass().getSimpleName(), oldPath+" -> "+newPath);
        try {

            // 获取assets目录下的所有文件及目录名
            String fileNames[] = context.getAssets().list(oldPath);

            // 如果是目录名，则将重复调用方法递归地将所有文件
            if (fileNames.length > 0) {
                File file = new File(newPath);
                file.mkdirs();
                for (String fileName : fileNames) {
                    copyFilesFassets(context, oldPath + "/" + fileName, newPath + "/" + fileName);
                }
            }
            // 如果是文件，则循环从输入流读取字节写入
            else {
                InputStream is = context.getAssets().open(oldPath);
                FileOutputStream fos = new FileOutputStream(new File(newPath));
                byte[] buffer = new byte[1024];
                int byteCount = 0;
                while ((byteCount = is.read(buffer)) != -1) {
                    fos.write(buffer, 0, byteCount);
                }
                fos.flush();
                is.close();
                fos.close();
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

	@Override
	public boolean Write(byte[] data) {
		// TODO Auto-generated method stub
		mSerialPort.write(data);
		return true;
	}

	@Override
	public byte[] Read() {
		// TODO Auto-generated method stub
		return mSerialPort.read();
	}
}
