#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <csetjmp>
#include "Utils.h"

extern jmp_buf GLOBAL_ENV;

#define GLOBAL_SETJMP() setjmp(GLOBAL_ENV)
#define GLOBAL_LONGJMP(v) longjmp(GLOBAL_ENV, v)

enum ExceptionIdEnum {
	EXCEPTION_NTDLL_INIT_FAILED				=	0x00000001,
	EXCEPTION_ADJUST_PRIVILEGE				=	0x00000002,

	MAX_EXCEPTION
};

extern const wchar_t* ExceptionDescription[MAX_EXCEPTION];

inline void Abort(int code) {
	if (ExceptionDescription[code - 1]) {
		Utils::MessageBoxFormat(NULL, L"Error", MB_APPLMODAL | MB_ICONERROR,
			ExceptionDescription[code - 1]);
	}
	else {
		Utils::MessageBoxFormat(NULL, L"Error", MB_APPLMODAL | MB_ICONERROR,
			L"DreamDota has encountered a critical error.\nError Code: 0x%08X", code); 
	}
#ifdef _DEBUG
	abort();
#else
	ExitProcess((UINT)code);
#endif
}

#endif