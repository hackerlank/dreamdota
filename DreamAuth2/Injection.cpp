#include "stdafx.h"
#include "Injection.h"

struct RemoteData {
	NTSTATUS ntstatus;
	DWORD LdrLoadDllAddr;
	UNICODE_STRING unicodeFilename;
	DWORD orgVtable;
	DWORD device;
	wchar_t	wstringPath[100];
	wchar_t wstringFilename[100];
};

static const uint32_t TPL_REMOTEDATA_ADDR = 0xDEADDEAD;
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
		mov esi, [esp + 8]
		push ebp;
		push ebx;
		push ecx;
		mov ebp, esp;
		sub esp, __LOCAL_SIZE;


		//自定位
		call locate;
locate:
		pop ebx;
		sub ebx, offset locate;
	}

	{
		RemoteData* remoteDataAddr = (RemoteData*)TPL_REMOTEDATA_ADDR;
		HANDLE module;
		DWORD orgVtable = remoteDataAddr->orgVtable;
		DWORD deviceObj, org_38;
		org_38 = *(DWORD*)(orgVtable + 0x38);

		deviceObj = remoteDataAddr->device;

		PUNICODE_STRING unicodeFilename = &(remoteDataAddr->unicodeFilename);
		PWSTR wstringPath = remoteDataAddr->wstringPath;
		PWSTR wstringFilename = remoteDataAddr->wstringFilename;
		void* ldrLoadDllAddr = (void*)remoteDataAddr->LdrLoadDllAddr;
		NTSTATUS* pNtstatus = &(remoteDataAddr->ntstatus);
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
			mov ecx, [pNtstatus];
			mov [ecx], eax;
		}

		*(DWORD*)(remoteDataAddr->device) = remoteDataAddr->orgVtable;

		__asm {
			mov ecx, deviceObj;
			mov eax, org_38;
			call eax;
		}
	}

	__asm {
		//epilog
		mov esp, ebp;
		pop ecx;
		pop ebx;
		pop ebp;
		pop esi;
		ret;
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
	GameModule::SearchResultType sr;
	void* mem_vtable;
	size_t mem_vtable_size;
	void* mem_shellcode;
	size_t mem_shellcode_size;
} InjectContext;

DWORD War3PID;
void SetWar3PID(DWORD pid) {
	War3PID = pid;
}

DWORD GetWar3PID() {
	return War3PID;
}

#pragma optimize( "", off ) 
NOINLINE bool War3Inject(const wchar_t* filename) {
	VMProtectBeginVirtualization("Injection::War3InjectInit");

	ULONG bytes;
	
	InitInjectCode();

	memcpy_s(&InjectContext.sr, sizeof(GameModule::SearchResultType), GameModule::GetLastSearchResult(), sizeof(GameModule::SearchResultType));
	GameModule::SearchResultType& sr = InjectContext.sr;

	HANDLE process = InjectContext.sr.process_handle;
	BYTE* device_vtable = (BYTE*)(InjectContext.sr.cgx_device_vtable);
	void* device = InjectContext.sr.cgx_device;

	//shellcode
	DWORD LdrLoadDllAddr = NULL;
	RemoteData remote_data = {0};
	if (HMODULE remoteNtdll = GetProcessModuleAddress(process, L"ntdll.dll")) {
		DWORD ntdllDiff = (DWORD)remoteNtdll - (DWORD)NTDLL::Module();
		LdrLoadDllAddr = (DWORD)NTDLL::LdrLoadDll + ntdllDiff;
		remote_data.LdrLoadDllAddr = LdrLoadDllAddr;
	} else 
		return false;

	remote_data.device = (DWORD)sr.cgx_device;
	remote_data.orgVtable = (DWORD)sr.cgx_device_vtable;

	//Write dll path
	GetCurrentDirectory(sizeof(remote_data.wstringPath) / sizeof(wchar_t), remote_data.wstringPath);
	
	//Write dll name
	wcscpy_s(remote_data.wstringFilename, sizeof(remote_data.wstringPath) / sizeof(wchar_t), filename);

	//Construct UNICODE_STRING
	remote_data.unicodeFilename.Buffer = NULL; //在汇编中指定
	remote_data.unicodeFilename.Length = (USHORT)wcslen(remote_data.wstringFilename) * sizeof(wchar_t);
	remote_data.unicodeFilename.MaximumLength = sizeof(remote_data.wstringPath);

	remote_data.ntstatus = -1;

	size_t data_mem_size = sizeof(RemoteData);
	size_t code_mem_size = CodeSize + (CodeSize % 4);
	size_t mem_size = code_mem_size + data_mem_size;
	void* mem = InjectContext.mem_shellcode = AllocateRemoteMemory(process, NULL, mem_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!mem) {
#ifdef _DEBUG
		OutputDebug("Allocate memory failed: 0x%X\n", GetLastError());
#endif
		return false;
	}
	InjectContext.mem_shellcode_size = mem_size;

#ifdef _DEBUG
	OutputDebug("Allocated address: 0x%08X\n", mem);
	OutputDebug("Data address: 0x%X\n", (BYTE*)mem + code_mem_size);
#endif

	BYTE* data = new BYTE[mem_size];
	memcpy_s(data, mem_size, CodeStartAddr, CodeSize);
	memcpy_s(data + code_mem_size, mem_size - code_mem_size, &remote_data, sizeof(RemoteData));
	void* data_addr = (PVOID)(((BYTE*)mem) + code_mem_size);
	bool replace_result = DWORDReplace(data, mem_size, TPL_REMOTEDATA_ADDR, (DWORD)data_addr);
	//写入shellcode
	if (!(replace_result && WriteRemoteMemory(process, mem, data, mem_size, &bytes) && bytes == mem_size)) {
#ifdef _DEBUG
		OutputDebug("Write shellcode failed: 0x%X\n", GetLastError());
#endif
		return false;
	}

	//vtable
	DWORD vtable[1 + 45];
	size_t vtable_size = sizeof(vtable);
	void* mem_vtable = InjectContext.mem_vtable = AllocateRemoteMemory(process, NULL, vtable_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	InjectContext.mem_vtable_size = vtable_size;
	if (!InjectContext.mem_vtable)
		return false;

	if (!(ReadRemoteMemory(process, device_vtable - 4, vtable, vtable_size, &bytes) && bytes == vtable_size)) {
#ifdef _DEBUG
		OutputDebug("Read vtable failed: 0x%X\n", GetLastError());
#endif
		return false;
	}

	vtable[1 + 14] = (DWORD)mem;

	if (!(WriteRemoteMemory(process, mem_vtable, vtable, vtable_size, &bytes) && bytes == vtable_size))
		return false;

	void* vtable_ptr = (BYTE*)mem_vtable + 4;
	//替换vtable
	if (!(WriteRemoteMemory(process, device, &vtable_ptr, 4, &bytes) && bytes == 4)) {
#ifdef _DEBUG
		OutputDebug("Replace vtable failed: 0x%X\n", GetLastError());
#endif
		return false;
	}
	VMProtectEnd();
	return true;
}

NOINLINE void War3InjectCleanup() {
	HANDLE process = InjectContext.sr.process_handle;
	if (InjectContext.mem_shellcode)
		FreeRemoteMemory(process, InjectContext.mem_shellcode, InjectContext.mem_shellcode_size, MEM_RELEASE);
	if (InjectContext.mem_vtable) 
		FreeRemoteMemory(process, InjectContext.mem_vtable, InjectContext.mem_vtable_size, MEM_RELEASE);;
	InjectContext.mem_shellcode = InjectContext.mem_vtable = NULL;
	InjectContext.mem_shellcode_size = InjectContext.mem_vtable_size = 0;
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
				OutputDebug("Open csrss process failed. skip.\n");
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
						OutputDebug("DuplicateHandle failed. last error: 0x%X. skip.\n", GetLastError());
#endif
						continue;
					}

					if (!NT_SUCCESS(ntstatus = NTDLL::QueryInformationProcess(processHandle, NTDLL::ProcessImageFileName, &processInfoData))) {
#ifdef _DEBUG
						OutputDebug("QueryInformationProcess failed. status: 0x%X. skip.\n", ntstatus);
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
		OutputDebug("Exception: 0x%X, Error Code: 0x%X\n", val, ntstatus);
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