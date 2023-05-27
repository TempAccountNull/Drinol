#include "stdafx.h"

#include "utils.h"
#include "version.h"
#include "config/config.h"
#include "gui/gui.h"
#include "gui/menu/menu.h"

[[noreturn]] void drinol_init(LPVOID hInstance)
{
	utils::cheat_nag();

	// Load data from the ini config.

	// Get config folder
	config::main::config_folder = utils::dll_path + "\\Drinol";

	//Check if config folder exists, if not, create one.
	if (!config::main::create_config_folder())
	{
		//spdlog::error("Failed to create the config folder.");
		MessageBox(nullptr, L"Failed to create the Drinol folder!", L"Drinol Error!", 0);
	}

	if (!config::main::load())
	{
		//puts("Failed to load main settings config file, creating a new one from scratch.");
		if (!config::main::create())
		{
			//spdlog::error("Failed to create new main settings config file.");
		}
		else if (!config::main::load())
		{
			//spdlog::error("Failed to load new main settings config file.");
			MessageBox(nullptr, L"Failed to generate and load the main config file!", L"Drinol Error!", 0);
		}
	}

	// Cant execute this any earlier or else things will break :(
	if (console::enabled)
	{
		// Initialize debug console.
		g_Console = std::make_unique<console>();
		g_Console->Initialize();
	}

	logging::init();

	spdlog::info(format(fg(fmt::terminal_color::bright_cyan) | fmt::emphasis::bold, "Welcome to Drinol! | https://github.com/matty45/Drinol | Branch: {}", CURRENT_BRANCH));

	// Print commit details
	spdlog::info("Commit: {}", COMMIT_HASH);
	spdlog::info("Commit Date: {}", COMMIT_DATE);
	spdlog::info("Commit Subject: {}", COMMIT_SUBJECT);
	spdlog::info("Commit Author: {}", COMMIT_AUTHOR);
	if constexpr (sizeof(OLDEST_CHANGED_FILE_BEFORE_COMMIT) > 1)
		spdlog::info("Mod");

	spdlog::info("Drinol is loading.");

	spdlog::debug("Drinol files directory: {}", config::main::config_folder);

	version_checking::validate();

#ifndef USE_BUILTIN_SIGS // Only read signatures built into drinol instead of the ini.

	if (!config::sigs::load())
	{
		spdlog::error("Failed to load signatures config file, creating a new one from scratch.");

		if (!config::sigs::create())
		{
			spdlog::error("Failed to create new signatures config file.");
		}
		else if (!config::sigs::load())
		{
			//spdlog::error("Failed to load new signatures config file.");
			MessageBox(NULL, L"Failed to generate and load the signatures config file!", L"Drinol Error!", 0);
		}
	}

	// Check if signatures.ini is valid.
	if (!config::sigs::validate())
	{
		MessageBox(NULL, L"The signatures.ini file failed to validate!\nPlease check the logs to find what part of the signatures file is invalid.\nYou can either fix this manually or just delete the file and Drinol will generate a new one the next time it starts up..", L"Drinol Error!", 0);
	}

#endif

	// Initialize Minhook
	if (MH_Initialize() != MH_OK)
	{
		MessageBox(nullptr, L"Failed to initialize minhook. Please restart the game and try again!", L"Drinol Error!", 0);
	}

	// Initialize UE4 middleware hooks.
	middleware::hooks::init();

	if (gui::enabled)
	{
		// Initialize DX11 hook and imgui overlay.
		g_Overlay = std::make_unique<gui>(); //	Global reference to overlay variables (show window)
		g_Overlay->init(); //	Initialize GUI
		g_Running = TRUE; //	gRunning = true , as gui is the last thing to be initialized.
	}

	spdlog::info("Drinol has loaded.");

	//	Executing Main Thread
	while (g_Running)
	{
		if (!menu::settings_window_open)
			// This will stop people from accidentally pressing hot-keys when they are trying to change them.
		{
			//	Exit Key
			if (GetAsyncKeyState(utils::detach_keybind) & 1)
			{
				g_Killswitch = TRUE;
				g_Running = FALSE;
			}

			//	Show Hide Menu
			if (gui::enabled)
			{
				if (GetAsyncKeyState(gui::toggle_ui_keybind) & 1)
					g_Overlay->bShowWindow ^= 1;
			}

			// Toggle wireframe
			if (GetAsyncKeyState(gui::toggle_wireframe_keybind) & 1)
				gui::render_wireframe ^= 1;
		}
	}

	//	Exit
	utils::detach();
	FreeLibraryAndExitThread(static_cast<HMODULE>(hInstance), EXIT_SUCCESS);
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

		utils::dll_module = hinstDLL;

		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(drinol_init), hinstDLL, NULL, nullptr);
		break;

	case DLL_PROCESS_DETACH:
		utils::detach();
		FreeLibraryAndExitThread(hinstDLL, 0);

	default:
		break;
	}

	return TRUE;
}
