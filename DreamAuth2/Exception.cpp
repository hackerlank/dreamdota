#include "stdafx.h"
#include "Exception.h"

jmp_buf GLOBAL_ENV;

const wchar_t* ExceptionDescription[MAX_EXCEPTION] = {
	/* 0x00000001 */	NULL,									
	/* 0x00000002 */	NULL,									
	/* 0x00000003 */	L"Fail to initialize locale text data.",
	/* 0x00000004 */	L"Fail to initialize network.",	
	/* 0x00000005 */	NULL,	
	/* 0x00000006 */	NULL,
	/* 0x00000007 */	NULL,
	/* 0x00000008 */	L"There is already a DreamAuth instance running.",

	NULL
};