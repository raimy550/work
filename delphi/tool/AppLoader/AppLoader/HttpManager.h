#pragma once
#include "Singleton.h"
#include "IHttpInterface.h"
#include <string>
using namespace std;

#define CHECK_VERSION_URL "http://192.168.7.150:4500/AppVersion/api/v1.0.0/checkUpdate"


class IWinHttp;
class ILogicCallBack;

class CHttpManager : public Sigleton<CHttpManager>, IHttpCallback
{
public:
	CHttpManager();
	~CHttpManager();
	
	BOOL DoUpdate();
	void SetLogicCallBack(ILogicCallBack* callback);
	virtual void OnDownloadCallback(void* pParam, DownloadState state, double nTotalSize, double nLoadSize);
	virtual bool IsNeedStop();

	BOOL CheckVersion();
	BOOL DownloadPackage();

	string GetNewVersion(){return m_strNewVer;}

private:
	virtual void Init();
	virtual void UnInit();
	int GetVersionCode(string strVersion);
	BOOL HandleCheckResp(string response);


private:
	std::string m_strCurVer;
	std::string m_strAppId;

	std::string m_strNewVer;
	std::string m_strNewVerUrl;
	int m_nNeedUpdate;

	IWinHttp* m_pHttp;
	ILogicCallBack* m_pLogicCallBack;

friend Sigleton<CHttpManager>;

};