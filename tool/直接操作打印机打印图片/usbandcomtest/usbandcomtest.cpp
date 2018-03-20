// usbandcomtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LoadDll.h"
#include "PrintSamples.h"
extern POS_Open				VC_POS_Open;//�򿪶˿�
extern POS_Close			VC_POS_Close;//�رն˿�
extern POS_RTQueryStatus	VC_POS_RTQueryStatus;//ʵʱ״̬��ѯ
extern POS_NETQueryStatus	VC_POS_NETQueryStatus;//����ӿڵ�״̬��ѯ
extern POS_StartDoc			VC_POS_StartDoc;//����һ���ĵ�
extern POS_EndDoc			VC_POS_EndDoc;//����һ���ĵ�
extern POS_BeginSaveFile	VC_POS_BeginSaveFile;//�����������ݵ��ļ�
extern POS_EndSaveFile		VC_POS_EndSaveFile;//�����������ݵ��ļ�
extern POS_GetVersionInfo	VC_POS_GetVersionInfo;//��ȡ��ǰ��̬��汾
extern POS_WriteFile        VC_POS_WriteFile;



#if 0
int _tmain(int argc, _TCHAR* argv[])
{
	if ( false == LoadPosdll() )
	{
		// �����̬�����ʧ��, ���˳�
		printf("���ض�̬��ʧ�ܣ�");
		getchar();
		return false;
	}

	//HANDLE handle = VC_POS_Open("COM1",9600,8,1,0,3);
	HANDLE handle = VC_POS_Open("USB001",0,0,0,0,POS_OPEN_BYUSB_PORT);
	if(handle == INVALID_HANDLE_VALUE)
	{
		printf("�򿪶˿�ʧ��");
		HANDLE USBPRINTER = CreateFile(_T("\\\\.\\COM1"), 
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, 
			OPEN_EXISTING,
			0, NULL );
		if (USBPRINTER == INVALID_HANDLE_VALUE)
		{
			printf("�����˿�ʧ��");
			USBPRINTER = CreateFile(_T("COM1"), 
				GENERIC_READ | GENERIC_WRITE,
				0, NULL, 
				OPEN_EXISTING,
				0, NULL );
			if (USBPRINTER == INVALID_HANDLE_VALUE)
			{
				printf("�ڶ��δ����˿�ʧ��");
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
		printf("��ѯ����ʧ��");
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
			printf("һ��������");
			PrintInStandardMode56();
		}
		else
		{
			
			if (iBits[0] == 0)
			{
				printf("��Ǯ��򿪣�");
			}

			if (iBits[1] == 1)
			{
				printf("��ӡ���ѻ���");
			}

			if (iBits[2] == 1)
			{
				printf("�ϸǴ򿪣�");
			}

			if (iBits[3] == 1)
			{
				printf("���ڽ�ֽ��");
			}

			if (iBits[4] == 1)
			{
				printf("��ӡ������");
			}

			if (iBits[5] == 1)
			{
				printf("�е�����");
			}

			if (iBits[6] == 1)
			{
				printf("ֽ������");
			}

			if (iBits[7] == 1)
			{
				printf("ȱֽ��");
			}
		}
	}
getchar();
	return 0;
}

#elif 1//�ã������ƣ���

#include <windows.h>
#include <string>
#include <IOSTREAM>
using namespace std;

typedef struct DataInfo
{
	string Port;  //���ڶ˿ں�
	int BawdRate;//������
	int DataBits;  //����λ
	char Parity;  //У��λ
	int ReceiveBuffer;  //������
	int StopBits;//ֹͣλ
}PrintDevice;

int   WriteData(string meg);
int InitPort(PrintDevice &device);
void InitializeDevicePar(PrintDevice &device);
HANDLE hPort=NULL;  //���
using namespace std;  
int bmpwidth,bmpheight,linebyte;  
unsigned char *pBmpBuf;  //�洢ͼ������  
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
	int linenum,ex; //linenum:һ�����ص��ֽ���������������ֽ� 

	//open file
	if((binFile=fopen(filename,"rb"))==NULL) return NULL;

	//read struts
	if(fread((void *)&fileHeader,1,sizeof(fileHeader),binFile)!=sizeof(fileHeader)) isRead=FALSE;
	if(fread((void *)&bmpHeader,1,sizeof(bmpHeader),binFile)!=sizeof(bmpHeader)) isRead=FALSE;

	//�ʣ�������ж���Ϊ�˱���ʲô������
	if(isRead==FALSE||fileHeader.bfOffBits<sizeof(fileHeader)+sizeof(bmpHeader)){
		fclose(binFile);
		return NULL;
	}

	//read image info
	*width=bmpHeader.biWidth;
	*height=bmpHeader.biHeight;
	linenum=(*width*1+3)/4*4;
	ex=linenum-*width*1;         //ÿһ�е�����ֽ�

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
	InitializeDevicePar(device);  //��ʼ����ӡ������
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

	wstring infilename(L"generate.bmp");
	//GetEncoderClassCLSID

	Bitmap* bmp = new Bitmap(infilename.c_str());
	UINT height = bmp->GetHeight();
	UINT width  = bmp->GetWidth();

	InitPort(device);  //��ʼ����ӡ���˿�
	//readBmp("123.bmp");
	
	BYTE *byte;// = RmwRead8BitBmpFile2Img("123.bmp", &w, &h);
	//////////////////////////////////////////////////////////////////////////
	DWORD iBytesLength;
	string s;
	char chInitCode[] = "\x0D\x1B\x40";//��ʼ����ӡ��
	bool bSuccess = WriteFile(hPort, chInitCode, (DWORD)3L, &iBytesLength, NULL);
	if (!bSuccess || !iBytesLength)
	{
		printf("��ӡ��ȱֽ���ѻ�������������!"); 
		
		return 0;
	}
	//��ֽ��˺ֽλ��
	//char chMoveToCut[] = "\x0A\x1D\x56\x41\x00";
	//WriteFile(hPort, chMoveToCut, (DWORD)5L, &iBytesLength, NULL);	
	//��ʾGS v
	/*s = _T("\nGS v 0 ����BMP��ʾ\n");
	WriteData(s);*/
	char sz[] = "\x1D\x2F\x03";
	WriteFile(hPort, sz, (DWORD)3L, &iBytesLength, NULL);

	char sz1[] = "\x1B\x33\x00";
	WriteFile(hPort, sz1, (DWORD)3L, &iBytesLength, NULL);
	//CloseHandle(hPort);//�رն˿�
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
		//����ģʽΪλͼģʽ  
		WriteFile(hPort, chEscBitmapCode2, 5, &iBytesLength, NULL);
		//ѭ����  
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
			//һ��д��һ��data��24������  
			WriteFile(hPort, data, 3, &iBytesLength, NULL);

			data[0] = 0x00;  
			data[1] = 0x00;  
			data[2] = 0x00;    // Clear to Zero.  
		}  

		//���У���ӡ�ڶ���  
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
	//	chEscBitmapCode2[48]=10;  //LF��ֽ
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
	

	////////////////////////////��ӡͷ��Ϣ��ʼ//////////////////////////////////
	//�������Ĵ��� + �ı���С, "FS ! n", n = 4 + 8+128, \x1C\x21�Ŵ����� \\0a��ӡ������
	s= "\x1C\x21\x8C";
	WriteData(s);

	s="�̵�-�Ϻ�����\x0A";
	WriteData(s); //��ӡ

	//ȡ�����ķŴ�����
	//DWORD iBytesLength = 0;\\ȡ���Ŵ�
	char chSetCode[] = "\x1C\x21\x0";
	WriteFile(hPort, chSetCode, (DWORD)3L, &iBytesLength, NULL);
	//////////////////////////��ӡͷ��Ϣ����///////////////////////////////////////

	//////////////////////////��ӡ��Ʒ��ʼ////////////////////////////////////////
	s="ɽ��ƻ��\t4.00\t2x\t8.00Ԫ\x0A";
	WriteData(s); //��ӡ
	s="��������\t5.00\t3x\t15.00Ԫ\x0A";
	WriteData(s); //��ӡ
	s="\x0A";
	WriteData(s); //��ӡ
	////////////////////////////��ӡ��Ʒ����//////////////////////////////////////
	s="С��:23.00Ԫ\x0A";
	WriteData(s); //��ӡ

	//��ֽ����ֽλ�ã�����ֽ��"GS V m n", n=��Ҫ���������
	s= "\x1D\x56\x41\x01";  //m=65 65��ȫ��,66�ǰ��У� n=1 0<=n<=255
	WriteData(s); //��ӡ

	CloseHandle(hPort);//�رն˿�

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
	{   // �򿪶˿�ʧ��
		printf("�򿪶˿�ʧ��");
		getchar();
		return false;
	}
	else
	{ 
		//���ö˿ڻ���
		SetupComm(hPort, 1024, 1024); 

		// �趨ͨѶ�˿ڳ�ʱ����
		COMMTIMEOUTS tmouts;
		tmouts.ReadIntervalTimeout = 100;
		tmouts.ReadTotalTimeoutMultiplier = 100;
		tmouts.ReadTotalTimeoutConstant = 100;
		tmouts.WriteTotalTimeoutConstant = 100;
		tmouts.WriteTotalTimeoutMultiplier = 100;
		SetCommTimeouts(hPort, &tmouts);

		//�趨ͨѶ�˿�ͨѶ����
		DCB dcb;
		BOOL bol = TRUE;

		//dcb.DCBlength = sizeof(dcb);
		
		bol=GetCommState(hPort, &dcb);
		dcb.BaudRate = device.BawdRate;
		dcb.ByteSize =device.DataBits;
		dcb.StopBits = device.StopBits;
		dcb.Parity = device.Parity;
		
		//bol = SetCommState(hPort, &dcb); //���ô���
		// ���ͨѶ�˿ڻ���
		PurgeComm(hPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);

		// ��ʼ���ص�IO����
		OVERLAPPED m_OverlappedRead;
		OVERLAPPED m_OverlappedWrite;
		HANDLE m_hStopCommEvent;
		HANDLE m_hDataReady;
		memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
		m_OverlappedRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));
		m_OverlappedWrite.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		// ��ʼ���¼�����
		m_hStopCommEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		m_hDataReady = CreateEvent(NULL, FALSE, FALSE, NULL);

		//��ʼ����ӡESC @
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
		printf("��ռ�ɹ�");

	}
	else
	{
		printf("��ռʧ��");
	}
	getchar();
}
#else

void main()
{
	
	
}
#endif