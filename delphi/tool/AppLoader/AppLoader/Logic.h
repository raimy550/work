#pragma once
#include "Singleton.h"
#include "ILogicCallBack.h"

class CHttpManager;

class CLogic : public Sigleton<CLogic>, ILogicCallBack
{
public:
	CLogic();
	~CLogic();

	virtual void Init();
	virtual void UnInit();
	virtual void FuncLogicCallBack(ELogicType eLogicType, EResult result);
private:
	void DoLogicDeleteOldData();
	void DoLogicNetUpdate();
	void DoLogicLocalUpdate();
private:
	CHttpManager* m_pHttpMng;


friend Sigleton<CLogic>;

};