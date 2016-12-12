#include "stdafx.h"
#include "NTDLL.h"
#include "Exception.h"

namespace NTDLL {

NtQuerySystemInformationT NtQuerySystemInformation;
NtQueryObjectT NtQueryObject;
NtOpenProcessT NtOpenProcess;
RtlAdjustPrivilegeT RtlAdjustPrivilege;
NtQueryInformationProcessT NtQueryInformationProcess;
RtlInitializeCriticalSectionT RtlInitializeCriticalSection;
LdrLoadDllT LdrLoadDll;
NtReadVirtualMemoryT NtReadVirtualMemory;
NtWriteVirtualMemoryT NtWriteVirtualMemory;
NtAllocateVirtualMemoryT NtAllocateVirtualMemory;
NtFreeVirtualMemoryT NtFreeVirtualMemory;
NtProtectVirtualMemoryT NtProtectVirtualMemory;

static UCHAR SavedObjectTypeArray[SAVED_OBJECT_TYPE_COUNT];
ObjectType GetObjectTypeByNumber(UCHAR ObjectTypeNumber) {
	for (int i = OBJECT_TYPE_UNKNOWN + 1; i < SAVED_OBJECT_TYPE_COUNT; ++i) {
		if (SavedObjectTypeArray[i] == ObjectTypeNumber)
			return (ObjectType)i;
	}
	return OBJECT_TYPE_UNKNOWN;
}

void QueryDataFreeBuffer(QueryData* result) {
	if (result->buffer) {
		delete [] result->buffer;
		result->buffer = NULL;
		result->bufffer_size = 0;
	}
}

void QueryDataInit(QueryData* result, DWORD size) {
	result->buffer = new BYTE[size];
	memset(result->buffer, 0, size);
	result->bufffer_size = size;
}

void QueryDataResize(QueryData* result, DWORD size) {
	if (result->buffer)
		delete [] result->buffer;
	result->buffer = new BYTE[size];
	memset(result->buffer, 0, size);
	result->bufffer_size = size;
}

void DumpObjectName(HANDLE handle) {
	BYTE* data = NULL;
	DWORD trySize = 0x1000;	
	NTSTATUS ntstatus;
	//NtQueryObject: Get object name
	while (true) {
		if (data)
			delete [] data;
		data = new BYTE[trySize];
		ntstatus = NtQueryObject(handle, ObjectNameInformation, (PVOID)(data), trySize, &trySize);
		if (NT_SUCCESS(ntstatus)) {
			break;
		} else {
			if (ntstatus != STATUS_INFO_LENGTH_MISMATCH && ntstatus != STATUS_BUFFER_OVERFLOW) {
				printf("error: 0x%X\n", ntstatus);
				delete [] data;
				return;
			} else {
				trySize *= 2;
			}
		}
	}
	wprintf(L"%ws\n", ((OBJECT_NAME_INFORMATION*)data)->Name.Buffer);
	if (data)
		delete [] data;
}

void DumpObjectTypeName(HANDLE handle) {
	BYTE* data = NULL;
	DWORD trySize = 0x1000;	
	NTSTATUS ntstatus;
	//NtQueryObject: Get object name
	while (true) {
		if (data)
			delete [] data;
		data = new BYTE[trySize];
		ntstatus = NtQueryObject(handle, ObjectTypeInformation, (PVOID)(data), trySize, &trySize);
		if (NT_SUCCESS(ntstatus)) {
			break;
		} else {
			if (ntstatus != STATUS_INFO_LENGTH_MISMATCH && ntstatus != STATUS_BUFFER_OVERFLOW) {
				printf("error: 0x%X\n", ntstatus);
				delete [] data;
				return;
			} else {
				trySize *= 2;
			}
		}
	}
	wprintf(L"%ws\n", ((PUBLIC_OBJECT_TYPE_INFORMATION*)data)->TypeName.Buffer);
	if (data)
		delete [] data;
}

NTSTATUS QuerySystemInformation(SYSTEM_INFORMATION_CLASS infoClass, QueryData* data) {
	jmp_buf env;
	int val = setjmp(env);
	NTSTATUS ntstatus;
	if (val == 0) {
		DWORD trySize = 0x500;
		bool inited = false;
		while (true) {
			if (inited)
				QueryDataResize(data, trySize);
			else {
				QueryDataInit(data, trySize);
				inited = true;
			}

			ntstatus = NtQuerySystemInformation(infoClass, data->buffer, trySize, &trySize);

			if (NT_SUCCESS(ntstatus)) 
				break;
			else {
				if (ntstatus != STATUS_INFO_LENGTH_MISMATCH) {
					longjmp(env, ntstatus);
				} else {
					trySize *= 2;
				}
			}
		}

	} else {
		QueryDataFreeBuffer(data);
	}
	return ntstatus;
}

NTSTATUS QueryObjectNameInformation(HANDLE handle, OBJECT_INFORMATION_CLASS infoClass, QueryData* data) {
	jmp_buf env;
	int val = setjmp(env);
	NTSTATUS ntstatus;
	if (val == 0) {
		DWORD trySize = 0x100;
		bool inited = false;
		while (true) {
			if (inited)
				QueryDataResize(data, trySize);
			else {
				QueryDataInit(data, trySize);
				inited = true;
			}

			ntstatus = NtQueryObject(handle, infoClass, (PVOID)(data->buffer), trySize, &trySize);

			if (NT_SUCCESS(ntstatus)) 
				break;
			else {
				if (ntstatus != STATUS_INFO_LENGTH_MISMATCH) {
					longjmp(env, ntstatus);
				} else {
					trySize *= 2;
				}
			}
		}

	} else {
		QueryDataFreeBuffer(data);
	}
	return ntstatus;
}

NTSTATUS QueryInformationProcess(HANDLE handle, PROCESSINFOCLASS infoClass, QueryData* data) {
	jmp_buf env;
	int val = setjmp(env);
	NTSTATUS ntstatus;
	if (val == 0) {
		DWORD trySize = 0x100;
		bool inited = false;
		while (true) {
			if (inited)
				QueryDataResize(data, trySize);
			else {
				QueryDataInit(data, trySize);
				inited = true;
			}

			ntstatus = NtQueryInformationProcess(handle, infoClass, (PVOID)(data->buffer), trySize, &trySize);

			if (NT_SUCCESS(ntstatus)) 
				break;
			else {
				if (ntstatus != STATUS_INFO_LENGTH_MISMATCH) {
					longjmp(env, ntstatus);
				} else {
					trySize *= 2;
				}
			}
		}

	} else {
		QueryDataFreeBuffer(data);
	}
	return ntstatus;
}

struct {
	HANDLE handle;
	DWORD pid;

	HANDLE eventObject;
} CurrentProcessInfo;

HMODULE NtdllModule = NULL;
HMODULE Module() {
	return NtdllModule;
}

void Init() {
	VMProtectBeginVirtualization("NTDLL_Init");

	HMODULE hNtdll = NtdllModule = GetModuleHandleA("ntdll.dll");
	bool success = 
		(hNtdll != NULL) &&
		(CurrentProcessInfo.pid = GetCurrentProcessId()) &&
		(CurrentProcessInfo.handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CurrentProcessInfo.pid)) &&
		(CurrentProcessInfo.eventObject = CreateEvent(NULL, FALSE, FALSE, NULL)) &&
		
		NULL != (NTDLL::NtQuerySystemInformation = (NTDLL::NtQuerySystemInformationT)(GetProcAddress(hNtdll, "NtQuerySystemInformation"))) && 
		NULL != (NTDLL::NtQueryObject = (NTDLL::NtQueryObjectT)(GetProcAddress(hNtdll, "NtQueryObject"))) && 
		NULL != (NTDLL::NtOpenProcess = (NTDLL::NtOpenProcessT)(GetProcAddress(hNtdll, "NtOpenProcess"))) && 
		NULL != (NTDLL::RtlAdjustPrivilege = (NTDLL::RtlAdjustPrivilegeT)(GetProcAddress(hNtdll, "RtlAdjustPrivilege"))) && 
		NULL != (NTDLL::NtQueryInformationProcess = (NTDLL::NtQueryInformationProcessT)(GetProcAddress(hNtdll, "NtQueryInformationProcess"))) && 
		NULL != (NTDLL::RtlInitializeCriticalSection = (NTDLL::RtlInitializeCriticalSectionT)(GetProcAddress(hNtdll, "RtlInitializeCriticalSection"))) && 
		NULL != (NTDLL::LdrLoadDll = (NTDLL::LdrLoadDllT)(GetProcAddress(hNtdll, "LdrLoadDll"))) &&
		NULL != (NTDLL::NtReadVirtualMemory = (NTDLL::NtReadVirtualMemoryT)(GetProcAddress(hNtdll, "NtReadVirtualMemory"))) &&
		NULL != (NTDLL::NtWriteVirtualMemory = (NTDLL::NtWriteVirtualMemoryT)(GetProcAddress(hNtdll, "NtWriteVirtualMemory"))) &&
		NULL != (NTDLL::NtAllocateVirtualMemory = (NTDLL::NtAllocateVirtualMemoryT)(GetProcAddress(hNtdll, "NtAllocateVirtualMemory"))) &&
		NULL != (NTDLL::NtFreeVirtualMemory = (NTDLL::NtFreeVirtualMemoryT)(GetProcAddress(hNtdll, "NtFreeVirtualMemory"))) &&
		NULL != (NTDLL::NtProtectVirtualMemory = (NTDLL::NtProtectVirtualMemoryT)(GetProcAddress(hNtdll, "NtProtectVirtualMemory")));

	if (success) {
		//—∞’“ObjectTypeNumer
		NTDLL::QueryData data;
		if (NT_SUCCESS(NTDLL::QuerySystemInformation(NTDLL::SystemHandleInformation, &data))) {
			DWORD* dwordPtr = (DWORD*)data.buffer;
			DWORD numOfHandles = dwordPtr[0];
			NTDLL::SYSTEM_HANDLE_INFORMATION* sysHandleInfos = (NTDLL::SYSTEM_HANDLE_INFORMATION*)(&dwordPtr[1]);
			for (DWORD i = 0; i < numOfHandles; ++i) {
				NTDLL::SYSTEM_HANDLE_INFORMATION* info = &(sysHandleInfos[i]);
				if (info->ProcessId == CurrentProcessInfo.pid) {
					if (!NTDLL::SavedObjectTypeArray[NTDLL::OBJECT_TYPE_PROCESS] && (HANDLE)info->Handle == CurrentProcessInfo.handle) {
						NTDLL::SavedObjectTypeArray[NTDLL::OBJECT_TYPE_PROCESS] = info->ObjectTypeNumber;
					}

					if (!NTDLL::SavedObjectTypeArray[NTDLL::OBJECT_TYPE_EVENT] && (HANDLE)info->Handle == CurrentProcessInfo.eventObject) {
						NTDLL::SavedObjectTypeArray[NTDLL::OBJECT_TYPE_EVENT] = info->ObjectTypeNumber;
					}
				}
			}
		}
	} else {
		GLOBAL_LONGJMP(EXCEPTION_NTDLL_INIT_FAILED);
	}

	VMProtectEnd();
}

void Cleanup() {

}

} //namespace