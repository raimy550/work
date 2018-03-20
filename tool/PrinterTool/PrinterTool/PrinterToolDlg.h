
// PrinterToolDlg.h : 头文件
//

#pragma once

class CLogic;
// CPrinterToolDlg 对话框
class CPrinterToolDlg : public CDialog
{
// 构造
public:
	CPrinterToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRINTERTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();

	void InitView();

private:
	CEdit* m_pEdit;
	CLogic* m_pLogic;
public:
	afx_msg void OnBnClickedButtonPrinterBmp();
};
