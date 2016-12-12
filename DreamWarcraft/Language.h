#include "stdafx.h"
#ifndef LANGUAGE_H_INCLUDED
#define LANGUAGE_H_INCLUDED

#include "../DreamAuth2/StringManager.h"
#include "AuthConnection.h"

#define LANGUAGE_BUFFER_SIZE 10240

#ifndef _SERVERSTRING
extern uint32_t LOCALE_DATA_EN_US[];
extern const uint32_t LangDataSize;
//跳过exe自行装载语言数据
INLINE uint32_t LoadLang(HMODULE module, uint8_t* dst) {
	memcpy_s(dst, LANGUAGE_BUFFER_SIZE,  LOCALE_DATA_EN_US, LangDataSize);
	return LangDataSize;
}
#endif

extern BYTE LangBuff[LANGUAGE_BUFFER_SIZE];

INLINE bool Language_Init(HMODULE module) {
	PipeContext* ctx = &AuthConnection_Ctx;
	uint32_t size = 0;
#ifndef _SERVERSTRING
	size = LoadLang(module, LangBuff);
	DEBUG_CODE(OutputDebug("Lang data size: %u", size));
#else
	jmp_buf env;
	int val = setjmp(env);
	if (val == 0) {
		DWORD bytes = 0;
		*(BYTE*)LangBuff = PIPE_MESSAGE_REQUEST_LANG;
		if (TRUE != Pipe_Write(ctx, LangBuff, 1, &bytes) || bytes != 1)
			longjmp(env, 1);
		if (TRUE != Pipe_Read(ctx, LangBuff, LANGUAGE_BUFFER_SIZE, &bytes) || bytes <= 1)
			longjmp(env, 2);
		size = bytes;
	} else {
		return false;
	}
#endif
	StringManager::Init(LangBuff, size);

	return true;
}

INLINE void Language_Cleanup() {
	StringManager::Cleanup();
}

#endif