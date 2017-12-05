#pragma once

#define PATH_RUN  CFileHelper::GetCurrDir().GetString()  //_T("C:\\Users\\raimy\\Desktop\\hookdemo")
#define INJECT_EXE _T("DphInjectExe.exe")
#define DIR_NAME_BACKUP _T("backup")
#define DIR_NAME_UPDATE _T("update")
#define SUFFIX_NAME_OLD _T("_old")
#define FILE_NAME_UPDATE _T("update.zip")
#define FILE_NAME_VERSION _T("version.xml")

#define SAVE_DEL(p) if((p)!=NULL){delete p; p=NULL;}