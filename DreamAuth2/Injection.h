#include "stdafx.h"
#ifndef INJECTION_H_
#define INJECTION_H_

#include "NTDLL.h"
#include "RemoteMemory.h"
#include <Psapi.h>
#include <process.h>
#include <WinBase.h>
#include <Tlhelp32.h>
#include <io.h>
#include "GameModule.h"

INLINE bool EnumProcessIdByName(const wchar_t* fileName, DWORD* buffer, size_t buffer_size, size_t* returnSize) {
	bool rv = false;
	HANDLE hProcessSnap = NULL;
	size_t offset = 0;
	PROCESSENTRY32 pe32 = {0};
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
		return false;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	if(Process32First(hProcessSnap, &pe32)) {
		do {
			if (0 == _wcsicmp(fileName, pe32.szExeFile)) {
				if (buffer && offset < buffer_size) {
					if (offset * 4 < buffer_size) {
						buffer[offset] = pe32.th32ProcessID;
					} else {
						goto Cleanup;
					}
				}
				offset++;
			}
		}
		while(Process32Next(hProcessSnap, &pe32));
		*returnSize = offset;
		rv = true;
	}
Cleanup:
	CloseHandle(hProcessSnap);
	return rv;
}

INLINE HMODULE GetProcessModuleAddress(HANDLE process, const wchar_t* dllname) {
	HMODULE arr[100];
	wchar_t filename[MAX_PATH];
	DWORD required;
	if (TRUE == EnumProcessModules(process, arr, sizeof(arr), &required)) {
		size_t n = required / sizeof(HMODULE);
		for (size_t i = 0; i < n; ++i) {
			if (size_t filenameLen = GetModuleFileNameEx(process, arr[i], filename, sizeof(filename) / sizeof(wchar_t))) {
				if (0 == _wcsicmp(&(filename[filenameLen - wcslen(dllname)]), dllname))
					return arr[i];
			}
		}
	}
	return NULL;
}

NOINLINE HANDLE NTFindProcessHandle(DWORD pid, wchar_t* name_buffer, size_t name_buffer_size);
NOINLINE bool NTGetProcessImageFileName(HANDLE processHandle, wchar_t* buffer, size_t buffer_size);

NOINLINE bool War3Inject(const wchar_t* filename);
NOINLINE void War3InjectCleanup();

INLINE const IMAGE_DOS_HEADER* GetRemotePEHeader(HANDLE process, void* base) {
	IMAGE_DOS_HEADER* p_dos_header = new IMAGE_DOS_HEADER;
	IMAGE_NT_HEADERS* p_nt_headers = new IMAGE_NT_HEADERS;

	ULONG bytes;

	if (!ReadRemoteMemory<IMAGE_DOS_HEADER>(process, base, p_dos_header, &bytes) && bytes == sizeof(IMAGE_DOS_HEADER))
		goto Failure;

	if (!ReadRemoteMemory<IMAGE_NT_HEADERS>(process, (void*)((uint32_t)base + p_dos_header->e_lfanew), p_nt_headers, &bytes) && bytes == sizeof(IMAGE_NT_HEADERS))
		goto Failure;

	p_dos_header->e_lfanew = (LONG)p_nt_headers;
	return p_dos_header;
Failure:
	delete p_dos_header;
	delete p_nt_headers;
	return NULL;
}

INLINE void FreeRemotePEHeader(const IMAGE_DOS_HEADER* p_dos_header) {
	delete (void*)p_dos_header->e_lfanew;
	delete p_dos_header;
}

void SetWar3PID(DWORD pid);
DWORD GetWar3PID();

#endif