#ifndef _STRING_OP_H
#define _STRING_OP_H
#include <Windows.h>
#include <string>
#include <xstring>
#include <vector>
using namespace std;

class CStringHelper
{
public:
	static string WtoC(const wstring& wstr, unsigned int nCodePage=CP_ACP);
	static wstring CtoW(const string& str, unsigned int nCodePage=CP_ACP);
	static std::vector<std::string> StdSplit(std::string str,std::string pattern);
};


#endif