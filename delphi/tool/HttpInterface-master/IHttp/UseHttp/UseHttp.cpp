// UseHttp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "..//IHttp/IHttpInterface.h"
#ifdef _DEBUG
#pragma comment(lib, "..//bin//Debug//IHttpD")
#else
#pragma comment(lib, "..//bin//Release//IHttp")
#endif
#include <crtdbg.h>
#include <Windows.h>


bool TestWinInet();
bool TestWinHttp();
bool TestSocketHttp();
bool TestDownloadFile();

class CMyCallback
	: public IHttpCallback
{
public:
	virtual void OnDownloadCallback(void* pParam, DownloadState state, double nTotalSize, double nLoadSize)
	{
		if (nTotalSize>0)
		{
			int nPercent = (int)( 100*(nLoadSize/nTotalSize) );
			printf("���ؽ��ȣ�%d%%\n", nPercent);
		}
	}
	virtual bool	IsNeedStop()
	{
		//�����Ҫ���ⲿ��ֹ���أ�����true
		return false;//��������
	}
};

//extern "C" __declspec(dllimport ) bool CreateInstance(IHttpBase** pBase, HttpFlag flag);


int _tmain(int argc, _TCHAR* argv[])
{
	//TestWinInet();		//����ʹ��WinInetʵ�ֵ�HTTP�ӿ�
	//TestWinHttp();		//����ʹ��WinHttpʵ�ֵ�HTTP�ӿ�
	//TestSocketHttp();		//����ʹ��Socketʵ�ֵ�HTTP�ӿ�
	TestDownloadFile();		//���������ļ���ʹ�ûص��ӿڻ�ȡ���ؽ���

	system("pause");
	//��ӡ���ڴ�й©��Ϣ
 	_CrtDumpMemoryLeaks();
	return 0;
}

bool TestWinInet()
{
	IWininetHttp* pHttp;
	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_WinInet);
	if (!bRet)
	{
		return false;
	}
	char* pMem = NULL;
	int nSize = 0;
	const wchar_t* pUrl = L"http://blog.csdn.net/mfcing";
	string str = pHttp->Request(pUrl, Hr_Get);
	if (str.empty())
	{
		//����ʧ��
		pHttp->FreeInstance();
		return false;
	}
	if (pHttp->DownloadToMem(pUrl, (void**)&pMem, &nSize))
	{
		//���ص��ڴ��У������ص��������Ч�ʸ��ߣ����ö�д�ļ�
		
		//����֮��һ��Ҫ�ͷ�����ڴ�ռ�
		free(pMem);
	}
	else
	{
		//����ʧ�ܣ���ȡ������Ϣ
		HttpInterfaceError code = pHttp->GetErrorCode();
		pHttp->FreeInstance();
		return false;
	}
	pHttp->FreeInstance();
	return true;
}

bool TestWinHttp()
{
	IWinHttp* pHttp;
	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_WinHttp);
	if (!bRet)
	{
		return false;
	}
	const char* pUrl = "www.haoso.com";
	string strHtml = pHttp->Request(pUrl, Hr_Get);
	if (strHtml.empty())
	{
		//����ʧ��
		pHttp->FreeInstance();
		return false;
	}
	else
	{
		printf("%s html : %s", pUrl, strHtml.c_str());
	}
	pHttp->FreeInstance();
	return true;
}

bool TestSocketHttp()
{
	ISocketHttp* pHttp;
	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_Socket);
	if (!bRet)
	{
		return false;
	}
	const wchar_t* pUrl = L"www.sogou.com";
	char* pHtml = NULL;
	int nSize = 0;
	if (!pHttp->DownloadToMem(pUrl, (void**)&pHtml, &nSize))
	{
		//����ʧ��
		pHttp->FreeInstance();
		return false;
	}
	printf("html: %s\n", pHtml);
	//�ͷ��ڴ�ռ�
	free(pHtml);
	pHttp->FreeInstance();
	return true;
}

bool TestDownloadFile()
{
	IWinHttp* pHttp;
	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_WinHttp);
	if (!bRet)
	{
		return false;
	}
	CMyCallback cb;
	pHttp->SetDownloadCallback(&cb, NULL);
	const wchar_t* pUrl = L"http://sw.bos.baidu.com/sw-search-sp/software/97e90d6bfca7b/WeChat_2.2.0.37_Setup.exe";
	const wchar_t* pSavePath = L"c:\\down.exe";
	if (!pHttp->DownloadFile(pUrl, pSavePath))
	{
		//����ʧ��
		pHttp->FreeInstance();
		return false;
	}
	pHttp->FreeInstance();
	return true;
}