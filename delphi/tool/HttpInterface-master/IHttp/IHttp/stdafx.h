// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>

#include "Common.h"
#include "Http.h"

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#ifndef HINTERNET
#define HINTERNET LPVOID
#endif
#define DOWNLOAD_BUFFER_SIZE	8*1024*1024	//8M�Ļ���