#pragma once
#include <Windows.h>
#include <cstdio>


typedef DWORD(__stdcall* fn_GetFileVersionInfoSizeA)(
	LPCSTR  lptstrFilename,
	LPDWORD lpdwHandle
	);

typedef BOOL(__stdcall* fn_VerQueryValueA)(
	LPCVOID pBlock,
	LPCSTR  lpSubBlock,
	LPVOID* lplpBuffer,
	PUINT   puLen
	);

typedef BOOL(__stdcall* fn_GetFileVersionInfoA)(
	LPCSTR lptstrFilename,
	DWORD  dwHandle,
	DWORD  dwLen,
	LPVOID lpData
	);

extern "C" DWORD GetFileVersionInfoSizeA_FN(
	LPCSTR  lptstrFilename,
	LPDWORD lpdwHandle)
{
	CHAR sys32Path[MAX_PATH];
	GetSystemDirectoryA(sys32Path, MAX_PATH);
	char dllPath[MAX_PATH];
	sprintf_s(dllPath, "%s\\version.dll", sys32Path);

	HMODULE original_dll = LoadLibraryA(dllPath);
	fn_GetFileVersionInfoSizeA original_func = (fn_GetFileVersionInfoSizeA)GetProcAddress(original_dll, "GetFileVersionInfoSizeA");

	return original_func(lptstrFilename, lpdwHandle);
}

extern "C"  BOOL VerQueryValueA_FN(
	LPCVOID pBlock,
	LPCSTR  lpSubBlock,
	LPVOID * lplpBuffer,
	PUINT   puLen)
{
	CHAR sys32Path[MAX_PATH];
	GetSystemDirectoryA(sys32Path, MAX_PATH);
	char dllPath[MAX_PATH];
	sprintf_s(dllPath, "%s\\version.dll", sys32Path);

	HMODULE original_dll = LoadLibraryA(dllPath);
	fn_VerQueryValueA original_func = (fn_VerQueryValueA)GetProcAddress(original_dll, "VerQueryValueA");

	return original_func(pBlock, lpSubBlock, lplpBuffer, puLen);
}

extern "C" BOOL GetFileVersionInfoA_FN(
	LPCSTR lptstrFilename,
	DWORD  dwHandle,
	DWORD  dwLen,
	LPVOID lpData)
{
	CHAR sys32Path[MAX_PATH];
	GetSystemDirectoryA(sys32Path, MAX_PATH);
	char dllPath[MAX_PATH];
	sprintf_s(dllPath, "%s\\version.dll", sys32Path);

	HMODULE original_dll = LoadLibraryA(dllPath);
	fn_GetFileVersionInfoA original_func = (fn_GetFileVersionInfoA)GetProcAddress(original_dll, "GetFileVersionInfoA");

	return original_func(lptstrFilename, dwHandle, dwLen, lpData);
}

extern "C" void GetFileVersionInfoByHandle_FN() { return; }
extern "C" void GetFileVersionInfoExA_FN() { return; }
extern "C" void GetFileVersionInfoExW_FN() { return; }
extern "C" void GetFileVersionInfoSizeExA_FN() { return; }
extern "C" void GetFileVersionInfoSizeExW_FN() { return; }
extern "C" void GetFileVersionInfoSizeW_FN() { return; }
extern "C" void GetFileVersionInfoW_FN() { return; }
extern "C" void VerFindFileA_FN() { return; }
extern "C" void VerFindFileW_FN() { return; }
extern "C" void VerInstallFileA_FN() { return; }
extern "C" void VerInstallFileW_FN() { return; }
extern "C" void VerLanguageNameA_FN() { return; }
extern "C" void VerLanguageNameW_FN() { return; }
extern "C" void VerQueryValueW_FN() { return; }

