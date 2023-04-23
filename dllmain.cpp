#include "stdafx.h"

void drinol_init()
{
	// Load data from the ini config.

	// Get config folder
	config::config_folder = utils::dll_path + "\\Drinol";

	//Check if config folder exists, if not, create one.
	if (!config::create_config_folder())
	{
		//spdlog::error("Failed to create the config folder.");
		MessageBox(NULL, L"Failed to create the Drinol folder!", L"Drinol Error!", 0);
	}

	if (!config::load_main_settings())
	{
		//puts("Failed to load main settings config file, creating a new one from scratch.");
		if (!config::create_new_main_settings())
		{
			//spdlog::error("Failed to create new main settings config file.");
		}
		else if (!config::load_main_settings())
		{
			//spdlog::error("Failed to load new main settings config file.");
			MessageBox(NULL, L"Failed to generate and load the main config file!", L"Drinol Error!", 0);
		}
	}

	if (!config::load_signatures())
	{
		//spdlog::error("Failed to load signatures config file, creating a new one from scratch.");

		std::string file_name = config::config_folder + "\\Signatures.ini";
		std::remove(file_name.c_str()); // delete file

		if (!config::create_new_signatures())
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
	if (!config::validate_sigs())
	{
		//spdlog::error("Could not validate existing signatures, generating new signatures file instead.");

		std::string file_name = config::config_folder + "\\Signatures.ini";
		std::remove(file_name.c_str()); // delete file

		if (!config::create_new_signatures())
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

	spdlog::info(format(fmt::fg(fmt::terminal_color::bright_yellow) | fmt::emphasis::bold, "Welcome to Drinol! | https://github.com/matty45/Drinol"));

	spdlog::info("Drinol is loading.");

	// Initialize Minhook
	if (MH_Initialize() != MH_OK)
	{
		MessageBox(NULL, L"Failed to initialize minhook. Please restart the game and try again!", L"Drinol Error!", 0);
	}

	// Initialize UE4 middleware hooks.
	middleware::hooks::init();

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

		utils::dll_module = hinstDLL;

		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(drinol_init), nullptr, NULL, nullptr);
		break;

	case DLL_PROCESS_DETACH:
		utils::detach();
		break;

	default:
		break;
	}

	return TRUE;
}