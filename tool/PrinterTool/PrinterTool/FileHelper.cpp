#include "stdafx.h"
#include "FileHelper.h"

BOOL CFileHelper::CopyFiles2Dir(wstring srcDir, wstring destDir)
{
	BOOL bRet = FALSE;
	WIN32_FIND_DATA findData;
	wstring strTemp;
	WCHAR charArr[128];
	wsprintf(charArr, _T("%s\\*.*"), srcDir.c_str());//查找指定目录下的直接的所有文件和目录

	HANDLE hFile = FindFirstFile(charArr, &findData);
	while (hFile != INVALID_HANDLE_VALUE)
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))//非目录
		{
			bRet = CopyFile2Dir(srcDir+ _T("\\") + findData.cFileName, destDir);
			if (!bRet)
			{
				break;
			}
		}

		if(!FindNextFile(hFile, &findData))
		{
			break;
		}
	}
	return bRet;

}

BOOL CFileHelper::RenameFiles(const wstring srcDir, const wstring suffix)
{
	BOOL bRet = TRUE;
	WIN32_FIND_DATA findData;
	wstring pathOld, pathCur;
	WCHAR charArr[128];
	wsprintf(charArr, _T("%s\\*.*"), srcDir.c_str());//查找指定目录下的直接的所有文件和目录

	HANDLE hFile = FindFirstFile(charArr, &findData);
	while (hFile != INVALID_HANDLE_VALUE)
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))//非目录
		{
			pathOld = srcDir+L"\\"+findData.cFileName+suffix;
			pathCur = srcDir+L"\\"+findData.cFileName;
			rename(CStringHelper::WtoC(pathCur).c_str(), CStringHelper::WtoC(pathOld).c_str());
		}

		if(!FindNextFile(hFile, &findData))
		{
			break;
		}
	}
	return bRet;
}

BOOL CFileHelper::DeleteFilesBySuffix(const wstring strDir, const wstring suffix)
{
	BOOL bRet = TRUE;
	WIN32_FIND_DATA findData;
	wstring fileName, tmp;
	WCHAR charArr[128];
	wsprintf(charArr, _T("%s\\*.*"), strDir.c_str());//查找指定目录下的直接的所有文件和目录

	HANDLE hFile = FindFirstFile(charArr, &findData);
	while (hFile != INVALID_HANDLE_VALUE)
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))//非目录
		{
			fileName = findData.cFileName;
			if (fileName.length()>suffix.length())
			{
				tmp.assign(&fileName[fileName.length()-suffix.length()], suffix.length());
				if (tmp == suffix)
				{
					DeleteFile((strDir+L"\\"+fileName).c_str());
				}
			}
		}

		if(!FindNextFile(hFile, &findData))
		{
			break;
		}
	}
	return bRet;
}

bool  CFileHelper::CheckDirExist(wstring &strPath)
{
	WIN32_FIND_DATA  wfd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(strPath.c_str(), &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = true;   
	}
	FindClose(hFind);
	return rValue;
}

bool CFileHelper::CreateDirs(const char* pathName)  
{  
	char path[MAX_PATH] = {0};  
	const char* pos = pathName;  
	while ((pos = strchr(pos, '\\')) != NULL)  
	{  
		memcpy(path, pathName, pos - pathName + 1);  
		pos++;  
		if (CheckDirExist(CStringHelper::CtoW(path)))  
		{  
			continue;  
		}  
		else  
		{  
			int ret = _mkdir(path);  
			if (ret == -1)  
			{  
				return false;  
			}  
		}  
	}  
	pos = pathName + strlen(pathName)-1;  
	if (*pos != '\\')  
	{  
		return _mkdir(pathName)==0;  
	}  
	return true;  
} 

wstring CFileHelper::GetFileNameByPath(wstring path)
{
	wstring wstRet=L"";
	int nPos= 0;
	nPos = path.find_last_of('\\');
	nPos++;
	if (nPos!=-1)
	{
		wstRet.assign(&path[nPos],path.length()-nPos);
	}

	return wstRet;
}

BOOL CFileHelper::CopyFile2Dir(wstring fileName, wstring destDir)
{
	BOOL bRet;
	if (!CheckDirExist(destDir))
	{
		CreateDirectory(destDir.c_str(), NULL);
		// 			if(!CreateDirs(CStringHelper::WtoC(destDir).c_str()))
		// 				return FALSE;
	}
	destDir = destDir +L"\\"+ GetFileNameByPath(fileName);
	bRet = CopyFile(fileName.c_str(), destDir.c_str(), TRUE);
	return bRet;
}


BOOL CFileHelper::ReleaseDirectory(CString chrDirName)
{
	BOOL bRemove = DoRemoveDirectory(chrDirName);
	if (bRemove)
		::RemoveDirectory(chrDirName);
	else
		return FALSE;

	return TRUE;

} //end of CIVMSvrInfo::ReleaseDirectory()


BOOL CFileHelper::DoRemoveDirectory(CString chrDirName)
{
	CString strDirName = chrDirName;

	BOOL result;
	HANDLE Handle;
	WIN32_FIND_DATA fData;
	CString strTemp;
	DWORD errorcode;

	Handle = FindFirstFile(strDirName + "\\*.*", &fData);

	if (Handle == INVALID_HANDLE_VALUE)
		return FALSE;

	do {
		errorcode = GetLastError();

		if ( fData.cFileName[0] == '.' )
			continue;

		if (fData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			if (strDirName[strDirName.GetLength()-1] != '\\'){
				TCHAR chA[MAX_PATH];
				CString strA = strDirName+'\\'+ fData.cFileName;
				lstrcpy(chA, strA);
				DoRemoveDirectory(chA);
			}
			else{
				TCHAR chB[MAX_PATH];
				CString strB = strDirName + fData.cFileName;
				lstrcpy(chB, strB);
				DoRemoveDirectory(chB);
			}

			strTemp = strDirName + _T("\\") + fData.cFileName;

			SetFileAttributes(strTemp, ~FILE_ATTRIBUTE_READONLY);
			if (!RemoveDirectory(strTemp))
				result = FALSE;
			else
				result = TRUE;
		}
		else
		{
			strTemp = strDirName + _T("\\") + fData.cFileName;
			BOOL bl = SetFileAttributes(strTemp, ~FILE_ATTRIBUTE_READONLY);

			if (!DeleteFile(strTemp))
				result = FALSE;
			else
				result = TRUE;
		}

	}while(FindNextFile(Handle,&fData));

	errorcode = GetLastError();

	if (errorcode == ERROR_NO_MORE_FILES)//空目录
	{
		::RemoveDirectory(strDirName);
		result = TRUE;
	}

	if (Handle)
		FindClose(Handle);

	return result;

} 

CString CFileHelper::GetCurrDir()
{
	CString sPath = _T("");
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer(); 
	int   nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos);
	return sPath;
}

BOOL CFileHelper::RunApp(CString path)
{
	SHELLEXECUTEINFO shell = { sizeof(shell) };
	shell.fMask = SEE_MASK_FLAG_DDEWAIT;
	shell.lpVerb = L"open";
	shell.lpFile = path;
	shell.nShow = SW_SHOWNORMAL;
	return ShellExecuteEx(&shell);
}