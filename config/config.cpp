// This is used for the management of config files, etc
#include "config.h"

#include "console.h"
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

#include "games/halo1/halo1_hooks.h"
#include "games/halo2/halo2_hooks.h"

//TODO: make spdlog log level configurable!

//https://stackoverflow.com/a/29798
inline const char* const bool_to_string(bool b)
{
	return b ? "true" : "false";
}

//https://www.geeksforgeeks.org/convert-float-to-string-in-cpp/
template<typename T>
std::string to_string(T value)
{
	// Convert float to string
	std::stringstream s;
	s << value; // appending the float value to the streamclass
	return s.str(); //converting the float value to string
}

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
	halo3::offsets::game_in_progress_aob_sig = ini.get("Halo3").get("game_in_progress");

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
	ini["Halo3"]["game_in_progress"] = "E8 ?? ?? ?? ?? 84 C0 74 13 B8 C8 00 00 00";

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

// Game Specific ini files

bool config::halo1_create()
{
	const mINI::INIFile file(config_folder + "\\Halo1.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["Weapons"]["bottomless_clip"] = "false";
	ini["Weapons"]["infinite_ammo"] = "false";

	ini["Player"]["god_mode"] = "false";

	ini["Game"]["ticks_per_second"] = "30.0";
	ini["Game"]["motion_sensor_show_all_units"] = "false";
	ini["Game"]["redirect_print"] = "false";

	ini["Rendering"]["fps_counter"] = "false";
	ini["Rendering"]["wireframe"] = "false";
	ini["Rendering"]["atmosphere_fog"] = "true";
	ini["Rendering"]["fog_plane"] = "true";
	ini["Rendering"]["enviroment_diffuse"] = "true";

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::halo1_save()
{
	const mINI::INIFile file(config_folder + "\\Halo1.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["Weapons"]["bottomless_clip"] = bool_to_string(*halo1::offsets::bottomless_clip);
	ini["Weapons"]["infinite_ammo"] = bool_to_string(*halo1::offsets::infinite_ammo);

	ini["Player"]["god_mode"] = bool_to_string(*halo1::offsets::god_mode);

	ini["Game"]["ticks_per_second"] = to_string(*halo1::offsets::game_ticks_per_second);
	ini["Game"]["motion_sensor_show_all_units"] = bool_to_string(*halo1::offsets::motion_sensor_show_all_units);
	ini["Game"]["redirect_print"] = bool_to_string(halo1::hooks::redirect_print);

	ini["Rendering"]["fps_counter"] = bool_to_string(*halo1::offsets::fps_counter);
	ini["Rendering"]["wireframe"] = bool_to_string(*halo1::offsets::wireframe);
	ini["Rendering"]["atmosphere_fog"] = bool_to_string(*halo1::offsets::atmosphere_fog);
	ini["Rendering"]["fog_plane"] = bool_to_string(*halo1::offsets::fog_plane);
	ini["Rendering"]["enviroment_diffuse"] = bool_to_string(*halo1::offsets::enviroment_diffuse);

	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::halo1_load()
{
	const mINI::INIFile file(config_folder + "\\Halo1.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	std::istringstream(ini.get("Weapons").get("bottomless_clip")) >> std::boolalpha >> *halo1::offsets::bottomless_clip;
	std::istringstream(ini.get("Weapons").get("infinite_ammo")) >> std::boolalpha >> *halo1::offsets::infinite_ammo;

	std::istringstream(ini.get("Player").get("god_mode")) >> std::boolalpha >> *halo1::offsets::god_mode;

	std::istringstream(ini.get("Game").get("ticks_per_second")) >> *halo1::offsets::game_ticks_per_second;
	std::istringstream(ini.get("Game").get("motion_sensor_show_all_units")) >> std::boolalpha >> *halo1::offsets::motion_sensor_show_all_units;
	std::istringstream(ini.get("Game").get("redirect_print")) >> std::boolalpha >> halo1::hooks::redirect_print;

	std::istringstream(ini.get("Rendering").get("fps_counter")) >> std::boolalpha >> *halo1::offsets::fps_counter;
	std::istringstream(ini.get("Rendering").get("wireframe")) >> std::boolalpha >> *halo1::offsets::wireframe;
	std::istringstream(ini.get("Rendering").get("atmosphere_fog")) >> std::boolalpha >> *halo1::offsets::atmosphere_fog;
	std::istringstream(ini.get("Rendering").get("fog_plane")) >> std::boolalpha >> *halo1::offsets::fog_plane;
	std::istringstream(ini.get("Rendering").get("enviroment_diffuse")) >> std::boolalpha >> *halo1::offsets::enviroment_diffuse;

	return true;
}

bool config::halo2_create()
{
	const mINI::INIFile file(config_folder + "\\Halo2.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["Game"]["redirect_print"] = "false";

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::halo2_save()
{
	const mINI::INIFile file(config_folder + "\\Halo2.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["Game"]["redirect_print"] = bool_to_string(halo2::hooks::redirect_print);

	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::halo2_load()
{
	const mINI::INIFile file(config_folder + "\\Halo2.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	std::istringstream(ini.get("Game").get("redirect_print")) >> std::boolalpha >> halo2::hooks::redirect_print;

	return true;
}

bool config::halo3_create()
{
	const mINI::INIFile file(config_folder + "\\Halo3.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["Rendering"]["motion_blur_expected_dt"] = "0.03";
	ini["Rendering"]["motion_blur_taps"] = "6";
	ini["Rendering"]["motion_blur_max_x"] = "0.03";
	ini["Rendering"]["motion_blur_max_y"] = "0.05";
	ini["Rendering"]["motion_blur_scale_x"] = "0.05";
	ini["Rendering"]["motion_blur_scale_y"] = "0.15";
	ini["Rendering"]["motion_blur_center_falloff"] = "1.4";

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::halo3_save()
{
	const mINI::INIFile file(config_folder + "\\Halo3.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["Rendering"]["motion_blur_expected_dt"] = to_string(*halo3::offsets::motion_blur_expected_dt);
	ini["Rendering"]["motion_blur_taps"] = to_string<int>(*halo3::offsets::motion_blur_taps);
	ini["Rendering"]["motion_blur_max_x"] = to_string(*halo3::offsets::motion_blur_max_x);
	ini["Rendering"]["motion_blur_max_y"] = to_string(*halo3::offsets::motion_blur_max_y);
	ini["Rendering"]["motion_blur_scale_x"] = to_string(*halo3::offsets::motion_blur_scale_x);
	ini["Rendering"]["motion_blur_scale_y"] = to_string(*halo3::offsets::motion_blur_scale_y);
	ini["Rendering"]["motion_blur_center_falloff"] = to_string(*halo3::offsets::motion_blur_center_falloff);
	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::halo3_load()
{
	const mINI::INIFile file(config_folder + "\\Halo3.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	std::istringstream(ini.get("Rendering").get("motion_blur_expected_dt")) >> *halo3::offsets::motion_blur_expected_dt;
	std::istringstream(ini.get("Rendering").get("motion_blur_taps")) >> *halo3::offsets::motion_blur_taps;
	std::istringstream(ini.get("Rendering").get("motion_blur_max_x")) >> *halo3::offsets::motion_blur_max_x;
	std::istringstream(ini.get("Rendering").get("motion_blur_max_y")) >> *halo3::offsets::motion_blur_max_y;
	std::istringstream(ini.get("Rendering").get("motion_blur_scale_x")) >> *halo3::offsets::motion_blur_scale_x;
	std::istringstream(ini.get("Rendering").get("motion_blur_scale_y")) >> *halo3::offsets::motion_blur_scale_y;
	std::istringstream(ini.get("Rendering").get("motion_blur_center_falloff")) >> *halo3::offsets::motion_blur_center_falloff;

	return true;
}