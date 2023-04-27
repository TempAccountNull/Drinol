#include "stdafx.h"

void utils::handle_game_init(int game_number)
{
	switch (game_number) {
	case games::e_games::halo1:
		version_checking::validate_game_dll("halo1");
		halo1::game::init();
		break;
	case games::e_games::halo2:
		version_checking::validate_game_dll("halo2");
		halo2::game::init();
		break;
	case games::e_games::halo3:
		version_checking::validate_game_dll("halo3");
		halo3::game::init();
		break;
	case games::e_games::halo4:
		version_checking::validate_game_dll("halo4");
		halo4::game::init();
		break;
	case games::e_games::groundhog:
		spdlog::error("Halo 2 Anniversary Multiplayer is not supported at the moment!");
		break;
	case games::e_games::halo3odst:
		version_checking::validate_game_dll("halo3odst");
		halo3odst::game::init();
		break;
	case games::e_games::haloreach:
		version_checking::validate_game_dll("haloreach");
		haloreach::game::init();
		break;
	default:
		assert(game_number <= 6);
	}

	games::current_game_number = game_number;
}

void utils::handle_game_deinit()
{
	switch (games::current_game_number) {
	case games::e_games::halo1:
		halo1::game::deinit();
		break;
	case games::e_games::halo2:
		halo2::game::deinit();
		break;
	case games::e_games::halo3:
		halo3::game::deinit();
		break;
	case games::e_games::halo4:
		halo4::game::deinit();
		break;
	case games::e_games::haloreach:
		haloreach::game::deinit();
		break;
	default:
		assert(games::current_game_number <= 6);
	}
}

// Saves the currently running games settings.
void utils::save_running_game_settings()
{
	switch (games::current_game_number) {
	case games::e_games::halo1:
		if (config::games::halo_1::save())
		{
			spdlog::info("Saved settings for Halo 1!");
		}
		break;
	case games::e_games::halo2:
		if (config::games::halo_2::save())
		{
			spdlog::info("Saved settings for Halo 2!");
		}
		break;
	case games::e_games::halo3:
		if (config::games::halo_3::save())
		{
			spdlog::info("Saved settings for Halo 3!");
		}
		break;
	case games::e_games::halo4:
		if (config::games::halo_4::save())
		{
			spdlog::info("Saved settings for Halo 4!");
		}
		break;
	default:
		assert(games::current_game_number <= 6);
	}
}

// Loads the currently running games settings.
void utils::load_running_game_settings()
{
	switch (games::current_game_number) {
	case games::e_games::halo1:
		if (config::games::halo_1::load())
		{
			spdlog::info("Loaded settings for Halo 1!");
		}
		break;
	case games::e_games::halo2:
		if (config::games::halo_2::load())
		{
			spdlog::info("Loaded settings for Halo 2!");
		}
		break;
	case games::e_games::halo3:
		if (config::games::halo_3::load())
		{
			spdlog::info("Loaded settings for Halo 3!");
		}
		break;
	case games::e_games::halo4:
		if (config::games::halo_4::load())
		{
			spdlog::info("Loaded settings for Halo 4!");
		}
		break;
	default:
		assert(games::current_game_number <= 6);
	}
}

void utils::reset_running_game_settings()
{
	switch (games::current_game_number) {
	case games::e_games::halo1:
		if (!config::games::halo_1::create())
		{
			spdlog::error("Failed to create fresh settings for Halo 1!");
			break;
		}
		if (!config::games::halo_1::load())
		{
			spdlog::error("Failed to load fresh settings for Halo 1!");
			break;
		}

		spdlog::info("Reset settings for Halo 1");
		break;
	case games::e_games::halo2:
		if (!config::games::halo_2::create())
		{
			spdlog::error("Failed to create fresh settings for Halo 2!");
			break;
		}
		if (!config::games::halo_2::load())
		{
			spdlog::error("Failed to load fresh settings for Halo 2!");
			break;
		}

		spdlog::info("Reset settings for Halo 2");
		break;
	case games::e_games::halo3:
		if (!config::games::halo_3::create())
		{
			spdlog::error("Failed to create fresh settings for Halo 3!");
			break;
		}
		if (!config::games::halo_3::load())
		{
			spdlog::error("Failed to load fresh settings for Halo 3!");
			break;
		}

		spdlog::info("Reset settings for Halo 3");
		break;
	case games::e_games::halo4:
		if (!config::games::halo_4::create())
		{
			spdlog::error("Failed to create fresh settings for Halo 4!");
			break;
		}
		if (!config::games::halo_4::load())
		{
			spdlog::error("Failed to load fresh settings for Halo 4!");
			break;
		}

		spdlog::info("Reset settings for Halo 4");
		break;
	default:
		assert(games::current_game_number <= 6);
	}
}

//https://github.com/citizenfx/fivem/blob/f3bb0460562b1eb1a7f9652ffcf73ad7282fd45e/code/client/shared/Hooking.h#L91-L113
char* utils::get_tls_pointer(LPCWSTR module_name, int TLSFunctionIndex)
{
	// ah, the irony in using TLS to get TLS
	static uint32_t* tlsIndex = ([module_name]()
		{
			char* base = reinterpret_cast<char*>(GetModuleHandleW(module_name));
			PIMAGE_DOS_HEADER moduleBase = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
			PIMAGE_NT_HEADERS ntBase = reinterpret_cast<PIMAGE_NT_HEADERS>(base + moduleBase->e_lfanew);
			PIMAGE_TLS_DIRECTORY tlsBase = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(base + ntBase->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
			return reinterpret_cast<uint32_t*>(tlsBase->AddressOfIndex);
		})();

#if defined(_M_IX86)
		LPVOID* tlsBase = (LPVOID*)__readfsdword(0x2C);
#elif defined(_M_AMD64)
		LPVOID* tlsBase = reinterpret_cast<LPVOID*>(__readgsqword(0x58));
#endif
		if (!TLSFunctionIndex)
		{
			return static_cast<char*>(tlsBase[*tlsIndex]);
		}
		else
		{
			return static_cast<char*>(tlsBase[*tlsIndex]) + TLSFunctionIndex;
		}
}

//0x00007ff8
#if defined _DEBUG

void utils::test_func(int test_int)
{
	haloreach::hooks::infinite_ammo = true;
}

uintptr_t utils::get_offset(uintptr_t address)
{
	uintptr_t base = Memcury::PE::GetModuleBase();

	uintptr_t offset = address;
	offset = offset - base;

	return offset;
}

void utils::print_game_tls_pointer()
{
	switch (games::current_game_number) {
	case games::e_games::halo1:
		spdlog::debug("Halo 1 TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"halo1.dll")));
		break;
	case games::e_games::halo2:
		spdlog::debug("Halo 2 TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"halo2.dll")));
		break;
	case games::e_games::halo3:
		spdlog::debug("Halo 3 TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"halo3.dll")));
		break;
	case games::e_games::halo3odst:
		spdlog::debug("Halo 3 ODST TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"halo3odst.dll")));
		break;
	case games::e_games::haloreach:
		spdlog::debug("Halo Reach TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"haloreach.dll")));
		break;
	case games::e_games::halo4:
		spdlog::debug("Halo 4 TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"halo4.dll")));
		break;
	default:
		assert(games::current_game_number <= 6);
	}
}

void utils::list_game_base_addresses()
{
	Memcury::Scanner::SetTargetModule("halo1.dll");

	spdlog::debug("Halo 1 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo2.dll");

	spdlog::debug("Halo 2 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo3.dll");

	spdlog::debug("Halo 3 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo4.dll");

	spdlog::debug("Halo 4 base : 0x{:X}", Memcury::PE::GetModuleBase());
}

void utils::backtrace(const char* func) {
	const int trace_count = 15;
	void* trace_back[trace_count];
	DWORD hash;
	RtlCaptureStackBackTrace(1, trace_count, trace_back, &hash);
	printf("%s callstack: ", func);
	for (int i = 0; i < trace_count; i++) {
		if (i == trace_count - 1) {
			printf("%p\n", (uintptr_t)trace_back[i]);
		}
		else {
			printf("%p:", (uintptr_t)trace_back[i]);
		}
	}
}

#endif

void utils::detach()
{
	handle_game_deinit();
	middleware::hooks::deinit();
	kiero::shutdown();
	console::deinit();
	//FreeLibraryAndExitThread(dll_module, 0);
}

HRESULT CALLBACK task_dialog_callback(HWND hwndWindow, UINT uNotification, WPARAM wParam, LPARAM lParam, LONG_PTR dwUserData)
{
	// https://stackoverflow.com/a/51989826

	switch (uNotification)
	{
	case TDN_DIALOG_CONSTRUCTED:
		SendMessageA(hwndWindow, TDM_ENABLE_BUTTON, IDYES, 0);
		break;
	case TDN_HYPERLINK_CLICKED:
		ShellExecute(0, 0, L"https://github.com/matty45/Drinol", 0, 0, SW_SHOW);
	case TDN_TIMER:
		DWORD* pTimeout = reinterpret_cast<DWORD*>(dwUserData);  // = tc.lpCallbackData
		DWORD timeElapsed = static_cast<DWORD>(wParam);
		if (*pTimeout && timeElapsed >= *pTimeout)
		{
			*pTimeout = 0; // Make sure we don't send the button message multiple times.
			SendMessageA(hwndWindow, TDM_SET_ELEMENT_TEXT, static_cast<WPARAM>(TDE_FOOTER), reinterpret_cast<LPARAM>(L" <A>Be sure to check out our github repo!</A>"));
			SendMessageA(hwndWindow, TDM_ENABLE_BUTTON, IDYES, 1);
		}
	}

	return S_OK;
}

void utils::cheat_nag()
{
	HKEY hKey;

	// Check if key exists, if not, create it.
	RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Drinol", NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

	LPBYTE value_data = nullptr;
	DWORD value_size = 0;

	// Check if value exists
	if (!RegQueryValueExA(hKey, "nag_message_closed", NULL, NULL, value_data, &value_size))
		return;

	//If value does not exist, display nag message.

	// Get window for the message box so we can freeze it.
	HWND handle = nullptr;
	while (handle == NULL)
	{
		handle = FindWindowA("UnrealWindow", "Halo: The Master Chief Collection  ");
	}

	// Display messsage.

	const TASKDIALOG_BUTTON buttons[] = {
		{ IDYES, L"Agree\nYou will not get ANY support if you ask for help regarding this subject." },
		{IDNO,L"Disagree"}
	};

	TASKDIALOGCONFIG config = { 0 };
	config.cbSize = sizeof(config);
	config.hwndParent = handle;
	config.hInstance = NULL;
	config.pszMainIcon = TD_WARNING_ICON;
	config.pszWindowTitle = L"PLEASE READ!";
	config.pszMainInstruction = L"This tool is not meant for gaining an unfair advantage in multiplayer.";
	config.pszContent = L"Do you agree to not use this tool for cheating purposes?";
	config.pszFooterIcon = TD_INFORMATION_ICON;
	config.pszFooter = L"Agree button will be enabled in 10 seconds.";
	config.dwFlags = TDF_SIZE_TO_CONTENT | TDF_USE_COMMAND_LINKS | TDF_CALLBACK_TIMER | TDF_ENABLE_HYPERLINKS;
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	DWORD timeout = 10000;  // milliseconds
	config.lpCallbackData = reinterpret_cast<LONG_PTR>(&timeout);

	config.pfCallback = task_dialog_callback;

	int nButtonPressed = 0;
	TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);

	switch (nButtonPressed)
	{
	case IDYES:
		break; // the user pressed button 0 (change password).
	case IDNO:
		SendMessageA(handle, WM_CLOSE, NULL, NULL);
		return;
	default:
		break; // should never happen
	}

	//// Destroy our buttons
	//if (buttons != nullptr) {
	//	for (auto button : buttons) delete[] button.pszButtonText;
	//	delete[] buttons;
	//}

	// Create a value so that the message box will never appear again!
	DWORD value = 1;
	LONG lResult = RegSetValueEx(hKey, L"nag_message_closed", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

	// Clear our window handle
	handle = NULL;

	RegCloseKey(hKey);
}