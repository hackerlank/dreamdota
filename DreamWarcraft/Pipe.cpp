#include "stdafx.h"
#include "Pipe.h"
#include "Thread.h"
#include "StringManager.h"
#include "Tools.h"
#include "Foundation.h"
#include "../DreamAuth/InlineUtils.h"
#include "Version.h"

HANDLE Pipe = NULL;

bool Pipe_Init() {
#ifndef _VMP 
	return true;
#endif

	VMProtectBeginVirtualization("Pipe Init");

	bool pipe_connected = false;
	char strbuff[100];
	GetString(STR::PIPE_NAME, strbuff, 100);
	while (!pipe_connected) {
		Pipe = CreateFile(
			strbuff,
			GENERIC_READ | GENERIC_WRITE, 
			0, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			0
		);
		if (Pipe != INVALID_HANDLE_VALUE) {
			//ªÒ»°KEY
			uint32_t req = VERSION.revision;
			if (Pipe_Write(&req, 4) && Pipe_Read(PUBLIC_ENCRYPTED_KEY, RSA_SIZE)) {

			} else {
				wchar_t strFatal[32];
				GetStringW(STR::FATAL_ERROR, strFatal, 32);
				InlineUtils::MessageBoxFormat(NULL, MB_ICONERROR, NULL, strFatal, GetLastError());
				CloseHandle(Pipe);
				return false;
			}

			pipe_connected = true;
		} else {
			return false;
		}
	}
	
	VMProtectEnd();

	return true;
}

__forceinline uint32_t Pipe_Write(void* message, uint32_t message_size) {
	DWORD rv;
	WriteFile(Pipe, message, message_size, &rv, NULL);
	return rv;
}

__forceinline uint32_t Pipe_Read(void* buffer, uint32_t buffer_size) {
	DWORD rv;
	ReadFile(Pipe, buffer, buffer_size, &rv, NULL);
	return rv;
}

__declspec(noinline) void Pipe_Cleanup() {
	VMProtectBeginVirtualization("Pipe Cleanup");
	CloseHandle(Pipe);
	VMProtectEnd();
}