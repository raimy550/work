#ifndef LOADDLL_H
#define LOADDLL_H
#pragma once
#include <Windows.h>
#define POS_SUCCESS                     1001 // 函数执行成功

#define POS_FAIL                        1002 // 函数执行失败

#define POS_ERROR_INVALID_HANDLE        1101 // 端口或文件的句柄无效

#define POS_ERROR_INVALID_PARAMETER     1102 // 参数无效

#define POS_ERROR_NOT_BITMAP            1103 // 不是位图格式的文件

#define POS_ERROR_NOT_MONO_BITMAP       1104 // 位图不是单色的

#define POS_ERROR_BEYONG_AREA           1105 // 位图超出打印机可以
											 // 处理的大小

#define POS_ERROR_INVALID_PATH          1106 // 没有找到指定的文件
											 // 路径或名称

#define POS_COM_DTR_DSR 0x00 // 流控制为DTR/DST
  
#define POS_COM_RTS_CTS 0x01 // 流控制为RTS/CTS 

#define POS_COM_XON_XOFF 0x02 // 流控制为XON/OFF 

#define POS_COM_NO_HANDSHAKE 0x03 // 无握手 

#define POS_OPEN_PARALLEL_PORT 0x12 // 打开并口通讯端口 

#define POS_OPEN_BYUSB_PORT 0x13 // 打开USB通讯端口 

#define POS_OPEN_PRINTNAME 0X14 //打开打印机驱动程序

#define POS_OPEN_NETPORT 0X15 // 打开以太网打印机

#define POS_FONT_TYPE_STANDARD 0x00 // 标准 ASCII
 
#define POS_FONT_TYPE_COMPRESSED 0x01 // 压缩 ASCII 
 
#define POS_FONT_TYPE_UDC 0x02 // 用户自定义字符
 
#define POS_FONT_TYPE_CHINESE 0x03 // 标准 “宋体”
 
#define POS_FONT_STYLE_NORMAL 0x00 // 正常
 
#define POS_FONT_STYLE_BOLD 0x08 // 加粗
 
#define POS_FONT_STYLE_THIN_UNDERLINE 0x80 // 1点粗的下划线
 
#define POS_FONT_STYLE_THICK_UNDERLINE 0x100 // 2点粗的下划线
 
#define POS_FONT_STYLE_UPSIDEDOWN 0x200 // 倒置（只在行首有效）
 
#define POS_FONT_STYLE_REVERSE 0x400 // 反显（黑底白字）
 
#define POS_FONT_STYLE_SMOOTH 0x800 // 平滑处理（用于放大时）
 
#define POS_FONT_STYLE_CLOCKWISE_90 0x1000 // 每个字符顺时针旋转 90 度

#define POS_PRINT_MODE_STANDARD 0x00 // 标准模式（行模式）
 
#define POS_PRINT_MODE_PAGE 0x01 // 页模式
 
#define POS_PRINT_MODE_BLACK_MARK_LABEL 0x02 // 黑标记标签模式

#define POS_BARCODE_TYPE_UPC_A 0x41 // UPC-A
 
#define POS_BARCODE_TYPE_UPC_E 0x42 // UPC-C
 
#define POS_BARCODE_TYPE_JAN13 0x43 // JAN13(EAN13)
 
#define POS_BARCODE_TYPE_JAN8 0x44 // JAN8(EAN8)
 
#define POS_BARCODE_TYPE_CODE39 0x45 // CODE39
 
#define POS_BARCODE_TYPE_ITF 0x46 // INTERLEAVED 2 OF 5
 
#define POS_BARCODE_TYPE_CODEBAR 0x47 // CODEBAR
 
#define POS_BARCODE_TYPE_CODE93 0x48 // 25
 
#define POS_BARCODE_TYPE_CODE128 0x49 // CODE 128
 
#define POS_FONT_TYPE_STANDARD 0x00 // 标准ASCII 
 
#define POS_FONT_TYPE_COMPRESSED 0x01 // 压缩ASCII
 
#define POS_HRI_POSITION_NONE 0x00 // 不打印
 
#define POS_HRI_POSITION_ABOVE 0x01 // 只在条码上方打印
 
#define POS_HRI_POSITION_BELOW 0x02 // 只在条码下方打印
 
#define POS_HRI_POSITION_BOTH 0x03 // 条码上、下方都打印
 
#define POS_BITMAP_PRINT_NORMAL 0x00 // 正常
 
#define POS_BITMAP_PRINT_DOUBLE_WIDTH 0x01 // 倍宽
 
#define POS_BITMAP_PRINT_DOUBLE_HEIGHT 0x02 // 倍高
 
#define POS_BITMAP_PRINT_QUADRUPLE 0x03 // 倍宽且倍高
 
#define POS_CUT_MODE_FULL 0x00 // 全切
 
#define POS_CUT_MODE_PARTIAL 0x01 // 半切
 
#define POS_AREA_LEFT_TO_RIGHT 0x0 // 左上角
 
#define POS_AREA_BOTTOM_TO_TOP 0x1 // 左下角
 
#define POS_AREA_RIGHT_TO_LEFT 0x2 // 右下角
 
#define POS_AREA_TOP_TO_BOTTOM 0x3 // 右上角
 

 

/***************通用函数*****************/
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

/******只支持标准打印模式(行模式)的函数******/
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

/****只支持页打印模式(P)或标签打印模式(L)的函数****/
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

/********杂项--主要用于调试和自定义控制函数使用*******/
typedef int (__stdcall *POS_WriteFile)(HANDLE hPort,char *pszData,int nBytesToWrite);

typedef int (__stdcall *POS_ReadFile)( HANDLE hPort,
									   char *pszData,
									   int nBytesToRead,
									   int nTimeouts);

typedef HANDLE (__stdcall *POS_SetHandle)(HANDLE hNewHandle);

typedef int (__stdcall *POS_GetVersionInfo)(int *pnMajor,int *pnMinor);

/****************加载和卸载动态库**************************/
bool LoadPosdll(void);

bool UnloadPosdll(void);

#endif
