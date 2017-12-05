#pragma once

enum ELogicType{
	ELogicType_NetUpdate,
	ELogicType_CheckVersion,
	ELogicType_DownLoadPackage

};

enum EResult{
	EResult_NetDownLoaded,
	EResult_HasNewVersion,
	EResult_DownLoadFinished
};


class ILogicCallBack
{
public:
	virtual void FuncLogicCallBack(ELogicType eLogicType, EResult result)=0;
};