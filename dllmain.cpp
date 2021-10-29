// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"



FILE* fDummy;

int WINAPI main()
{
#if defined _DEBUG
	//Initialize Console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	//Redirect output to console

	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	std::cout << "Welcome to Drinol!" << std::endl;
#endif

	//Do shit, etc hooks whatever
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), nullptr, NULL, nullptr);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		//utils::dll_management::kill_dll();
	}

	return TRUE;
}