
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the THLPRINTERDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// THLPRINTERDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
/*#ifdef THLPRINTERDLL_EXPORTS
#define THLPRINTERDLL_API __declspec(dllexport)
#else
#define THLPRINTERDLL_API __declspec(dllimport)
#endif

// This class is exported from the ThLPrinterDLL.dll
class THLPRINTERDLL_API CThLPrinterDLL {
public:
	CThLPrinterDLL(void);
	// TODO: add your methods here.
};

extern THLPRINTERDLL_API int nThLPrinterDLL;

THLPRINTERDLL_API int fnThLPrinterDLL(void);*/

#ifndef ThLPrinterDLL
#define ThLPrinterDLL

//函数返回值
#define K_OK		0
#define K_FAILED	-1

//串口流控制
#define NONSHAKE	0
#define RTSCTS		1
#define XONOFF		2
#define DTRDSR		3

//串口波特率
#define B2400		1
#define B4800		2
#define B7200		3
#define B9600		4  //default
#define B19200		5
#define B38400		6
#define B57600		7
#define B115200 	8

//通信端口号

#define COM1		1
#define COM2		2
#define COM3		3
#define COM4		4
#define COM5		5
#define COM6		6
#define COM7		7
#define	COM8		8
#define COM9		9
#define COM10		10
#define LTP1		11
#define LTP2		12
typedef int (WINAPI *STATUS_PROC)(BYTE pParam);

#ifdef __cplusplus
extern "C"
{
#endif
//打开打印机端口。    @1
int WINAPI GcOpenPrinter(int iPort,int baud,int hedshk=0);

//关闭打印机端口。           @2
int WINAPI GcClosePrinter();

//当前位置打印字符串(不真正打印,只在该位置填充字符串)。  @3
int WINAPI GcPrintString(char *szStr);

 //启用\取消字节状态返回回调函数。         @4            
int WINAPI GcEnableCallBackFunc(int iEnable=0);

//设置单字节状态返回回调函数 ,仅适用于串口打印机      @5
//(当打印机状态变化时,会上传一个状态字节)
int WINAPI GcSetCallBackFunc(STATUS_PROC pCallBackFunc);

//打印并换行             命令：LF      @6
int WINAPI GcPrintFeedLine();

//打印并回车,打印缓冲区的内容，但不进纸   命令：CR      @7
int WINAPI GcPrintEnter();

//页模式：打印并退回到标准模式
//黑标模式：打印并走黑标到打印其始位置。 命令：FF      @8
int WINAPI GcPrintExitStandardMode();

//頁模式下取消打印数据,在指定打印区域的数据被删除 命令：CAN     @9
int  WINAPI GcCancelPrintPageMode();

//获取打印机状态,iStatus的值为：1～5    命令：DLE EOT     @10
int WINAPI GcRealtimeGetStatus(BYTE iStatus);

//实时响应主机请求,n=1：从错误恢复并从错误出现的行重新开始打印。
//n=2：清除接收缓存区和打印缓存区。命令：DLE ENQ   @11
int WINAPI GcRealtimeResponse(int iRes);

//水平定位,此命令移动打印位置到下一个水平定位点位置。命令：HT  @12
int WINAPI GcMoveHorizontalTAB(); 

//页模式下打印数据,页模式下打印区域中打印缓冲区中全部数据  命令：ESC FF   @13
int WINAPI GcPrintPageMode();          

//设置西文字符右间距以半点为设定单位。命令：ESC SP        @14
int WINAPI GcSetASCIIRightSpace(int iSpace=0);

//设置字符打印方式。命令：ESC ! n             @15
int WINAPI GcSetPrintMode(int mode=0);

// 设置绝对打印位置，设定在[(nL+ nH*256)*0.125 毫米]。 命令:ESC $  @16
int GcSetAbsoluPrintPosition(int nL,int nH);

//允许/禁止用户自定义字符。 命令:ESC %         @17
int WINAPI GcSelectUserDefineSet(int iSet=0);

//设置用户自定义字符n, m分别为起始码和终止码，最多为95个。命令：ESC &   @18
//输入参数例子：32，32，d[0]=0xff，d[1]=0x81
int WINAPI GcUserDefineCharacter(int n,int m,int a, BYTE d[]);

//设置/取消下画线n=0 或 48，取消下划线。默认值line＝0。  命令：ESC -    @19
//line=1 或 49，设定下划线(1点粗)，iLine=2或50，设定下划线(2点粗)    
int WINAPI GcSetUnderLine(int iLine=0);           

//设置字符行距为3.75毫米。命令：ESC 2          @20
int WINAPI GcSelectDefaultLineSpace();

//设定字符行距,n:0~255。命令：ESC 3 n          @21
int WINAPI GcSetLineSpace(int iSpace=30);

//取消用户自定义字符,de:32~126。命令：ESC ?     @22
int WINAPI GcCancelUserDefineCharacter(int de);  

//初始化打印机。命令：ESC @                   @23 
int WINAPI GcInitializePrinter();

//设置水平制表点。命令：ESC D             @24
int WINAPI GcSetHorizonTABPosition(char * string);   

//设定或解除加重打印模式。命令： ESC  E             @25
//当 nNum 的最低有效位(LSB)为 0 时，解除加重打印模式。
//当 nNum 的最低有效位(LSB)为 1 时，设定加重打印模式。
int WINAPI GcEmphasizedPrintSet(int nNum=0);

//设定或解除重叠打印模式。命令： ESC  G             @26
//当 nNum 的最低有效位(LSB)为 0 时，解除重叠打印模式。
//当 nNum 的最低有效位(LSB)为 1 时，设定重叠打印模式。
int WINAPI GcSuperposePrintSet(int nNum=0);

//打印并进纸nNum点行,打印行缓冲器里的数据并向前走纸nNum点行。命令： ESC  J   @27 
int WINAPI GcPrintFeedPaper(int nNum);

//从标准模式切换到页模式。命令：ESC L         @28
int WINAPI GcSelectPageMode();

//选择字符字型。命令：ESC M             @29
//nNum=0, 48	选择字型 A (12×24)
//nNum=1, 49	选择字型 B (9×17)
int WINAPI GcSelectCharacterAB(int nNum);

//选择11个不同国家的不同ASCII字符集。命令：ESC R      @30
int WINAPI GcSelectInternationalCharacterSet(int ch=0);

//从页模式切换到标准模式。命令：ESC S      @31
int WINAPI GcSelectStardardMode();

//在页模式下选择打印方向,参数:direct的值为0~3,48~51。命令：ESC T      @32
int WINAPI GcPagePrintDirection(int direct=0);

//设置/解除顺时针90度旋转,参数x=0,48解除顺时针90度旋转模式。命令：ESC V     @33
//x=1,49 设置顺时针90度旋转模式。     
int WINAPI GcClockwiseRotation90Set(int x=0);

//设置打印页长(76~185mm),打印宽度(72mm),设置打印区域。命令：ESC  W     @34
int WINAPI GcSetPrintAreaPageMode(int X0,int Y0,int iWidth,int iLength);

//设置相对打印位置。[(nL + nH  * 256)*0.125 毫米]。命令：ESC \       @35
int WINAPI GcSetRelativePrintPosition(int nL,int nH);

//选择对齐方式 //nNum=0, 48	左对齐。   命令：ESC  a       @36
//nNum=1, 49 居中  //nNum=2, 50	右对齐
int WINAPI GcSelectJustification(int nNum=0);

//选择测纸检测器以输出缺纸信号。命令：ESC c 3       @37
int WINAPI GcSelectPaperSensor(int nNum=0);

//选择停止打印的测纸传感器,设定纸尽时停止打印。命令：ESC c 4     @38
int WINAPI GcSelectSensorStopPrint(int nNum=0);

//允许、禁止面板开关，当nNum的最低位为0时，使能面板按键。命令：ESC c 5     @39
//最低位为1时，禁止面板按键。默认值nNum=0。
int WINAPI GcSetPanelButtonsEnable(int nNum=0);

//打印并进纸n字符行,打印行缓冲器里的数据并向前走纸iNum字符行。命令：ESC d    @40
int WINAPI GcPrintFeedSomeLines(int iNum); 

//选择字符代码表。         命令：ESC t       @41 
int WINAPI GcSelectCharacterCodeTable(int iNum);

//送黑标纸至打印起始位置。命令：GS FF          @42
int WINAPI GcFeedMarkStartPosition();

//设定字符大小             命令：GS !             @43
int WINAPI GcSelectCharacterSize(int W=0,int H=0);

// 在页模式下对缓冲数据设定绝对垂直打印起始位置。  命令：GS $          @44
// 该命令将绝对打印位置设定在[(nL + nH * 256)*0.125 毫米]。
int GcPageAbsoluVerticalPosition(int nL,int nH);

// 在指定打印纸上用指定模式执行测试打印。  命令：GS ( A          @45
int WINAPI GcExecuteTestPrint(int nNum,int mNum);

//用户自定义命令功能1与2。命令:GS ( E pL pH m=1或2        @46
int WINAPI GcUserDefineCommand(int m);

//设置MemorySwitch,用户设置命令，参数nSwitch为所选择的Memory1～8。
//数组b[]为所选择的memory每个开关值。             命令:GS ( E pL pH m=3        @47
int WINAPI GcSetMemorySwitch(int nSwitch, int b[]);

//读取memoryswitch,用户自定义命令功能4。 命令:GS ( E pL pH m=3      @48
int WINAPI GcGetMemorySwitch(int nSwitch,BYTE iSwitch[11]);

//该命令仅在允许BM传感器时有效。        命令:GS ( F pL pH a=1/2 m    @49
//设置参数a所调整的黑标定位偏移量。   
int WINAPI GcSetAdjustmentValue(int a,int m,int nL,int nH);

//定制打印机控制值。         命令:GS ( M pL pH a n m    @50
int WINAPI GcCustomizeControlValue(int n,int m);

//选择HRI字符的打印位置             命令:GS H n         @51
//nNum=0, 48	不打印,nNum=1, 49	在条形码上方
//nNum=2, 50	在条形码下方,nNum=3, 51	在条形码的上方及下方
int WINAPI GcSelectHRIPosition(int nNum=0);

//传送打印机 ID。           命令:GS I n         @52
int WINAPI GcTransmitPrinterID(BYTE PrinterID);

//用nL 和 nH设定左边空白量。    命令:GS L nL nH         @53
// 左边空白量设置为 [(nL + nH * 256) * 0.125 毫米]
int WINAPI GcSetLeftMargin(int nL=0,int nH=0);


//将打印位置设置为打印行起点。         命令:GS T n         @54
//nNum=0, 48	删除打印缓冲区中的所有数据后设置打印位置为打印行起始点
//nNum=1, 49	将打印缓冲区中的所有数据打印后设置打印位置为打印行起始点
int WINAPI GcSetBeginningPosition(int nNum);

//选择切纸方式及切纸送纸,0≤nNum≤255。命令：GS V m / GS V m n       @55
int WINAPI GcSelectCutPaper(int mNum,int nNum);

//设置打印区域宽度。命令：GS W nL nH               @56
int WINAPI GcSetPrintingAreaWidth(int nL,int nH);

//页模式下设置从当前位置起，相对垂直打印起点位置。命令：GS \ nL nH        @57
//该命令设置的距离从当前位置到 [(nL + nH * 256)*0.125 毫米].
int WINAPI GcPageRelativeVertialPosition(int nL,int nH);

//允许禁止自动状态回复(ASB)。命令：GS a n            @58
int WINAPI GcAutoStatusBackSet(int nNum);

//设置解除平滑模式。   命令：GS b n            @59
int WINAPI GcSmoothingModeSet(int nNum=0);

// 选择HRI(Human Readable Interpretation)字符字型。命令：GS f n        @60
int WINAPI GcSelectHRICharacter(int nNum=0);

//设置条形码高度,参数iNum为设定垂直方向的点数iNum:1~255。命令：GS h n       @61
int WINAPI GcSetBarCodeHeight(int iNum=162);

//条形码系统打印条形码,m为,0~6,65~73。命令：GS k m       @62
int WINAPI GcPrintBarCode(int m,int n,char * string);

//传送状态,iStatus=1,49。命令：GS r       @63
int WINAPI GcTransmitStatus(BYTE iStatus);

//设置条形码的宽度,参数nNum:2~6。命令：GS w n      @64
int WINAPI GcSetBarCodeWidth(int nNum);

//设置汉字字符打印模式组合。命令：FS ! n      @65
int WINAPI GcSetChinesePrintMode(int iMode=0);

//进入汉字打印方式。命令：FS &       @66
int WINAPI GcSelectChineseMode();

//设置/取消汉字字符下划线模式。命令：FS -       @67
int WINAPI GcChineseUnderLineSet(int nNum=0);

//退出汉字打印方式。命令：FS .    @68
int WINAPI GcExitChineseMode();

//定义用户自定义汉字,每次只能定义一个汉字.     命令：FS 2 c1 c2      @69
//c1、c2为通过FS C 所确定的用户自定义汉字区内的区位码.
int WINAPI GcUserDefineChinese(int c1,int c2,int d[]);

//选择用户自定义汉字区 nNum= 0、1、2、48、49、50。命令：FS C n      @70
int WINAPI GcSelectChineseCodeSys(int nNum=0);

//设置汉字字左字右间距L,R:0~32。命令：FS S n1 n2            @71
int WINAPI GcSetChineseLRSpace(int L=0,int R=0);

//设置/取消汉字四倍模式打印。命令：FS W         @72
//parameter最低位为0，取消汉字四倍模式打印。
//parameter最低位为1，设置汉字四倍模式打印。
int WINAPI GcSetChineseQuadrupleSize(int parameter=0);

//iMode最低位为1，打开颠倒打印模式。为0则关闭颠倒打印模式。命令: ESC { n   @73
int WINAPI GcUpsidedownPrintiModeSet(int iMode=0);

//打印NV位图 用m指定的模式打印NV位图n。   命令: FS p n m   @74
/*  m	模式	垂直点密度	水平点密度
0, 48	普通	203.2 dpi	203.2 dpi
1, 49	倍宽	203.2 dpi	101.6 dpi
2, 50	倍高	101.6 dpi	203.2 dpi
3, 51	4倍大小	101.6 dpi	101.6 dpi
dpi: 每 25.4 毫米 {1英寸}打印点数
n 是NV位图的数量(用 FS q 命令定义)*/
int WINAPI GcPrintNVBitImage(int n,int m); 

//定义NV位图。             命令: FS q n           @75
int WINAPI GcDefineNVBitImage(char *szBmpFile);

//在当前位置打印BMP图象。命令:ESC * m           @76
int WINAPI GcPrintBitmap(char *szBmpFile,int m=33);

//下装图形并打印。   命令：GS * 和 GS / m      @77
int WINAPI GcPrintDownloadBitImage(char *szBmpFile,int m=0);

BYTE WINAPI SetByte(BYTE byte, int Index);

#ifdef __cplusplus
}
#endif

#endif