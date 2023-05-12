#include "main.h"
#include "Halo.h"
#include "Apex.h"

NtUserSetSysColors_t NtUserSetSysColors;
DWORD aNewColors[1];

HKEY svcRoot, svcKey;

LSTATUS PrepareDriverRegEntry(const std::wstring& svcName, const std::wstring& path)
{
	DWORD dwType = 1;
	LSTATUS status = 0;
	WCHAR wszLocalPath[MAX_PATH] = { 0 };

	swprintf_s(wszLocalPath, ARRAYSIZE(wszLocalPath), L"\\??\\%s", path.c_str());

	status = RegOpenKeyW(HKEY_LOCAL_MACHINE, L"system\\CurrentControlSet\\Services", &svcRoot);
	if (status)
		return status;

	status = RegCreateKeyW(svcRoot, svcName.c_str(), &svcKey);
	if (status)
		return status;

	status = RegSetValueExW(
		svcKey, L"ImagePath", 0, REG_SZ,
		reinterpret_cast<const BYTE*>(wszLocalPath),
		static_cast<DWORD>(sizeof(WCHAR) * (wcslen(wszLocalPath) + 1))
	);

	if (status)
		return status;

	DWORD32 self_pid = GetCurrentProcessId();

	status = RegSetValueExW(svcKey, L"pid", 0, REG_DWORD, (BYTE*)&self_pid, sizeof(self_pid));

	if (status)
		return status;

	return RegSetValueExW(svcKey, L"Type", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&dwType), sizeof(dwType));
}

NTSTATUS LoadDriver(const std::wstring& svcName, const std::wstring& path)
{
	UNICODE_STRING Ustr;

	// If path is empty then attempt to start existing service
	if (!path.empty() && PrepareDriverRegEntry(svcName, path) != 0)
	{
		printf("Driver not found");
		return -1;
	}

	std::wstring regPath = L"\\registry\\machine\\SYSTEM\\CurrentControlSet\\Services\\" + svcName;
	RtlInitUnicodeString(&Ustr, regPath.c_str());

	return NtLoadDriver(&Ustr);
}

BOOL SeLoadDriverPrivilege() 
{
	TOKEN_PRIVILEGES tp;
	LUID luid;
	HANDLE hToken = 0;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) || !hToken)
		return false;

	if (!LookupPrivilegeValueA(NULL, "SeLoadDriverPrivilege", &luid))
	{
		CloseHandle(hToken);
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		CloseHandle(hToken);
		return FALSE;
	}

	CloseHandle(hToken);

	return TRUE;
}

NTSTATUS KeWriteVirtualMemory(uintptr_t pid, unsigned char* source, uintptr_t destination, SIZE_T size)
{
	Command cmd;
	cmd.selfref = (uintptr_t)&cmd;
	cmd.cmdId = COMMAND_READWRITE;
	cmd.rw = 1;
	cmd.pid = pid;
	cmd.pSource = source;
	cmd.destination = destination;
	cmd.size = size;

	if (!NtUserSetSysColors(sizeof(cmd) / 4, (char*)&cmd, (char*)aNewColors, 0))
		cmd.pid = STATUS_INVALID_CID;

#ifdef _DEBUG
	printf("Status: 0x%x\n\n", cmd.pid);
#endif // DEBUG

	return cmd.pid;
}

NTSTATUS KeReadVirtualMemory(uintptr_t pid, unsigned char* source, uintptr_t destination, SIZE_T size)
{
	Command cmd;
	cmd.selfref = (uintptr_t)&cmd;
	cmd.cmdId = COMMAND_READWRITE;
	cmd.rw = 0;
	cmd.pid = pid;
	cmd.pSource = source;
	cmd.destination = destination;
	cmd.size = size;

	if (!NtUserSetSysColors(sizeof(cmd) / 4, (char*)&cmd, (char*)aNewColors, 0))
		cmd.pid = STATUS_INVALID_CID;

#ifdef DEBUG
	printf("Status: 0x%x\n\n", cmd.pid);
#endif // DEBUG

	return cmd.pid;
}

uintptr_t KeGetProcessPEB(uintptr_t pid)
{
	Command cmd;
	cmd.selfref = (uintptr_t)&cmd;
	cmd.cmdId = COMMAND_GETPROCPID;
	cmd.pid = pid;

	if (!NtUserSetSysColors(sizeof(cmd) / 4, (char*)&cmd, (char*)aNewColors, 0))
		cmd.pid = STATUS_INVALID_CID;

	return cmd.pid;
}

uintptr_t GetModuleBase(uintptr_t input_pid, uintptr_t input_peb, const wchar_t* name)
{
	PEB peb = { 0 };
	KeReadVirtualMemory(input_pid, (unsigned char*)input_peb, (uintptr_t)&peb, sizeof(peb));

	PEB_LDR_DATA ldr;
	KeReadVirtualMemory(input_pid, (unsigned char*)peb.Ldr, (uintptr_t)&ldr, sizeof(ldr));

	LDR_DATA_TABLE_ENTRY* pModEntry;
	for (LIST_ENTRY* pCur = ldr.InMemoryOrderModuleList.Flink; (uint8_t*)pCur != (uint8_t*)peb.Ldr + offsetof(PEB_LDR_DATA, InMemoryOrderModuleList); pCur = pModEntry->InMemoryOrderLinks.Flink)
	{
		LDR_DATA_TABLE_ENTRY curData;
		KeReadVirtualMemory(input_pid, (unsigned char*)pCur, (uintptr_t)&curData, sizeof(curData));

		pModEntry = CONTAINING_RECORD(&curData, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
		if (pModEntry->BaseDllName.Buffer)
		{
			wchar_t wszBuff[260];
			KeReadVirtualMemory(input_pid, (unsigned char*)pModEntry->BaseDllName.Buffer, (uintptr_t)wszBuff, (SIZE_T)(pModEntry->BaseDllName.Length + 2));

			//printf("%p: %S\n", pModEntry->DllBase, wszBuff);

			if (_wcsicmp(name, wszBuff) == 0)
			{
				return (uintptr_t)pModEntry->DllBase;
				break;
			}
		}
	}

	return 0;
}

uintptr_t GetPIDByName(const wchar_t* name)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_wcsicmp(entry.szExeFile, name) == 0)
			{
				return entry.th32ProcessID;
				break;
			}
		}
	}
}

int main()
{
	LoadLibrary(L"user32.dll");
	NtUserSetSysColors = (NtUserSetSysColors_t)GetProcAddress(LoadLibrary(L"win32u.dll"), "NtUserSetSysColors");
	aNewColors[0] = RGB(0x80, 0x00, 0x80);

	char input = 0;
	printf("1) Load driver\n");
	printf("2) Test Function\n");
	printf("3) Halo MCC\n");
	printf("4) Apex Legends\n");
	
	while (true)
	{
		scanf("%c", &input);
		fflush(stdin);

		if (input == '1')
		{
			if (!SeLoadDriverPrivilege())
				return 0;

			wchar_t buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
			std::wstring bg = std::wstring(buffer).substr(0, pos);
			bg += L"\\ReadWriteDriverMapper.sys";

			NTSTATUS a = LoadDriver(L"ReadWriteDriver", bg.c_str());

			RegDeleteKey(svcRoot, L"ReadWriteDriver");

			DeleteFile(L"ReadWriteDriverMapper.sys");

			printf("NSTATUS Result: 0x%x\n", a);
		}
		else if (input == '2')
		{
			uintptr_t pid = GetPIDByName(L"notepad.exe");
			uintptr_t notepad_base = GetModuleBase(pid, KeGetProcessPEB(pid), L"notepad.exe");
			printf("Notepad Base: 0x%p\n", notepad_base);

			__int64 writeVal = 0xBADC0FFEE0DDF00D;
			KeWriteVirtualMemory(pid, (unsigned char*)&writeVal, notepad_base, sizeof(writeVal));

			__int64 readVal;
			KeReadVirtualMemory(pid, (unsigned char*)notepad_base, (uintptr_t)&readVal, sizeof(writeVal));
			printf("Read value: 0x%p\n", readVal);

			uintptr_t PEBAddress = KeGetProcessPEB(pid);			
			printf("PEB Address: 0x%p\n", PEBAddress);

			printf("ntdll.dll Address: 0x%p\n", GetModuleBase(pid, PEBAddress, L"ntdll.dll"));
		}
		else if (input == '3')
		{
			Halo();
		}
		else if (input == '4')
		{
			Apex();
		}
	}

	getchar();
	getchar();
}