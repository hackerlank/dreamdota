#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <csetjmp>
#include "InlineUtils.h"

extern jmp_buf GLOBAL_ENV;

#define GLOBAL_SETJMP() setjmp(GLOBAL_ENV)
#define GLOBAL_LONGJMP(v) longjmp(GLOBAL_ENV, v)

enum ExceptionIdEnum {
	EXCEPTION_INIT_RESSTRING_FAILED			=	0x00000001,
	EXCEPTION_NTDLL_INIT_FAILED				=	0x00000002,
	EXCEPTION_LOCALESTRING_INIT_FAILED		=	0x00000003,
	EXCEPTION_ZMQ_INIT_FAILED				=	0x00000004,
	EXCEPTION_REGISTER_CLASS_FAILED			=	0x00000005,
	EXCEPTION_CREATE_WINDOW_FAILED			=	0x00000006,
	EXCEPTION_PIPE_CREATE_FAILED			=	0x00000007,
	EXCEPTION_MULTI_INSTANCE				=	0x00000008,

	MAX_EXCEPTION
};

extern const wchar_t* ExceptionDescription[MAX_EXCEPTION];

inline void Abort(int code) {
	if (ExceptionDescription[code]) {
		InlineUtils::MessageBoxFormat(NULL, MB_APPLMODAL | MB_ICONERROR, L"Error", 
			L"DreamAuth has encountered a critical error:\n\n%ws\n", ExceptionDescription[code]);
	}
	else {
		InlineUtils::MessageBoxFormat(NULL, MB_APPLMODAL | MB_ICONERROR, L"Error", 
			L"DreamAuth has encountered a critical error.\nError Code: 0x%08X", code); 
	}
#ifdef _DEBUG
	abort();
#else
	ExitProcess((UINT)code);
#endif
}

#endif