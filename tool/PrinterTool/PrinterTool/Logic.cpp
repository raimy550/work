#include "stdafx.h"
#include "Logic.h"
#include "SerialPort.h"
#include "StringOp.h"
#include "BmpUtils.h"

CLogic::CLogic()
{
	m_pBmp=NULL;
	Init();
}

CLogic::~CLogic()
{

}

void CLogic::Init()
{
	m_serialPort = new CSerialPort();
	m_serialPort->Open(2, 115200);
	BYTE data[3] = {0x1c, 0x21, 0x8c};
	DWORD dwWrite;
	m_serialPort->Write(data, 3, &dwWrite);
}

void CLogic::DoLogicPrint(CString str)
{
	DWORD dwWrite;
	wstring wStr = str.GetBuffer(str.GetLength());
	string strRet = CStringOp::WtoC(wStr);
// 	WCHAR*   lp=str.GetBuffer(str.GetLength());          
// 	str.ReleaseBuffer();   
	strRet = strRet + "\n";
	m_serialPort->Write((LPBYTE)strRet.c_str(),strRet.length(), &dwWrite);	
}

void CLogic::DoLogicTestPrintBmp(CString bmpPath)
{
	if (m_pBmp!=NULL)
	{
		delete m_pBmp;
		m_pBmp=NULL;
	}

	m_pBmp = new CBmpUtils();

	m_pBmp->loadBmp(CStringOp::WtoC(bmpPath.GetString()));
	byte* buf;
	buf = m_pBmp->printerBmp(m_serialPort);
// 	DWORD dwWrite;
// 	m_serialPort->Write(buf, m_pBmp->getPrinterBmpCount(), &dwWrite);
}