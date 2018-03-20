// PrintBMP_DemoDlg.h : header file
//

#if !defined(AFX_PRINTBMP_DEMODLG_H__899F4FBC_BE3A_48E4_A47F_5B24F8B04091__INCLUDED_)
#define AFX_PRINTBMP_DEMODLG_H__899F4FBC_BE3A_48E4_A47F_5B24F8B04091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPrintBMP_DemoDlg dialog

class CPrintBMP_DemoDlg : public CDialog
{
// Construction
public:
	CPrintBMP_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintBMP_DemoDlg)
	enum { IDD = IDD_PRINTBMP_DEMO_DIALOG };
	CComboBox	m_baud;
	CComboBox	m_port;
	int		m_PrinterType;
	CString	m_Addr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintBMP_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPrintBMP_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnExit();
	afx_msg void OnConnet();
	afx_msg void OnFindBMP();
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTBMP_DEMODLG_H__899F4FBC_BE3A_48E4_A47F_5B24F8B04091__INCLUDED_)
