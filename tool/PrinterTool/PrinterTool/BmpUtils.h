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
	int mBmpWidth;//ͼ��Ŀ�   
	int mBmpHeight;//ͼ��ĸ�   
	RGBQUAD *mPColorTable;//��ɫ��ָ��   
	int mBiBitCount;//ͼ�����ͣ�ÿ����λ�� 
	int mLineByte;//ÿ��������ռ���ֽ�����������4�ı�����
	int mPrinterBmpCount;
};