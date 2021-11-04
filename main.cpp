#include "pch.h"
#include "ui.h"
#include "utils.h"
#include "main.h"

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

	ui::unhook_ui();

	FreeLibraryAndExitThread(dll_hmodule, NULL);
};

int WINAPI start()
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

	main::current_game = utils::check_for_game();

	if (main::current_game == "halo1.dll" || main::current_game == "halo2.dll")
	{
		std::wstring tmp;
		utils::string_to_wstring(tmp, main::current_game);

		MessageBox(GetConsoleWindow(), (tmp + L" is not supported at the moment. Sorry!").c_str(), L"Invalid Game!", MB_OK | MB_ICONERROR);

		kill_dll();
	}
	else
	{
		if (MH_Initialize() == MH_OK)
		{
			std::cout << "Minhook Initialized!" << std::endl;
			utils::init_game_offsets(main::current_game);
			ui::hook_ui();

			while (true)
			{
				if (!utils::active)
				{
					break;
				}
			}
		}

		kill_dll();
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		dll_hmodule = hModule;
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(start), nullptr, NULL, nullptr);  // NOLINT(clang-diagnostic-main)
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		kill_dll();
	}

	return TRUE;
}