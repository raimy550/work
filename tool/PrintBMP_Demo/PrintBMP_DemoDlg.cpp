// PrintBMP_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrintBMP_Demo.h"
#include "PrintBMP_DemoDlg.h"
#include "devioctl.h"
#include "usbiodef.h"
#include "usbprint.h"
#include <setupapi.h>
#include <devguid.h>
#include "SetupApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFont  m_font;
HANDLE m_hcom;                                 //2013.12.10
DCB    dcb;
BOOL   Connect;
COMMTIMEOUTS comtimeout;
BYTE WINAPI SetByte(BYTE byte, int Index);
unsigned char Byte2HalfByte(unsigned char cData);
void TwoByte2OddEven(unsigned char *pFirst,unsigned char *pSecond);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintBMP_DemoDlg dialog

CPrintBMP_DemoDlg::CPrintBMP_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintBMP_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintBMP_DemoDlg)
	m_PrinterType = 0;
	m_Addr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrintBMP_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintBMP_DemoDlg)
	DDX_Control(pDX, IDC_COMBO2, m_baud);
	DDX_Control(pDX, IDC_COMBO1, m_port);
	DDX_Radio(pDX, IDC_RADIO1, m_PrinterType);
	DDX_Text(pDX, IDC_EDIT1, m_Addr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPrintBMP_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintBMP_DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, OnExit)
	ON_BN_CLICKED(IDC_BUTTON1, OnConnet)
	ON_BN_CLICKED(IDC_BUTTON3, OnFindBMP)
	ON_BN_CLICKED(IDC_BUTTON4, OnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintBMP_DemoDlg message handlers

BOOL CPrintBMP_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	/******************************************************************************/
	LOGFONT lf;
	CFont *pfont;
	pfont=GetDlgItem(IDC_STATIC_LOGE)->GetFont();
	pfont->GetLogFont(&lf);
	lf.lfHeight=-25;
	lf.lfWeight=800;
	m_font.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_LOGE)->SetFont(&m_font);
	/******************************************************************************/
	Connect = 0;
	m_port.InsertString(0,"COM1");
	m_port.InsertString(1,"COM2");
	m_port.InsertString(2,"COM3");
	m_port.InsertString(3,"COM4");
	m_port.InsertString(4,"LPT1");
	m_port.InsertString(5,"LPT2");
	m_port.InsertString(6,"USB");
	m_port.SetCurSel(0);
	
	m_baud.InsertString(0,"4800");
	m_baud.InsertString(1,"9600");
	m_baud.InsertString(2,"19200");
	m_baud.InsertString(3,"38400");
	m_baud.InsertString(4,"115200");
	
	m_baud.SetCurSel(4);
    
	m_PrinterType = 0;
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPrintBMP_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPrintBMP_DemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPrintBMP_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CPrintBMP_DemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_LOGE)
	{
		pDC->SetTextColor(RGB(0,0,255));
		//pDC->SetBkColor(RGB(255,255,255));
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CPrintBMP_DemoDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	if(m_hcom!=NULL)
	{
		CloseHandle(m_hcom);
		Connect=0;
		m_hcom=NULL;
	}
	OnOK();	
}
static const GUID GuidName = { 0x28d78fad, 0x5a12, 0x11D1, { 0xae, 0x5b,  0x00,  0x00,  0xf8,  0x03,  0xa8,  0xc2 } };
void CPrintBMP_DemoDlg::OnConnet() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//OpenPrinter();
	if(!Connect)
	{
		CString a,b;
		int baudn;
		m_port.GetWindowText(a);
		m_baud.GetWindowText(b);
		if(m_hcom!=NULL)
		{
			CloseHandle(m_hcom);
			m_hcom=NULL;
		}
		if((a == "LPT1")||(a == "LPT2"))
		{
			m_hcom=CreateFile(a,GENERIC_WRITE,FILE_SHARE_READ ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(m_hcom==(HANDLE)-1)//打开串口失败
			{
				AfxMessageBox("此端口被占用或已损坏");
				m_hcom=NULL;
				return;
			}
			GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);//隐藏波特率选项
			GetDlgItem(IDC_STATIC_BAUD)->ShowWindow(SW_HIDE);
		}
		else if((a == "USB"))
		{
			char cInterfaceName[255];	//打印机路径名
			int iCount = 0;
			HDEVINFO devs;
			DWORD devcount;
			SP_DEVINFO_DATA devinfo;
			SP_DEVICE_INTERFACE_DATA devinterface;
			DWORD size;
			GUID intfce;
			PSP_DEVICE_INTERFACE_DETAIL_DATA interface_detail;
			memset(cInterfaceName,0,255);
			intfce = GuidName;
			devs = SetupDiGetClassDevs(&intfce, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
			if (devs == INVALID_HANDLE_VALUE) 
			{
				//MessageBox("ERROR");
				return ;
			}
			
			devcount = 0;
			devinterface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
			if(!SetupDiEnumDeviceInterfaces(devs, 0, &intfce, iCount, &devinterface))
			{
				MessageBox("无法找到USB设备");
				return;
			}
			while (SetupDiEnumDeviceInterfaces(devs, 0, &intfce, iCount, &devinterface)) 
			{
				iCount++;
				char driverkey[255]; 
				
				size = 0;
				/* See how large a buffer we require for the device interface details */
				SetupDiGetDeviceInterfaceDetail(devs, &devinterface, 0, 0, &size, 0);
				devinfo.cbSize = sizeof(SP_DEVINFO_DATA);
				interface_detail = (_SP_DEVICE_INTERFACE_DETAIL_DATA_A *)calloc(1, size);
				if (interface_detail) 
				{
					interface_detail->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA);
					devinfo.cbSize = sizeof(SP_DEVINFO_DATA);
					if (!SetupDiGetDeviceInterfaceDetail(devs, &devinterface, interface_detail, size, 0, &devinfo)) 
					{
						free(interface_detail);
						SetupDiDestroyDeviceInfoList(devs);
						return ;
					}
					/* Make a copy of the device path for later use */
					
					memset(driverkey,0,50);
					DWORD dataType;
					if (!SetupDiGetDeviceRegistryProperty(devs, &devinfo, SPDRP_HARDWAREID, &dataType,
						(LPBYTE)driverkey, size, 0)) 
					{
						SetupDiDestroyDeviceInfoList(devs);
						return ;
					}
					
					_strupr(driverkey);
					
					//if(strstr(driverkey,"VID_0483") != NULL)
					{
						strcpy(cInterfaceName, interface_detail->DevicePath);
						free(interface_detail);
						SetupDiDestroyDeviceInfoList(devs);	
						m_hcom=INVALID_HANDLE_VALUE;
						m_hcom=CreateFile(cInterfaceName, GENERIC_WRITE|GENERIC_READ, 0,
							NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
						if(m_hcom!=INVALID_HANDLE_VALUE)
						{
							//MessageBox("打开端口成功");
						}
						else
						{
						//	MessageBox("打开端口失败");
						}
						
						break;
					}
					
				}
				else
				{
					SetupDiDestroyDeviceInfoList(devs);
					//	return iNumber;
				}
			}
			
			SetupDiDestroyDeviceInfoList(devs);	
			GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);//隐藏波特率选项
			GetDlgItem(IDC_STATIC_BAUD)->ShowWindow(SW_HIDE);
		}
		else
		{
			m_hcom=CreateFile(a,GENERIC_WRITE|GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(m_hcom==(HANDLE)-1)//打开串口失败
			{
				AfxMessageBox("此端口被占用或已损坏");
				m_hcom=NULL;
				return;
			}
			
			if (b=="4800")
				baudn=4800;
			else if(b=="9600")
				baudn=9600;
			else if(b=="19200")
				baudn=19200;
			else if(b=="38400")
				baudn=38400;
			else if(b=="115200")
				baudn=115200;
			else 
				baudn=9600;
			
			GetCommState(m_hcom,&dcb);
			dcb.BaudRate=baudn;
			dcb.ByteSize=8;
			dcb.Parity=NOPARITY;
			dcb.StopBits=ONESTOPBIT;
			dcb.fOutxCtsFlow =0;
			dcb.fOutxDsrFlow =0;
			dcb.fRtsControl =0;
			dcb.fDtrControl =0;
			SetCommState(m_hcom,&dcb);
			SetupComm(m_hcom,1024,1024);
		}		
		comtimeout.ReadIntervalTimeout=0xffff;
		comtimeout.ReadTotalTimeoutConstant=0xffff;
		comtimeout.ReadTotalTimeoutMultiplier=0xffff;
		comtimeout.WriteTotalTimeoutConstant=0xffff;
		comtimeout.WriteTotalTimeoutMultiplier=0xffff;
		SetCommTimeouts(m_hcom,&comtimeout);
		//SetTimer(0,100,NULL);//开启定时器  每500ms读一下串口
		GetDlgItem(IDC_BUTTON1)->SetWindowText("断  开");//连接按钮显示断开
		PurgeComm(m_hcom,PURGE_TXCLEAR| PURGE_RXCLEAR);//清除BUFF
		GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(true);

		GetDlgItem(IDC_COMBO1)->EnableWindow(false);
		GetDlgItem(IDC_COMBO2)->EnableWindow(false);
		Connect=1;
	}
	else
	{
		Connect=0;
		//KillTimer(0);
		GetDlgItem(IDC_BUTTON1)->SetWindowText("连  接");
		GetDlgItem(IDC_COMBO1)->EnableWindow(true);
		GetDlgItem(IDC_COMBO2)->EnableWindow(true);

		GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(false);

		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BAUD)->ShowWindow(SW_SHOW);
		CloseHandle(m_hcom);
		m_hcom=NULL;
	}	
}

void CPrintBMP_DemoDlg::OnFindBMP() 
{
	// TODO: Add your control notification handler code here
	CString strFileName;
	CFile file;
	CFileException e;
	
	char BASED_CODE szFilter[] = "Bmp Files (*.bmp)|*.bmp | All Files (*.*)|*.*||";
	HWND hDlg=GetSafeHwnd();
	CFileDialog OpenFileDlg(TRUE, "*.bmp", "*.bmp", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	
	if(OpenFileDlg.DoModal() == IDOK)
	{
		strFileName = OpenFileDlg.GetPathName();
		file.Open(strFileName, CFile::modeRead, &e);
		m_Addr = strFileName;
	}
	else
	{
		return;
	}
	file.Close();
	UpdateData(FALSE);
	//char *Name;
	//Name = (LPTSTR)(LPCSTR)strFileName;
}

void CPrintBMP_DemoDlg::OnPrint() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BYTE *lpImgData;
	//	BYTE *lpTempPtr;
	BYTE *ImgData;
	int *lpIntBuf; //add
	HDC hDisplayDC=NULL;
	HDC hDisplayMemDC=NULL;
	HBITMAP hBitmap;
	HBITMAP hBitmap2;
	HBITMAP hOldBitmap=NULL;
	long BufSize;
	int ImgWidth,ImgHeight,LineBytes;
	BITMAP bm;
	COLORREF color,oldcolor;
	BYTE r,g,b;
	int i,j;
    int rows,cols;
    
	char *Name;
	if(m_Addr=="")
	{
		MessageBox("请选择正确的BMP路径");
		return;
	}	
	Name = (LPTSTR)(LPCSTR)m_Addr;
	hBitmap=(HBITMAP)::LoadImage(NULL,Name,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);//|LR_LOADTRANSPARENT);
	DWORD error = GetLastError();
	if (hBitmap==NULL) return;
	
	::ZeroMemory(&bm,sizeof(BITMAP));
	::GetObject(hBitmap,sizeof(BITMAP),&bm);
	
	ImgWidth=bm.bmWidth;
	ImgHeight=bm.bmHeight;
	
	LineBytes=(bm.bmBitsPixel*ImgWidth+31)/8;
	LineBytes=LineBytes/4*4;
	LineBytes=bm.bmWidthBytes;
	
	hDisplayDC=::GetDC(NULL);
	hDisplayMemDC=::CreateCompatibleDC(hDisplayDC);
	hBitmap2=(HBITMAP)::CreateCompatibleBitmap(hDisplayDC,ImgWidth,ImgHeight);
	hOldBitmap=(HBITMAP)::SelectObject(hDisplayMemDC,hBitmap2);
	::SelectObject(hDisplayMemDC,hBitmap);
	
	if (ImgWidth>640) ImgWidth=640;
	BufSize=ImgWidth*(ImgHeight);
	lpImgData=(BYTE *)malloc(BufSize);
	
	if (lpImgData==NULL) return;
	memset(lpImgData,0xff,BufSize);
	lpIntBuf=(int *)malloc(BufSize*sizeof(int));
	
	if (lpIntBuf==NULL) 
	{
		if (lpImgData!=NULL)
			free(lpImgData);
		return;
	}
	
// 	if( (ImgHeight*ImgWidth/8) > 72*640 )
// 	{
// 		return;
// 	}
	
	for (j=0;j<ImgWidth;j++)
	{
		for ( i=0;i<ImgHeight;i++)
		{
			color=::GetPixel(hDisplayMemDC,i,j);
			r=GetRValue(color);
			g=GetGValue(color);
			b=GetBValue(color);
			r=(9798*r+19235*g+3735*b)/32768;
			if (r>240)
			{
				oldcolor=RGB(255,255,255);
			}
			else
			{
				oldcolor=RGB(0,0,0);
			}
			::SetPixelV(hDisplayMemDC,i,j,oldcolor);
		}
	}
	if(m_PrinterType == 0)
	{
		//MessageBox("remin");
		
		rows=(int)((ImgHeight+23)/24);
		cols=ImgWidth;
		ImgData=new BYTE[rows*cols*3];
		BYTE* data=new BYTE[rows*cols*3];
		memset(ImgData,0,rows*cols*3);
		for (i=0;i<rows;i++)
		{
			for (j=0;j<cols;j++)
			{
				for (int l=0;l<3;l++)
				{
					for (int k=0;k<8;k++)
					{
						if (::GetPixel(hDisplayMemDC,j,24*i+l*8+k)==RGB(0,0,0))
						{
							ImgData[3*i*cols+j*3+l]=SetByte(ImgData[3*i*cols+j*3+l],7-k);
						}
					}
				}
			}
		}
        int t =0;
		memset(data,0,sizeof(data));
		for (j=0;j<rows;j++)
		{
			for (i=0;i<cols;i++)
			{
				for (int k=0;k<3;k++)

					data[t++] = ImgData[3*j*cols+3*i+k];
			}
		}
		BYTE buf[20];
		DWORD dw;
		
		
		for (i=0;i<rows;i++)
		{
			buf[0]=0x1b;
			buf[1]=0x2a;
			buf[2]=33;
			buf[3]=cols%256;
			buf[4]=cols/256;
			WriteFile(m_hcom,buf,5,&dw,NULL);
			WriteFile(m_hcom,&data[i*cols*3],cols*3,&dw,NULL);
			buf[0]=0x1B;
			buf[1]=0x4A;
			buf[2]=24; 
			WriteFile(m_hcom,buf,3,&dw,NULL);
		}

		buf[0]=0x1d;
		buf[1]=0x56;
		buf[2]=0x42;//m
		buf[3]=0x00;
		WriteFile(m_hcom,buf,4,&dw,NULL);
	}
	else
	{
		//MessageBox("zhenda");
		unsigned char data1[10000];
		unsigned char data2[10000];
		rows=(int)(ImgHeight/8+(ImgHeight%8==0?0:1));
		cols=ImgWidth;
		ImgData=new BYTE[rows*cols+cols];
		memset(ImgData,0,rows*cols+cols);
		for (i=0;i<rows;i++)
		{
			for (j=0;j<cols;j++)
			{
				for (int k=0;k<8;k++)
				{
					if (::GetPixel(hDisplayMemDC,j,8*i+k)==RGB(0,0,0))
					{
						ImgData[i*cols+j]=SetByte(ImgData[i*cols+j],7-k);
					}
				}
			}
		}

		int t =0;
		memset(data1,0,10000);
		memset(data2,0,10000);
		for (int j=0;j<rows;j=j+2)
		{
			for (int i=0;i<cols;i++)
			{
				TwoByte2OddEven(&ImgData[j*cols+i],&ImgData[(j+1)*cols+i]);
				data1[t] = ImgData[j*cols+i];
				data2[t] = ImgData[(j+1)*cols+i];
				t++;
			}
		}
		BYTE buf[20];
		DWORD dw;
		for (i=0;i< rows/2;i++)
		{
			buf[0]=0x1b;
			buf[1]=0x2a;
			buf[2]=1;
			buf[3]=cols%256;
			buf[4]=cols/256;
			WriteFile(m_hcom,buf,5,&dw,NULL);
			WriteFile(m_hcom,&data1[i*cols],cols,&dw,NULL);
			buf[0]=0x1B;
			buf[1]=0x4A;
			buf[2]=1; 
			WriteFile(m_hcom,buf,3,&dw,NULL);

			buf[0]=0x1b;
			buf[1]=0x2a;
			buf[2]=1;
			buf[3]=cols%256;
			buf[4]=cols/256;
			WriteFile(m_hcom,buf,5,&dw,NULL);
			WriteFile(m_hcom,&data2[i*cols],cols,&dw,NULL);
			buf[0]=0x1B;
			buf[1]=0x4A;
			buf[2]=15; 
			WriteFile(m_hcom,buf,3,&dw,NULL);
		}
		if(rows/2)
		{
			buf[0]=0x1b;
			buf[1]=0x2a;
			buf[2]=1;
			buf[3]=cols%256;
			buf[4]=cols/256;
			WriteFile(m_hcom,buf,5,&dw,NULL);
			WriteFile(m_hcom,&data1[(rows+1)/2*cols],cols,&dw,NULL);
			buf[0]=0x1B;
			buf[1]=0x4A;
			buf[2]=16; 
			WriteFile(m_hcom,buf,3,&dw,NULL);
		}
		buf[0]=0x1d;
		buf[1]=0x56;
		buf[2]=0x42;//m
		buf[3]=0x00;
		WriteFile(m_hcom,buf,4,&dw,NULL);
	}
}
BYTE WINAPI SetByte(BYTE byte, int Index)
{
	BYTE bTemp2=1;
	bTemp2<<=Index;
	return (byte|bTemp2);
}
unsigned char Byte2HalfByte(unsigned char cData)
{
	unsigned char cResult;
	cResult = 0;
	// odd bit 1010 1010=0xaa
	cData &= 0xaa;
	// bit 7
	cResult = cData & 0x80;
	// bit 5
	cResult |= (cData & 0x20) << 1;
	// bit 3
	cResult |= (cData & 0x08) << 2;
	// bit 1
	cResult |= (cData & 0x02) << 3;
	return cResult;
}

void TwoByte2OddEven(unsigned char *pFirst,unsigned char *pSecond)
{
	unsigned char cOdd;
	unsigned char cEven;
	cOdd = Byte2HalfByte(*pFirst) | (Byte2HalfByte(*pSecond) >> 4);
	cEven = Byte2HalfByte(*pFirst<<1) | (Byte2HalfByte(*pSecond<<1) >> 4);
	*pFirst = cOdd;
	*pSecond = cEven;
}
