#pragma once

#include <stdio.h>
#include <iostream>
#include <phnt_windows.h>
#include <phnt.h>
#include <tlhelp32.h>

NTSTATUS KeWriteVirtualMemory(uintptr_t pid, unsigned char* source, uintptr_t destination, SIZE_T size);
NTSTATUS KeReadVirtualMemory(uintptr_t pid, unsigned char* source, uintptr_t destination, SIZE_T size);
uintptr_t GetPIDByName(const WCHAR* name);
uintptr_t KeGetProcessPEB(uintptr_t pid);
uintptr_t GetModuleBase(uintptr_t input_pid, uintptr_t input_peb, const wchar_t* name);

typedef BOOL(__fastcall* NtUserSetSysColors_t)(unsigned int cElements, char* lpaElements, char* lpaRgbValues, int Flags);

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