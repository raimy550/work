/******************************************************************* 
 *  当前版本:0.5.0.1128 
 *  作者: lakerszhy(lakerszhy@gmail.com)
 *  日期: 2013-11-28
 ******************************************************************/  

#ifdef PRINTERDLL_EXPORTS
#define PRINTERDLL_API __declspec(dllexport)
#else
#define PRINTERDLL_API __declspec(dllimport)
#endif

//打印机类型
enum PRINTER_TYPE {POS_OPEN_BYUSB_PORT, POS_OPEN_NETPORT};

//打印机状态
enum PRINTER_STATUS {NORMAL, LESS_PAPER, NO_PAPER, NOT_CONNECT, CUTTER_ERROR, ABNORMAL_TEMPERATURE, UNKOWN};

//HRI打印位置
enum HRI_POSITION {NOT_PRINT, ABOVE_BARCODE, BELOW_BARCODE, ABOVE_BELOW_BARCODE};

//字符模式
#define CHARACTER_MODEL_COMPRESSION		0x00000001 //压缩ASCII
#define CHARACTER_MODEL_BOLDFACE		0x00000008 //加粗
#define CHARACTER_MODEL_DOUBLE_HEIGHT	0x00000010 //双字高
#define CHARACTER_MODEL_DOUBLE_WIDTH	0x00000020 //双字宽
#define CHARACTER_MODEL_UNDERLINE		0x00000080 //下划线

#define POS_SUCCESS                     1001 // 函数执行成功
#define POS_FAIL                        1002 // 函数执行失败

#define POS_ERROR_INVALID_HANDLE        1101 // 端口或文件的句柄无效
#define POS_ERROR_INVALID_PARAMETER     1102 // 参数无效

extern "C" 
{
	/************************************************************************/
	//描述：打开打印机端口      
	//参数：szPrinterName：[in] 指向以 null 结尾的打印机名称或端口名称
	//			如果printerType为POS_OPEN_BYUSB_PORT，szPrinterName为"USB"
	//			如果printerType为POS_OPEN_NETPORT，szPrinterName为打印机ip地址
	//		printerType:[in] 打印机类型,POS_OPEN_BYUSB_PORT或POS_OPEN_NETPORT
	// 返回值：成功返回POS_SUCCESS
	//         失败返回POS_ERROR_INVALID_PARAMETER或INVALID_HANDLE_VALUE
	/************************************************************************/
	PRINTERDLL_API int Wz_Open(const char* szPrinterName, enum PRINTER_TYPE printerType);

	/************************************************************************/
	//描述：关闭打印机端口
	//参数：无
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_Close();

	/************************************************************************/
	//描述：复位打印机
	//参数：无
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_Reset();

	/************************************************************************/
	//描述：打印szText中的内容
	//参数：szText：[in] 需要打印的内容
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_Print(const char* szText);

	/************************************************************************/
	//描述：打印机走纸nRows行
	//参数：nRows：[in] 走纸行数, 0-20之间
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_FreedPaper(const int nRows);

	/************************************************************************/
	//描述：打开钱箱
	//参数：无
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_OpenCashBox();

	/************************************************************************/
	//描述：打印EAN13码
	//参数：szCode：[in] 需要打印的13位条码
	//		hriPosition：[in] HRI打印位置
	//					 NOT_PRINT：不打印HRI
	//					 ABOVE_BARCODE：HRI在条码之上
	//				 	 BELOW_BARCODE：HRI在条码下面
	//					 ABOVE_BELOW_BARCODE：在条码上面和下面都打印HRI
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_PrintBarCode(const char* szCode, enum HRI_POSITION hriPosition);

	/************************************************************************/
	//描述：设置条码高度为nHeight（nHeight/8mm即nHeight/203英寸）
	//参数：nHeight：[in] 条码高度，0-255，默认216
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetBarCodeHeight(const int nHeight);

	/************************************************************************/
	//描述：设置条码宽度为nWidth
	//参数：nWidth：[in] 条码高度，2-6，默认2
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetBarCodeWidth(const int nWidth);

	/************************************************************************/
	//描述：启用/禁用走纸键
	//参数：bEnable：[in] 是否启用走纸键
	//				 true： 启用走纸键
	//				 false：禁用走纸键
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_EnableFeedButton(bool bEnable);

	/************************************************************************/
	//描述：切纸
	//参数：无
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_CutPaper();

	/************************************************************************/
	//描述：设置行间距为nSpace/203英寸（nSpace/8mm）
	//	    当nSpace太小时，行高等于字符高度
	//      当nSpace超出指定范围，此命令被忽略
	//参数：nSpace：[in] 行间距 0-255，默认27（3.37mm）
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetLineSpace(const int nSpace);

	/************************************************************************/
	//描述：设置字符右间距为nSpace点
	//      当nSpace超出指定范围，此命令被忽略
	//参数：nSpace：[in] 行间距 0-32，默认0
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetWordSpace(const int nSpace);

	/************************************************************************/
	//描述：获得打印机状态
	//参数：无
	//返回值：NORMAL：打印机正常
	//		  LESS_PAPER：纸将尽
	//		  NO_PAPER：缺纸
	//		  NOT_CONNECT：打印机未连接
	//		  CUTTER_ERROR：切刀错误
	//		  ABNORMAL_TEMPERATURE：打印机温度异常
	//		  UNKOWN：未知错误
	/************************************************************************/
	PRINTERDLL_API int Wz_GetStatus();

	/************************************************************************/
	//描述：设置字符模式
	//参数：dwCharModel：[in] 可以为以下值：
	//			CHARACTER_MODEL_COMPRESSION：	压缩ASCII
	//			CHARACTER_MODEL_BOLDFACE：		加粗
	//			CHARACTER_MODEL_DOUBLE_HEIGHT：	双字高
	//			CHARACTER_MODEL_DOUBLE_WIDTH：	双字宽
	//			CHARACTER_MODEL_UNDERLINE：		下划线
	//返回值：成功返回POS_SUCCESS
	//		  失败返回POS_FAIL或POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetCharModel(const DWORD dwCharModel);

};