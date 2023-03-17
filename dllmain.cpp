#include <iostream>
#include <minhook/include/MinHook.h>

#include "utils.h"
#include "config/config.h"
#include "gui/gui.h"
#include "middleware/middleware.h"

//TODO: possibly make the console appear in the release build or have it inside the menu?

#include "spdlog/logger.h"

#include "console.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

void drinol_init()
{
	// Load data from the ini config.

	// Get config folder
	config::config_folder = utils::dll_path + "\\Drinol";

	//Check if config folder exists, if not, create one.
	if (!config::create_config_folder())
	{
		//puts("Failed to create the config folder.");
		MessageBox(NULL, L"Failed to create the Drinol folder!", L"Drinol Error!", 0);
	}

	if (!config::load_main_settings())
	{
		//puts("Failed to load main settings config file, creating a new one from scratch.");
		if (!config::create_new_main_settings())
		{
			//puts("Failed to create new main settings config file.");
		}
		else if (!config::load_main_settings())
		{
			//puts("Failed to load new main settings config file.");
			MessageBox(NULL, L"Failed to generate and load the main config file!", L"Drinol Error!", 0);
		}
	}

	if (!config::load_signatures())
	{
		//puts("Failed to load signatures config file, creating a new one from scratch.");
		if (!config::create_new_signatures())
		{
			//puts("Failed to create new signatures config file.");
		}
		else if (!config::load_signatures())
		{
			//puts("Failed to load new signatures config file.");
			MessageBox(NULL, L"Failed to generate and load the signatures config file!", L"Drinol Error!", 0);
		}
	}

	if (console::log_to_file)
	{
		try
		{
			std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt("Drinol", "Drinol/logs/log.txt");
			logger->flush_on(spdlog::level::info);
			spdlog::set_default_logger(logger);
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::string error = "Could not log to a file: ";
			error += ex.what();

			MessageBoxA(NULL, error.c_str(), "Drinol Error!", 0);
		}
	}

	if (console::enabled)
	{
		// Initialize debug console.
		console::init();
	}

	spdlog::info("Drinol is loading.");

	// Initialize Minhook
	if (MH_Initialize() != MH_OK)
	{
		MessageBox(NULL, L"Failed to initialize minhook. Please restart the game and try again!", L"Drinol Error!", 0);
	}

	// Initialize UE4 middleware hooks.
	middleware::init();

	if (gui::enabled) {
		// Initialize DX11 hook and imgui overlay.
		gui::init();
	}

	spdlog::info("Drinol has loaded.");
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