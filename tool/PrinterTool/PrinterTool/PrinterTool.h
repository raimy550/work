
// PrinterTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPrinterToolApp:
// �йش����ʵ�֣������ PrinterTool.cpp
//

class CPrinterToolApp : public CWinAppEx
{
public:
	CPrinterToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPrinterToolApp theApp;