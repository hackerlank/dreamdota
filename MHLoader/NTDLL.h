#ifndef NTDLL_H
#define NTDLL_H

#include <winternl.h>

namespace NTDLL {

const NTSTATUS STATUS_INFO_LENGTH_MISMATCH = (NTSTATUS)0xC0000004L;
const NTSTATUS STATUS_BUFFER_OVERFLOW = (NTSTATUS)0x80000005L;

const ULONG SE_DEBUG_PRIVILEGE = 20L;


typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation,
    SystemProcessorInformation,
    SystemPerformanceInformation,
    SystemTimeOfDayInformation,
    SystemPathInformation,
    SystemProcessInformation,
    SystemCallCountInformation,
    SystemDeviceInformation,
    SystemProcessorPerformanceInformation,
    SystemFlagsInformation,
    SystemCallTimeInformation,
    SystemModuleInformation,
    SystemLocksInformation,
    SystemStackTraceInformation,
    SystemPagedPoolInformation,
    SystemNonPagedPoolInformation,
    SystemHandleInformation,
    SystemObjectInformation,
    SystemPageFileInformation,
    SystemVdmInstemulInformation,
    SystemVdmBopInformation,
    SystemFileCacheInformation,
    SystemPoolTagInformation,
    SystemInterruptInformation,
    SystemDpcBehaviorInformation,
    SystemFullMemoryInformation,
    SystemLoadGdiDriverInformation,
    SystemUnloadGdiDriverInformation,
    SystemTimeAdjustmentInformation,
    SystemSummaryMemoryInformation,
    SystemNextEventIdInformation,
    SystemEventIdsInformation,
    SystemCrashDumpInformation,
    SystemExceptionInformation,
    SystemCrashDumpStateInformation,
    SystemKernelDebuggerInformation,
    SystemContextSwitchInformation,
    SystemRegistryQuotaInformation,
    SystemExtendServiceTableInformation,
    SystemPrioritySeperation,
    SystemPlugPlayBusInformation,
    SystemDockInformation,
    SystemPowerInformation,
    SystemProcessorSpeedInformation,
    SystemCurrentTimeZoneInformation,
    SystemLookasideInformation
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_HANDLE_INFORMATION {
    ULONG ProcessId;
    UCHAR ObjectTypeNumber;
    UCHAR Flags;
    USHORT Handle;
    PVOID Object;
    ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllInformation,
    ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

#pragma warning( push )
#pragma warning( disable : 4200 )
typedef struct _OBJECT_NAME_INFORMATION {
  UNICODE_STRING          Name;
  WCHAR                   NameBuffer[0];
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;
#pragma warning( pop )

typedef enum _PROCESSINFOCLASS {
    ProcessBasicInformation = 0,
	ProcessDebugPort = 7,
    ProcessWow64Information = 26,
	ProcessImageFileName = 27
} PROCESSINFOCLASS;

typedef struct _CLIENT_ID{
    PVOID UniqueProcess;
    PVOID UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

//Functions
typedef NTSTATUS (__stdcall *NtQuerySystemInformationT)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
);
extern NtQuerySystemInformationT NtQuerySystemInformation;


typedef NTSTATUS (__stdcall *NtQueryObjectT)(
  HANDLE Handle,
  ULONG ObjectInformationClass,
  PVOID ObjectInformation,
  ULONG ObjectInformationLength,
  PULONG ReturnLength
);
extern NtQueryObjectT NtQueryObject;

typedef NTSTATUS (__stdcall *NtOpenProcessT)(
  PHANDLE ProcessHandle,
  ACCESS_MASK AccessMask,
  POBJECT_ATTRIBUTES ObjectAttributes,
  NTDLL::PCLIENT_ID ClientId 
);
extern NtOpenProcessT NtOpenProcess;

typedef NTSTATUS (__stdcall *RtlAdjustPrivilegeT)(
  ULONG    Privilege,
  BOOLEAN  Enable,
  BOOLEAN  CurrentThread,
  PBOOLEAN Enabled
);
extern RtlAdjustPrivilegeT RtlAdjustPrivilege;

typedef NTSTATUS (__stdcall *NtQueryInformationProcessT)(
	HANDLE ProcessHandle,
	ULONG ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
);
extern NtQueryInformationProcessT NtQueryInformationProcess;

typedef NTSTATUS (__stdcall *RtlInitializeCriticalSectionT)(
  RTL_CRITICAL_SECTION* crit
);
extern RtlInitializeCriticalSectionT RtlInitializeCriticalSection;

typedef NTSTATUS (__stdcall *LdrLoadDllT)(
  PWCHAR PathToFile OPTIONAL,
  ULONG Flags OPTIONAL,
  PUNICODE_STRING ModuleFileName,
  PHANDLE ModuleHandle 
);
extern LdrLoadDllT LdrLoadDll;

typedef NTSTATUS (__stdcall *NtReadVirtualMemoryT)(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG NumberOfBytesToRead,
	PULONG NumberOfBytesReaded
);
extern NtReadVirtualMemoryT NtReadVirtualMemory;

typedef NTSTATUS (__stdcall *NtWriteVirtualMemoryT)(
	HANDLE ProcessHandle,
	PVOID BaseAddress,
	PVOID Buffer,
	ULONG NumberOfBytesToWrite,
	PULONG NumberOfBytesWritten
);
extern NtWriteVirtualMemoryT NtWriteVirtualMemory;

typedef NTSTATUS (__stdcall *NtAllocateVirtualMemoryT)(
	HANDLE     ProcessHandle,
	OUT PVOID  *BaseAddress,
	ULONG      ZeroBits,
	OUT PULONG RegionSize,
	ULONG      AllocationType,
	ULONG      Protect
);
extern NtAllocateVirtualMemoryT NtAllocateVirtualMemory;

typedef NTSTATUS (__stdcall *NtFreeVirtualMemoryT)(
	HANDLE     ProcessHandle,
	PVOID      *BaseAddress,
	OUT PULONG RegionSize,
	ULONG      FreeType 
);
extern NtFreeVirtualMemoryT NtFreeVirtualMemory;

typedef NTSTATUS (__stdcall *NtProtectVirtualMemoryT)(
	HANDLE     ProcessHandle,
	OUT PVOID  *BaseAddress,
	OUT PULONG NumberOfBytesToProtect,
	ULONG      NewAccessProtection,
	PULONG     OldAccessProtection
);
extern NtProtectVirtualMemoryT NtProtectVirtualMemory;

//Custom
struct QueryData {
	BYTE* buffer;
	DWORD bufffer_size;

	QueryData() {
		this->buffer = NULL;
		this->bufffer_size = 0;
	}

	~QueryData() {
		if (this->buffer)
			delete [] this->buffer;
	}
};

const DWORD SAVED_OBJECT_TYPE_COUNT = 3;
enum ObjectType {
	OBJECT_TYPE_UNKNOWN,
	OBJECT_TYPE_PROCESS,
	OBJECT_TYPE_EVENT
};

void DumpObjectName(HANDLE handle);
void DumpObjectTypeName(HANDLE handle);
ObjectType GetObjectTypeByNumber(UCHAR ObjectTypeNumber);

NTSTATUS QuerySystemInformation(SYSTEM_INFORMATION_CLASS infoClass, QueryData* data);
NTSTATUS QueryObjectNameInformation(HANDLE handle, OBJECT_INFORMATION_CLASS infoClass, QueryData* data);
NTSTATUS QueryInformationProcess(HANDLE handle, PROCESSINFOCLASS infoClass, QueryData* data);

void Init();
void Cleanup();
HMODULE Module();

} //namespace

#endif