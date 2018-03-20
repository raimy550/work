/**
 * 
 */
package com.peripheral.printer.api;

/**打印机公共信息定义
 * @author raimy
 *
 */
public class PrinterUtils {
	
/**
 *默认值 ----------------------------------------------
 */
		public static final String NET_IP_ADDR = "192.168.2.123";//IP地址
		public static final Integer NET_PORT = 9100;//网络端口
		public static final Integer SERIAL_BAUDRAT = 115200 ;//串口波特率
	
/**
 *打印机通信类型 ----------------------------------------------
 */
	public static final int COMMU_NONE = 0;//无
	public static final int COMMU_SERIAL = 1;//串口
	public static final int COMMU_USB = 2; //USB
	public static final int COMMU_BLUETOOTH = 3;//蓝牙
	public static final int COMMU_NET = 4;//网口，wifi
	
/**
 *操作类型0-100 --------------------------------------------------
 */
	
	/**
	 * 操作名：搜索
	 * OpType_Search
	 * 参数说明：
	 * mCommuType：通信类型
	 */
	public static final byte OpType_Search=0;
	
	/**
	 * 操作名：打印位图
	 * OpType_PrintBmp
	 * 参数说明：
	 * mStrParam1：位图路径
	 */
	public static final byte OpType_PrintBmp=1;
	
	/**
	 * 操作名：连接
	 * OpType_Connect
	 * 参数说明：
	 * 串口： 	mIdent:唯一标识设备描述符
	 * 	   	mStrParam1：串口设备描述符
	 *     	mIntParam1：串口波特率
	 * USB：	mIdent:唯一标识："Usb供应商ID-产品ID"
	 * 		mIntParam1：供应商ID
	 *     	mIntParam2：产品ID
	 * 网口：	mIdent:Ip地址
	 * 		mStrParam1：Ip地址，默认为192.168.1.23; 
	 * 	   	mIntParam1：端口号，默认为9100
	 */
	public static final byte OpType_Connect=2;
	
	/**
	 * 操作名：断开
	 * OpType_DisConnect
	 * 参数说明：参考连接操作
	 */
	public static final byte OpType_DisConnect=3;
	
	/**暂不使用
	 *  操作名：连接
	 * OpType_GetInfo
	 * 参数说明：
	 */
	public static final byte OpType_GetInfo=4;
	
	/**
	 * 操作名：停止搜索
	 * OpType_StopSearch
	 * 参数说明：
	 * mCommuType：通信类型
	 */
	public static final byte OpType_StopSearch=5;
	
/**
 *数据返回类型100-200-----------------------------------------------
 */
	/**
	 * 打印机状态
	 * 参数
	 * mStrParam1:
	 */
	public static final byte  BackData_Data=100;
	/**
	 * 打印机状态
	 * 参数
	 * mStrParam1: 
	 */
	public static final byte BackData_PrinterState=101;	
	
/**
 *操作结果-----------------------------------------------
 */
	public static final byte Result_Fail = 0;
	public static final byte Result_Suc = 1;//当操作类型为搜索时， 接收到成功后，调用接口GetSearchList返回搜索列表
	
/**
 *错误码信息----------------------------------------------
 */
	public static final int Err_None = 0;
	//搜索
	public static final int Err_Searching = 1;//正在搜索中，上次的搜索未完成
	public static final int Err_No_Device = 2;//为找到设备
	public static final int Err_Already_Connected = 3;//已连接
}
