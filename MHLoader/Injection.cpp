#include <Windows.h>
#include <cstdint>
#include <cstdio>
#include <csetjmp>
#include <VMP.h>
#include "NTDLL.h"
#include "Injection.h"
#include <cassert>

struct RemoteData {
	DWORD LdrLoadDllAddr;
	DWORD DefWindowProcAddr;
	void* invoker;
	UNICODE_STRING unicodeFilename;
	wchar_t	wstringPath[MAX_PATH];
	wchar_t wstringFilename[MAX_PATH];
};

static const uint32_t TPL_REMOTEDATA_ADDR = 0xCCCCCCCC;
void* CodeStartAddr = NULL;
DWORD CodeSize = 0;
__declspec( naked ) void InitInjectCode() {
	__asm {
		mov eax, offset end;
		sub eax, offset start;
		mov CodeSize, eax;
		mov CodeStartAddr, offset start;
		ret;
		
start:	//以下代码会被写入war3进程

		//prolog
		push esi;
		lea esi, [esp + 8]; //指向第一个栈中的参数
		push ebp;
		push ebx;
		push ecx;
		push edx;
		mov ebp, esp;
		sub esp, __LOCAL_SIZE;


		//自定位
		call locate;
locate:
		pop ebx;
		sub ebx, offset locate;
	}

	{
		HWND hwnd;
		UINT msg;
		WPARAM wParam;
		LPARAM lParam;
		__asm {
			mov eax, [ebp + 4]; //ecx
			mov hwnd, eax;

			mov eax, [ebp]; //edx
			mov msg, eax;

			mov eax, [esi];
			mov wParam, eax;

			mov eax, [esi + 4];
			mov lParam, eax;
		}
		RemoteData* remoteDataAddr = (RemoteData*)TPL_REMOTEDATA_ADDR;
		*(DWORD*)(remoteDataAddr->invoker) = 0;
		
		HANDLE module;

		PUNICODE_STRING unicodeFilename = &(remoteDataAddr->unicodeFilename);
		PWSTR wstringPath = remoteDataAddr->wstringPath;
		PWSTR wstringFilename = remoteDataAddr->wstringFilename;
		void* ldrLoadDllAddr = (void*)remoteDataAddr->LdrLoadDllAddr;
		void* defWindowProcAddr = (void*)remoteDataAddr->DefWindowProcAddr;
		ULONG flags = 0;
		PULONG pFlags = &flags;
		PHANDLE pHandle = &module;

		remoteDataAddr->unicodeFilename.Buffer = wstringFilename; //将UNICODE_STRING的buffer指向wstringPath

		__asm {
			push pHandle;
			push unicodeFilename;
			push pFlags;
			push wstringPath;
			mov eax, ldrLoadDllAddr;
			call eax;
		}

		__asm {
			push lParam;
			push wParam;
			push msg;
			push hwnd;
			mov eax, defWindowProcAddr;
			call eax;
		}
	}

	__asm {
		//epilog
		mov esp, ebp;
		pop edx;
		pop ecx;
		pop ebx;
		pop ebp;
		pop esi;
		ret 8;
end:
	} 
}

bool DWORDReplace(void* mem, size_t mem_size, DWORD search, DWORD to) {
	if (mem_size < 4)
		return false;

	BYTE* p = (BYTE*)mem;
	for (int i = 0; i < (int)(mem_size - 4); ++i) {
		DWORD* current = (DWORD*)(p + i);
		if (*current == search) {
			*current = to;
			return true;
		}
	}
	return false;
}

struct War3InjectContext {
	void* mem_shellcode;
	size_t mem_shellcode_size;
} InjectContext;

#pragma optimize( "", off ) 
NOINLINE bool Inject(HWND win, HANDLE process, void* invoker, wchar_t* dllname) {
	VMProtectBeginVirtualization("Injection::Inject");

	ULONG bytes;
	
	InitInjectCode();

	//shellcode
	DWORD LdrLoadDllAddr = NULL;
	RemoteData remote_data;
	memset(&remote_data, 0, sizeof(RemoteData));
	if (HMODULE remoteNtdll = GetProcessModuleAddress(process, L"ntdll.dll")) {
		DWORD ntdllDiff = (DWORD)remoteNtdll - (DWORD)NTDLL::Module();
		LdrLoadDllAddr = (DWORD)NTDLL::LdrLoadDll + ntdllDiff;
		remote_data.LdrLoadDllAddr = LdrLoadDllAddr;
	} else 
		return false;

	if (HMODULE remoteUser32 = GetProcessModuleAddress(process, L"User32.dll")) {
		DWORD user32Diff = (DWORD)remoteUser32 - (DWORD)GetModuleHandle(L"User32.dll");
		remote_data.DefWindowProcAddr = (DWORD)DefWindowProc + user32Diff;
	} else 
		return false;

	//Write dll path
	GetCurrentDirectory(MAX_PATH, remote_data.wstringPath);
	
	//Write dll name
	wcscpy_s(remote_data.wstringFilename, MAX_PATH, dllname);

	remote_data.invoker = invoker;

	//Construct UNICODE_STRING
	remote_data.unicodeFilename.Buffer = NULL; //在汇编中指定
	remote_data.unicodeFilename.Length = (USHORT)wcslen(remote_data.wstringFilename) * sizeof(wchar_t);
	remote_data.unicodeFilename.MaximumLength = sizeof(remote_data.wstringFilename);

	size_t data_mem_size = sizeof(RemoteData);
	size_t code_mem_size = CodeSize + (CodeSize % 4);
	size_t mem_size = code_mem_size + data_mem_size;
	void* mem = InjectContext.mem_shellcode = AllocateRemoteMemory(process, NULL, mem_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!mem) {
#ifdef _DEBUG
		printf("Allocate memory failed: 0x%X\n", GetLastError());
#endif
		return false;
	}
	InjectContext.mem_shellcode_size = mem_size;

#ifdef _DEBUG
	printf("Allocated address: 0x%08X\n", mem);
	printf("Data address: 0x%X\n", (BYTE*)mem + code_mem_size);
#endif

	BYTE* data = new BYTE[mem_size];
	memcpy_s(data, mem_size, CodeStartAddr, CodeSize);
	memcpy_s(data + code_mem_size, mem_size - code_mem_size, &remote_data, sizeof(RemoteData));
	void* data_addr = (PVOID)(((BYTE*)mem) + code_mem_size);
	bool replace_result = DWORDReplace(data, mem_size, TPL_REMOTEDATA_ADDR, (DWORD)data_addr);
	//写入shellcode
	if (!(replace_result && WriteRemoteMemory(process, mem, data, mem_size, &bytes) && bytes == mem_size)) {
#ifdef _DEBUG
		printf("Write shellcode failed: 0x%X\n", GetLastError());
#endif
		return false;
	}
	
	//写入Invoker
	if (!(WriteRemoteMemory(process, invoker, &mem, 4, &bytes) && bytes == 4)) {
#ifdef _DEBUG
		printf("Write invoker failed: 0x%X\n", GetLastError());
#endif
		return false;
	}
	
	VMProtectEnd();
	return true;
}

NOINLINE HANDLE NTFindProcessHandle(DWORD pid, wchar_t* name_buffer, size_t name_buffer_size) {
	VMProtectBeginVirtualization("Injection::FindProcessHandle");
	const size_t MAX_CSRSS_COUNT = 10;
	DWORD csrssPIDArray[MAX_CSRSS_COUNT] = {0};
	size_t csrssCount = 0;
	HANDLE rv = NULL;
	HANDLE tmp;
	void* testmem;
	if (pid && NULL != (tmp = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid))) {
		if (NULL != (testmem = AllocateRemoteMemory(tmp, NULL, 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE))) {
			FreeRemoteMemory(tmp, testmem, 1, MEM_RELEASE);
			return tmp;
		}
	}

	NTSTATUS ntstatus;
	NTDLL::QueryData data;
	size_t returnSize;

	jmp_buf env;
	int val = setjmp(env);
	if (val == 0) {
		//Enum all handles
		if (!NT_SUCCESS(NTDLL::QuerySystemInformation(NTDLL::SystemHandleInformation, &data)))
			longjmp(env, 1);

		DWORD* dwordPtr = (DWORD*)data.buffer;
		DWORD handleCount = dwordPtr[0];
		NTDLL::SYSTEM_HANDLE_INFORMATION* sysHandleInfoArray = (NTDLL::SYSTEM_HANDLE_INFORMATION*)(&dwordPtr[1]);

		//csrss.exe
		if (!EnumProcessIdByName(L"csrss.exe", csrssPIDArray, MAX_CSRSS_COUNT, &returnSize) || !returnSize) {
			longjmp(env, 3);
		}
		csrssCount = returnSize;

		for (size_t i = 0; i < csrssCount; ++i) {			
			DWORD csrssPID = csrssPIDArray[i];
			HANDLE csrssHandle = OpenProcess(PROCESS_DUP_HANDLE, false, csrssPID);
			HANDLE processHandle = NULL;
			if (!csrssHandle) {
#ifdef _DEBUG
				printf("Open csrss process failed. skip.\n");
#endif
				continue;
			}

			//Search for Warcraft III Process Handle
			NTDLL::QueryData processInfoData;
			for (size_t i = 0; rv == NULL && i < handleCount; ++i) {
				if (processHandle) {
					CloseHandle(processHandle);
					processHandle = NULL;
				}

				NTDLL::SYSTEM_HANDLE_INFORMATION& item = sysHandleInfoArray[i];
				if (item.ProcessId == csrssPID && NTDLL::GetObjectTypeByNumber(item.ObjectTypeNumber) == NTDLL::OBJECT_TYPE_PROCESS) {
					if (!DuplicateHandle(csrssHandle, (HANDLE)item.Handle, GetCurrentProcess(), &processHandle, NULL, FALSE, DUPLICATE_SAME_ACCESS)) {
#ifdef _DEBUG
						printf("DuplicateHandle failed. last error: 0x%X. skip.\n", GetLastError());
#endif
						continue;
					}

					if (!NT_SUCCESS(ntstatus = NTDLL::QueryInformationProcess(processHandle, NTDLL::ProcessImageFileName, &processInfoData))) {
#ifdef _DEBUG
						printf("QueryInformationProcess failed. status: 0x%X. skip.\n", ntstatus);
#endif
						continue;
					}

					UNICODE_STRING* nameString = ((UNICODE_STRING*)processInfoData.buffer);

					if (pid) {
						if (GetProcessId(processHandle) == pid) {
							rv = processHandle;
						}
					} else {
						if (wcsstr(nameString->Buffer, name_buffer)) {
							rv = processHandle;
						}
					}
				}
			}
			if (!rv && processHandle) {
				CloseHandle(processHandle);
				processHandle = NULL;
			}
		}
	} else {
#ifdef _DEBUG
		printf("Exception: 0x%X, Error Code: 0x%X\n", val, ntstatus);
#endif
	}
	VMProtectEnd();
	return rv;
}

NOINLINE bool NTGetProcessImageFileName(HANDLE processHandle, wchar_t* buffer, size_t buffer_size) {
	VMProtectBeginMutation("Injection::GetProcessImageFileName");
	bool rv = false;
	NTSTATUS ntstatus;
	NTDLL::QueryData processInfoData;
	if (NT_SUCCESS(ntstatus = NTDLL::QueryInformationProcess(processHandle, NTDLL::ProcessImageFileName, &processInfoData))) {
		UNICODE_STRING* nameString = ((UNICODE_STRING*)processInfoData.buffer);
		wcscpy_s(buffer, buffer_size, nameString->Buffer);
		rv = true;	
	}
	VMProtectEnd();
	return rv;
}

#pragma optimize( "", on ) 