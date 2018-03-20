#include "stdafx.h"
#include "BmpUtils.h"
#include "SerialPort.h"

CBmpUtils::CBmpUtils()
{
	mPBmpBuf=NULL;
}

CBmpUtils::~CBmpUtils()
{
	if (mPBmpBuf)
	{
		delete[] mPBmpBuf;
		mPBmpBuf = NULL;
	}
}




bool CBmpUtils::readBmp(string strPath)
{

	FILE *fp= fopen(strPath.c_str(),"rb");

	if (fp==0)
		return false;
	
	int nSize = sizeof(BITMAPINFOHEADER);
	//跳过位图文件头结构BITMAPFILEHEADER  
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head={};
	fread(&head, sizeof(BITMAPINFOHEADER), 1,  fp);//获取图像宽、高、每像素所占位数等信息

	mBmpWidth = head.biWidth;  

	mBmpHeight = head.biHeight;  

	mBiBitCount = head.biBitCount; 

	mLineByte=(mBmpWidth * mBiBitCount/8+3)/4*4;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）  

	if(mBiBitCount==8) //灰度图像有颜色表，且颜色表表项为256    
	{  

		//申请颜色表所需要的空间，读颜色表进内存   

		mPColorTable=new RGBQUAD[256];  

		fread(mPColorTable,sizeof(RGBQUAD),256,fp);  

	}  

	//申请位图数据所需要的空间，读位图数据进内存 
	if (mPBmpBuf!=NULL)
	{
		delete[] mPBmpBuf;
	}

	mPBmpBuf=new unsigned char[mLineByte * mBmpHeight];  

	fread(mPBmpBuf,1,mLineByte * mBmpHeight,fp);  

	fclose(fp);//关闭文件   
	return true;
}

int CBmpUtils::rgb2Gray(int r, int g, int b)
{
	int gray = (int) (0.29900 * r + 0.58700 * g + 0.11400 * b);  //灰度转化公式
	return  gray;
}

bool CBmpUtils::loadBmp(string strPath)
{
	readBmp(strPath);
	return true;
}


int CBmpUtils::px2Byte(int x, int y, int BitCount)
{
	//return 1;
	int byteCount = mBiBitCount/8;
	int r,g,b, nRet;
	if (x>mBmpWidth || y>mBmpHeight)
	{
		return 0;
	}

	r = mPBmpBuf[y*mLineByte+x*byteCount];
	g = mPBmpBuf[y*mLineByte+x*byteCount+1];
	b = mPBmpBuf[y*mLineByte+x*byteCount+2];

	int nGray = rgb2Gray(r,g, b);
	if (nGray<200)
	{
		nRet=1;
	}
	else
	{
		nRet=0;
	}

	return nRet;
}

int CBmpUtils::changePointPx1(unsigned char* arry)
{
	int v = 0;
	for (int j = 0; j <8; j++) {
		if( arry[j] == 1) {
			v = v | 1 << j;
		}
	}
	return v;
}

int CBmpUtils::getPrinterBmpCount()
{
	return mPrinterBmpCount;
}

unsigned char* CBmpUtils::printerBmp(CSerialPort* serialPort)
{
	unsigned char* pBmpBufOut=NULL;
	
	int byteCount = mBiBitCount/8;

	//mPrinterBmpCount =  (mLineByte/(mBiBitCount/3*8)+1)*mBmpHeight; //每行像素点数=行字节数除以没像素点Byte数+1
	int count =0;
	count = (mBmpHeight+23)/24;
	mPrinterBmpCount = ((mBmpWidth/8+1)*24)*count;
	pBmpBufOut = new unsigned char[mPrinterBmpCount];

//	int index=0;	
// 	BYTE nL = (BYTE)(mBmpWidth&0x00FF);
// 	BYTE nH = (BYTE)((mBmpWidth&0xFF00)>>8);
// 	pBmpBufOut[index++] = 0x1B;
// 	pBmpBufOut[index++] = 0x2A;
// 	pBmpBufOut[index++] = 0x33; // m=33时，选择24点双密度打印，分辨率达到200DPI。
// 	pBmpBufOut[index++] = nL;//0x82+ 0x1*256 = 384点/行
// 	pBmpBufOut[index++] = nH;

	int index=0;
	BYTE cmd[20];
	DWORD dwWrite;
	for (int i=0; i<count; i++)
	{
		BYTE nL = (BYTE)(mBmpWidth&0x00FF);
		BYTE nH = (BYTE)((mBmpWidth&0xFF00)>>8);
		
		cmd[0] = 0x1B;
		cmd[1] = 0x2A;
		cmd[2] = 0x21; // m=33时，选择24点双密度打印，分辨率达到200DPI。
		cmd[3] = nL;//0x82+ 0x1*256 = 384点/行
		cmd[4] = nH;	

		
		serialPort->Write(cmd, 5, &dwWrite);

		for (int hang=i*24; ; hang++)
		{
			for (int lie=0; lie<mBmpWidth; lie=lie+8)
			{
				BYTE by[8];
				for (int n=0; n<8; n++)
				{
					by[n] = px2Byte(lie+n, hang, mBiBitCount);
				}
				pBmpBufOut[index++]=changePointPx1(by);
			}

			if ((hang+1)%24==0)
			{
				serialPort->Write(&pBmpBufOut[count*24*((mBmpWidth+7)/8)], 24*((mBmpWidth+7)/8), &dwWrite);
				cmd[0]=0x1B;
				cmd[1]=0x4A;
				cmd[2]=24; 
				serialPort->Write(cmd,3,&dwWrite);
				break;
			}
		}	
	}
	cmd[0]=0x1d;
	cmd[1]=0x56;
	cmd[2]=0x42;//m
	cmd[3]=0x00;
	serialPort->Write(cmd,4,&dwWrite);

// 	for (int i=0; i<mBmpHeight; i++)
// 	{
// 		for (int j=0; j<mBmpWidth; j=j+8)
// 		{
// 
// 			unsigned char by[8];
// 			for (int n=0; n<8; n++)
// 			{
// 				by[n] = px2Byte(j+n, i, mBiBitCount);
// 			}
// 			pBmpBufOut[index++]=changePointPx1(by);
// 		}
// 	}
	return pBmpBufOut;
}


