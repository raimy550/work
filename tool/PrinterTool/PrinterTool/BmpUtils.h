#pragma once
#include <Windows.h>

#include <xstring>
using namespace std;
class CSerialPort;

class CBmpUtils{
public:
		CBmpUtils();
		~CBmpUtils();
		bool loadBmp(string strPath);
		unsigned char* printerBmp(CSerialPort* serialPort);
		int getPrinterBmpCount();
private:
		bool readBmp(string strPath);
		int  rgb2Gray(int r, int g, int b);
		int px2Byte(int x, int y, int BitCount);
		int changePointPx1(unsigned char* arry);

private:
	unsigned char* mPBmpBuf;
	int mBmpWidth;//图像的宽   
	int mBmpHeight;//图像的高   
	RGBQUAD *mPColorTable;//颜色表指针   
	int mBiBitCount;//图像类型，每像素位数 
	int mLineByte;//每行像素所占的字节数（必须是4的倍数）
	int mPrinterBmpCount;
};