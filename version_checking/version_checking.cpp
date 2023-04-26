#include "stdafx.h"

char mcc_exe_path[MAX_PATH];

std::string get_file_version_number(LPCSTR filename)
{
	DWORD version_handle = 0;
	DWORD version_size = GetFileVersionInfoSizeA(filename, &version_handle);
	UINT val_size = 0;
	LPBYTE buffer = NULL;
	std::string version_number;
	bool version_info_attained = false;

	if (version_size != NULL)
	{
		LPSTR version_data = new char[version_size];

		if (GetFileVersionInfoA(filename, version_handle, version_size, version_data))
		{
			if (VerQueryValue(version_data, L"\\", reinterpret_cast<void**>(&buffer), &val_size))
			{
				if (val_size)
				{
					VS_FIXEDFILEINFO* version_info = reinterpret_cast<VS_FIXEDFILEINFO*>(buffer);

					// some weird signature check
					if (version_info->dwSignature == 0xfeef04bd)
					{
						version_number = fmt::format("{}.{}.{}.{}", version_info->dwFileVersionMS >> 16 & 0xffff, version_info->dwFileVersionMS >> 0 & 0xffff, version_info->dwFileVersionLS >> 16 & 0xffff, version_info->dwFileVersionLS >> 0 & 0xffff);
						version_info_attained = true;
					}
				}
			}
		}
	}

	return version_info_attained ? version_number : "NULL";
}

std::string get_mcc_executable_version()
{
	// Get handle of MCC Executable

	GetModuleFileNameA(NULL, mcc_exe_path, sizeof mcc_exe_path);

	// Read the exes version info and return version
	return get_file_version_number(mcc_exe_path);
}

std::string get_game_dll_version(std::string filename)
{
	// Get path of MCC
	GetModuleFileNameA(NULL, mcc_exe_path, sizeof mcc_exe_path);

	// Get MCC root directory
	std::string dll_path = std::regex_replace(mcc_exe_path, std::regex("\\\\mcc.*"), "");

	dll_path = dll_path.append("\\" + filename + "\\" + filename + ".dll");

	//auto shit = SetCurrentDirectoryA(dll_path.replace("\\mcc\\binaries\\win64\\MCC-Win64-Shipping.exe", "").c_str());

	// Read the dlls version info and return version
	return get_file_version_number(dll_path.c_str());
}

//mcc_exe_path = 0x00007ffe30acd860 "D:\\Games\\SteamLibrary\\steamapps\\common\\Halo The Master Chief Collection\\mcc\\binaries\\win64\\MCC-Win64-Shipping.exe"

void version_checking::validate()
{
	std::string mcc_executable_version = get_mcc_executable_version();
	// Validate MCC EXE version
	if (mcc_executable_version != COMPATIBLE_DRINOL_VERSION)
	{
		spdlog::critical("Drinol does not support MCC version: '{}'", mcc_executable_version);
		spdlog::warn("This version of Drinol supports: '{}'", COMPATIBLE_DRINOL_VERSION);
		spdlog::warn(format(fg(fmt::terminal_color::bright_yellow) | fmt::emphasis::bold, "This may cause some potential problems/crashes."));
	}
	else
		spdlog::info(format(fg(fmt::terminal_color::bright_green) | fmt::emphasis::bold, "You're running a supported version of MCC: {}!", mcc_executable_version));
}

void version_checking::validate_game_dll(std::string filename)
{
	std::string dll_version = get_game_dll_version(filename);
	// Validate MCC EXE version
	if (dll_version != COMPATIBLE_DRINOL_VERSION)
	{
		spdlog::critical("Drinol does not support {} version: '{}'", filename, dll_version);
		spdlog::warn("This version of Drinol supports: '{}'", COMPATIBLE_DRINOL_VERSION);
		spdlog::warn(format(fg(fmt::terminal_color::bright_yellow) | fmt::emphasis::bold, "This may cause some potential problems/crashes."));
	}
	else
		spdlog::info(format(fg(fmt::terminal_color::bright_green) | fmt::emphasis::bold, "You're running a supported version of {} MCC: {}!", filename, dll_version));
}