#include "stdafx.h"
#include "utils.h"

#include "config/config.h"
#include "games/groundhog/groundhog.h"
#include "games/halo1/halo1.h"
#include "games/halo2/halo2.h"
#include "games/halo3/halo3.h"
#include "games/halo3/halo3_hooks.h"
#include "games/halo3odst/halo3odst.h"
#include "games/halo4/halo4.h"
#include "games/haloreach/haloreach.h"

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
		version_checking::validate_game_dll("groundhog");
		groundhog::game::init();
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
	case games::e_games::groundhog:
		groundhog::game::deinit();
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
	std::string logMessage;

	switch (games::current_game_number) {
	case games::e_games::halo1:
		if (config::games::halo_1::save())
		{
			logMessage = "Saved settings for Halo 1!";
		}
		break;
	case games::e_games::halo2:
		if (config::games::halo_2::save())
		{
			logMessage = "Saved settings for Halo 2!";
		}
		break;
	case games::e_games::halo3:
		if (config::games::halo_3::save())
		{
			logMessage = "Saved settings for Halo 3!";
		}
		break;
	case games::e_games::halo4:
		if (config::games::halo_4::save())
		{
			logMessage = "Saved settings for Halo 4!";
		}
		break;
	case games::e_games::groundhog:
		if (config::games::groundhog::save())
		{
			logMessage = "Saved settings for Halo 2 Anniversary Multiplayer!";
		}
		break;
	default:
		assert(games::current_game_number <= 6);
	}

	if (!logMessage.empty())
	{
		spdlog::info(logMessage);
	}
}

// Loads the currently running games settings.
void utils::load_running_game_settings()
{
	std::string logMessage;

	switch (games::current_game_number) {
	case games::e_games::halo1:
		if (config::games::halo_1::load())
		{
			logMessage = "Loaded settings for Halo 1!";
		}
		break;
	case games::e_games::halo2:
		if (config::games::halo_2::load())
		{
			logMessage = "Loaded settings for Halo 2!";
		}
		break;
	case games::e_games::halo3:
		if (config::games::halo_3::load())
		{
			logMessage = "Loaded settings for Halo 3!";
		}
		break;
	case games::e_games::halo4:
		if (config::games::halo_4::load())
		{
			logMessage = "Loaded settings for Halo 4!";
		}
		break;
	case games::e_games::groundhog:
		if (config::games::groundhog::load())
		{
			logMessage = "Loaded settings for Halo 2 Anniversary Multiplayer!";
		}
		break;
	default:
		assert(games::current_game_number <= 6);
	}

	if (!logMessage.empty())
	{
		spdlog::info(logMessage);
	}
}

void utils::reset_running_game_settings()
{
	std::string game_name;
	bool success = false;

	switch (games::current_game_number) {
	case games::e_games::halo1:
		game_name = "Halo 1";
		success = config::games::halo_1::create() && config::games::halo_1::load();
		break;
	case games::e_games::halo2:
		game_name = "Halo 2";
		success = config::games::halo_2::create() && config::games::halo_2::load();
		break;
	case games::e_games::halo3:
		game_name = "Halo 3";
		success = config::games::halo_3::create() && config::games::halo_3::load();
		break;
	case games::e_games::halo4:
		game_name = "Halo 4";
		success = config::games::halo_4::create() && config::games::halo_4::load();
		break;
	case games::e_games::groundhog:
		game_name = "Halo 2 Anniversary Multiplayer";
		success = config::games::groundhog::create() && config::games::groundhog::load();
		break;
	default:
		assert(games::current_game_number <= 6);
	}

	if (success) {
		spdlog::info("Reset settings for {}", game_name);
	}
	else {
		spdlog::error("Failed to create/load fresh settings for {}!", game_name);
	}
}

//https://github.com/citizenfx/fivem/blob/f3bb0460562b1eb1a7f9652ffcf73ad7282fd45e/code/client/shared/Hooking.h#L91-L113
char* utils::memory::get_tls_pointer(LPCWSTR module_name, int TLSFunctionIndex)
{
	const uint32_t* tlsIndex = nullptr;

	while (!tlsIndex)
	{
		// ah, the irony in using TLS to get TLS
		tlsIndex = ([module_name]()
			{
				char* base = reinterpret_cast<char*>(GetModuleHandleW(module_name));
				const PIMAGE_DOS_HEADER moduleBase = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
				const PIMAGE_NT_HEADERS ntBase = reinterpret_cast<PIMAGE_NT_HEADERS>(base + moduleBase->e_lfanew);
				const PIMAGE_TLS_DIRECTORY tlsBase = reinterpret_cast<PIMAGE_TLS_DIRECTORY>(base + ntBase->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
				return reinterpret_cast<uint32_t*>(tlsBase->AddressOfIndex);
			})();
	}

#if defined(_M_IX86)
	LPVOID* tlsBase = (LPVOID*)__readfsdword(0x2C);
#elif defined(_M_AMD64)
	LPVOID* tlsBase = reinterpret_cast<LPVOID*>(__readgsqword(0x58));
#endif

	if (tlsBase && tlsIndex != nullptr)
	{
		if (!TLSFunctionIndex)
			return static_cast<char*>(tlsBase[*tlsIndex]);
		else
			return static_cast<char*>(tlsBase[*tlsIndex]) + TLSFunctionIndex; //return static_cast<char*>(tlsBase[*tlsIndex]);
	}
	else
		spdlog::error("utils::get_tls_pointer: NULL POINTER!!!!");
	return nullptr;
}

void utils::detach()
{
	handle_game_deinit();
	middleware::hooks::deinit();
	kiero::shutdown();
	g_Console->Destroy();
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
		ShellExecute(nullptr, nullptr, L"https://github.com/matty45/Drinol", nullptr, nullptr, SW_SHOW);
	case TDN_TIMER:
		DWORD* pTimeout = reinterpret_cast<DWORD*>(dwUserData);  // = tc.lpCallbackData
		const DWORD timeElapsed = static_cast<DWORD>(wParam);
		if (*pTimeout && timeElapsed >= *pTimeout)
		{
			*pTimeout = 0; // Make sure we don't send the button message multiple times.
			SendMessageA(hwndWindow, TDM_SET_ELEMENT_TEXT, TDE_FOOTER, reinterpret_cast<LPARAM>(L" <A>Be sure to check out our github repo!</A>"));
			SendMessageA(hwndWindow, TDM_ENABLE_BUTTON, IDYES, 1);
		}
	}

	return S_OK;
}

void utils::cheat_nag()
{
	HKEY hKey;

	// Check if key exists, if not, create it.
	RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Drinol", NULL, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hKey, nullptr);

	const LPBYTE value_data = nullptr;
	DWORD value_size = 0;

	// Check if value exists
	if (!RegQueryValueExA(hKey, "nag_message_closed", nullptr, nullptr, value_data, &value_size))
		return;

	//If value does not exist, display nag message.

	// Get window for the message box so we can freeze it.
	HWND handle = nullptr;
	while (handle == nullptr)
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
	config.hInstance = nullptr;
	config.pszMainIcon = TD_WARNING_ICON;
	config.pszWindowTitle = L"PLEASE READ!";
	config.pszMainInstruction = L"This tool is not meant for gaining an unfair advantage in multiplayer.";
	config.pszContent = L"Do you agree not to use this for cheating?";
	config.pszFooterIcon = TD_INFORMATION_ICON;
	config.pszFooter = L"Agree button will be enabled in 10 seconds.";
	config.dwFlags = TDF_SIZE_TO_CONTENT | TDF_USE_COMMAND_LINKS | TDF_CALLBACK_TIMER | TDF_ENABLE_HYPERLINKS;
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	DWORD timeout = 10000;  // milliseconds
	config.lpCallbackData = reinterpret_cast<LONG_PTR>(&timeout);

	config.pfCallback = task_dialog_callback;

	int nButtonPressed = 0;
	TaskDialogIndirect(&config, &nButtonPressed, nullptr, nullptr);

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
	const DWORD value = 1;
	LONG lResult = RegSetValueEx(hKey, L"nag_message_closed", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));

	// Clear our window handle
	handle = nullptr;

	RegCloseKey(hKey);
}

void utils::memory::patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

//void utils::memory::nop(BYTE* dst, BYTE* src, unsigned int size)
//{
//	utils::memory::patch()
//}

void utils::memory::store_memory_bytes(BYTE* stored_bytes, void* src_address, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(src_address, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	memcpy(stored_bytes, src_address, size);

	VirtualProtect(src_address, size, oldprotect, &oldprotect);
}

//https://cpp.hotexamples.com/examples/-/-/GetKeyNameTextA/cpp-getkeynametexta-function-examples.html#0x2c44d0247cd42dfffc97108642151a9d9a982ec31f298c4329e9162e1fdd9647-39,,56,
std::string utils::keys::get_key_name(BYTE key)
{
	DWORD sc = MapVirtualKeyA(key, 0);
	// check key for ascii
	BYTE buf[256] = {};
	WORD temp;
	DWORD asc = (key <= 32);
	if (!asc && (key != VK_DIVIDE)) asc = ToAscii(key, sc, buf, &temp, 1);
	// set bits
	sc <<= 16;
	sc |= 0x1 << 25;  // <- don't care
	if (!asc) sc |= 0x1 << 24; // <- extended bit
	// convert to ansi string
	if (GetKeyNameTextA(sc, reinterpret_cast<char*>(buf), sizeof(buf)))
		return reinterpret_cast<char*>(buf);
	else return "";
}

bool utils::keys::is_key_pressed(int keyCode) {
	return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
}

int utils::keys::capture_next_key()
{
	for (int keyCode = 0; keyCode < 256; ++keyCode) {
		if (is_key_pressed(keyCode)) {
			return keyCode;
		}
	}
	return 0;
}

//0x00007ff8
#if defined _DEBUG

void utils::test_func(int test_int)
{
	halo3::hooks::game_tick_test = true;

	//for (int i = 0; i < 16; i++) {
	//	halo3::engine::s_thread_local_storage* tls = halo3::game::get_tls();

	//	halo3::engine::player_datum* player_datum = &tls->player_data->players[i];

	//	if (player_datum->unit_index)
	//	{
	//		spdlog::info("Player Datum : 0x{:X}", reinterpret_cast<uintptr_t>(player_datum));
	//	}
	//}

	//for (int i = 0; i < 30; i++) {
	//	game_globals->game_options.game_mode = 1;
	//	halo3::game::skulls::skull_primary_enable(i, true);
	//	halo3::game::skulls::skull_secondary_enable(i, true);
	//}

	//spdlog::info("Game Allegiance Globals: 0x{:X}", reinterpret_cast<uintptr_t>(halo3::offsets::globals::game_allegiance_globals));
}

uintptr_t utils::memory::get_offset(uintptr_t address)
{
	const uintptr_t base = Memcury::PE::GetModuleBase();

	uintptr_t offset = address;
	offset = offset - base;

	return offset;
}

void utils::memory::print_game_tls_pointer(bool suspend)
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
	case games::e_games::groundhog:
		spdlog::debug("Halo 2 Anniversary Multiplayer TLS Pointer : 0x{:X}", reinterpret_cast<uintptr_t>(get_tls_pointer(L"groundhog.dll")));
		break;
	default:
		assert(games::current_game_number <= 6);
	}

	if (suspend)
	{
		typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);

		const NtSuspendProcess pfnNtSuspendProcess = reinterpret_cast<NtSuspendProcess>(GetProcAddress(
			GetModuleHandleW(L"ntdll"), "NtSuspendProcess"));

		pfnNtSuspendProcess(GetCurrentProcess());
		CloseHandle(GetCurrentProcess());
	}
}

void utils::memory::list_game_base_addresses()
{
	Memcury::Scanner::SetTargetModule("halo1.dll");

	spdlog::debug("Halo 1 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo2.dll");

	spdlog::debug("Halo 2 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo3.dll");

	spdlog::debug("Halo 3 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo4.dll");

	spdlog::debug("Halo 4 base : 0x{:X}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("groundhog.dll");

	spdlog::debug("Halo 2 Anniversary Multiplayer base : 0x{:X}", Memcury::PE::GetModuleBase());
}

void utils::memory::backtrace(const char* func) {
	const int trace_count = 15;
	void* trace_back[trace_count];
	DWORD hash;
	RtlCaptureStackBackTrace(1, trace_count, trace_back, &hash);
	printf("%s callstack: ", func);
	for (int i = 0; i < trace_count; i++) {
		if (i == trace_count - 1) {
			printf("%llu\n", reinterpret_cast<uintptr_t>(trace_back[i]));
		}
		else {
			printf("%llu:", reinterpret_cast<uintptr_t>(trace_back[i]));
		}
	}
}

#endif