// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <codecvt>

#include "ui.h"
#include "utils.h"

std::string current_game; //TODO: add exit-time destructor for this var
FILE* fDummy;
HMODULE dll_hmodule;

void kill_dll()
{
	//Unhook shit, etc

#if defined _DEBUG
	//Unload Console
	fclose(fDummy);
	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif

	//dx11::CleanupD3D();

	FreeLibraryAndExitThread(dll_hmodule, NULL);
};

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

	//Do shit, hooks whatever etc

	std::cout << "Waiting for a game to be running." << std::endl;

	current_game = utils::check_for_game();

	if (current_game != "halo3.dll")
	{
		std::wstring tmp;
		utils::string_to_wstring(tmp, current_game);

		MessageBox(GetConsoleWindow(), (tmp + L" is not supported at the moment, please use halo3.dll").c_str(), L"Invalid Game!", MB_OK | MB_ICONERROR);

		kill_dll();
	}
	else
	{
		if (MH_Initialize() == MH_OK)
		{
			std::cout << "Minhook Initialized!" << std::endl;
			ui::hook_ui();
		}

		while (true)
		{
			if (!utils::active)
			{
				break;
			}
		}

		kill_dll();
	}
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		dll_hmodule = hModule;
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), nullptr, NULL, nullptr);  // NOLINT(clang-diagnostic-main)
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		kill_dll();
	}

	return TRUE;
}