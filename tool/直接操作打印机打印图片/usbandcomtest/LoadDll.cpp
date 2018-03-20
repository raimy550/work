#include "StdAfx.h"
#include "LoadDll.h"

HMODULE g_hPosdll = NULL;
/***************通用函数******************/
POS_Open						VC_POS_Open						= NULL;
 
POS_Close						VC_POS_Close					= NULL;

POS_Reset						VC_POS_Reset					= NULL;
 
POS_SetMode						VC_POS_SetMode					= NULL;
 
POS_SetMotionUnit				VC_POS_SetMotionUnit			= NULL;

POS_SetCharSetAndCodePage		VC_POS_SetCharSetAndCodePage	= NULL;
 
POS_FeedLine					VC_POS_FeedLine					= NULL;
 
POS_SetLineSpacing				VC_POS_SetLineSpacing			= NULL;
 
POS_SetRightSpacing				VC_POS_SetRightSpacing			= NULL;
 
POS_PreDownloadBmpToRAM			VC_POS_PreDownloadBmpToRAM		= NULL;
 
POS_PreDownloadBmpsToFlash		VC_POS_PreDownloadBmpsToFlash	= NULL;
 
POS_QueryStatus					VC_POS_QueryStatus				= NULL;

POS_NETQueryStatus				VC_POS_NETQueryStatus			= NULL;
 
POS_RTQueryStatus				VC_POS_RTQueryStatus			= NULL;
 
POS_KickOutDrawer				VC_POS_KickOutDrawer			= NULL;
 
POS_CutPaper					VC_POS_CutPaper					= NULL;

POS_StartDoc					VC_POS_StartDoc					= NULL;

POS_EndDoc						VC_POS_EndDoc					= NULL;
 
POS_EndSaveFile					VC_POS_EndSaveFile				= NULL;
 
POS_BeginSaveFile				VC_POS_BeginSaveFile			= NULL;
/***********只支持标准打印模式(行模式)的函数************/
POS_S_SetAreaWidth				VC_POS_S_SetAreaWidth			= NULL;

POS_S_TextOut					VC_POS_S_TextOut				= NULL;

POS_S_DownloadAndPrintBmp		VC_POS_S_DownloadAndPrintBmp	= NULL;
 
POS_S_PrintBmpInRAM				VC_POS_S_PrintBmpInRAM			= NULL;
 
POS_S_PrintBmpInFlash			VC_POS_S_PrintBmpInFlash		= NULL;
 
POS_S_SetBarcode				VC_POS_S_SetBarcode				= NULL;
/*******只支持页打印模式(P)或标签打印模式(L)的函数*******/
POS_PL_SetArea					VC_POS_PL_SetArea				= NULL;
 
POS_PL_TextOut					VC_POS_PL_TextOut				= NULL;

POS_PL_DownloadAndPrintBmp		VC_POS_PL_DownloadAndPrintBmp	= NULL;
 
POS_PL_PrintBmpInRAM			VC_POS_PL_PrintBmpInRAM			= NULL;

POS_PL_SetBarcode				VC_POS_PL_SetBarcode			= NULL;
 
POS_PL_Print					VC_POS_PL_Print					= NULL;

POS_PL_Clear					VC_POS_PL_Clear					= NULL; 
/*****杂项---主要用于调试和自定义控制函数使用*****/
POS_WriteFile					VC_POS_WriteFile				= NULL;
 
POS_ReadFile					VC_POS_ReadFile					= NULL;
 
POS_SetHandle					VC_POS_SetHandle				= NULL;
 
POS_GetVersionInfo				VC_POS_GetVersionInfo			= NULL;
/***********加载动态库****************/

bool LoadPosdll(void)
{
	g_hPosdll = LoadLibrary("POSDLL.dll");
	if(!g_hPosdll)
	{
		return false;
	}
	/***************加载通用函数******************/
	VC_POS_Open = (POS_Open) GetProcAddress(g_hPosdll,"POS_Open");
	if(VC_POS_Open == NULL)
	{
		return false;
	}

	VC_POS_Close = (POS_Close) GetProcAddress(g_hPosdll,"POS_Close");
	if(VC_POS_Close == NULL)
	{
		return false;
	}

	VC_POS_Reset = (POS_Reset) GetProcAddress(g_hPosdll,"POS_Reset");
	if(VC_POS_Reset == NULL)
	{
		return false;
	}

	VC_POS_SetMode = (POS_SetMode) GetProcAddress(g_hPosdll,"POS_SetMode");
	if(VC_POS_SetMode == NULL)
	{
		return false;
	}

	VC_POS_SetMotionUnit = (POS_SetMotionUnit) GetProcAddress(g_hPosdll,"POS_SetMotionUnit");
	if(VC_POS_SetMotionUnit == NULL)
	{
		return false;
	}

	VC_POS_SetCharSetAndCodePage = (POS_SetCharSetAndCodePage) GetProcAddress(g_hPosdll,"POS_SetCharSetAndCodePage");
	if(VC_POS_SetCharSetAndCodePage == NULL)
	{
		return false;
	}

	VC_POS_FeedLine = (POS_FeedLine) GetProcAddress(g_hPosdll,"POS_FeedLine");
	if(VC_POS_FeedLine == NULL)
	{
		return false;
	}

	VC_POS_SetLineSpacing = (POS_SetLineSpacing) GetProcAddress(g_hPosdll,"POS_SetLineSpacing");
	if(VC_POS_SetLineSpacing == NULL)
	{
		return false;
	}

	VC_POS_SetRightSpacing = (POS_SetRightSpacing) GetProcAddress(g_hPosdll,"POS_SetRightSpacing");
	if(VC_POS_SetRightSpacing == NULL)
	{
		return false;
	}

	VC_POS_PreDownloadBmpToRAM = (POS_PreDownloadBmpToRAM) GetProcAddress(g_hPosdll,"POS_PreDownloadBmpToRAM");
	if(VC_POS_PreDownloadBmpToRAM == NULL)
	{
		return false;
	}

	VC_POS_PreDownloadBmpsToFlash = (POS_PreDownloadBmpsToFlash) GetProcAddress(g_hPosdll,"POS_PreDownloadBmpsToFlash");
	if(VC_POS_PreDownloadBmpsToFlash == NULL)
	{
		return false;
	}

	VC_POS_QueryStatus = (POS_QueryStatus) GetProcAddress(g_hPosdll,"POS_QueryStatus");
	if(VC_POS_QueryStatus == NULL)
	{
		return false;
	}

	VC_POS_RTQueryStatus = (POS_RTQueryStatus) GetProcAddress(g_hPosdll,"POS_RTQueryStatus");
	if(VC_POS_RTQueryStatus == NULL)
	{
		return false;
	}

	VC_POS_NETQueryStatus = (POS_NETQueryStatus)GetProcAddress(g_hPosdll,"POS_NETQueryStatus");
	if(VC_POS_NETQueryStatus == NULL)
	{
		return false;
	}

	VC_POS_KickOutDrawer = (POS_KickOutDrawer) GetProcAddress(g_hPosdll,"POS_KickOutDrawer");
	if(VC_POS_KickOutDrawer == NULL)
	{
		return false;
	}

	VC_POS_CutPaper = (POS_CutPaper) GetProcAddress(g_hPosdll,"POS_CutPaper");
	if(VC_POS_CutPaper == NULL)
	{
		return false;
	}

	VC_POS_StartDoc = (POS_StartDoc) GetProcAddress(g_hPosdll,"POS_StartDoc");
	if(VC_POS_StartDoc == NULL)
	{
		return false;
	}

	VC_POS_EndDoc = (POS_EndDoc) GetProcAddress(g_hPosdll,"POS_EndDoc");
	if(VC_POS_StartDoc == NULL)
	{
		return false;
	}

	VC_POS_EndSaveFile = (POS_EndSaveFile) GetProcAddress(g_hPosdll,"POS_EndSaveFile");
	if(VC_POS_EndSaveFile == NULL)
	{
		return false;
	}

	VC_POS_BeginSaveFile = (POS_BeginSaveFile) GetProcAddress(g_hPosdll,"POS_BeginSaveFile");
	if(VC_POS_StartDoc == NULL)
	{
		return false;
	}
	/***********只支持标准打印模式(行模式)的函数************/
	VC_POS_S_SetAreaWidth = (POS_S_SetAreaWidth) GetProcAddress(g_hPosdll,"POS_S_SetAreaWidth");
	if(VC_POS_S_SetAreaWidth == NULL)
	{
		return false;
	}

	VC_POS_S_TextOut = (POS_S_TextOut) GetProcAddress(g_hPosdll,"POS_S_TextOut");
	if(VC_POS_S_TextOut == NULL)
	{
		return false;
	}

	VC_POS_S_DownloadAndPrintBmp = (POS_S_DownloadAndPrintBmp) GetProcAddress(g_hPosdll,"POS_S_DownloadAndPrintBmp");
	if(VC_POS_S_DownloadAndPrintBmp == NULL)
	{
		return false;
	}

	VC_POS_S_PrintBmpInRAM = (POS_S_PrintBmpInRAM) GetProcAddress(g_hPosdll,"POS_S_PrintBmpInRAM");
	if(VC_POS_S_PrintBmpInRAM == NULL)
	{
		return false;
	}

	VC_POS_S_PrintBmpInFlash = (POS_S_PrintBmpInFlash) GetProcAddress(g_hPosdll,"POS_S_PrintBmpInFlash");
	if(VC_POS_S_PrintBmpInFlash == NULL)
	{
		return false;
	}

	VC_POS_S_SetBarcode = (POS_S_SetBarcode) GetProcAddress(g_hPosdll,"POS_S_SetBarcode");
	if(VC_POS_S_SetBarcode == NULL)
	{
		return false;
	}
	/*******只支持页打印模式(P)或标签打印模式(L)的函数*******/
	VC_POS_PL_SetArea = (POS_PL_SetArea) GetProcAddress(g_hPosdll,"POS_PL_SetArea");
	if(VC_POS_PL_SetArea == NULL)
	{
		return false;
	}

	VC_POS_PL_TextOut = (POS_PL_TextOut) GetProcAddress(g_hPosdll,"POS_PL_TextOut");
	if(VC_POS_PL_TextOut == NULL)
	{
		return false;
	}

	VC_POS_PL_DownloadAndPrintBmp = (POS_PL_DownloadAndPrintBmp) GetProcAddress(g_hPosdll,"POS_PL_DownloadAndPrintBmp");
	if(VC_POS_PL_DownloadAndPrintBmp == NULL)
	{
		return false;
	}

	VC_POS_PL_PrintBmpInRAM = (POS_PL_PrintBmpInRAM) GetProcAddress(g_hPosdll,"POS_PL_PrintBmpInRAM");
	if(VC_POS_PL_PrintBmpInRAM == NULL)
	{
		return false;
	}

	VC_POS_PL_SetBarcode = (POS_PL_SetBarcode) GetProcAddress(g_hPosdll,"POS_PL_SetBarcode");
	if(VC_POS_PL_SetBarcode == NULL)
	{
		return false;
	}

	VC_POS_PL_Print = (POS_PL_Print) GetProcAddress(g_hPosdll,"POS_PL_Print");
	if(VC_POS_PL_Print == NULL)
	{
		return false;
	}

	VC_POS_PL_Clear = (POS_PL_Clear) GetProcAddress(g_hPosdll,"POS_PL_Clear");
	if(VC_POS_PL_Clear == NULL)
	{
		return false;
	}
	/*****杂项---主要用于调试和自定义控制函数使用*****/
	VC_POS_WriteFile = (POS_WriteFile) GetProcAddress(g_hPosdll,"POS_WriteFile");
	if(VC_POS_WriteFile == NULL)
	{
		return false;
	}

	VC_POS_ReadFile = (POS_ReadFile) GetProcAddress(g_hPosdll,"POS_ReadFile");
	if(VC_POS_ReadFile == NULL)
	{
		return false;
	}

	VC_POS_SetHandle = (POS_SetHandle) GetProcAddress(g_hPosdll,"POS_SetHandle");
	if(VC_POS_SetHandle == NULL)
	{
		return false;
	}
	
	VC_POS_GetVersionInfo = (POS_GetVersionInfo) GetProcAddress(g_hPosdll,"POS_GetVersionInfo");
	if(VC_POS_GetVersionInfo == NULL)
	{
		return false;
	}

	return true;
}

bool UnloadPosdll(void)
{
	if (NULL == g_hPosdll)
	{
		return false;
	}

	FreeLibrary(g_hPosdll);

	return true;
}