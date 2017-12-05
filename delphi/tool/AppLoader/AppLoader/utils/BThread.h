#pragma once
#include <Windows.h>
class CBThread
{
public:
	CBThread()
	{
		m_hEvent = NULL;
		m_hThread = NULL;
	}

	~CBThread()
	{
		
	}
public:
	void InitThread()
	{
		m_bSuspend = true;
		m_bWorking = true;
		m_hEvent = ::CreateEvent(NULL, TRUE, false, NULL);
		m_hThread = ::CreateThread(NULL, 0, CBThread::ThreadProc, (LPVOID)this, CREATE_SUSPENDED, &m_dwThreadID);
	}

	void UnInitThread()
	{
		m_bWorking = false;
		if (m_hEvent != NULL)
		{
			DWORD dwRet = WaitForSingleObject(m_hEvent, 3000);

			if (WAIT_TIMEOUT == dwRet && m_hThread != NULL)
			{
				OutputDebugString(_T("-------------------UnInitThread time out\n"));
				TerminateThread(m_hThread, -1);
				m_hThread = NULL;
			}
			OutputDebugString(_T("-------------------UnInitThread sucess\n"));
			CloseHandle(m_hEvent);
			m_hEvent = NULL;
		}
		if (m_hThread != NULL)
		{
			CloseHandle(m_hThread);
			m_hThread = NULL;
		}
	}


	BOOL Resume()
	{
		if (m_hThread != NULL)
		{
			m_bSuspend? ::ResumeThread(m_hThread) : NULL;
			m_bSuspend = false;
			return TRUE;
		}
		return FALSE;
	}

	BOOL Suspend()
	{
		if (m_hThread != NULL)
		{
			m_bSuspend? NULL : ::SuspendThread(m_hThread);
			m_bSuspend = true;
			return TRUE;
		}
		return FALSE;
	}

	virtual DWORD CallBackThread(LPVOID lpParam) = 0;
private:

	static DWORD CALLBACK ThreadProc(LPVOID lpParam)
	{
		CBThread* pBThread = static_cast<CBThread*>(lpParam);
		if (NULL == pBThread)
		{
			return 0;
		}
		pBThread->CallBackThread(lpParam);
		SetEvent(pBThread->m_hEvent);
		return -1;
	}

private:
	HANDLE m_hThread;
	DWORD  m_dwThreadID;
	HANDLE m_hEvent;
	bool   m_bSuspend;
	bool   m_bWorking;
};