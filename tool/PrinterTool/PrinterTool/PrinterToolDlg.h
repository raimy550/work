
// PrinterToolDlg.h : ͷ�ļ�
//

#pragma once

class CLogic;
// CPrinterToolDlg �Ի���
class CPrinterToolDlg : public CDialog
{
// ����
public:
	CPrinterToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRINTERTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
