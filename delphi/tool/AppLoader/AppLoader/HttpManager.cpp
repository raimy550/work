#include "stdafx.h"
#include "HttpManager.h"
#include <assert.h>
#include <fstream>
#include "json.h"
#include "IHttpInterface.h"
#include "StringHelper.h"
#include <math.h>
#include "ILogicCallBack.h"
#include "FileHelper.h"

CHttpManager::CHttpManager()
{
	Init();
}

CHttpManager::~CHttpManager()
{
	UnInit();
}

void CHttpManager::Init()
{
	ifstream ifs;
	wstring wstrPath=L""; 
	wstrPath = wstrPath + PATH_RUN +_T("\\")+FILE_NAME_VERSION;
	ifs.open(CStringHelper::WtoC(wstrPath).c_str());
	assert(ifs.is_open());

	Json::Reader reader;
	Json::Value root;
	Json::Value jNode;
	if (!reader.parse(ifs, root, false))
	{
		ifs.close();
		return;
	}
	ifs.close();

	jNode = root["PcHook"];
	m_strAppId = jNode["appid"].asString();
	m_strCurVer = jNode["version"].asString();
}

void CHttpManager::UnInit()
{

}

BOOL CHttpManager::DoUpdate()
{
	return CheckVersion();
}

void CHttpManager::SetLogicCallBack(ILogicCallBack* callback)
{
	m_pLogicCallBack = callback;
}

int CHttpManager::GetVersionCode(string strVersion)
{
	int nRet = 0;
	vector<string> strArr = CStringHelper::StdSplit(strVersion, ".");
	int nSize = strArr.size();
	for (int i=0; i< nSize; i++)
	{
		
		nRet += pow((double)10, (double)(nSize-i-1)) * atoi(strArr[i].c_str());
	}
	
	
	return nRet;
}

BOOL CHttpManager::CheckVersion()
{
	IWinHttp* pHttp;
	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_WinInet);
	if (!bRet)
	{
		return FALSE;
	}

	Json::FastWriter jwrite;
	Json::Value jroot;
	Json::Value jitem1, jitem2;
	Json::Value arrayObj;

	jitem1["appId"] = m_strAppId;
	jitem1["versionCode"] = GetVersionCode(m_strCurVer);
	arrayObj.append(jitem1);
	jroot["apps"] = arrayObj;
	
	std::string out = jroot.toStyledString();  

	std::string response = pHttp->Request(CHECK_VERSION_URL, Hr_Post, out.c_str(), "Content-Type: application/json");
	
	if (pHttp->GetErrorCode() == Hir_Success)
	{
		return HandleCheckResp(response);
	}
	
	
	return FALSE;
}

BOOL CHttpManager::HandleCheckResp(string response)
{
	Json::Reader reader;
	Json::Value root;
	BOOL bRet = TRUE;
	reader.parse(response, root);
	if (root["data"].size() ==1)
	{
		m_strNewVer = root["data"][0]["newVersion"].asString();
		m_strNewVerUrl = root["data"][0]["fileURL"].asString();
		m_nNeedUpdate = root["data"][0]["needUpdate"].asInt();

		if (m_nNeedUpdate==1)
		{
			m_pLogicCallBack->FuncLogicCallBack(ELogicType_CheckVersion, EResult_HasNewVersion);
		}
		
		
//		return DownloadPackage(m_strNewVerUrl);
	}
	
	
	return bRet;
}

void CHttpManager::OnDownloadCallback(void* pParam, DownloadState state, double nTotalSize, double nLoadSize)
{
	char tmp[1024];
	if (nTotalSize>0)
	{
		int nPercent = (int)( 100*(nLoadSize/nTotalSize) );
		sprintf(tmp, "下载进度：%d%%\n", nPercent);
		OutputDebugStringA(tmp);
	}

	if (state == DS_Finished)
	{
		m_pLogicCallBack->FuncLogicCallBack(ELogicType_DownLoadPackage, EResult_DownLoadFinished);
	}

}

bool CHttpManager::IsNeedStop()
{
	//如果需要在外部终止下载，返回true
	return false;//继续下载
}


BOOL CHttpManager::DownloadPackage()
{
	IWinHttp* pHttp;
	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_WinHttp);
	
	pHttp->SetDownloadCallback(this, NULL);
	wstring pUrl = CStringHelper::CtoW(m_strNewVerUrl);
	wstring pSavePath = PATH_RUN;
	pSavePath = pSavePath +L"\\"+FILE_NAME_UPDATE;

	if (!pHttp->DownloadFile(pUrl.c_str(), pSavePath.c_str()))
	{
		//下载失败
		pHttp->FreeInstance();
		return FALSE;
	}
	pHttp->FreeInstance();
	return TRUE;
}
