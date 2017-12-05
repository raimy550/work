#include "stdafx.h"
#include "StringHelper.h"

string CStringHelper::WtoC(const wstring &wstr, unsigned int nCodePage)
{
	std::string strRet = "";
	int nLen = WideCharToMultiByte(nCodePage, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (0==nLen)
		return strRet;
	char* pChar = new char[nLen];
	if (!pChar)
		return strRet;

	int nRet = WideCharToMultiByte(nCodePage, 0, wstr.c_str(), -1, pChar, nLen, NULL, NULL);
	if (0==nRet)
		return strRet;
	strRet = pChar;
	delete[] pChar;
	pChar = NULL;
	return strRet;
}

wstring CStringHelper::CtoW(const string &str, unsigned int nCodePage)
{
	wstring retWstr = L"";
	int nLen = MultiByteToWideChar(nCodePage, 0, str.c_str(), -1, NULL, 0);
	if (0==nLen)
		return retWstr;
	wchar_t* pWchar = new wchar_t[nLen];
	pWchar[nLen-1]=0;
	if (!pWchar)
		return retWstr;

	int nRet = MultiByteToWideChar(nCodePage, 0, str.c_str(), str.size(), pWchar, nLen);
	if (0==nLen)
		return retWstr;
	if (0xFEFF == pWchar[0])
		pWchar++;
	retWstr = pWchar;
	delete[] pWchar;
	pWchar = NULL;
	return retWstr;
}

std::vector<std::string> CStringHelper::StdSplit(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();
	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}
