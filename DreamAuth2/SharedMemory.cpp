#include "stdafx.h"
#include "SharedMemory.h"

namespace SharedMemory {
	void* Smem = NULL;
	HANDLE File = NULL;
	wchar_t Name[9];

	void Init() {
		
	}

	void Cleanup() {
		Close();
	}

	void Close() {
		if (Smem) {
			UnmapViewOfFile(Smem);
			Smem = NULL;
		}

		if (File) {
			CloseHandle(File);
			File = NULL;
		}
	}

	void* Create() {
		_snwprintf_s(Name, 8, L"%08X", GetId());
		File = CreateFileMappingW(
            INVALID_HANDLE_VALUE,   // use paging file
            NULL,                   // default security
            PAGE_READWRITE,         // read/write access
            0,                      // maximum object size (high-order DWORD)
            SMEM_SIZE,              // maximum object size (low-order DWORD)
			Name);					// name of mapping object			
		if (!File)
			return NULL;

		Smem = (void*)MapViewOfFile(File, FILE_MAP_ALL_ACCESS, 0, 0, SMEM_SIZE);
		if (!Smem)
			return NULL;

		return Smem;
	}

	DWORD GetId() {
		return 0xA2A2A2A2;

		/*
		VMProtectBeginVirtualization("SharedMemory::GetId");
        BYTE szCpu[16] = {0};
        UINT uCpuID = 0U;
		DWORD rv = NULL;
        __try 
        {
            _asm 
            {
                mov eax, 0
                cpuid
                mov dword ptr szCpu[0], ebx
                mov dword ptr szCpu[4], edx
                mov dword ptr szCpu[8], ecx
                mov eax, 1
                cpuid
                mov uCpuID, edx
            }
			DWORD* pDWORD = (DWORD*)szCpu;
			rv = (pDWORD[0] + 0xDEADDEADu) ^ (pDWORD[1] - 0xDD3ADD3A);
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            rv = 0xEEDD3AEEu;
        }
		VMProtectEnd();
		return rv;
		*/
        
	}

	void* Open() {
		if (Smem) 
			return Smem;

		_snwprintf_s(Name, 8, L"%08X", GetId());
		File = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, Name);
		if (!File)
			return NULL;

		Smem = (void*)MapViewOfFile(File, FILE_MAP_ALL_ACCESS, 0, 0, SMEM_SIZE);
		if (!Smem)
			return NULL;

		return Smem;
	}

} //namespace