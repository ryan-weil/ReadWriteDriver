#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <intrin.h>
#include <stdint.h>

typedef __int64(__fastcall* t_Win32FreePool)(__int64, __int64, __int64);

typedef (__fastcall* MmAllocateIndependentPages_t)(IN  SIZE_T NumberOfBytes, IN  ULONG Node);

extern NTSTATUS FixRegister();

//NTSTATUS NTAPI MmCopyVirtualMemory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress,
//	SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode, PSIZE_T ReturnSize);

NTKERNELAPI PPEB NTAPI PsGetProcessPeb(IN PEPROCESS Process);

NTSYSAPI PVOID RtlPcToFileHeader(PVOID PcValue, PVOID* BaseOfImage);

NTSTATUS ZwQuerySystemInformation(
	_In_      ULONG                    SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
);

typedef struct
{
	uintptr_t      selfref;
	uintptr_t      pid;         // Target process
	uintptr_t      destination;
	int            cmdId;       // action to perform
	char		   rw;          // 0 = read, 1 = write
	unsigned char* pSource;
	SIZE_T         size;
} Command;

#define COMMAND_READWRITE  0xB16B00B5
#define COMMAND_GETPROCPID 0xBADA55
#define COMMAND_ISLOADED   0x69420

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;