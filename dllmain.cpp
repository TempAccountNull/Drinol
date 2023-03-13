#include <iostream>
#include <minhook/include/MinHook.h>

#include "utils.h"
#include "config/config.h"
#include "gui/gui.h"
#include "middleware/middleware.h"

//TODO: possibly make the console appear in the release build or have it inside the menu?
#if defined _DEBUG
#include "console.h"
#endif

void drinol_init()
{
#if defined _DEBUG
	// Initialize debug console.
	console::init();
#endif

	std::cout << "Drinol is loading." << std::endl;

	// Load data from the ini config.

	// Get config folder
	config::config_folder = utils::dll_path + "\\Drinol";

	if (!config::load())
	{
		std::cout << "Failed to load config, creating a new one from scratch." << std::endl;
		if (!config::create_new())
		{
			std::cout << "Failed to create new config." << std::endl;

			if (!config::load())
			{
				std::cout << "Failed to load new config." << std::endl;
			}
		}
	}

	// Initialize Minhook
	if (MH_Initialize() != MH_OK)
	{
		std::cout << "Failed to initialize minhook. Please restart the game and try again!" << std::endl;
	}

	// Initialize UE4 middleware hooks.
	middleware::init();

	if (gui::enabled) {
		// Initialize DX11 hook and imgui overlay.
		gui::init();
	}

	std::cout << "Drinol has loaded." << std::endl;

#if defined NDEBUG
	MessageBox(NULL, L"Drinol has successfully initialized!", L"Hello!", 0);
#endif
	}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	// ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);

		//Get folder dll is in. (So we can save ini and other files there instead of the games working dir.) UGLY CODE
		CHAR   DllPath[MAX_PATH];
		GetModuleFileNameA(hinstDLL, DllPath, _countof(DllPath));
		utils::dll_path = DllPath;
		utils::dll_path = utils::dll_path.substr(0, utils::dll_path.find_last_of("\\/"));

		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(drinol_init), nullptr, NULL, nullptr);
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}

	return TRUE;
}