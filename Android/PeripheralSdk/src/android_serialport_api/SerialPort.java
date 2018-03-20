/**
 * 
 */
package android_serialport_api;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;

import android.content.Context;
import android.util.Log;

import com.raimy.utils.LogHelper;

/**
 * @author raimy
 *
 */
public class SerialPort {
	private static final String TAG = "SerialPort";

    /*
     * Do not remove or rename the field mFd: it is used by native method close();
     */
    private FileDescriptor mFd;//文件描述
    private FileInputStream mFileInputStream;
    private FileOutputStream mFileOutputStream;
    private static boolean sLoaded = false;
    public SerialPort(String libPath){
//    	if (!sLoaded) {
//    		System.load(libPath);
//    		sLoaded = true;
//		}	   	
    }
    
    /**
     *获得一个窗口 
     * @param device 设备
     * @param baudrate 波特率
     * @param flags 标志
     * @throws SecurityException
     * @throws IOException
     */
    public Boolean Connect(File device, int baudrate, int flags) throws SecurityException, IOException {

        /* Check access permission */ //检查权限
    	Boolean bRet = false;
//        if (!device.canRead() || !device.canWrite()) {
//            try {
//                //如果丢失权限，就再获取权限
//                /* Missing read/write permission, trying to chmod the file */
//                Process su;
//                su = Runtime.getRuntime().exec("/system/bin/su");
//                String cmd = "chmod 666 " + device.getAbsolutePath() + "\n" + "exit\n";
//                //写命令
//                su.getOutputStream().write(cmd.getBytes());
//                if ((su.waitFor() != 0) || !device.canRead() || !device.canWrite()) {
//                    throw new SecurityException();
//                }
//            } catch (Exception e) {
//                e.printStackTrace();
//                throw new SecurityException();
//            }
//        }
        //打开设备，这里面调用jni 的open方法
        mFd = open(device.getAbsolutePath(), baudrate, flags);
        if (mFd == null) {
            LogHelper.logE(TAG, "native open fail :"+device.getAbsolutePath());
            throw new IOException();
        }else {
        	LogHelper.logI(TAG, "native open sucess :" + device.getAbsolutePath());
		}
        mFileInputStream = new FileInputStream(mFd);
        mFileOutputStream = new FileOutputStream(mFd);
        bRet = true;
        return bRet;
    }

    // Getters and setters
    public FileInputStream getInputStream() {
        return mFileInputStream;
    }

    public FileOutputStream getOutputStream() {
        return mFileOutputStream;
    }
    
    
    public byte[] read() {
		byte[] btTmpRecv = new byte[1024];
		Arrays.fill(btTmpRecv, (byte) 0);
		try {
			int size = mFileInputStream.read(btTmpRecv);
			byte[] btRecv = new byte[size];
			System.arraycopy(btTmpRecv, 0, btRecv, 0, size);
			//Log.i(TAG, "收到串口数据："+ParserUtils.bytes2HexString(btRecv));
			return btRecv;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	public synchronized void write(byte[] bytes) {
		try {
			mFileOutputStream.write(bytes);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			Log.i(TAG, "mFileOutputStream write:" + "异常");
			e.printStackTrace();
		}
	}

    //============== JNI=========================================
    /**
     * 打开串口设备的方法
     * @param path 设备的绝对路径
     * @param baudrate 波特率
     * @param flags 标志
     * @return
     */
    private native static FileDescriptor open(String path, int baudrate, int flags);
    //关闭设备
    public native void close();
    //加载库文件
    static {
        System.loadLibrary("serial_port");
    }
}
