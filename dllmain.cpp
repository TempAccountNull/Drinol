#include "stdafx.h"

void drinol_init(LPVOID hInstance)
{
	utils::cheat_nag();

	// Load data from the ini config.

	// Get config folder
	config::main::config_folder = utils::dll_path + "\\Drinol";

	//Check if config folder exists, if not, create one.
	if (!config::main::create_config_folder())
	{
		//spdlog::error("Failed to create the config folder.");
		MessageBox(NULL, L"Failed to create the Drinol folder!", L"Drinol Error!", 0);
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
			MessageBox(NULL, L"Failed to generate and load the main config file!", L"Drinol Error!", 0);
		}
	}

	if (!config::sigs::load())
	{
		//spdlog::error("Failed to load signatures config file, creating a new one from scratch.");

		std::string file_name = config::main::config_folder + "\\Signatures.ini";
		std::remove(file_name.c_str()); // delete file

		if (!config::sigs::create())
		{
			//spdlog::error("Failed to create new signatures config file.");
		}
		//else if (!config::load_signatures())
		//{
		//	//spdlog::error("Failed to load new signatures config file.");
		//	MessageBox(NULL, L"Failed to generate and load the signatures config file!", L"Drinol Error!", 0);
		//}
	}

	// Check if loaded signatures are valid. Warning, nasty bugs may occur if the sig lists have empty entries. TODO: Prevent bugs?
	if (!config::sigs::validate())
	{
		//spdlog::error("Could not validate existing signatures, generating new signatures file instead.");

		std::string file_name = config::main::config_folder + "\\Signatures.ini";
		std::remove(file_name.c_str()); // delete file

		if (!config::sigs::create())
		{
			//spdlog::error("Failed to create new signatures config file.");
			MessageBox(NULL, L"Could not validate existing signatures, tried to generate a new signatures file to no avail......", L"Drinol Error!", 0);
		}
	}

	if (console::enabled)
	{
		// Initialize debug console.
		console::init();
	}

	logging::init();

	spdlog::info(format(fmt::fg(fmt::terminal_color::bright_cyan) | fmt::emphasis::bold, "Welcome to Drinol! | https://github.com/matty45/Drinol"));

	spdlog::info("Drinol is loading.");

	spdlog::debug("Drinol files directory: {}", config::main::config_folder);

	version_checking::validate();

	// Initialize Minhook
	if (MH_Initialize() != MH_OK)
	{
		MessageBox(NULL, L"Failed to initialize minhook. Please restart the game and try again!", L"Drinol Error!", 0);
	}

	// Initialize UE4 middleware hooks.
	middleware::hooks::init();
	
	if (gui::enabled) 
	{
		// Initialize DX11 hook and imgui overlay.
		g_Overlay = std::make_unique<gui>();		//	Global reference to overlay variables (show window)
		g_Overlay->init();							//	Initialize GUI
		g_Running = TRUE;							//	gRunning = true , as gui is the last thing to be initialized.
	}

	spdlog::info("Drinol has loaded.");
	
	//	Executing Main Thread
	while (g_Running)
	{
		//	Exit Key
		if (GetAsyncKeyState(VK_END) & 1) 
		{
			g_Killswitch = TRUE;
			g_Running = FALSE;
		}

		//	Show Hide Menu
		//if (GetAsyncKeyState(gui::toggle_ui_keybind) & 1)  0x0D not sure what key this is
		if (GetAsyncKeyState(VK_INSERT) & 1)
			g_Overlay->bShowWindow ^= 1;
	}

	//	Exit 
	utils::detach();
	FreeLibraryAndExitThread((HMODULE)hInstance, EXIT_SUCCESS);
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
		break;

	default:
		break;
	}

	return TRUE;
}