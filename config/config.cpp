// This is used for the management of config files, etc
#include "config.h"

#include "console.h"
#include "framework.h"
#include "games/halo1/halo1_offsets.h"
#include "games/halo2/halo2_offsets.h"
#include "games/halo3/halo3_offsets.h"
#include "games/halo3odst/halo3odst_offsets.h"
#include "games/haloreach/haloreach_offsets.h"
#include "gui/gui.h"
#include "gui/menu/menu.h"
#include "middleware/middleware.h"
#include "mINI/src/mini/ini.h"
#include <spdlog/spdlog.h>

bool config::load_main_settings()
{
	const mINI::INIFile file(config_folder + "\\MainSettings.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	std::istringstream(ini.get("UI").get("hookdx11")) >> std::boolalpha >> gui::enabled;

	gui::ui_ini_path = ini.get("UI").get("imguiinidir");

	std::istringstream(ini.get("console").get("consolewindow")) >> std::boolalpha >> console::enabled;

	std::istringstream(ini.get("console").get("logtofile")) >> std::boolalpha >> console::log_to_file;

	std::istringstream(ini.get("console").get("imguiconsole")) >> std::boolalpha >> menu::console_enabled;

	//std::string level = ini.get("Console").get("loglevel");

	//TODO: Get rid of this ugly code >:( --- Does not work anyways, idk why
	//if (level == "debug")
	//{
	//	spdlog::set_level(spdlog::level::debug);
	//}
	//else if (level == "info")
	//{
	//	spdlog::set_level(spdlog::level::info);
	//}
	//else if (level == "warn")
	//{
	//	spdlog::set_level(spdlog::level::warn);
	//}
	//else if (level == "trace")
	//{
	//	spdlog::set_level(spdlog::level::trace);
	//}
	//else if (level == "error")
	//{
	//	spdlog::set_level(spdlog::level::err);
	//}
	//else if (level == "critical")
	//{
	//	spdlog::set_level(spdlog::level::critical);
	//}
	//else if (level == "off")
	//{
	//	spdlog::set_level(spdlog::level::off);
	//}

	return true;
}

bool config::create_config_folder()
{
	// Create a directory to store all the config files (keeps things tidy :p)
	// from https://stackoverflow.com/a/9235708
	if (CreateDirectoryA(config_folder.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		//puts("Created a new directory to store the config files, or it already exists!");
	}
	else
	{
		// Failed to create directory
		return false;
	}
	return true;
}

bool config::create_new_main_settings()
{
	const mINI::INIFile file(config_folder + "\\MainSettings.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["UI"]["hookdx11"] = "true";
	ini["UI"]["imguiinidir"] = config_folder + "\\UI.ini";

	ini["Console"]["consolewindow"] = "true";
	ini["Console"]["imguiconsole"] = "false";
	ini["Console"]["logtofile"] = "false";

	//ini["Console"]["loglevel"] = "trace";

	//ini["Middleware"];

	//ini["Halo1A"];

	//ini["Halo2A"];

	//ini["Halo3"];

	//ini["Halo3ODST"];

	//ini["HaloReach"];

	//ini["Halo4"];

	//ini["Halo2AMP"];

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::load_signatures()
{
	const mINI::INIFile file(config_folder + "\\Signatures.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	//Middleware sigs
	middleware::start_game_engine_t_aob_sig = ini.get("Middleware").get("start_game_engine_t");
	middleware::UICommandOverlayPush_t_aob_sig = ini.get("Middleware").get("UICommandOverlayPush_t");

	//Halo 1 Sigs
	halo1::offsets::hs_function_table_aob_sig = ini.get("Halo1A").get("hs_function_table");
	halo1::offsets::hs_external_globals_aob_sig = ini.get("Halo1A").get("hs_external_globals");
	halo1::offsets::hs_type_names_aob_sig = ini.get("Halo1A").get("hs_type_names");
	halo1::offsets::game_ticks_per_second_aob_sig = ini.get("Halo1A").get("game_ticks_per_second");

	//Halo 2 Sigs
	halo2::offsets::hs_function_table_aob_sig = ini.get("Halo2A").get("hs_function_table");
	halo2::offsets::hs_external_globals_aob_sig = ini.get("Halo2A").get("hs_external_globals");
	halo2::offsets::hs_type_names_aob_sig = ini.get("Halo2A").get("hs_type_names");

	//Halo 3 Sigs
	halo3::offsets::hs_function_table_aob_sig = ini.get("Halo3").get("hs_function_table");
	halo3::offsets::hs_external_globals_aob_sig = ini.get("Halo3").get("hs_external_globals");
	halo3::offsets::hs_type_names_aob_sig = ini.get("Halo3").get("hs_type_names");

	//Halo 3 ODST Sigs
	halo3odst::offsets::hs_function_table_aob_sig = ini.get("Halo3ODST").get("hs_function_table");
	halo3odst::offsets::hs_external_globals_aob_sig = ini.get("Halo3ODST").get("hs_external_globals");
	halo3odst::offsets::hs_type_names_aob_sig = ini.get("Halo3ODST").get("hs_type_names");

	//Halo Reach Sigs
	haloreach::offsets::hs_function_table_aob_sig = ini.get("HaloReach").get("hs_function_table");
	haloreach::offsets::hs_external_globals_aob_sig = ini.get("HaloReach").get("hs_external_globals");
	haloreach::offsets::hs_type_names_aob_sig = ini.get("HaloReach").get("hs_type_names");

	return true;
}

bool config::create_new_signatures()
{
	const mINI::INIFile file(config_folder + "\\Signatures.ini");

	mINI::INIStructure ini;

	// populate the structure

	//Middleware sigs
	ini["Middleware"]["start_game_engine_t"] = "83 FF 06 77 1A";
	ini["Middleware"]["UICommandOverlayPush_t"] = "41 83 C9 FF 4C 8B C5";

	// Halo 1 sigs
	ini["Halo1A"]["hs_function_table"] = "48 8D 1D ?? ?? ?? ?? 48 8D 35 ?? ?? ?? ?? 48 89 7C 24 30";
	ini["Halo1A"]["hs_external_globals"] = "48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35";
	ini["Halo1A"]["hs_type_names"] = "48 8D 35 ?? ?? ?? ?? 4C 8B 0B";
	ini["Halo1A"]["game_ticks_per_second"] = "F3 0F 5C 05 ?? ?? ?? ?? F3 0F 2C F8";

	// Halo 2 sigs
	ini["Halo2A"]["hs_function_table"] = "48 8D 3D ?? ?? ?? ?? 48 89 74 24 30 0F 1F 40 00";
	ini["Halo2A"]["hs_external_globals"] = "48 8D 05 ?? ?? ?? ?? 0F 1F 40 00 48 0F BF D3";
	ini["Halo2A"]["hs_type_names"] = "48 8D 35 ?? ?? ?? ?? 48 8B 1C C6";

	// Halo 3 sigs
	ini["Halo3"]["hs_function_table"] = "48 8D 35 ?? ?? ?? ?? 48 8B D5";
	ini["Halo3"]["hs_external_globals"] = "48 8D 05 ?? ?? ?? ?? 48 0F BF D3";
	ini["Halo3"]["hs_type_names"] = "48 8D 05 ?? ?? ?? ?? 4C 8B C3 48 8D 0D";

	// Halo 3 ODST sigs
	ini["Halo3ODST"]["hs_function_table"] = "48 8D 35 ?? ?? ?? ?? 48 8B D5";
	ini["Halo3ODST"]["hs_external_globals"] = "48 8D 1D ?? ?? ?? ?? 4C 8B 59 48";
	ini["Halo3ODST"]["hs_type_names"] = "48 8D 05 ?? ?? ?? ?? 4D 8B 09";

	// Halo Reach sigs
	ini["HaloReach"]["hs_function_table"] = "4C 8D 35 ?? ?? ?? ?? 33 DB 49 8B FE";
	ini["HaloReach"]["hs_external_globals"] = "48 8D 1D ?? ?? ?? ?? BF BC 06 00 00 4C 8B 0B";
	ini["HaloReach"]["hs_type_names"] = "48 8D 05 ?? ?? ?? ?? 4D 8B 09";

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}