// SerialPort.cpp: implementation of the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SerialPort.h"

//#include "CommInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialPort::CSerialPort()
{
	m_hComm=INVALID_HANDLE_VALUE;
	m_dwCurPort=0;
	m_pSender=NULL;
	m_pfnOnReceiveData=NULL;

	m_pReadThread=NULL;

	m_dwBauti=0;
}

CSerialPort::~CSerialPort()
{
	Close();
}

BOOL CSerialPort::IsOpen()
{
	return m_hComm!=INVALID_HANDLE_VALUE;
}

void CSerialPort::Close()
{
	if (IsOpen())
	{
		if (m_pReadThread)
		{
			m_pReadThread->Terminate();
			delete m_pReadThread;
			m_pReadThread=NULL;
		}

		CloseHandle(m_hComm);
		m_hComm=INVALID_HANDLE_VALUE;
		
		
	}
}

BOOL CSerialPort::Open(DWORD dwPort,DWORD dwBauti,BOOL bWaitEvent)
{
	
	/*lpy-modifyed-add :	2012/03/28 有时也会打开COM0的串口。所以等于0，也是正常的。*/
	if (dwPort < 0||dwPort > 255)
	{
		return FALSE;
	}
	
	Close(); 
	
	TCHAR sPort[20]={0};

	if (dwPort < 10)
	{
	   _stprintf(sPort,_T("COM%d"), dwPort);
	}
	else
	{
		_stprintf(sPort,L"\\\\.\\COM%d",dwPort);
	}

	wprintf(L"CSerialPort::Open port : %s\n",sPort);
	m_hComm = CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		int n = GetLastError();
		TRACE(L"CSerialPort::Open sPort=%s,dwBauti=%d,failed!!!\n",sPort,dwBauti);

		TCHAR szTemp[MAX_PATH] = {0};
		_stprintf(szTemp,L"CSerialPort::Open port : %s Failed!!!!\n",sPort);
		wprintf(L"%s",szTemp);
		return FALSE;
	}
	
	this->m_dwCurPort = dwPort;
	this->m_dwBauti=dwBauti;

	TRACE(L"CSerialPort::Open sPort=%s,dwBauti=%d\n",sPort,dwBauti);
	
	DCB dcb;
	GetCommState(m_hComm,&dcb);
	dcb.DCBlength=sizeof(dcb);
	dcb.BaudRate=dwBauti;
	dcb.fParity=FALSE;
	dcb.Parity=NOPARITY;
	dcb.ByteSize=8;
	dcb.StopBits=ONESTOPBIT;
	SetCommState(m_hComm,&dcb);


	//PurgeComm(m_hComm,PURGE_TXCLEAR | PURGE_RXCLEAR);

	BOOL bRet=SetupComm(m_hComm,4096,4096);
	
	TRACE(L"CSerialPort::Open  SetupComm bRet=%d,error code=%d..\n",bRet,GetLastError());
	
	SetCommMask(m_hComm,EV_RXCHAR);
	
	COMMTIMEOUTS timeouts;
	GetCommTimeouts(m_hComm,&timeouts);

	TRACE(L"CSerialPort::Open  GetCommTimeouts ReadIntervalTimeout=%d,ReadTotalTimeoutMultiplier=%d,ReadTotalTimeoutConstant=%d..\n"
		,timeouts.ReadIntervalTimeout,timeouts.ReadTotalTimeoutMultiplier,timeouts.ReadTotalTimeoutConstant);



	// set the timeout values
	timeouts.ReadIntervalTimeout = 1000;
	timeouts.ReadTotalTimeoutMultiplier = 1000;
	timeouts.ReadTotalTimeoutConstant = 1000;
	timeouts.WriteTotalTimeoutMultiplier = 1000;
	timeouts.WriteTotalTimeoutConstant = 1000;

	bRet=SetCommTimeouts(m_hComm,&timeouts);
	TRACE(L"CSerialPort::Open  SetCommTimeouts bRet=%d,error code=%d..\n",bRet,GetLastError());

		
	m_bWaitEvent=bWaitEvent;
	
	m_pReadThread=new CReadCommThread();
	m_pReadThread->BindPort(this);
	m_pReadThread->Create();
	m_pReadThread->Resume();

	return TRUE;
}


BOOL CSerialPort::SetReceiveFunc(FOnReceiveData pfnOnReceiveData,LPVOID pSender)
{
	if (pfnOnReceiveData==NULL||pSender==NULL)
	{
		return FALSE;
	}
	m_pfnOnReceiveData=pfnOnReceiveData;
	m_pSender=pSender;
	return TRUE;
}


void CSerialPort::Purge(DWORD dwFlag)
{
	if (!IsOpen())
	{
		return ;
	}
    //PurgeComm(m_hComm,dwFlag);
}

void CSerialPort::SetMark(DWORD dwMark)
{
	if (!IsOpen())
	{
		return ;
	}
    SetCommMask(m_hComm,dwMark);
}

BOOL CSerialPort::WaitEvent(LPDWORD dwMark)
{
	if (!IsOpen())
	{
		return FALSE;
	}
	OVERLAPPED olWaite;
	memset(&olWaite,0,sizeof(olWaite)); 
	olWaite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

    WaitCommEvent(m_hComm,dwMark,&olWaite);
	DWORD dwByte=0;
	if(GetOverlappedResult(m_hComm,&olWaite,&dwByte,TRUE) == FALSE)
     {
         if(GetLastError() != ERROR_IO_PENDING)
	         {
		              return 0x30;
		        }

	     DWORD dwErrors;
         COMSTAT comStat;
         memset(&comStat,0,sizeof(comStat));
         ClearCommError(m_hComm,&dwErrors,&comStat);
         return FALSE;
     }
	return TRUE;
}

DWORD CSerialPort::Read(BYTE* pBuf, DWORD dwMax)
{
    if (!IsOpen())
    {
		TRACE(_T("CSerialPort::Read !IsOpen .\n"));
		return 0;
    }

	DWORD	dwErr		= 0;
	COMSTAT cmst		= {0};
	DWORD	dwHasRead	= 0;
	BOOL	bClearError	= FALSE;

	BOOL bRet = ClearCommError(m_hComm,&dwErr,&cmst);
	if (!bRet||cmst.cbInQue<=0)
	{
       return 0 ;
		//cmst.cbInQue = dwMax;
	}
	DWORD dwInQueue=cmst.cbInQue;
	long lStart=0;

	DWORD dwReadBytes=0;
	lStart=GetTickCount();
	
	
	
	while(dwHasRead<dwInQueue)
	{
		OVERLAPPED olRead;
		memset(&olRead,0,sizeof(olRead));
		dwReadBytes=0;
		bRet=ReadFile(m_hComm,pBuf+dwHasRead,dwInQueue-dwHasRead,&dwReadBytes,&olRead);
		OutputDebugStringA("Read ");
		for (int i=0; i<dwReadBytes; i++)
		{
			char wc[8] = {0};
			sprintf(wc,"%x ",pBuf[i]);
			OutputDebugStringA(wc);
		}
		OutputDebugStringA("\n");
		//TRACE(_T("CSerialPort::Read  dwInQueue=%d,dwReadBytes=%d.\n"),dwInQueue,dwReadBytes);
		if (!bRet||dwReadBytes<=0)
		{
			break;
		}
		dwHasRead += dwReadBytes;
	}
	
	
	return dwHasRead;
}

void CSerialPort::ReceiveData(LPBYTE pBuf, DWORD dwCnt)
{
    if (m_pfnOnReceiveData)
    {
		m_pfnOnReceiveData(m_pSender,pBuf,dwCnt);
    }
}

BOOL CSerialPort::Write(LPBYTE pBuf, DWORD dwByteCnt, LPDWORD dwWriteBytes)
{
	if (!IsOpen())
    {
		return FALSE;
    }

	//PurgeComm(m_hComm,PURGE_TXCLEAR | PURGE_RXCLEAR);
	OutputDebugStringA("Write ");
	for (int i=0; i<dwByteCnt; i++)
	{
		char wc[8] = {0};
		sprintf(wc,"%02x ",pBuf[i]);
		OutputDebugStringA(wc);
	}
	OutputDebugStringA("\n");
	OVERLAPPED olWrite;
	memset(&olWrite,0,sizeof(olWrite));
	olWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);  
    return WriteFile(m_hComm, pBuf, dwByteCnt, dwWriteBytes,&olWrite);
}

CReadCommThread::CReadCommThread()
{
	m_hThread=NULL;
	m_pPort=NULL;
	m_bTerminal=FALSE;

	m_iInputBuf=new BYTE[QUEUE_SIZE];

	memset(m_iInputBuf,0,QUEUE_SIZE);
	m_dwInputBufCnt=0;
	m_pBuffer=NULL;
	m_bRunning=FALSE;
	
}

CReadCommThread::~CReadCommThread()
{
	if (m_iInputBuf)
	{
		delete []m_iInputBuf;
		m_iInputBuf=NULL;
	}
}

void CReadCommThread::Create()
{
	DWORD dwThreadID=0;
    m_hThread=CreateThread(NULL,0,ThreadFunc,this,CREATE_SUSPENDED,&dwThreadID);
	//SetThreadPriority(m_hThread,THREAD_PRIORITY_ABOVE_NORMAL);
}

void CReadCommThread::BindPort(CSerialPort *pPort)
{
	m_pPort=pPort;

}

DWORD WINAPI CReadCommThread::ThreadFunc(LPVOID lParam)
{
	CReadCommThread *pThis=(CReadCommThread*)lParam;
	pThis->m_bTerminal=FALSE;

	if (!pThis)
	{
		pThis->m_bTerminal=TRUE;
		return 1;
	}

	pThis->Execute();

	pThis->m_bTerminal=TRUE;

	return 0;
}




void CReadCommThread::Execute()
{
	m_bRunning=TRUE;

	if (m_pPort->IsWaitEvent())
	{
	   m_pPort->SetMark(EV_RXCHAR|EV_TXEMPTY);
	}

	DWORD dwRet=0;
	DWORD dwWaitMark=0;
	while(TRUE)
	{
		if (!m_bRunning)
		{
			break;
		}

		if (m_pPort->IsWaitEvent())
		{
			if (!m_pPort->WaitEvent(&dwWaitMark))
			{ 
				goto EndExecute;
			}

			//TRACE(_T("CReadCommThread::Execute wait event success.\n"));
			if (dwWaitMark&EV_RXCHAR)
			{
				memset(m_iInputBuf,0,QUEUE_SIZE);
				m_dwInputBufCnt=m_pPort->Read(m_iInputBuf,QUEUE_SIZE);
				//TRACE(_T("CReadCommThread::Execute EV_RXCHAR cnt=%d.\n"),m_dwInputBufCnt);
				//wprintf(_T("CReadCommThread::Execute() EV_RXCHAR cnt=%d.\n"), m_dwInputBufCnt);
				if (m_dwInputBufCnt>0)
				{
					this->HandleData();
					//Sleep(50);			//debug
				}
			}
		}
		else
		{
			Sleep(SLEEP_TIME);
			memset(m_iInputBuf,0,QUEUE_SIZE);
			m_dwInputBufCnt=m_pPort->Read(m_iInputBuf,QUEUE_SIZE);

			if (m_dwInputBufCnt>0)
			{
				this->HandleData();
			}
		}

		//m_pPort->Purge(PURGE_RXCLEAR);	
		//m_pPort->SetMark(EV_RXCHAR);

		
	}

EndExecute:
	m_pPort->Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);
	return ;  
}

void CReadCommThread::Resume()
{
	ResumeThread(m_hThread);
}

void CReadCommThread::HandleData()
{
    if (m_dwInputBufCnt<=0)
    {
		return ;
    }
	
	m_pPort->ReceiveData(m_iInputBuf,m_dwInputBufCnt);	

    m_dwInputBufCnt=0;
}

void CReadCommThread::Terminate()
{
    m_bRunning=FALSE;
	if (m_hThread==NULL)			
	{
		return ;
	}
	if (!m_bTerminal)
	{

		m_pPort->SetMark(EV_ERR|EV_TXEMPTY);

		Sleep(20);
		DWORD dwExitCode=0;
		GetExitCodeThread(m_hThread,&dwExitCode);
		if (dwExitCode&STILL_ACTIVE)
		{
			TerminateThread(m_hThread,0);
			Sleep(10);
		}
	}
	CloseHandle(m_hThread);
	m_hThread=NULL;
	
}

DWORD WINAPI CSerialPort::ReadThreadFunc(LPVOID lParam)
{
	CSerialPort *pMain=(CSerialPort*)lParam;	
	pMain->SetMark(EV_RXCHAR);
	
	DWORD dwRet=0;
	DWORD dwWaitMark=0;
	while(TRUE)
	{
	
		
		Sleep(SLEEP_TIME);
		if (!pMain->WaitEvent(&dwWaitMark))
		{ 
			goto EndExecute;
		}
		if (dwWaitMark&EV_RXCHAR)
		{
			BYTE buf[QUEUE_SIZE];
			memset(buf,0,QUEUE_SIZE);
			DWORD dwInputBufCnt=pMain->Read(buf,QUEUE_SIZE);
			if (dwInputBufCnt>0)
			{
				pMain->ReceiveData(buf,dwInputBufCnt);
			}
		}
		
		pMain->SetMark(EV_RXCHAR);
		
	}
	
EndExecute:
    pMain->Purge(PURGE_TXCLEAR | PURGE_RXCLEAR);
    return 0;  
}

BOOL CSerialPort::ClearError()
{
	if (!IsOpen())
    {
		return FALSE;
    }
	DWORD dwErr=0;
	COMSTAT cmst={0};
    BOOL bRet=ClearCommError(m_hComm,&dwErr,&cmst);
	return bRet;
}

BOOL CSerialPort::Reset()
{
   	if (!IsOpen())
    {
		return FALSE;
    }

	this->Close();

	return this->Open(m_dwCurPort,m_dwBauti,m_bWaitEvent);

}
