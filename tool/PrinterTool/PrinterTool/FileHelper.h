#pragma once
#include <Windows.h>
#include "StringHelper.h"
#include <direct.h>
#include <iostream>
#include <afx.h>

class CFileHelper
{
public:
	static BOOL CopyFiles2Dir(wstring srcDir, wstring destDir);

	static BOOL RenameFiles(const wstring srcDir, const wstring suffix);

	static BOOL DeleteFilesBySuffix(const wstring strDir, const wstring suffix);

	static bool  CheckDirExist(wstring &strPath);

	static bool CreateDirs(const char* pathName)  ;
	
	static wstring GetFileNameByPath(wstring path);

	static BOOL CopyFile2Dir(wstring fileName, wstring destDir);


	static BOOL ReleaseDirectory(CString chrDirName);

	static BOOL DoRemoveDirectory(CString chrDirName);

	static CString GetCurrDir();

	static BOOL RunApp(CString path);

};