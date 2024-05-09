#include <iostream>
#include <Windows.h>

using namespace std;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow)
{
	Sleep(6000);

	LPSTR DllPath = "D:\\WinAsm2024[2]\\DllInjection\\Simple-DLL-Injection\\Debug\\testlib.dll";
	int dwSize = strlen(DllPath) * sizeof(char);

	HWND hwnd = FindWindowW(NULL, L"Window");
	DWORD procID;

	GetWindowThreadProcessId(hwnd, &procID);

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	LPVOID pDllPath = VirtualAllocEx(handle, 0, dwSize, MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(handle, pDllPath, (LPVOID)DllPath, dwSize, 0);

	HMODULE hModuleKernel32 = GetModuleHandleW(L"Kernel32.dll");
	DWORD hModuleProc = (DWORD)GetProcAddress(hModuleKernel32, "LoadLibraryA");
	HANDLE hLoadThread = CreateRemoteThread(handle, 0, 0, (LPTHREAD_START_ROUTINE)hModuleProc, pDllPath, 0, 0);

	WaitForSingleObject(hLoadThread, INFINITE);
	VirtualFreeEx(handle, pDllPath, dwSize, MEM_RELEASE);

	return 0;
}
