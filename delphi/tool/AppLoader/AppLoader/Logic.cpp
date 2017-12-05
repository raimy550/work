#include "stdafx.h"
#include "Logic.h"
#include "json.h"
#include <Windows.h>
#include <fstream>
#include "IHttpInterface.h"
#include "unzip.h"
#include "HttpManager.h"
#include "FileHelper.h"

CLogic::CLogic()
{

}

CLogic::~CLogic()
{
	
}

// class CMyCallback
// 	: public IHttpCallback
// {
// public:
// 	virtual void OnDownloadCallback(void* pParam, DownloadState state, double nTotalSize, double nLoadSize)
// 	{
// 		char tmp[1024];
// 		if (nTotalSize>0)
// 		{
// 			int nPercent = (int)( 100*(nLoadSize/nTotalSize) );
// 			sprintf(tmp, "下载进度：%d%%\n", nPercent);
// 			OutputDebugStringA(tmp);
// 		}
// 	}
// 	virtual bool	IsNeedStop()
// 	{
// 		//如果需要在外部终止下载，返回true
// 		return false;//继续下载
// 	}
// };

void CLogic::Init()
{
	m_pHttpMng = CHttpManager::GetInstance();
	m_pHttpMng->SetLogicCallBack(this);

	CFileHelper::RunApp(CFileHelper::GetCurrDir()+_T("\\")+INJECT_EXE);

	DoLogicDeleteOldData();

	DoLogicNetUpdate();

//test jason
// 	Json::FastWriter jwrite;
// 	Json::Value jroot;
// 	Json::Value jitem1, jitem2;
// 	Json::Value arrayObj;
// 
// 	jitem1["attr1"] = "value1";
// 	jitem2["attr2"] = "value2";
// 	arrayObj.append(jitem1);
// 	arrayObj.append(jitem2);
// 
// 	for (int i=0; i<5; i++)
// 	{
// 		jroot["root"][i]["sub"] = arrayObj;
// 	}
// 	
// 	std::string out = jroot.toStyledString();  
// 	// 输出无格式json字符串  
// 	Json::FastWriter writer;  
// 	std::string strWrite = writer.write(jroot);
// 	std::ofstream ofs;
// 	ofs.open("test_write.json");
// 	ofs << strWrite;
// 	ofs.close();

// request:
// {
// appId:'777ecd87-c984-49d0-b67c-55e48bca2f37',
// versionCode:175,
// }  


// 	Json::FastWriter jwrite;
// 	Json::Value jroot;
// 	Json::Value jitem1, jitem2;
// 	Json::Value arrayObj;
// 
// 	jitem1["appid"] = "PcHook";
// 	jitem1["version"] = "v1.0.0.0";
// 	jroot["PcHook"] = jitem1;
// 	
// 	std::string out = jroot.toStyledString();  
// 	// 输出无格式json字符串  
// 	Json::FastWriter writer;  
// 	std::string strWrite = writer.write(jroot);
// 	std::ofstream ofs;
// 	ofs.open("version.xml");
// 	ofs << strWrite;
// 	ofs.close();

//test download
// 	IWinHttp* pHttp;
// 	bool bRet = CreateInstance((IHttpBase**)&pHttp, Hf_WinHttp);
// 	if (!bRet)
// 	{
// 		return;
// 	}
// 	CMyCallback cb;
// 	pHttp->SetDownloadCallback(&cb, NULL);
// 	const wchar_t* pUrl = L"http://sw.bos.baidu.com/sw-search-sp/software/97e90d6bfca7b/WeChat_2.2.0.37_Setup.exe";
// 	const wchar_t* pSavePath = L"c:\\down.exe";
// 	if (!pHttp->DownloadFile(pUrl, pSavePath))
// 	{
// 		//下载失败
// 		pHttp->FreeInstance();
// 		return;
// 	}
// 	pHttp->FreeInstance();
// 	return;

//test unzip
// 	HZIP hz = OpenZip(_T("c:\\cpp-httplib-master.zip"),0);  
// 	ZIPENTRY ze; 
// 	GetZipItem(hz,-1,&ze); 
// 	int numitems=ze.index;  
// 	for (int i=0; i<numitems; i++)  
// 	{ 
// 		GetZipItem(hz,i,&ze);  
// 		UnzipItem(hz,i,ze.name);  
// 	}  
// 	CloseZip(hz); 

}

void CLogic::UnInit()
{
	SAVE_DEL(m_pHttpMng);
}

void CLogic::FuncLogicCallBack(ELogicType eLogicType, EResult result)
{
	if (ELogicType_CheckVersion == eLogicType)
	{
		string ver = m_pHttpMng->GetNewVersion();
		ver = ver+",是否需要下载升级？";
		int nRet = MessageBoxA(NULL, ver.c_str(), NULL, MB_YESNO);
	
		if (nRet == IDYES)
		{
			m_pHttpMng->DownloadPackage();
		}
	}else if (ELogicType_DownLoadPackage == eLogicType)
	{
		if (EResult_DownLoadFinished == result)
		{
			DoLogicLocalUpdate();

			MessageBoxA(NULL, "升级成功，请重新启动电脑", NULL, MB_OK);
		}
	}
}

void CLogic::DoLogicDeleteOldData()
{
	wstring backupDir = PATH_RUN;
	backupDir = backupDir+_T("\\")+DIR_NAME_BACKUP;

	wstring updateDir = PATH_RUN;
	updateDir = updateDir+_T("\\")+DIR_NAME_UPDATE;

	wstring updatePath = PATH_RUN;
	updatePath = updatePath+_T("\\")+FILE_NAME_UPDATE;
	
	CFileHelper::DeleteFilesBySuffix(PATH_RUN, SUFFIX_NAME_OLD);

	CFileHelper::ReleaseDirectory(backupDir.c_str());
	CFileHelper::ReleaseDirectory(updateDir.c_str());
}

void CLogic::DoLogicNetUpdate()
{
	m_pHttpMng->DoUpdate();	
}

void CLogic::DoLogicLocalUpdate()
{
	wstring srcDir = PATH_RUN;
	wstring updatePath = PATH_RUN;
	updatePath = updatePath+_T("\\")+FILE_NAME_UPDATE;
	wstring backupDir = PATH_RUN;
	backupDir = backupDir+_T("\\")+DIR_NAME_BACKUP;

	HZIP hz = OpenZip(updatePath.c_str(),0);  
	ZIPENTRY ze; 
	GetZipItem(hz,-1,&ze); 
	int numitems=ze.index;  
	for (int i=0; i<numitems; i++)  
	{ 
		GetZipItem(hz,i,&ze);  
		UnzipItem(hz,i,ze.name);  
	}  
	CloseZip(hz);

	CFileHelper::CopyFiles2Dir(srcDir, backupDir);
	CFileHelper::RenameFiles(srcDir, SUFFIX_NAME_OLD);
	CFileHelper::CopyFiles2Dir(srcDir+_T("\\")+DIR_NAME_UPDATE, srcDir);
}

