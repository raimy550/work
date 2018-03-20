// usbandcomtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LoadDll.h"
#include "PrintSamples.h"
extern POS_Open				VC_POS_Open;//打开端口
extern POS_Close			VC_POS_Close;//关闭端口
extern POS_RTQueryStatus	VC_POS_RTQueryStatus;//实时状态查询
extern POS_NETQueryStatus	VC_POS_NETQueryStatus;//网络接口的状态查询
extern POS_StartDoc			VC_POS_StartDoc;//启动一个文档
extern POS_EndDoc			VC_POS_EndDoc;//结束一个文档
extern POS_BeginSaveFile	VC_POS_BeginSaveFile;//启动保存数据到文件
extern POS_EndSaveFile		VC_POS_EndSaveFile;//结束保存数据到文件
extern POS_GetVersionInfo	VC_POS_GetVersionInfo;//获取当前动态库版本
extern POS_WriteFile        VC_POS_WriteFile;



#if 0
int _tmain(int argc, _TCHAR* argv[])
{
	if ( false == LoadPosdll() )
	{
		// 如果动态库加载失败, 则退出
		printf("加载动态库失败！");
		getchar();
		return false;
	}

	//HANDLE handle = VC_POS_Open("COM1",9600,8,1,0,3);
	HANDLE handle = VC_POS_Open("USB001",0,0,0,0,POS_OPEN_BYUSB_PORT);
	if(handle == INVALID_HANDLE_VALUE)
	{
		printf("打开端口失败");
		HANDLE USBPRINTER = CreateFile(_T("\\\\.\\COM1"), 
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, 
			OPEN_EXISTING,
			0, NULL );
		if (USBPRINTER == INVALID_HANDLE_VALUE)
		{
			printf("创建端口失败");
			USBPRINTER = CreateFile(_T("COM1"), 
				GENERIC_READ | GENERIC_WRITE,
				0, NULL, 
				OPEN_EXISTING,
				0, NULL );
			if (USBPRINTER == INVALID_HANDLE_VALUE)
			{
				printf("第二次创建端口失败");
			}
			
			getchar();
		}
		else
		{
			int in = VC_POS_WriteFile(USBPRINTER, "test", 4);
			if (in == POS_SUCCESS)
			{
				VC_POS_WriteFile(USBPRINTER, "test", 4);
				VC_POS_WriteFile(USBPRINTER, "test", 4);
				VC_POS_WriteFile(USBPRINTER, "test", 4);
				printf("over");
				getchar();
			}
		}

	}
	char Status = 0;
	int nRet = VC_POS_RTQueryStatus(&Status);
	if (POS_FAIL == nRet)
	{
		printf("查询串口失败");
	}
	else
	{	
		int iBits[8];
		for (int i = 0; i < 8; i++)
		{
			iBits[i] = (Status >> i) & 0x01;
		}
		if(Status == 1)
		{
			printf("一切正常！");
			PrintInStandardMode56();
		}
		else
		{
			
			if (iBits[0] == 0)
			{
				printf("有钱箱打开！");
			}

			if (iBits[1] == 1)
			{
				printf("打印机脱机！");
			}

			if (iBits[2] == 1)
			{
				printf("上盖打开！");
			}

			if (iBits[3] == 1)
			{
				printf("正在进纸！");
			}

			if (iBits[4] == 1)
			{
				printf("打印机出错！");
			}

			if (iBits[5] == 1)
			{
				printf("切刀出错！");
			}

			if (iBits[6] == 1)
			{
				printf("纸将尽！");
			}

			if (iBits[7] == 1)
			{
				printf("缺纸！");
			}
		}
	}
getchar();
	return 0;
}

#elif 1//ＣｒｅａｔｅＦｉｌｅ

#include <windows.h>
#include <string>
#include <IOSTREAM>
using namespace std;

typedef struct DataInfo
{
	string Port;  //串口端口号
	int BawdRate;//波特率
	int DataBits;  //数据位
	char Parity;  //校验位
	int ReceiveBuffer;  //缓冲区
	int StopBits;//停止位
}PrintDevice;

int   WriteData(string meg);
int InitPort(PrintDevice &device);
void InitializeDevicePar(PrintDevice &device);
HANDLE hPort=NULL;  //句柄
using namespace std;  
int bmpwidth,bmpheight,linebyte;  
unsigned char *pBmpBuf;  //存储图像数据  
#if 1
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace std;
using namespace Gdiplus;

int adsa() {
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

	wstring infilename(L"1.jpg");
	string outfilename("color.txt");

	Bitmap* bmp = new Bitmap(infilename.c_str());
	UINT height = bmp->GetHeight();
	UINT width  = bmp->GetWidth();
	cout << "width " << width << ", height " << height << endl;

	Color color;
	ofstream fout(outfilename.c_str());

	for (UINT y = 0; y < height; y++)
		for (UINT x = 0; x < width ; x++) {
			bmp->GetPixel(x, y, &color);
			fout << x << "," << y << ";"
				<< (int)color.GetRed()   << ","
				<< (int)color.GetGreen() << ","
				<< (int)color.GetBlue()  << endl;
		}

		fout.close();

		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return 0;
}
#else

BYTE *RmwRead8BitBmpFile2Img(const char * filename,int *width,int *height){
	FILE *binFile;
	BYTE *pImg=NULL;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER bmpHeader;
	BOOL isRead=TRUE;
	int linenum,ex; //linenum:一行像素的字节总数，包括填充字节 

	//open file
	if((binFile=fopen(filename,"rb"))==NULL) return NULL;

	//read struts
	if(fread((void *)&fileHeader,1,sizeof(fileHeader),binFile)!=sizeof(fileHeader)) isRead=FALSE;
	if(fread((void *)&bmpHeader,1,sizeof(bmpHeader),binFile)!=sizeof(bmpHeader)) isRead=FALSE;

	//问，这里的判断是为了避免什么样问题
	if(isRead==FALSE||fileHeader.bfOffBits<sizeof(fileHeader)+sizeof(bmpHeader)){
		fclose(binFile);
		return NULL;
	}

	//read image info
	*width=bmpHeader.biWidth;
	*height=bmpHeader.biHeight;
	linenum=(*width*1+3)/4*4;
	ex=linenum-*width*1;         //每一行的填充字节

	fseek(binFile,fileHeader.bfOffBits,SEEK_SET);
	pImg=new BYTE[(*width)*(*height)];
	if(pImg!=NULL){
		for(int i=0;i<*height;i++){
			int r=fread(pImg+(*height-i-1)*(*width),sizeof(BYTE),*width,binFile);
			if(r!=*width){
				delete pImg;
				fclose(binFile);
				return NULL;
			}
			fseek(binFile,ex,SEEK_CUR);
		}
	}
	fclose(binFile);
	return pImg;
}
#endif

int main()
{
	PrintDevice device;
	InitializeDevicePar(device);  //初始化打印机参数
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

	wstring infilename(L"generate.bmp");
	//GetEncoderClassCLSID

	Bitmap* bmp = new Bitmap(infilename.c_str());
	UINT height = bmp->GetHeight();
	UINT width  = bmp->GetWidth();

	InitPort(device);  //初始化打印机端口
	//readBmp("123.bmp");
	
	BYTE *byte;// = RmwRead8BitBmpFile2Img("123.bmp", &w, &h);
	//////////////////////////////////////////////////////////////////////////
	DWORD iBytesLength;
	string s;
	char chInitCode[] = "\x0D\x1B\x40";//初始化打印机
	bool bSuccess = WriteFile(hPort, chInitCode, (DWORD)3L, &iBytesLength, NULL);
	if (!bSuccess || !iBytesLength)
	{
		printf("打印机缺纸，脱机或其它错误发生!"); 
		
		return 0;
	}
	//进纸到撕纸位置
	//char chMoveToCut[] = "\x0A\x1D\x56\x41\x00";
	//WriteFile(hPort, chMoveToCut, (DWORD)5L, &iBytesLength, NULL);	
	//演示GS v
	/*s = _T("\nGS v 0 绘制BMP演示\n");
	WriteData(s);*/
	char sz[] = "\x1D\x2F\x03";
	WriteFile(hPort, sz, (DWORD)3L, &iBytesLength, NULL);

	char sz1[] = "\x1B\x33\x00";
	WriteFile(hPort, sz1, (DWORD)3L, &iBytesLength, NULL);
	//CloseHandle(hPort);//关闭端口
#if 1
	BYTE data[1] = {0};
	BYTE chEscBitmapCode2[5];//"\x1D\x76\x30\x00\x00\x00\x00\x00";

	chEscBitmapCode2[0] = 0x1B;
	chEscBitmapCode2[1] = 0x2A;
	chEscBitmapCode2[2] = 0x21;
	chEscBitmapCode2[3] = width%256;
	chEscBitmapCode2[4] = width/256;
	for (int i = 0; i < (bmp->GetHeight() / 24 + 1); i++)  
	{  
		//设置模式为位图模式  
		WriteFile(hPort, chEscBitmapCode2, 5, &iBytesLength, NULL);
		//循环宽  
		for (int j = 0; j < bmp->GetWidth(); j++)  
		{  
			for (int k = 0; k < 24; k++)  
			{  
				if (((i * 24) + k) < bmp->GetHeight())  // if within the BMP size  
				{  
					Color color;
					bmp->GetPixel(j, (i * 24) + k, &color);  
					if (color.GetR() == 0)  
					{  
						data[k / 8] += (BYTE)(128 >> (k % 8));  

					}  
				}  
			}  
			//一次写入一个data，24个像素  
			WriteFile(hPort, data, 3, &iBytesLength, NULL);

			data[0] = 0x00;  
			data[1] = 0x00;  
			data[2] = 0x00;    // Clear to Zero.  
		}  

		//换行，打印第二行  
		BYTE data2[] = { 0xA };  
		WriteFile(hPort, data2, 1, &iBytesLength, NULL); 
	} // data  
#else

	int iBitmapWidth = bmp->GetWidth();
	int iBitmapHeight = bmp->GetHeight();
	char chEscBitmapCode2[] = "\x1D\x76\x30\x00\x00\x00\x00\x00";

	chEscBitmapCode2[4] = (char)((iBitmapWidth / 8) % 256);
	chEscBitmapCode2[5] = (char)((iBitmapWidth / 8) / 256);
	chEscBitmapCode2[6] = (char)(iBitmapHeight % 256);
	chEscBitmapCode2[7] = (char)(iBitmapHeight / 256);

	WriteFile(hFile, chEscBitmapCode2, (DWORD)8L, &iBytesLength, NULL);	

#endif
// 	chEscBitmapCode2[4] = (char)((w / 8) % 256);
// 	chEscBitmapCode2[5] = (char)((w / 8) / 256);
// 	chEscBitmapCode2[6] = (char)(h % 256);
// 	chEscBitmapCode2[7] = (char)(h / 256);
	//for (int i = 0; i < ((bmp->GetHeight() + 7) / 8); i++)  

// 	for (int i = 0; i < ((bmp->GetHeight() + 7) / 8); i++)  
// 	{  
// 		WriteFile(hPort, chEscBitmapCode2, 5, &iBytesLength, NULL);
// 		//_serialPort.Write(escBmp, 0, escBmp.Length);  
// 
// 		for (int j = 0; j < bmp->GetWidth(); j++)  
// 		{  
// 			for (int k = 0; k < 8; k++)  
// 			{  
// 		
// 				if (((i * 8) + k) < bmp->GetHeight())  // if within the BMP size  
// 				{  
// 					Color color;
// 					bmp->GetPixel(j, (i * 8) + k, &color);  
// 					if (color.GetRed() == 0)  
// 					{ 
// 						data[0] += (BYTE)(128 >> k);  
// 					}  
// 				}  
// 			}  
// 			WriteFile(hPort, data, 1, &iBytesLength, NULL);
// 			
// 			data[0] = 0x00; // Clear to Zero.  
// 		}  
// 		BYTE by =  0x0A;
// 		WriteFile(hPort, &by, 1, &iBytesLength, NULL);
// 	}
	
	delete bmp;
	GdiplusShutdown(gdiplustoken);
	return 0;
	//for(int y=0;y<6;y++)
	//{
	//	for (int i=5;i<48;i++)
	//		chEscBitmapCode2[i]=logo[(i-5)+(y*48)];
	//	chEscBitmapCode2[48]=10;  //LF走纸
	//	WriteFile(hPort, chEscBitmapCode2, (DWORD)54L, &iBytesLength, NULL);	

	//}
	//WriteFile(hPort, chEscBitmapCode2, (DWORD)8L, &iBytesLength, NULL);	

 	//for (int h = 0; h < w*h; h++)
 	//{
// 		for (int w = 0; w < (bmpwidth / 8) ; w++)
// 		{
			//char *Temp = pBmpBuf[h][w];
			//WriteFile(hPort, byte, (DWORD)w*h, &iBytesLength, NULL);			
		//}
	//}


	//////////////////////////////////////////////////////////////////////////
	

	////////////////////////////打印头信息开始//////////////////////////////////
	//设置中文粗体 + 四倍大小, "FS ! n", n = 4 + 8+128, \x1C\x21放大字体 \\0a打印并换行
	s= "\x1C\x21\x8C";
	WriteData(s);

	s="商店-上海鼎捷\x0A";
	WriteData(s); //打印

	//取消中文放大设置
	//DWORD iBytesLength = 0;\\取消放大
	char chSetCode[] = "\x1C\x21\x0";
	WriteFile(hPort, chSetCode, (DWORD)3L, &iBytesLength, NULL);
	//////////////////////////打印头信息结束///////////////////////////////////////

	//////////////////////////打印商品开始////////////////////////////////////////
	s="山东苹果\t4.00\t2x\t8.00元\x0A";
	WriteData(s); //打印
	s="福建橘子\t5.00\t3x\t15.00元\x0A";
	WriteData(s); //打印
	s="\x0A";
	WriteData(s); //打印
	////////////////////////////打印商品结束//////////////////////////////////////
	s="小计:23.00元\x0A";
	WriteData(s); //打印

	//进纸到切纸位置，再切纸，"GS V m n", n=需要多进的行数
	s= "\x1D\x56\x41\x01";  //m=65 65是全切,66是半切， n=1 0<=n<=255
	WriteData(s); //打印

	CloseHandle(hPort);//关闭端口

	return 0;
}
void InitializeDevicePar(PrintDevice &device)
{
	device.Port="COM1";
	device.BawdRate=9600;
	device.DataBits=8;
	device.StopBits=ONESTOPBIT;
	device.Parity=NOPARITY;  //NONE
	device.ReceiveBuffer=256;
}
int InitPort(PrintDevice &device)
{
	hPort = CreateFile(device.Port.c_str(), GENERIC_READ | GENERIC_WRITE,
		0, NULL, 
		OPEN_EXISTING,
		0, NULL );

	if (hPort == INVALID_HANDLE_VALUE) 
	{   // 打开端口失败
		printf("打开端口失败");
		getchar();
		return false;
	}
	else
	{ 
		//设置端口缓冲
		SetupComm(hPort, 1024, 1024); 

		// 设定通讯端口超时参数
		COMMTIMEOUTS tmouts;
		tmouts.ReadIntervalTimeout = 100;
		tmouts.ReadTotalTimeoutMultiplier = 100;
		tmouts.ReadTotalTimeoutConstant = 100;
		tmouts.WriteTotalTimeoutConstant = 100;
		tmouts.WriteTotalTimeoutMultiplier = 100;
		SetCommTimeouts(hPort, &tmouts);

		//设定通讯端口通讯参数
		DCB dcb;
		BOOL bol = TRUE;

		//dcb.DCBlength = sizeof(dcb);
		
		bol=GetCommState(hPort, &dcb);
		dcb.BaudRate = device.BawdRate;
		dcb.ByteSize =device.DataBits;
		dcb.StopBits = device.StopBits;
		dcb.Parity = device.Parity;
		
		//bol = SetCommState(hPort, &dcb); //配置串口
		// 清除通讯端口缓存
		PurgeComm(hPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);

		// 初始化重叠IO对象
		OVERLAPPED m_OverlappedRead;
		OVERLAPPED m_OverlappedWrite;
		HANDLE m_hStopCommEvent;
		HANDLE m_hDataReady;
		memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
		m_OverlappedRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));
		m_OverlappedWrite.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		// 初始化事件对象
		m_hStopCommEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		m_hDataReady = CreateEvent(NULL, FALSE, FALSE, NULL);

		//初始化打印ESC @
		DWORD iBytesLength;
		char chInitCode[] = "\x0D\x1B\x40";
		WriteFile(hPort, chInitCode, (DWORD)3L, &iBytesLength, NULL);
	}

	return 0;

}
int   WriteData(string meg)
{
	DWORD dwWrite;
	WriteFile(hPort, meg.c_str(), (DWORD)meg.length(), &dwWrite, NULL);
	return 0;
}
#elif 0
#include "ThLPrinterDLL.h"
#pragma comment(lib, "ThLPrinterDLL.lib")
void main()
{
	int res = GcOpenPrinter(1, 4);
	if (res == 0)
	{
		printf("独占成功");

	}
	else
	{
		printf("独占失败");
	}
	getchar();
}
#else

void main()
{
	
	
}
#endif