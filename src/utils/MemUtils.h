#pragma once
#include <Windows.h>
#include <TlHelp32.h>

DWORD getProcessId(LPCWSTR processName) {

	DWORD processId = 0;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(hSnapshot, &entry)) {
		do {
			if (wcscmp(entry.szExeFile, processName) == 0) {
				processId = entry.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &entry));
	}
	return processId;
}

DWORD_PTR getDllBaseAddress(DWORD processId, const wchar_t* dllName) {
	DWORD_PTR dllBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

	if (hSnapshot != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);

		if (Module32First(hSnapshot, &entry)) {
			do {
				if (wcscmp(entry.szModule, dllName) == 0) {
					dllBaseAddress = (DWORD_PTR)entry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &entry));
		}
		CloseHandle(hSnapshot);

	}
	return dllBaseAddress;
}