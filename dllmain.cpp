// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "utils.h"

FILE* fDummy;

int WINAPI main()
{
	//Initialize Console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitleA("Drinol - WIP");

	//Redirect output to console

	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	std::cout << "Welcome to Drinol!" << std::endl;

	//Do shit, etc hooks whatever

	utils::check_for_game();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), nullptr, NULL, nullptr);  // NOLINT(clang-diagnostic-main)
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		//utils::dll_management::kill_dll();
	}

	return TRUE;
}