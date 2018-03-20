#pragma once
class CSerialPort;
class CBmpUtils;
class CLogic 
{
public:
	CLogic();
	~CLogic();
	void DoLogicPrint(CString str);
	void DoLogicTestPrintBmp(CString bmpPath);
private:
	void Init();

private:
	CSerialPort* m_serialPort;
	CBmpUtils* m_pBmp;

};