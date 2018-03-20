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
	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER  
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head={};
	fread(&head, sizeof(BITMAPINFOHEADER), 1,  fp);//��ȡͼ����ߡ�ÿ������ռλ������Ϣ

	mBmpWidth = head.biWidth;  

	mBmpHeight = head.biHeight;  

	mBiBitCount = head.biBitCount; 

	mLineByte=(mBmpWidth * mBiBitCount/8+3)/4*4;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����  

	if(mBiBitCount==8) //�Ҷ�ͼ������ɫ������ɫ�����Ϊ256    
	{  

		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�   

		mPColorTable=new RGBQUAD[256];  

		fread(mPColorTable,sizeof(RGBQUAD),256,fp);  

	}  

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ� 
	if (mPBmpBuf!=NULL)
	{
		delete[] mPBmpBuf;
	}

	mPBmpBuf=new unsigned char[mLineByte * mBmpHeight];  

	fread(mPBmpBuf,1,mLineByte * mBmpHeight,fp);  

	fclose(fp);//�ر��ļ�   
	return true;
}

int CBmpUtils::rgb2Gray(int r, int g, int b)
{
	int gray = (int) (0.29900 * r + 0.58700 * g + 0.11400 * b);  //�Ҷ�ת����ʽ
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

	//mPrinterBmpCount =  (mLineByte/(mBiBitCount/3*8)+1)*mBmpHeight; //ÿ�����ص���=���ֽ�������û���ص�Byte��+1
	int count =0;
	count = (mBmpHeight+23)/24;
	mPrinterBmpCount = ((mBmpWidth/8+1)*24)*count;
	pBmpBufOut = new unsigned char[mPrinterBmpCount];

//	int index=0;	
// 	BYTE nL = (BYTE)(mBmpWidth&0x00FF);
// 	BYTE nH = (BYTE)((mBmpWidth&0xFF00)>>8);
// 	pBmpBufOut[index++] = 0x1B;
// 	pBmpBufOut[index++] = 0x2A;
// 	pBmpBufOut[index++] = 0x33; // m=33ʱ��ѡ��24��˫�ܶȴ�ӡ���ֱ��ʴﵽ200DPI��
// 	pBmpBufOut[index++] = nL;//0x82+ 0x1*256 = 384��/��
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
		cmd[2] = 0x21; // m=33ʱ��ѡ��24��˫�ܶȴ�ӡ���ֱ��ʴﵽ200DPI��
		cmd[3] = nL;//0x82+ 0x1*256 = 384��/��
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


