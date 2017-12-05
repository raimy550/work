
// InstallDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Install.h"
#include "InstallDlg.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CInstallDlg �Ի���




CInstallDlg::CInstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstallDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInstallDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_INSTALL, &CInstallDlg::OnBnClickedButtonInstall)
	ON_BN_CLICKED(IDC_BUTTON_UNINSTALL, &CInstallDlg::OnBnClickedButtonUninstall)
END_MESSAGE_MAP()


// CInstallDlg ��Ϣ�������

BOOL CInstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	MoveWindow(0,0,0,0);
	InitView();
	InitLogic();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CInstallDlg::InitView()
{
	m_pStaticInfo = (CStatic*)GetDlgItem(IDC_STATIC_INFO);
	m_pStaticInfo->SetWindowText(STR_INSTALL_INFO);
	m_pBtnStart = (CButton*)GetDlgItem(IDC_BUTTON_INSTALL);
}

void CInstallDlg::InitLogic()
{
	HKEY RegKey;
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer();   
	int   nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos);   
	CString lpszFile = sPath + _T("\\")+ POWER_ON_EXE_NAME; 

	CString   fullName;   
	fullName=lpszFile;   
	RegKey=NULL;   
	LSTATUS ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &RegKey);  
	if (ret == ERROR_SUCCESS)
	{
		ret = RegSetValueEx(RegKey,REG_KEY_NAME,0,REG_SZ,(BYTE*)(LPCTSTR)fullName,fullName.GetLength()*2);//�����������Ҫ��ע�����ע�������  
		if (ret != ERROR_SUCCESS)
		{
			RegCloseKey(RegKey);
			PostMessage(WM_QUIT,0,0);
		}
		RegCloseKey(RegKey);
	}
	PostMessage(WM_QUIT,0,0);
}

void CInstallDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInstallDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CInstallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CInstallDlg::OnBnClickedButtonInstall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	HKEY RegKey;
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer();   
	int   nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos);   
	CString lpszFile = sPath + _T("\\")+ POWER_ON_EXE_NAME; 

	CString str;
	m_pBtnStart->GetWindowText(str);
	if (str.Compare(_T("��ʼ����"))==0)
	{
		SHELLEXECUTEINFO shell = { sizeof(shell) };
		shell.fMask = SEE_MASK_FLAG_DDEWAIT;
		shell.lpVerb = L"open";
		shell.lpFile = lpszFile;
		shell.nShow = SW_SHOWNORMAL;
		BOOL ret = ShellExecuteEx(&shell);
		PostMessage(WM_QUIT,0,0);
		return;
	}


	CFileFind   fFind;   
	BOOL   bSuccess;   
	bSuccess=fFind.FindFile(lpszFile);   
	fFind.Close();   
	if(bSuccess)   
	{   
		CString   fullName;   
		fullName=lpszFile;   
		RegKey=NULL;   
		LSTATUS ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &RegKey);  
		if (ret == ERROR_SUCCESS)
		{
			ret = RegSetValueEx(RegKey,REG_KEY_NAME,0,REG_SZ,(BYTE*)(LPCTSTR)fullName,fullName.GetLength()*2);//�����������Ҫ��ע�����ע�������  
			if (ret == ERROR_SUCCESS)
			{
				m_pStaticInfo->SetWindowText(STR_INSTALL_SUCESS);
				m_pBtnStart->SetWindowText(_T("��ʼ����"));
			}
			else
				m_pStaticInfo->SetWindowText(STR_INSTALL_FAIL);

			RegCloseKey(RegKey);
		}
		 
	}   
	else   
	{ 
		::AfxMessageBox(_T("û�ҵ�ִ�г������Ƚ�ѹ��װ����������Install.exe"));   
		exit(0);   
	} 

}

void CInstallDlg::OnBnClickedButtonUninstall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HKEY RegKey;
	LSTATUS ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &RegKey);  
	if (ret == ERROR_SUCCESS)
	{
		RegDeleteValue(RegKey, REG_KEY_NAME);
		RegCloseKey(RegKey);		
	}

// 	ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &RegKey);  
// 	if (ret == ERROR_SUCCESS)
// 	{
// 		RegDeleteValue(RegKey, _T("inject"));
// 		RegCloseKey(RegKey);		
// 	}
	

}
