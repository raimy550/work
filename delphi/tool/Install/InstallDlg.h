
// InstallDlg.h : ͷ�ļ�
//

#pragma once


// CInstallDlg �Ի���
class CInstallDlg : public CDialog
{
// ����
public:
	CInstallDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_INSTALL_DIALOG };

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
	afx_msg void OnBnClickedButtonInstall();
	void InitView();
	void InitLogic();
private:
	CStatic* m_pStaticInfo;
	CButton* m_pBtnStart;
public:
	afx_msg void OnBnClickedButtonUninstall();
};
