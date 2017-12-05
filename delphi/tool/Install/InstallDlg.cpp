
// InstallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Install.h"
#include "InstallDlg.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CInstallDlg 对话框




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


// CInstallDlg 消息处理程序

BOOL CInstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MoveWindow(0,0,0,0);
	InitView();
	InitLogic();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
		ret = RegSetValueEx(RegKey,REG_KEY_NAME,0,REG_SZ,(BYTE*)(LPCTSTR)fullName,fullName.GetLength()*2);//这里加上你需要在注册表中注册的内容  
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CInstallDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CInstallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CInstallDlg::OnBnClickedButtonInstall()
{
	// TODO: 在此添加控件通知处理程序代码

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
	if (str.Compare(_T("开始运行"))==0)
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
			ret = RegSetValueEx(RegKey,REG_KEY_NAME,0,REG_SZ,(BYTE*)(LPCTSTR)fullName,fullName.GetLength()*2);//这里加上你需要在注册表中注册的内容  
			if (ret == ERROR_SUCCESS)
			{
				m_pStaticInfo->SetWindowText(STR_INSTALL_SUCESS);
				m_pBtnStart->SetWindowText(_T("开始运行"));
			}
			else
				m_pStaticInfo->SetWindowText(STR_INSTALL_FAIL);

			RegCloseKey(RegKey);
		}
		 
	}   
	else   
	{ 
		::AfxMessageBox(_T("没找到执行程序，请先解压安装包，再运行Install.exe"));   
		exit(0);   
	} 

}

void CInstallDlg::OnBnClickedButtonUninstall()
{
	// TODO: 在此添加控件通知处理程序代码
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
