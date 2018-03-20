#include "StdAfx.h"
#include "PrintSamples.h"
#include "LoadDll.h"

bool bSaveToTxt;
/***************ͨ�ú���******************/
extern POS_Open							VC_POS_Open;
 
extern POS_Close						VC_POS_Close;

extern POS_Reset						VC_POS_Reset;
 
extern POS_SetMode						VC_POS_SetMode;
 
extern POS_SetMotionUnit				VC_POS_SetMotionUnit;

extern POS_SetCharSetAndCodePage		VC_POS_SetCharSetAndCodePage;
 
extern POS_FeedLine						VC_POS_FeedLine;
 
extern POS_SetLineSpacing				VC_POS_SetLineSpacing;
 
extern POS_SetRightSpacing				VC_POS_SetRightSpacing;
 
extern POS_PreDownloadBmpToRAM			VC_POS_PreDownloadBmpToRAM;
 
extern POS_PreDownloadBmpsToFlash		VC_POS_PreDownloadBmpsToFlash;
 
extern POS_QueryStatus					VC_POS_QueryStatus;
 
extern POS_RTQueryStatus				VC_POS_RTQueryStatus;
 
extern POS_KickOutDrawer				VC_POS_KickOutDrawer;
 
extern POS_CutPaper						VC_POS_CutPaper;

extern POS_StartDoc						VC_POS_StartDoc;

extern POS_EndDoc						VC_POS_EndDoc;
 
extern POS_EndSaveFile					VC_POS_EndSaveFile;
 
extern POS_BeginSaveFile				VC_POS_BeginSaveFile;
/***********ֻ֧�ֱ�׼��ӡģʽ(��ģʽ)�ĺ���************/
extern POS_S_SetAreaWidth				VC_POS_S_SetAreaWidth;

extern POS_S_TextOut					VC_POS_S_TextOut;

extern POS_S_DownloadAndPrintBmp		VC_POS_S_DownloadAndPrintBmp;
 
extern POS_S_PrintBmpInRAM				VC_POS_S_PrintBmpInRAM;
 
extern POS_S_PrintBmpInFlash			VC_POS_S_PrintBmpInFlash;
 
extern POS_S_SetBarcode				VC_POS_S_SetBarcode;
/*******ֻ֧��ҳ��ӡģʽ(P)���ǩ��ӡģʽ(L)�ĺ���*******/
extern POS_PL_SetArea					VC_POS_PL_SetArea;
 
extern POS_PL_TextOut					VC_POS_PL_TextOut;

extern POS_PL_DownloadAndPrintBmp		VC_POS_PL_DownloadAndPrintBmp;
 
extern POS_PL_PrintBmpInRAM			VC_POS_PL_PrintBmpInRAM;

extern POS_PL_SetBarcode				VC_POS_PL_SetBarcode;
 
extern POS_PL_Print					VC_POS_PL_Print;

extern POS_PL_Clear					VC_POS_PL_Clear; 
/*****����---��Ҫ���ڵ��Ժ��Զ�����ƺ���ʹ��*****/
extern POS_WriteFile					VC_POS_WriteFile;
 
extern POS_ReadFile					VC_POS_ReadFile;
 
extern POS_SetHandle					VC_POS_SetHandle;
 
extern POS_GetVersionInfo				VC_POS_GetVersionInfo;
// -----------------------------------------------------------------------------
// ��ӡͷ���ԼΪ 80mm �Ĵ�ӡ����

BOOL PrintInStandardMode80(void)
{
	static bool bIsFirst = true;
	
	//�ѷ��͵���ӡ����ͨѶ�˿ڵ����ݺ�ָ��浽�ļ�"Test.txt"��
	if(bSaveToTxt)
	{
		VC_POS_BeginSaveFile("Test.txt", false);
	}

	if (bIsFirst)
	{
		// Ԥ����λͼ�� Flash��������粻�ᶪʧ

		char *pBitImages[2];
		pBitImages[0] = "Kitty.bmp";
		pBitImages[1] = "Look.bmp";
		int nRet = VC_POS_PreDownloadBmpToRAM("Kitty.bmp", 0);
		nRet = VC_POS_PreDownloadBmpToRAM("generate.bmp", 1);
		//int nRet = VC_POS_PreDownloadBmpsToFlash(pBitImages, 2);generate

		if(POS_SUCCESS != nRet)
		{
			return false;
		}
		bIsFirst = false;
	}

    int nRet = VC_POS_SetMotionUnit(180, 180);

	if(POS_SUCCESS != nRet)
	{
		return false;
	}

	VC_POS_SetMode(POS_PRINT_MODE_STANDARD);
	
	VC_POS_SetRightSpacing(0);

	VC_POS_SetLineSpacing(100);
	VC_POS_S_TextOut("Beiyang POS Printer", 50, 2, 3, POS_FONT_TYPE_STANDARD, 
		POS_FONT_STYLE_NORMAL);
		
	VC_POS_SetLineSpacing(35);

	VC_POS_FeedLine();
	VC_POS_FeedLine();

	VC_POS_S_TextOut("����������ӡ��", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_THICK_UNDERLINE);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("�� �� �� �� �� ӡ ��", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_THIN_UNDERLINE);
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	VC_POS_SetLineSpacing(24);

	// ��ͬ���ַ��Ҽ��
	
	VC_POS_SetRightSpacing(0);
	VC_POS_S_TextOut("BTP-2000CP", 20, 1, 1, POS_FONT_TYPE_STANDARD, 
		POS_FONT_STYLE_NORMAL);
	VC_POS_S_TextOut("POS Thermal Printer", 200, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();

	VC_POS_SetRightSpacing(2);
	VC_POS_S_TextOut("BTP-2001CP", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_S_TextOut("POS Thermal Printer", 200, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();

	VC_POS_SetRightSpacing(4);
	VC_POS_S_TextOut("BTP-2002CP", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_S_TextOut("POS Thermal Printer", 200, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	// ��ͬ���ַ����

	VC_POS_SetRightSpacing(2);
	VC_POS_S_TextOut("���������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("���������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_REVERSE);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("˳ʱ����ת90�������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_CLOCKWISE_90);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("���������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_UPSIDEDOWN);
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	

	// ��ӡ����

	VC_POS_SetRightSpacing(0);

	VC_POS_S_TextOut("----------------------------------", 50, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();

	VC_POS_S_TextOut("Barcode - Code 128", 160, 1, 1, POS_FONT_TYPE_COMPRESSED,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	VC_POS_S_SetBarcode("{A*1234ABCDE*{C5678", 50, POS_BARCODE_TYPE_CODE128,
		2, 50, POS_FONT_TYPE_COMPRESSED, POS_HRI_POSITION_BOTH, 19);
	VC_POS_FeedLine();
	
	VC_POS_S_TextOut("----------------------------------", 50, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);	
	VC_POS_FeedLine();

	// ��ӡ�����ص� Flash �е�λͼ

	VC_POS_FeedLine();
	VC_POS_S_TextOut("-------------> Logo 1", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	//VC_POS_S_PrintBmpInFlash(1, 20, POS_BITMAP_PRINT_NORMAL);
	int res = VC_POS_S_PrintBmpInRAM(0, 20,POS_BITMAP_PRINT_NORMAL );
	VC_POS_FeedLine();
	res = VC_POS_S_PrintBmpInRAM(0, 20,POS_BITMAP_PRINT_NORMAL );
	VC_POS_FeedLine();
	res = VC_POS_S_PrintBmpInRAM(0, 20,POS_BITMAP_PRINT_QUADRUPLE );
	VC_POS_FeedLine();
	VC_POS_S_TextOut("-------------> Logo 2", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	//VC_POS_S_PrintBmpInFlash(2, 20, POS_BITMAP_PRINT_NORMAL);

	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	// ��ֽ
	VC_POS_CutPaper(POS_CUT_MODE_FULL, 0);

	// �����������ݺ�ָ��ļ��Ĳ�����
	if(bSaveToTxt)
	{
		VC_POS_EndSaveFile();
	}

	return TRUE;
}

BOOL PrintInPageMode80(void)
{
	static bool bIsFirst = true;
	
	// �ѷ��͵���ӡ����ͨѶ�˿ڵ����ݺ�ָ��浽�ļ�"Test.txt"��
	if(bSaveToTxt)
	{
		VC_POS_BeginSaveFile("Test.txt", false);
	}
	// Ԥ����λͼ�� RAM�����������ʧ

	int nRet = VC_POS_PreDownloadBmpToRAM("kitty.bmp", 0);// ID ��Ϊ 0

	if(POS_SUCCESS != nRet)
	{
		return false;
	}

	VC_POS_PreDownloadBmpToRAM("Look.bmp", 1); // ID ��Ϊ 1

	VC_POS_SetMotionUnit(180, 180);

	VC_POS_SetMode(POS_PRINT_MODE_PAGE);	

	VC_POS_PL_SetArea(10, 10, 620, 800, POS_AREA_BOTTOM_TO_TOP);
	VC_POS_PL_Clear();

	VC_POS_SetRightSpacing(0);

	VC_POS_PL_TextOut("Beiyang POS Thermal Printer", 20, 80, 2, 2, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_THICK_UNDERLINE);

	// ��ͬ�ַ��Ҽ��

	VC_POS_SetRightSpacing(0);
	VC_POS_PL_TextOut("BTP-2000CP", 30, 140, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_TextOut("POS Thermal Printer", 300, 140, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	VC_POS_SetRightSpacing(4);
	VC_POS_PL_TextOut("BTP-2001CP", 30, 180, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_TextOut("POS Thermal Printer", 300, 180, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	VC_POS_SetRightSpacing(8);
	VC_POS_PL_TextOut("BTP-2002CP", 30, 220, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_TextOut("POS Thermal Printer", 300, 220, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	VC_POS_SetRightSpacing(0);

	VC_POS_PL_TextOut("********************", 110, 260, 2, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	// ��ӡ����

	VC_POS_PL_TextOut("Barcode - Code 128", 260, 290, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_SetBarcode("{A*123ABC*{C34567890", 40, 360, POS_BARCODE_TYPE_CODE128, 3, 50,
		POS_FONT_TYPE_COMPRESSED, POS_HRI_POSITION_BELOW, 20);	

	// ��ӡ�Ѿ����ص� RAM �е�λͼ

	VC_POS_PL_PrintBmpInRAM(0, 50,  450, POS_BITMAP_PRINT_NORMAL);
	VC_POS_PL_PrintBmpInRAM(0, 230, 450, POS_BITMAP_PRINT_NORMAL);
	VC_POS_PL_PrintBmpInRAM(1, 410, 450, POS_BITMAP_PRINT_NORMAL);
	VC_POS_PL_PrintBmpInRAM(1, 530, 450, POS_BITMAP_PRINT_NORMAL);

	VC_POS_PL_Print();
	VC_POS_PL_Clear();
	VC_POS_CutPaper(POS_CUT_MODE_PARTIAL, 150);

	// �����������ݺ�ָ��ļ��Ĳ�����
	if(bSaveToTxt)
	{
		VC_POS_EndSaveFile();
	}

	return TRUE;
}

// -----------------------------------------------------------------------------
// ��ӡͷ���ԼΪ 56mm �Ĵ�ӡ����

BOOL PrintInStandardMode56(void)
{
	static bool bIsFirst = true;
	
	// �ѷ��͵���ӡ����ͨѶ�˿ڵ����ݺ�ָ��浽�ļ�"Test.txt"��
	if(bSaveToTxt)
	{
		VC_POS_BeginSaveFile("Test.txt", false);
	}

	if (bIsFirst)
	{
		// Ԥ����λͼ�� Flash��������粻�ᶪʧ

		char *pBitImages[2];
		pBitImages[0] = "Kitty.bmp";
		pBitImages[1] = "Look.bmp";

		int nRet = VC_POS_PreDownloadBmpsToFlash(pBitImages, 2);

		if(POS_SUCCESS != nRet)
		{
			return false;
		}

		bIsFirst = false;
	}

	int nRet = VC_POS_SetMotionUnit(180, 180);

	if(POS_SUCCESS != nRet)
	{
		return false;
	}

	VC_POS_SetMode(POS_PRINT_MODE_STANDARD);
	
	VC_POS_SetRightSpacing(0);

	VC_POS_SetLineSpacing(100);
	VC_POS_S_TextOut("Beiyang POS Thermal Printer", 30, 1, 2, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
		
	VC_POS_SetLineSpacing(35);

	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_S_TextOut("����������ӡ��", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_THICK_UNDERLINE);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("�� �� �� �� �� ӡ ��", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_THIN_UNDERLINE);
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	VC_POS_SetLineSpacing(24);
	
	// ��ͬ���ַ��Ҽ��
	
	VC_POS_SetRightSpacing(0);
	VC_POS_S_TextOut("BTP-2000CP", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_S_TextOut("POS Printer", 200, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();

	VC_POS_SetRightSpacing(2);
	VC_POS_S_TextOut("BTP-2001CP", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_S_TextOut("POS Printer", 200, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();

	VC_POS_SetRightSpacing(4);
	VC_POS_S_TextOut("BTP-2002CP", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_S_TextOut("POS Printer", 200, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	// ��ͬ�������ʽ

	VC_POS_SetRightSpacing(5);
	VC_POS_S_TextOut("���������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("���������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_REVERSE);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("˳ʱ����ת90�������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_CLOCKWISE_90);
	VC_POS_FeedLine();
	VC_POS_S_TextOut("���������ӡ", 20, 1, 1, POS_FONT_TYPE_CHINESE,
		POS_FONT_STYLE_UPSIDEDOWN);
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	// ��ӡ����

	VC_POS_SetRightSpacing(0);
	
	VC_POS_S_TextOut("-----------------------", 50, 1, 1, POS_FONT_TYPE_STANDARD, 
		POS_FONT_STYLE_NORMAL);

	VC_POS_FeedLine();

	VC_POS_S_TextOut("Barcode - Code 128", 100, 1, 1, POS_FONT_TYPE_COMPRESSED,
		POS_FONT_STYLE_NORMAL);

	VC_POS_FeedLine();

	VC_POS_S_SetBarcode("{A*123AB{C567", 40, POS_BARCODE_TYPE_CODE128, 2, 50,
		POS_FONT_TYPE_COMPRESSED, POS_HRI_POSITION_BOTH, 13);
	
	VC_POS_S_TextOut("-----------------------", 50, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	VC_POS_FeedLine();

	// ��ӡ�����ص� Flash �е�λͼ

	VC_POS_FeedLine();
	VC_POS_S_TextOut("-------------> Logo 1", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_S_PrintBmpInFlash(1, 20, POS_BITMAP_PRINT_NORMAL);
	VC_POS_FeedLine();

	VC_POS_S_TextOut("-------------> Logo 2", 20, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_FeedLine();
	VC_POS_S_PrintBmpInFlash(2, 20, POS_BITMAP_PRINT_NORMAL);

	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();
	VC_POS_FeedLine();

	// ��ֽ
	VC_POS_CutPaper(POS_CUT_MODE_FULL, 0);

	// �����������ݺ�ָ��ļ��Ĳ�����
	if(bSaveToTxt)
	{
		VC_POS_EndSaveFile();
	}
	
	return TRUE;
}

BOOL PrintInPageMode56(void)
{
	static bool bIsFirst = true;	

	// �ѷ��͵���ӡ����ͨѶ�˿ڵ����ݺ�ָ��浽�ļ�"Test.txt"��
	if(bSaveToTxt)
	{
		VC_POS_BeginSaveFile("Test.txt", false);
	}

	// Ԥ����λͼ�� RAM�����������ʧ

	int nRet = VC_POS_PreDownloadBmpToRAM("kitty.bmp", 0); // ID ��Ϊ 0
	if(POS_SUCCESS != nRet)
	{
		return false;
	}
	VC_POS_PreDownloadBmpToRAM("Look.bmp", 1); // ID ��Ϊ 1

	VC_POS_SetMotionUnit(180, 180);

	VC_POS_SetMode(POS_PRINT_MODE_PAGE);	

	VC_POS_PL_SetArea(10, 10, 440, 800, POS_AREA_BOTTOM_TO_TOP);

	//VC_POS_PL_Clear();

	VC_POS_SetRightSpacing(0);

	VC_POS_PL_TextOut("Beiyang POS Thermal Printer", 0, 50, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_THICK_UNDERLINE);

	// ��ͬ�ַ��Ҽ��

	VC_POS_SetRightSpacing(0);
	VC_POS_PL_TextOut("BTP-2000CP", 5, 80, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_TextOut("POS Thermal Printer", 230, 80, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);


	VC_POS_SetRightSpacing(4);
	VC_POS_PL_TextOut("BTP-2001CP", 5, 110, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_TextOut("POS Thermal Printer", 230, 110, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	VC_POS_SetRightSpacing(8);
	VC_POS_PL_TextOut("BTP-2002CP", 5, 140, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	VC_POS_PL_TextOut("POS Thermal Printer", 230, 140, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);
	
	VC_POS_SetRightSpacing(0);
	VC_POS_SetLineSpacing(0);

	VC_POS_PL_TextOut("********************", 70, 170, 2, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	// ��ӡ����

	VC_POS_PL_TextOut("Barcode - Code 128", 180, 195, 1, 1, POS_FONT_TYPE_STANDARD,
		POS_FONT_STYLE_NORMAL);

	VC_POS_PL_SetBarcode("{A*12345ABC*{C90", 5, 260, POS_BARCODE_TYPE_CODE128, 3, 50,
		POS_FONT_TYPE_COMPRESSED, POS_HRI_POSITION_BELOW, 16);	
	
	// ��ӡ�Ѿ����ص� RAM �е�λͼ

	VC_POS_PL_PrintBmpInRAM(0, 50, 330, POS_BITMAP_PRINT_NORMAL);	
	VC_POS_PL_PrintBmpInRAM(1, 410, 330, POS_BITMAP_PRINT_NORMAL);


	VC_POS_PL_Print();

	VC_POS_PL_Clear();

	VC_POS_CutPaper(POS_CUT_MODE_PARTIAL, 150);

	// �����������ݺ�ָ��ļ��Ĳ�����
	if(bSaveToTxt)
	{
		VC_POS_EndSaveFile();
	}

	return TRUE;
}

