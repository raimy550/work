
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

//��������ֵ
#define K_OK		0
#define K_FAILED	-1

//����������
#define NONSHAKE	0
#define RTSCTS		1
#define XONOFF		2
#define DTRDSR		3

//���ڲ�����
#define B2400		1
#define B4800		2
#define B7200		3
#define B9600		4  //default
#define B19200		5
#define B38400		6
#define B57600		7
#define B115200 	8

//ͨ�Ŷ˿ں�

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
//�򿪴�ӡ���˿ڡ�    @1
int WINAPI GcOpenPrinter(int iPort,int baud,int hedshk=0);

//�رմ�ӡ���˿ڡ�           @2
int WINAPI GcClosePrinter();

//��ǰλ�ô�ӡ�ַ���(��������ӡ,ֻ�ڸ�λ������ַ���)��  @3
int WINAPI GcPrintString(char *szStr);

 //����\ȡ���ֽ�״̬���ػص�������         @4            
int WINAPI GcEnableCallBackFunc(int iEnable=0);

//���õ��ֽ�״̬���ػص����� ,�������ڴ��ڴ�ӡ��      @5
//(����ӡ��״̬�仯ʱ,���ϴ�һ��״̬�ֽ�)
int WINAPI GcSetCallBackFunc(STATUS_PROC pCallBackFunc);

//��ӡ������             ���LF      @6
int WINAPI GcPrintFeedLine();

//��ӡ���س�,��ӡ�����������ݣ�������ֽ   ���CR      @7
int WINAPI GcPrintEnter();

//ҳģʽ����ӡ���˻ص���׼ģʽ
//�ڱ�ģʽ����ӡ���ߺڱ굽��ӡ��ʼλ�á� ���FF      @8
int WINAPI GcPrintExitStandardMode();

//�ģʽ��ȡ����ӡ����,��ָ����ӡ��������ݱ�ɾ�� ���CAN     @9
int  WINAPI GcCancelPrintPageMode();

//��ȡ��ӡ��״̬,iStatus��ֵΪ��1��5    ���DLE EOT     @10
int WINAPI GcRealtimeGetStatus(BYTE iStatus);

//ʵʱ��Ӧ��������,n=1���Ӵ���ָ����Ӵ�����ֵ������¿�ʼ��ӡ��
//n=2��������ջ������ʹ�ӡ�����������DLE ENQ   @11
int WINAPI GcRealtimeResponse(int iRes);

//ˮƽ��λ,�������ƶ���ӡλ�õ���һ��ˮƽ��λ��λ�á����HT  @12
int WINAPI GcMoveHorizontalTAB(); 

//ҳģʽ�´�ӡ����,ҳģʽ�´�ӡ�����д�ӡ��������ȫ������  ���ESC FF   @13
int WINAPI GcPrintPageMode();          

//���������ַ��Ҽ���԰��Ϊ�趨��λ�����ESC SP        @14
int WINAPI GcSetASCIIRightSpace(int iSpace=0);

//�����ַ���ӡ��ʽ�����ESC ! n             @15
int WINAPI GcSetPrintMode(int mode=0);

// ���þ��Դ�ӡλ�ã��趨��[(nL+ nH*256)*0.125 ����]�� ����:ESC $  @16
int GcSetAbsoluPrintPosition(int nL,int nH);

//����/��ֹ�û��Զ����ַ��� ����:ESC %         @17
int WINAPI GcSelectUserDefineSet(int iSet=0);

//�����û��Զ����ַ�n, m�ֱ�Ϊ��ʼ�����ֹ�룬���Ϊ95�������ESC &   @18
//����������ӣ�32��32��d[0]=0xff��d[1]=0x81
int WINAPI GcUserDefineCharacter(int n,int m,int a, BYTE d[]);

//����/ȡ���»���n=0 �� 48��ȡ���»��ߡ�Ĭ��ֵline��0��  ���ESC -    @19
//line=1 �� 49���趨�»���(1���)��iLine=2��50���趨�»���(2���)    
int WINAPI GcSetUnderLine(int iLine=0);           

//�����ַ��о�Ϊ3.75���ס����ESC 2          @20
int WINAPI GcSelectDefaultLineSpace();

//�趨�ַ��о�,n:0~255�����ESC 3 n          @21
int WINAPI GcSetLineSpace(int iSpace=30);

//ȡ���û��Զ����ַ�,de:32~126�����ESC ?     @22
int WINAPI GcCancelUserDefineCharacter(int de);  

//��ʼ����ӡ�������ESC @                   @23 
int WINAPI GcInitializePrinter();

//����ˮƽ�Ʊ�㡣���ESC D             @24
int WINAPI GcSetHorizonTABPosition(char * string);   

//�趨�������ش�ӡģʽ����� ESC  E             @25
//�� nNum �������Чλ(LSB)Ϊ 0 ʱ��������ش�ӡģʽ��
//�� nNum �������Чλ(LSB)Ϊ 1 ʱ���趨���ش�ӡģʽ��
int WINAPI GcEmphasizedPrintSet(int nNum=0);

//�趨�����ص���ӡģʽ����� ESC  G             @26
//�� nNum �������Чλ(LSB)Ϊ 0 ʱ������ص���ӡģʽ��
//�� nNum �������Чλ(LSB)Ϊ 1 ʱ���趨�ص���ӡģʽ��
int WINAPI GcSuperposePrintSet(int nNum=0);

//��ӡ����ֽnNum����,��ӡ�л�����������ݲ���ǰ��ֽnNum���С���� ESC  J   @27 
int WINAPI GcPrintFeedPaper(int nNum);

//�ӱ�׼ģʽ�л���ҳģʽ�����ESC L         @28
int WINAPI GcSelectPageMode();

//ѡ���ַ����͡����ESC M             @29
//nNum=0, 48	ѡ������ A (12��24)
//nNum=1, 49	ѡ������ B (9��17)
int WINAPI GcSelectCharacterAB(int nNum);

//ѡ��11����ͬ���ҵĲ�ͬASCII�ַ��������ESC R      @30
int WINAPI GcSelectInternationalCharacterSet(int ch=0);

//��ҳģʽ�л�����׼ģʽ�����ESC S      @31
int WINAPI GcSelectStardardMode();

//��ҳģʽ��ѡ���ӡ����,����:direct��ֵΪ0~3,48~51�����ESC T      @32
int WINAPI GcPagePrintDirection(int direct=0);

//����/���˳ʱ��90����ת,����x=0,48���˳ʱ��90����תģʽ�����ESC V     @33
//x=1,49 ����˳ʱ��90����תģʽ��     
int WINAPI GcClockwiseRotation90Set(int x=0);

//���ô�ӡҳ��(76~185mm),��ӡ���(72mm),���ô�ӡ�������ESC  W     @34
int WINAPI GcSetPrintAreaPageMode(int X0,int Y0,int iWidth,int iLength);

//������Դ�ӡλ�á�[(nL + nH  * 256)*0.125 ����]�����ESC \       @35
int WINAPI GcSetRelativePrintPosition(int nL,int nH);

//ѡ����뷽ʽ //nNum=0, 48	����롣   ���ESC  a       @36
//nNum=1, 49 ����  //nNum=2, 50	�Ҷ���
int WINAPI GcSelectJustification(int nNum=0);

//ѡ���ֽ����������ȱֽ�źš����ESC c 3       @37
int WINAPI GcSelectPaperSensor(int nNum=0);

//ѡ��ֹͣ��ӡ�Ĳ�ֽ������,�趨ֽ��ʱֹͣ��ӡ�����ESC c 4     @38
int WINAPI GcSelectSensorStopPrint(int nNum=0);

//������ֹ��忪�أ���nNum�����λΪ0ʱ��ʹ����尴�������ESC c 5     @39
//���λΪ1ʱ����ֹ��尴����Ĭ��ֵnNum=0��
int WINAPI GcSetPanelButtonsEnable(int nNum=0);

//��ӡ����ֽn�ַ���,��ӡ�л�����������ݲ���ǰ��ֽiNum�ַ��С����ESC d    @40
int WINAPI GcPrintFeedSomeLines(int iNum); 

//ѡ���ַ������         ���ESC t       @41 
int WINAPI GcSelectCharacterCodeTable(int iNum);

//�ͺڱ�ֽ����ӡ��ʼλ�á����GS FF          @42
int WINAPI GcFeedMarkStartPosition();

//�趨�ַ���С             ���GS !             @43
int WINAPI GcSelectCharacterSize(int W=0,int H=0);

// ��ҳģʽ�¶Ի��������趨���Դ�ֱ��ӡ��ʼλ�á�  ���GS $          @44
// ��������Դ�ӡλ���趨��[(nL + nH * 256)*0.125 ����]��
int GcPageAbsoluVerticalPosition(int nL,int nH);

// ��ָ����ӡֽ����ָ��ģʽִ�в��Դ�ӡ��  ���GS ( A          @45
int WINAPI GcExecuteTestPrint(int nNum,int mNum);

//�û��Զ��������1��2������:GS ( E pL pH m=1��2        @46
int WINAPI GcUserDefineCommand(int m);

//����MemorySwitch,�û������������nSwitchΪ��ѡ���Memory1��8��
//����b[]Ϊ��ѡ���memoryÿ������ֵ��             ����:GS ( E pL pH m=3        @47
int WINAPI GcSetMemorySwitch(int nSwitch, int b[]);

//��ȡmemoryswitch,�û��Զ��������4�� ����:GS ( E pL pH m=3      @48
int WINAPI GcGetMemorySwitch(int nSwitch,BYTE iSwitch[11]);

//�������������BM������ʱ��Ч��        ����:GS ( F pL pH a=1/2 m    @49
//���ò���a�������ĺڱ궨λƫ������   
int WINAPI GcSetAdjustmentValue(int a,int m,int nL,int nH);

//���ƴ�ӡ������ֵ��         ����:GS ( M pL pH a n m    @50
int WINAPI GcCustomizeControlValue(int n,int m);

//ѡ��HRI�ַ��Ĵ�ӡλ��             ����:GS H n         @51
//nNum=0, 48	����ӡ,nNum=1, 49	���������Ϸ�
//nNum=2, 50	���������·�,nNum=3, 51	����������Ϸ����·�
int WINAPI GcSelectHRIPosition(int nNum=0);

//���ʹ�ӡ�� ID��           ����:GS I n         @52
int WINAPI GcTransmitPrinterID(BYTE PrinterID);

//��nL �� nH�趨��߿հ�����    ����:GS L nL nH         @53
// ��߿հ�������Ϊ [(nL + nH * 256) * 0.125 ����]
int WINAPI GcSetLeftMargin(int nL=0,int nH=0);


//����ӡλ������Ϊ��ӡ����㡣         ����:GS T n         @54
//nNum=0, 48	ɾ����ӡ�������е��������ݺ����ô�ӡλ��Ϊ��ӡ����ʼ��
//nNum=1, 49	����ӡ�������е��������ݴ�ӡ�����ô�ӡλ��Ϊ��ӡ����ʼ��
int WINAPI GcSetBeginningPosition(int nNum);

//ѡ����ֽ��ʽ����ֽ��ֽ,0��nNum��255�����GS V m / GS V m n       @55
int WINAPI GcSelectCutPaper(int mNum,int nNum);

//���ô�ӡ�����ȡ����GS W nL nH               @56
int WINAPI GcSetPrintingAreaWidth(int nL,int nH);

//ҳģʽ�����ôӵ�ǰλ������Դ�ֱ��ӡ���λ�á����GS \ nL nH        @57
//���������õľ���ӵ�ǰλ�õ� [(nL + nH * 256)*0.125 ����].
int WINAPI GcPageRelativeVertialPosition(int nL,int nH);

//�����ֹ�Զ�״̬�ظ�(ASB)�����GS a n            @58
int WINAPI GcAutoStatusBackSet(int nNum);

//���ý��ƽ��ģʽ��   ���GS b n            @59
int WINAPI GcSmoothingModeSet(int nNum=0);

// ѡ��HRI(Human Readable Interpretation)�ַ����͡����GS f n        @60
int WINAPI GcSelectHRICharacter(int nNum=0);

//����������߶�,����iNumΪ�趨��ֱ����ĵ���iNum:1~255�����GS h n       @61
int WINAPI GcSetBarCodeHeight(int iNum=162);

//������ϵͳ��ӡ������,mΪ,0~6,65~73�����GS k m       @62
int WINAPI GcPrintBarCode(int m,int n,char * string);

//����״̬,iStatus=1,49�����GS r       @63
int WINAPI GcTransmitStatus(BYTE iStatus);

//����������Ŀ��,����nNum:2~6�����GS w n      @64
int WINAPI GcSetBarCodeWidth(int nNum);

//���ú����ַ���ӡģʽ��ϡ����FS ! n      @65
int WINAPI GcSetChinesePrintMode(int iMode=0);

//���뺺�ִ�ӡ��ʽ�����FS &       @66
int WINAPI GcSelectChineseMode();

//����/ȡ�������ַ��»���ģʽ�����FS -       @67
int WINAPI GcChineseUnderLineSet(int nNum=0);

//�˳����ִ�ӡ��ʽ�����FS .    @68
int WINAPI GcExitChineseMode();

//�����û��Զ��庺��,ÿ��ֻ�ܶ���һ������.     ���FS 2 c1 c2      @69
//c1��c2Ϊͨ��FS C ��ȷ�����û��Զ��庺�����ڵ���λ��.
int WINAPI GcUserDefineChinese(int c1,int c2,int d[]);

//ѡ���û��Զ��庺���� nNum= 0��1��2��48��49��50�����FS C n      @70
int WINAPI GcSelectChineseCodeSys(int nNum=0);

//���ú����������Ҽ��L,R:0~32�����FS S n1 n2            @71
int WINAPI GcSetChineseLRSpace(int L=0,int R=0);

//����/ȡ�������ı�ģʽ��ӡ�����FS W         @72
//parameter���λΪ0��ȡ�������ı�ģʽ��ӡ��
//parameter���λΪ1�����ú����ı�ģʽ��ӡ��
int WINAPI GcSetChineseQuadrupleSize(int parameter=0);

//iMode���λΪ1���򿪵ߵ���ӡģʽ��Ϊ0��رյߵ���ӡģʽ������: ESC { n   @73
int WINAPI GcUpsidedownPrintiModeSet(int iMode=0);

//��ӡNVλͼ ��mָ����ģʽ��ӡNVλͼn��   ����: FS p n m   @74
/*  m	ģʽ	��ֱ���ܶ�	ˮƽ���ܶ�
0, 48	��ͨ	203.2 dpi	203.2 dpi
1, 49	����	203.2 dpi	101.6 dpi
2, 50	����	101.6 dpi	203.2 dpi
3, 51	4����С	101.6 dpi	101.6 dpi
dpi: ÿ 25.4 ���� {1Ӣ��}��ӡ����
n ��NVλͼ������(�� FS q �����)*/
int WINAPI GcPrintNVBitImage(int n,int m); 

//����NVλͼ��             ����: FS q n           @75
int WINAPI GcDefineNVBitImage(char *szBmpFile);

//�ڵ�ǰλ�ô�ӡBMPͼ������:ESC * m           @76
int WINAPI GcPrintBitmap(char *szBmpFile,int m=33);

//��װͼ�β���ӡ��   ���GS * �� GS / m      @77
int WINAPI GcPrintDownloadBitImage(char *szBmpFile,int m=0);

BYTE WINAPI SetByte(BYTE byte, int Index);

#ifdef __cplusplus
}
#endif

#endif