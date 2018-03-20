// SerialPort.h: interface for the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALPORT_H__D7CDE38B_0012_422F_A77A_0ECB36941689__INCLUDED_)
#define AFX_SERIALPORT_H__D7CDE38B_0012_422F_A77A_0ECB36941689__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#define QUEUE_SIZE 10240*8/*256*//*evdo 8192 or 4096*/

/************************************************************************/
/* 由于以前是有可能读取大量的短信和电话本数据，导致要把回应数据缓冲区调到256K，
现在改为循环单次读取数据，所以只需把回应数据缓冲区调到4K，基本上就能够满足了。
*/
/************************************************************************/

#define MAX_DATA_SIZE 512

#define SLEEP_TIME 50

typedef void (* FOnReceiveData)(LPVOID,void*,DWORD);


class CReadCommThread;

class CSerialPort  
{
public:
	BOOL Reset();
	BOOL ClearError();
	static DWORD WINAPI ReadThreadFunc(LPVOID lParam);
	BOOL Write(LPBYTE  pBuf,DWORD dwByteCnt,LPDWORD dwWriteBytes);
	void ReceiveData(LPBYTE pBuf,DWORD dwCnt);
	DWORD Read(BYTE*  pBuf,DWORD dwMax);
	BOOL WaitEvent(LPDWORD dwMark);
	void SetMark(DWORD dwMark);
	void Purge(DWORD dwFlag);



	BOOL Open(DWORD dwPort,DWORD dwBauti,BOOL bWaitEvent = TRUE);
	void Close();
	BOOL IsOpen();
	CSerialPort();
	virtual ~CSerialPort();

	BOOL SetReceiveFunc(FOnReceiveData pfnOnReceiveData,LPVOID pSender);

	BOOL IsWaitEvent()
	{
		return m_bWaitEvent;
	}

	

private:
	HANDLE             m_hComm;
	DWORD              m_dwCurPort;
	FOnReceiveData     m_pfnOnReceiveData;
	LPVOID             m_pSender;
    HANDLE             m_hCloseEvent; 
	CReadCommThread    *m_pReadThread;
	DWORD              m_dwBauti;

	BOOL               m_bWaitEvent;

};




class CReadCommThread  
{
public:
	void Terminate();
	void Resume();
	void Execute();
	void BindPort(CSerialPort *pPort);
	void Create();
	CReadCommThread();
	virtual ~CReadCommThread();

	static DWORD WINAPI ThreadFunc(LPVOID lParam);

	
	BOOL         m_bTerminal;
	
	
private:
	
	HANDLE       m_hThread;
	CSerialPort  *m_pPort;
	BYTE         *m_iInputBuf;
	BYTE         *m_pBuffer;
	DWORD         m_dwInputBufCnt;
	
	BOOL          m_bRunning;


	
protected:
	void HandleData();
};


#endif // !defined(AFX_SERIALPORT_H__D7CDE38B_0012_422F_A77A_0ECB36941689__INCLUDED_)
