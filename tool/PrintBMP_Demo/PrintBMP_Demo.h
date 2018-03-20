// PrintBMP_Demo.h : main header file for the PRINTBMP_DEMO application
//

#if !defined(AFX_PRINTBMP_DEMO_H__6D374A92_C525_4143_AE05_86AF1784E3D9__INCLUDED_)
#define AFX_PRINTBMP_DEMO_H__6D374A92_C525_4143_AE05_86AF1784E3D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrintBMP_DemoApp:
// See PrintBMP_Demo.cpp for the implementation of this class
//

class CPrintBMP_DemoApp : public CWinApp
{
public:
	CPrintBMP_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintBMP_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPrintBMP_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTBMP_DEMO_H__6D374A92_C525_4143_AE05_86AF1784E3D9__INCLUDED_)
