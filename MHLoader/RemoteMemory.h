#include "stdafx.h"
#ifndef REMOTEMEMORY_H_
#define REMOTEMEMORY_H_
#include "NTDLL.h"

inline bool ReadRemoteMemory(HANDLE process, PVOID baseAddr, PVOID buffer, ULONG regionSize, PULONG bytes = NULL) {
	NTSTATUS status = NTDLL::NtReadVirtualMemory(process, baseAddr, buffer, regionSize, bytes);
	if (NT_SUCCESS(status))
		return true;
	else {
		SetLastError(status);
		return false;
	}
}

template <typename T>
inline bool ReadRemoteMemory(HANDLE process, PVOID baseAddr, PVOID buffer, PULONG bytes = NULL) {
	return ReadRemoteMemory(process, baseAddr, buffer, sizeof(T), bytes);
}

inline bool WriteRemoteMemory(HANDLE process, PVOID baseAddr, PVOID buffer, ULONG regionSize, PULONG bytes = NULL) {
	NTSTATUS status = NTDLL::NtWriteVirtualMemory(process, baseAddr, (PVOID)buffer, regionSize, bytes);
	if (NT_SUCCESS(status))
		return true;
	else {
		SetLastError(status);
		return false;
	}
}

template <typename T>
inline bool WriteRemoteMemory(HANDLE process, PVOID baseAddr, PVOID buffer, PULONG bytes = NULL) {
	return WriteRemoteMemory(process, baseAddr, buffer, sizeof(T), bytes);
}



inline PVOID AllocateRemoteMemory(HANDLE process, PVOID baseAddr, ULONG regionSize, ULONG allocationType, ULONG protect) {
	PVOID rv = baseAddr;
	NTSTATUS status = NTDLL::NtAllocateVirtualMemory(process, &rv, 0, &regionSize, allocationType, protect);
	if (NT_SUCCESS(status))
		return rv;
	else {
		SetLastError(status);
		return NULL;
	}
}

inline bool FreeRemoteMemory(HANDLE process, PVOID baseAddr, ULONG regionSize, ULONG freeType) {
	NTSTATUS status = NTDLL::NtFreeVirtualMemory(process, &baseAddr, &regionSize, freeType);
	if (NT_SUCCESS(status))
		return true;
	else {
		SetLastError(status);
		return false;
	}
}

#endif