#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		MessageBox(0, L"ทดสอบ!", L"ทดสอบ", MB_ICONINFORMATION);

	ExitProcess(0);

	return TRUE;
}
