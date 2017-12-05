/*
���������ض����HTTP���ؿ⣬��ʱֻ֧������
Ҧ����
2014��10��30��18:05:13
*/
#pragma once
#include <string>
#include <map>
using std::wstring;
using std::string;
using std::map;
#include <WinSock2.h>


//����HTTP����ͷ
struct HTTP_HERDER
{
	char szType[5];				//�������ͣ�GET����POST
	char szRequest[MAX_PATH];	//��������
	char szVersion[9];			//HTTP�汾���̶�ֵ��HTTP/1.1
	char szAccept[100];			//�����ļ����ͣ�Ĭ��ֵΪ��nAccept: */*
	char szHostName[30];		//������������ַ�����磺www.baidu.com
	char szRange[11];			//�ϵ�������ʼ�㣬Range: bytes=*-
	char szConnection[11];		//���ӷ�ʽ��Ĭ�ϣ�Keep-Alive
	HTTP_HERDER()
	{
		memset(this, 0, sizeof(HTTP_HERDER));
		strcpy_s(szVersion, "HTTP/1.1");
		strcpy_s(szConnection, "Keep-Alive");
	}
	string ToString()
	{
		string strRet;
		strRet.append(szType);
		strRet.append(" ");
		strRet.append(szRequest);
		strRet.append(" ");
		strRet.append(szVersion);
		strRet.append("\r\nAccept: ");
		strRet.append(szAccept);
		strRet.append("\r\nHost: ");
		strRet.append(szHostName);
		if ( strlen(szRange)>0 )//���϶ϵ�������Ϣ
		{
			strRet.append("\r\nRange: bytes=");
			strRet.append(szRange);
			strRet.append("-");
		}
		strRet.append("\r\nConnection: ");
		strRet.append(szConnection);
		strRet.append("\r\n\r\n");
		return strRet;
	}
};



class CHttpSocket
	: public ISocketHttp
	, public IHttp
{
public:
	CHttpSocket();
	virtual ~CHttpSocket();
	virtual bool	DownloadFile(LPCWSTR lpUrl, LPCWSTR lpFilePath);
	virtual	LPCWSTR	GetIpAddr()const												{ return m_strIpAddr.c_str();	}
	virtual void	SetDownloadCallback(IHttpCallback* pCallback, void* pParam)		{ m_pCallback = pCallback; m_lpParam = pParam; }
	virtual HttpInterfaceError GetErrorCode()										{ return m_error;				}
	virtual	void	FreeInstance()													{ delete this;					}
	virtual bool	DownloadToMem(LPCWSTR lpUrl, OUT void** ppBuffer, OUT int* nSize);

protected:
	class CHttpHeader
	{
	public:
		CHttpHeader(const char* pHeader);
		CHttpHeader(const std::string& strHeader);
		virtual		~CHttpHeader(void);
		//********************************
		//�ⲿ�ӿ�
		//********************************
		//��ȡHTTP�汾
		const char*		GetHttpVersion()const { return m_szHttpVersion; }
		//��ȡHTTP����������ֵ
		const int		GetReturnValue()const { return m_uReturnValue; }
		//��ȡHTTP�����ַ�
		const char*		GetContent()const	  { return m_strContent.c_str(); }
		//��ȡĳһ������Ӧ��ֵ
		std::string		GetValue(const std::string& strKey);
	protected:
		//����HTTPͷ�ṹ
		bool	Revolse(const std::string& strHeader);
	private:
		//HTTP�������汾
		char		m_szHttpVersion[9];
		//����ֵ
		int		m_uReturnValue;
		//����˵���ַ���
		std::string	m_strContent;
		//���صļ�ֵ��
		std::map<std::string, std::string>	m_ValueMap;
	};

protected:
	bool	InitSocket(const string& strHostName, const WORD sPort);
	void	InitRequestHeader( HTTP_HERDER& header, LPCSTR pRequest, HttpRequest type=Hr_Get, LPCSTR pRange=NULL, const char* pAccept="*/*" );

private:
	SOCKET	m_socket;
	wstring	m_strIpAddr;

};