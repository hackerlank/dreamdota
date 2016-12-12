#include "stdafx.h"
#include "Exception.h"

jmp_buf GLOBAL_ENV;

const wchar_t* ExceptionDescription[MAX_EXCEPTION] = {
	/* 0x00000001 */	L"初始化失败，请检查程序是否被杀毒软件阻止。",									
	/* 0x00000002 */	L"获取管理员权限失败，请检查您是否有管理员权限以及程序是否被杀毒软件阻止。",								

	NULL
};