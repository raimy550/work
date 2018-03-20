#ifndef LOADDLL_H
#define LOADDLL_H
#pragma once
#include <Windows.h>
#define POS_SUCCESS                     1001 // ����ִ�гɹ�

#define POS_FAIL                        1002 // ����ִ��ʧ��

#define POS_ERROR_INVALID_HANDLE        1101 // �˿ڻ��ļ��ľ����Ч

#define POS_ERROR_INVALID_PARAMETER     1102 // ������Ч

#define POS_ERROR_NOT_BITMAP            1103 // ����λͼ��ʽ���ļ�

#define POS_ERROR_NOT_MONO_BITMAP       1104 // λͼ���ǵ�ɫ��

#define POS_ERROR_BEYONG_AREA           1105 // λͼ������ӡ������
											 // ����Ĵ�С

#define POS_ERROR_INVALID_PATH          1106 // û���ҵ�ָ�����ļ�
											 // ·��������

#define POS_COM_DTR_DSR 0x00 // ������ΪDTR/DST
  
#define POS_COM_RTS_CTS 0x01 // ������ΪRTS/CTS 

#define POS_COM_XON_XOFF 0x02 // ������ΪXON/OFF 

#define POS_COM_NO_HANDSHAKE 0x03 // ������ 

#define POS_OPEN_PARALLEL_PORT 0x12 // �򿪲���ͨѶ�˿� 

#define POS_OPEN_BYUSB_PORT 0x13 // ��USBͨѶ�˿� 

#define POS_OPEN_PRINTNAME 0X14 //�򿪴�ӡ����������

#define POS_OPEN_NETPORT 0X15 // ����̫����ӡ��

#define POS_FONT_TYPE_STANDARD 0x00 // ��׼ ASCII
 
#define POS_FONT_TYPE_COMPRESSED 0x01 // ѹ�� ASCII 
 
#define POS_FONT_TYPE_UDC 0x02 // �û��Զ����ַ�
 
#define POS_FONT_TYPE_CHINESE 0x03 // ��׼ �����塱
 
#define POS_FONT_STYLE_NORMAL 0x00 // ����
 
#define POS_FONT_STYLE_BOLD 0x08 // �Ӵ�
 
#define POS_FONT_STYLE_THIN_UNDERLINE 0x80 // 1��ֵ��»���
 
#define POS_FONT_STYLE_THICK_UNDERLINE 0x100 // 2��ֵ��»���
 
#define POS_FONT_STYLE_UPSIDEDOWN 0x200 // ���ã�ֻ��������Ч��
 
#define POS_FONT_STYLE_REVERSE 0x400 // ���ԣ��ڵװ��֣�
 
#define POS_FONT_STYLE_SMOOTH 0x800 // ƽ���������ڷŴ�ʱ��
 
#define POS_FONT_STYLE_CLOCKWISE_90 0x1000 // ÿ���ַ�˳ʱ����ת 90 ��

#define POS_PRINT_MODE_STANDARD 0x00 // ��׼ģʽ����ģʽ��
 
#define POS_PRINT_MODE_PAGE 0x01 // ҳģʽ
 
#define POS_PRINT_MODE_BLACK_MARK_LABEL 0x02 // �ڱ�Ǳ�ǩģʽ

#define POS_BARCODE_TYPE_UPC_A 0x41 // UPC-A
 
#define POS_BARCODE_TYPE_UPC_E 0x42 // UPC-C
 
#define POS_BARCODE_TYPE_JAN13 0x43 // JAN13(EAN13)
 
#define POS_BARCODE_TYPE_JAN8 0x44 // JAN8(EAN8)
 
#define POS_BARCODE_TYPE_CODE39 0x45 // CODE39
 
#define POS_BARCODE_TYPE_ITF 0x46 // INTERLEAVED 2 OF 5
 
#define POS_BARCODE_TYPE_CODEBAR 0x47 // CODEBAR
 
#define POS_BARCODE_TYPE_CODE93 0x48 // 25
 
#define POS_BARCODE_TYPE_CODE128 0x49 // CODE 128
 
#define POS_FONT_TYPE_STANDARD 0x00 // ��׼ASCII 
 
#define POS_FONT_TYPE_COMPRESSED 0x01 // ѹ��ASCII
 
#define POS_HRI_POSITION_NONE 0x00 // ����ӡ
 
#define POS_HRI_POSITION_ABOVE 0x01 // ֻ�������Ϸ���ӡ
 
#define POS_HRI_POSITION_BELOW 0x02 // ֻ�������·���ӡ
 
#define POS_HRI_POSITION_BOTH 0x03 // �����ϡ��·�����ӡ
 
#define POS_BITMAP_PRINT_NORMAL 0x00 // ����
 
#define POS_BITMAP_PRINT_DOUBLE_WIDTH 0x01 // ����
 
#define POS_BITMAP_PRINT_DOUBLE_HEIGHT 0x02 // ����
 
#define POS_BITMAP_PRINT_QUADRUPLE 0x03 // �����ұ���
 
#define POS_CUT_MODE_FULL 0x00 // ȫ��
 
#define POS_CUT_MODE_PARTIAL 0x01 // ����
 
#define POS_AREA_LEFT_TO_RIGHT 0x0 // ���Ͻ�
 
#define POS_AREA_BOTTOM_TO_TOP 0x1 // ���½�
 
#define POS_AREA_RIGHT_TO_LEFT 0x2 // ���½�
 
#define POS_AREA_TOP_TO_BOTTOM 0x3 // ���Ͻ�
 

 

/***************ͨ�ú���*****************/
typedef HANDLE (__stdcall *POS_Open)( LPCTSTR lpName, 
									  int nComBaudrate,
									  int nComDataBits, 
									  int nComStopBits, 
									  int nComParity, 
									  int nParam );

typedef int (__stdcall *POS_Close)(void);

typedef int (__stdcall *POS_Reset)(void);

typedef int (__stdcall *POS_SetMode)(int nPrintMode);

typedef int (__stdcall *POS_SetMotionUnit)(int nHorizontalMU,int nVerticalMU);

typedef int (__stdcall *POS_SetCharSetAndCodePage)(int nCharSet,int nCodePage);

typedef int (__stdcall *POS_FeedLine)(void);

typedef int (__stdcall *POS_SetLineSpacing)(int nDistance);

typedef int (__stdcall *POS_SetRightSpacing)(int nDistance);

typedef int (__stdcall *POS_PreDownloadBmpToRAM)(char *pszPath,int nID);

typedef int (__stdcall *POS_PreDownloadBmpsToFlash)(char *pszPaths[],int nCount);

typedef int (__stdcall *POS_QueryStatus)(char *pszStatus,int nTimeouts);

typedef int (__stdcall *POS_RTQueryStatus)(char *pszStatus);

typedef int (__stdcall *POS_NETQueryStatus)(char *ipAddress,char *pszStatus);

typedef int (__stdcall *POS_KickOutDrawer)(int nID,int nOnTimes,int nOffTimes);

typedef int (__stdcall *POS_CutPaper)(int nMode,int nDistance);

typedef bool (__stdcall *POS_StartDoc)();

typedef bool (__stdcall *POS_EndDoc)();

typedef bool (__stdcall *POS_EndSaveFile)();

typedef bool (__stdcall *POS_BeginSaveFile)(LPCTSTR lpFileName,bool bToPrinter);

/******ֻ֧�ֱ�׼��ӡģʽ(��ģʽ)�ĺ���******/
typedef int (__stdcall *POS_S_SetAreaWidth)(int nWidth);

typedef int (__stdcall *POS_S_TextOut)( char *pszString,			 
									    int nOrgx,									 
									    int nWidthTimes,									 
									    int nHeightTimes,									 
									    int nFontType,									 
									    int nFontStyle);

typedef int (__stdcall *POS_S_DownloadAndPrintBmp)(char *pszPath,int nOrgx,int nMode);

typedef int (__stdcall *POS_S_PrintBmpInRAM)(int nID,int nOrgx,int nMode);

typedef int (__stdcall *POS_S_PrintBmpInFlash)(int nID,int nOrgx,int nMode);

typedef int (__stdcall *POS_S_SetBarcode)( char *pszInfoBuffer,
										   int nOrgx,
										   int nType,
										   int nWidthX,
										   int nHeight,
										   int nHriFontType,
										   int nHriFontPosition,
										   int nBytesToPrint);

/****ֻ֧��ҳ��ӡģʽ(P)���ǩ��ӡģʽ(L)�ĺ���****/
typedef int (__stdcall *POS_PL_SetArea)( int nOrgx,
									     int nOrgy,
									     int nWidth,
									     int nHeight,
									     int nDirection);

typedef int (__stdcall *POS_PL_TextOut)( char *pszString,
										 int nOrgx,
										 int nOrgy,
										 int nWidthTimes,
										 int nHeightTimes,
										 int nFontType,
										 int nFontStyle);

typedef int (__stdcall *POS_PL_DownloadAndPrintBmp)(char *pszPath,int nOrgx,int nOrgy,int nMode);

typedef int (__stdcall *POS_PL_PrintBmpInRAM)(int nID,int nOrgx,int nOrgy,int nMode);

typedef int (__stdcall *POS_PL_SetBarcode)( char *pszInfoBuffer,
											int nOrgx,
											int nOrgy,
											int nType,
											int nWidthX,
											int nHeight,
											int nHriFontType,
											int nHriFontPosition,
											int nBytesToPrint);

typedef int (__stdcall *POS_PL_Print)(void);

typedef int (__stdcall *POS_PL_Clear)(void);

/********����--��Ҫ���ڵ��Ժ��Զ�����ƺ���ʹ��*******/
typedef int (__stdcall *POS_WriteFile)(HANDLE hPort,char *pszData,int nBytesToWrite);

typedef int (__stdcall *POS_ReadFile)( HANDLE hPort,
									   char *pszData,
									   int nBytesToRead,
									   int nTimeouts);

typedef HANDLE (__stdcall *POS_SetHandle)(HANDLE hNewHandle);

typedef int (__stdcall *POS_GetVersionInfo)(int *pnMajor,int *pnMinor);

/****************���غ�ж�ض�̬��**************************/
bool LoadPosdll(void);

bool UnloadPosdll(void);

#endif
