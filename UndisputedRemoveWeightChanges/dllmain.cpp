#include "version/version.h"
#include "utils/MemUtils.h"

DWORD WINAPI threadFunc(LPVOID lpParam) {
	DWORD undisputedProcessId = getProcessId(L"Undisputed.exe");
	DWORD_PTR GameAssemblyBaseAddress = 0;
	unsigned char* hook_location;
	DWORD oldProtect;
	DWORD nopInstruction = 0x90;
	HANDLE hUndisputedProcess;

	while (GameAssemblyBaseAddress == 0) {
		GameAssemblyBaseAddress = getDllBaseAddress(undisputedProcessId, L"GameAssembly.dll");
	}
	hook_location = (unsigned char*)(GameAssemblyBaseAddress + 0x1DB5EE4);
	hUndisputedProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, 0, undisputedProcessId);

	VirtualProtectEx(hUndisputedProcess, (void*)hook_location, 4, PAGE_EXECUTE_READWRITE, &oldProtect);

	//replaces changing weight instruction with nop's
	for (int i = 0; i < 4; i++) {
		WriteProcessMemory(hUndisputedProcess, (void*)(hook_location + i), &nopInstruction, 1, NULL);
	}

	CloseHandle(hUndisputedProcess);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstdll, DWORD fdwReason, LPVOID lpvReserved) {
	HANDLE hThread;

	switch (fdwReason) {

		case DLL_PROCESS_ATTACH:
			hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, NULL);
			CloseHandle(hThread);
			break;

		case DLL_PROCESS_DETACH:
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}