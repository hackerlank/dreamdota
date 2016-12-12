#include "LocaleString.h"

#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

BOOL CreatePipeSecurity(PSECURITY_ATTRIBUTES *ppSa);
void FreePipeSecurity(PSECURITY_ATTRIBUTES pSa);

const uint32_t PIPE_BUFFER_SIZE = 102400;

enum PipeMessageType {
	PIPE_MESSAGE_NULL			= 0x0,
	PIPE_MESSAGE_REQUEST_DATA	= 0x1,
	PIPE_MESSAGE_REQUEST_LANG	= 0x2,
	PIPE_MESSAGE_NET			= 0x3,
};

struct PipeContext {
	volatile bool disconnected;
	DWORD hostPID;
	HANDLE pipe;
	char pipeName[26];
};

INLINE void Pipe_GetRandomName(const char* format, char* rv, uint32_t rv_size) {
	char name[MAX_PATH];
	srand(GetTickCount());
	char* charTable = new char[16];
	for (int i = 0; i < 16; ++i)
		charTable[i] = (char)(65 + i);
	BYTE rndValue[8];
	for (int i = 0; i < 4; ++i) {
		((WORD*)rndValue)[i] = (WORD)rand();
	}
	for (int i = 0; i < 8; ++i) {
		name[i * 2]		= charTable[rndValue[i] / 0x10];
		name[i * 2 + 1] = charTable[rndValue[i] % 0x10];
	}
	name[16] = 0;
	delete [] charTable;
	sprintf_s(rv, rv_size, format, name);
}

INLINE bool Pipe_Create(PipeContext* ctx) {
	bool rv = false;
	char pipeName[128];
	Pipe_GetRandomName(StringManager::StringUTF8(STR::PIPE_NAME).c_str(), pipeName, sizeof(pipeName));
	memcpy_s(ctx->pipeName, 26, pipeName, 26);
	ctx->pipeName[26] = 0;
	ctx->disconnected = false;

	PSECURITY_ATTRIBUTES pSa = NULL;
	if (CreatePipeSecurity(&pSa)) {
		rv = (INVALID_HANDLE_VALUE != (ctx->pipe = CreateNamedPipeA(
			pipeName, 
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			1,
			PIPE_BUFFER_SIZE,
			PIPE_BUFFER_SIZE,
			NULL,
			pSa
		)));
		FreePipeSecurity(pSa);
	}

	return rv;
}

INLINE bool Pipe_Listen(PipeContext* ctx) {
	return TRUE == ConnectNamedPipe(ctx->pipe, NULL) && !(ctx->disconnected);
}

INLINE bool Pipe_Connect(PipeContext* ctx) {
	bool rv = false;
	rv = (INVALID_HANDLE_VALUE != (ctx->pipe = CreateFileA(
			ctx->pipeName,
			GENERIC_READ | GENERIC_WRITE, 
			0, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			0
	)));
	return rv;
}

INLINE bool Pipe_Read(PipeContext* ctx, void* buffer, uint32_t buffer_size, DWORD* bytes) {
	return TRUE == ReadFile(ctx->pipe, buffer, buffer_size, bytes, NULL);
}

INLINE bool Pipe_Write(PipeContext* ctx, const void* buffer, uint32_t buffer_size, DWORD* bytes) {
	return TRUE == WriteFile(ctx->pipe, buffer, buffer_size, bytes, NULL);
}

INLINE void Pipe_Term(PipeContext* ctx) {
	ctx->disconnected = true;
	//防止，阻塞连接一次
	BYTE null = 0;
	DWORD bytes;
	HANDLE pipe = CreateFileA(
			ctx->pipeName,
			GENERIC_READ | GENERIC_WRITE, 
			0, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			0
	);
	if (pipe != INVALID_HANDLE_VALUE)
		CloseHandle(pipe);
	if (ctx->pipe != NULL && ctx->pipe != INVALID_HANDLE_VALUE) {
		WriteFile(pipe, &null, 1, &bytes, NULL);
		CloseHandle(ctx->pipe);
		ctx->pipe = NULL;
	}
}

#endif