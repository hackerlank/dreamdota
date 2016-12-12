#include "stdafx.h"
#include "SystemTools.h"
#include "NTDLL.h"
#include "Injection.h"
#include <winternl.h>

namespace SystemTools {
	bool g_inited = false;

	size_t GetVMAllocationSize(void* start) {
		size_t rv = 0;
		MEMORY_BASIC_INFORMATION mbi;
		BYTE* ptr = (BYTE*)start;
		size_t q_result_bytes = VirtualQuery(ptr, &mbi, sizeof(mbi));
		if (q_result_bytes) {
			void* base = mbi.AllocationBase;
			size_t region_size = mbi.RegionSize;
			BYTE* ptr = (BYTE*)start;
			while(q_result_bytes && mbi.AllocationBase == base) {
				ptr += region_size;
				rv += region_size;
				q_result_bytes = VirtualQuery(ptr, &mbi, sizeof(mbi));
			}
		}
		return rv;
	}

	size_t GetVMAllocationSizeEx(HANDLE process, void* start) {
		size_t rv = 0;
		MEMORY_BASIC_INFORMATION mbi;
		BYTE* ptr = (BYTE*)start;
		size_t q_result_bytes = VirtualQueryEx(process, ptr, &mbi, sizeof(mbi));
		if (q_result_bytes) {
			void* base = mbi.AllocationBase;
			size_t region_size = mbi.RegionSize;
			BYTE* ptr = (BYTE*)start;
			while(q_result_bytes && mbi.AllocationBase == base) {
				ptr += region_size;
				rv += region_size;
				q_result_bytes = VirtualQueryEx(process, ptr, &mbi, sizeof(mbi));
			}
		}
		return rv;
	}

	bool GetModuleInfo(const TCHAR* module_name, ModuleInfo* info) {
		bool rv = false;
		HMODULE handle = GetModuleHandle(module_name);
		if (handle) {
			info->handle = handle;
			if ((info->image_size = GetVMAllocationSize((void*)handle)) > 0) {
				rv = true;
			}
		}
		return rv;
	}

	bool GetModuleInfoEx(HANDLE process, const TCHAR* module_name, ModuleInfo* info) {
		bool rv = false;
		HMODULE handle = GetProcessModuleAddress(process, module_name);
		if (handle) {
			info->handle = handle;
			if ((info->image_size = GetVMAllocationSizeEx(process, (void*)handle)) > 0) {
				rv = true;
			}
		}
		return rv;
	}

	bool GetThreadInfo(DWORD tid, ThreadInfo* info) {
		bool rv = false;
		HANDLE handle = OpenThread(THREAD_QUERY_INFORMATION, FALSE, tid);
		if (handle) {
			DWORD start_addr = NULL;
			ULONG rsize = 0;
			NTDLL::QueryData data;
			if (NT_SUCCESS(NTDLL::QueryInformationThread(handle, NTDLL::ThreadQuerySetWin32StartAddress, &data))) {
				info->start_address = *(void**)(data.buffer);
				rv = true;
			}
			CloseHandle(handle);
		}
		return rv;
	}

	bool Init() {
		bool rv = true;

		g_inited = rv;
		return rv;
	}

	void Cleanup() {
		if (g_inited) {

		}
	}
}