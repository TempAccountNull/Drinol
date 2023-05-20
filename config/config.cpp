#include "stdafx.h"
#include "config.h"

#include "utils.h"
#include "games/halo1/halo1.h"
#include "games/halo1/halo1_hooks.h"
#include "games/halo1/halo1_offsets.h"
#include "games/halo1/halo1_sigs.h"
#include "games/halo2/halo2_hooks.h"
#include "games/halo2/halo2_sigs.h"
#include "games/halo3/halo3.h"
#include "games/halo3/halo3_hooks.h"
#include "games/halo3/halo3_offsets.h"
#include "games/halo3/halo3_sigs.h"
#include "games/halo3odst/halo3odst_sigs.h"
#include "games/halo4/halo4_sigs.h"
#include "games/haloreach/haloreach_sigs.h"
#include "gui/gui.h"
#include "gui/menu/menu.h"

// This is used for the management of config files, etc

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

//https://stackoverflow.com/a/5100745
template< typename T >
std::string int_to_hex_string(T i)
{
	std::stringstream stream;
	stream << "0x"
		//<< std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}

#pragma region main_config
bool config::main::save()
{
	const mINI::INIFile file(config_folder + "\\MainSettings.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["General"]["detach_keybind"] = int_to_hex_string(utils::detach_keybind);

	ini["Render"]["toggle_wireframe_keybind"] = int_to_hex_string(gui::toggle_wireframe_keybind);

	ini["UI"]["hookdx11"] = bool_to_string(gui::enabled);
	ini["UI"]["imguiinidir"] = gui::ui_ini_path;
	ini["UI"]["toggle_ui_keybind"] = int_to_hex_string(gui::toggle_ui_keybind);

	ini["Console"]["consolewindow"] = bool_to_string(console::enabled);
	ini["Console"]["imguiconsole"] = bool_to_string(menu::console_enabled);

	ini["Console"]["logtofile"] = bool_to_string(logging::log_to_file);

	ini["Console"]["loglevel"] = to_string(logging::log_level);

	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::main::load()
{
	const mINI::INIFile file(config_folder + "\\MainSettings.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	gui::toggle_wireframe_keybind = std::stoul(ini.get("Render").get("toggle_wireframe_keybind"), nullptr, 16);

	utils::detach_keybind = std::stoul(ini.get("General").get("detach_keybind"), nullptr, 16);

	std::istringstream(ini.get("UI").get("hookdx11")) >> std::boolalpha >> gui::enabled;

	gui::ui_ini_path = ini.get("UI").get("imguiinidir");

	gui::toggle_ui_keybind = std::stoul(ini.get("UI").get("toggle_ui_keybind"), nullptr, 16);

	std::istringstream(ini.get("console").get("consolewindow")) >> std::boolalpha >> console::enabled;

	std::istringstream(ini.get("console").get("imguiconsole")) >> std::boolalpha >> menu::console_enabled;

	std::istringstream(ini.get("console").get("logtofile")) >> std::boolalpha >> logging::log_to_file;

	logging::log_level = std::stoi(ini.get("Console").get("loglevel"));

	return true;
}

bool config::main::create_config_folder()
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

bool config::main::create()
{
	const mINI::INIFile file(config_folder + "\\MainSettings.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["General"]["detach_keybind"] = "0x23";

	ini["Render"]["toggle_wireframe_keybind"] = "0x24";

	ini["UI"]["hookdx11"] = "true";
	ini["UI"]["imguiinidir"] = config_folder + "\\UI.ini";
	ini["UI"]["toggle_ui_keybind"] = "0x2D";

	ini["Console"]["consolewindow"] = "true";
	ini["Console"]["imguiconsole"] = "false";

	ini["Console"]["logtofile"] = "true";

	ini["Console"]["loglevel"] = "0";

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
#pragma endregion

#pragma region sigs_config
bool config::sigs::load()
{
	const mINI::INIFile file(main::config_folder + "\\Signatures.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	//Middleware sigs
	for (std::pair<const std::string, std::string>& item : middleware::sigs::list)
	{
		item.second = ini.get("middleware").get(item.first);
	}

	//Halo 1 Sigs
	for (std::pair<const std::string, std::string>& item : halo1::sigs::list)
	{
		item.second = ini.get("halo1a").get(item.first);
	}

	//Halo 2 Sigs
	for (std::pair<const std::string, std::string>& item : halo2::sigs::list)
	{
		item.second = ini.get("halo2a").get(item.first);
	}

	//Halo 3 Sigs
	for (std::pair<const std::string, std::string>& item : halo3::sigs::list)
	{
		item.second = ini.get("Halo3").get(item.first);
	}

	//Halo 3 ODST Sigs
	for (std::pair<const std::string, std::string>& item : halo3odst::sigs::list)
	{
		item.second = ini.get("Halo3ODST").get(item.first);
	}

	//Halo Reach Sigs

	for (std::pair<const std::string, std::string>& item : haloreach::sigs::list)
	{
		item.second = ini.get("HaloReach").get(item.first);
	}

	//Halo 4 Sigs

	for (std::pair<const std::string, std::string>& item : halo4::sigs::list)
	{
		item.second = ini.get("Halo4").get(item.first);
	}

	return true;
}

bool config::sigs::create()
{
	const mINI::INIFile file(main::config_folder + "\\Signatures.ini");

	mINI::INIStructure ini;

	// populate the structure
	// TODO: Merge these for loops
	//Middleware sigs
	for (std::pair<const std::string, std::string> item : middleware::sigs::list)
	{
		ini["Middleware"][item.first] = item.second;
	}

	// Halo 1 sigs
	for (std::pair<const std::string, std::string> item : halo1::sigs::list)
	{
		ini["Halo1a"][item.first] = item.second;
	}

	// Halo 2 sigs
	for (std::pair<const std::string, std::string> item : halo2::sigs::list)
	{
		ini["Halo2a"][item.first] = item.second;
	}

	// Halo 3 sigs
	for (std::pair<const std::string, std::string> item : halo3::sigs::list)
	{
		ini["Halo3"][item.first] = item.second;
	}

	// Halo 3 ODST sigs
	for (std::pair<const std::string, std::string> item : halo3odst::sigs::list)
	{
		ini["Halo3ODST"][item.first] = item.second;
	}

	// Halo Reach sigs
	for (std::pair<const std::string, std::string> item : haloreach::sigs::list)
	{
		ini["HaloReach"][item.first] = item.second;
	}

	// Halo 4 sigs
	for (std::pair<const std::string, std::string> item : halo4::sigs::list)
	{
		ini["Halo4"][item.first] = item.second;
	}

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::sigs::validate()
{
	// TODO: Merge these for loops

	for (std::pair<const std::string, std::string> element : middleware::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	for (std::pair<const std::string, std::string> element : halo1::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	for (std::pair<const std::string, std::string> element : halo2::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	for (std::pair<const std::string, std::string> element : halo3::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	for (std::pair<const std::string, std::string> element : halo3odst::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	for (std::pair<const std::string, std::string> element : haloreach::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	for (std::pair<const std::string, std::string> element : halo4::sigs::list)
	{
		if (element.first.empty() || element.second.empty())
		{
			return false;
		}
	}

	return true;
}
#pragma endregion

#pragma region game_configs
// Game Specific ini files

bool config::games::halo_1::create()
{
	const mINI::INIFile file(main::config_folder + "\\Halo1.ini");

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

bool config::games::halo_1::save()
{
	const mINI::INIFile file(main::config_folder + "\\Halo1.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["Weapons"]["bottomless_clip"] = bool_to_string(*halo1::offsets::variables::bottomless_clip);
	ini["Weapons"]["infinite_ammo"] = bool_to_string(*halo1::offsets::variables::infinite_ammo);

	ini["Player"]["god_mode"] = bool_to_string(*halo1::offsets::variables::god_mode);

	ini["Game"]["ticks_per_second"] = to_string(*halo1::offsets::variables::game_ticks_per_second);
	ini["Game"]["motion_sensor_show_all_units"] = bool_to_string(*halo1::offsets::variables::motion_sensor_show_all_units);
	ini["Game"]["redirect_print"] = bool_to_string(halo1::hooks::redirect_print);
	ini["Game"]["toggle_ai"] = bool_to_string(halo1::game::toggle_ai_bool);

	ini["Rendering"]["fps_counter"] = bool_to_string(*halo1::offsets::variables::fps_counter);
	ini["Rendering"]["wireframe"] = bool_to_string(*halo1::offsets::variables::wireframe);
	ini["Rendering"]["atmosphere_fog"] = bool_to_string(*halo1::offsets::variables::atmosphere_fog);
	ini["Rendering"]["fog_plane"] = bool_to_string(*halo1::offsets::variables::fog_plane);
	ini["Rendering"]["enviroment_diffuse"] = bool_to_string(*halo1::offsets::variables::enviroment_diffuse);

	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::games::halo_1::load()
{
	const mINI::INIFile file(main::config_folder + "\\Halo1.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	std::istringstream(ini.get("Weapons").get("bottomless_clip")) >> std::boolalpha >> *halo1::offsets::variables::bottomless_clip;
	std::istringstream(ini.get("Weapons").get("infinite_ammo")) >> std::boolalpha >> *halo1::offsets::variables::infinite_ammo;

	std::istringstream(ini.get("Player").get("god_mode")) >> std::boolalpha >> *halo1::offsets::variables::god_mode;

	std::istringstream(ini.get("Game").get("ticks_per_second")) >> *halo1::offsets::variables::game_ticks_per_second;
	std::istringstream(ini.get("Game").get("motion_sensor_show_all_units")) >> std::boolalpha >> *halo1::offsets::variables::motion_sensor_show_all_units;
	std::istringstream(ini.get("Game").get("redirect_print")) >> std::boolalpha >> halo1::hooks::redirect_print;

	std::istringstream(ini.get("Game").get("toggle_ai")) >> std::boolalpha >> halo1::game::toggle_ai_bool;

	std::istringstream(ini.get("Rendering").get("fps_counter")) >> std::boolalpha >> *halo1::offsets::variables::fps_counter;
	std::istringstream(ini.get("Rendering").get("wireframe")) >> std::boolalpha >> *halo1::offsets::variables::wireframe;
	std::istringstream(ini.get("Rendering").get("atmosphere_fog")) >> std::boolalpha >> *halo1::offsets::variables::atmosphere_fog;
	std::istringstream(ini.get("Rendering").get("fog_plane")) >> std::boolalpha >> *halo1::offsets::variables::fog_plane;
	std::istringstream(ini.get("Rendering").get("enviroment_diffuse")) >> std::boolalpha >> *halo1::offsets::variables::enviroment_diffuse;

	return true;
}

bool config::games::halo_2::create()
{
	const mINI::INIFile file(main::config_folder + "\\Halo2.ini");

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

bool config::games::halo_2::save()
{
	const mINI::INIFile file(main::config_folder + "\\Halo2.ini");

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

bool config::games::halo_2::load()
{
	const mINI::INIFile file(main::config_folder + "\\Halo2.ini");

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

bool config::games::halo_3::create()
{
	const mINI::INIFile file(main::config_folder + "\\Halo3.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["Rendering"]["motion_blur_expected_dt"] = "0.03";
	ini["Rendering"]["motion_blur_taps"] = "6";
	ini["Rendering"]["motion_blur_max_x"] = "0.03";
	ini["Rendering"]["motion_blur_max_y"] = "0.05";
	ini["Rendering"]["motion_blur_scale_x"] = "0.05";
	ini["Rendering"]["motion_blur_scale_y"] = "0.15";
	ini["Rendering"]["motion_blur_center_falloff"] = "1.4";
	ini["Game"]["player_weapon_projectiles_only"] = "false";
	ini["Game"]["player_ally_projectiles_only"] = "false";
	ini["Game"]["Machinima"] = "false";

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::games::halo_3::save()
{
	const mINI::INIFile file(main::config_folder + "\\Halo3.ini");

	mINI::INIStructure ini;

	// populate the structure

	ini["Rendering"]["motion_blur_expected_dt"] = to_string(*halo3::offsets::variables::motion_blur_expected_dt);
	ini["Rendering"]["motion_blur_taps"] = to_string<int>(*halo3::offsets::variables::motion_blur_taps);
	ini["Rendering"]["motion_blur_max_x"] = to_string(*halo3::offsets::variables::motion_blur_max_x);
	ini["Rendering"]["motion_blur_max_y"] = to_string(*halo3::offsets::variables::motion_blur_max_y);
	ini["Rendering"]["motion_blur_scale_x"] = to_string(*halo3::offsets::variables::motion_blur_scale_x);
	ini["Rendering"]["motion_blur_scale_y"] = to_string(*halo3::offsets::variables::motion_blur_scale_y);
	ini["Rendering"]["motion_blur_center_falloff"] = to_string(*halo3::offsets::variables::motion_blur_center_falloff);
	ini["Game"]["player_weapon_projectiles_only"] = bool_to_string(halo3::hooks::player_weapon_projectiles_only);
	ini["Game"]["Machinima"] = bool_to_string(halo3::game::machinima_mode);
	ini["Game"]["player_ally_projectiles_only"] = bool_to_string(halo3::hooks::player_ally_projectiles_only);

	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::games::halo_3::load()
{
	const mINI::INIFile file(main::config_folder + "\\Halo3.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value
	std::istringstream(ini.get("Game").get("player_weapon_projectiles_only")) >> std::boolalpha >> halo3::hooks::player_weapon_projectiles_only;
	std::istringstream(ini.get("Game").get("player_ally_projectiles_only")) >> std::boolalpha >> halo3::hooks::player_ally_projectiles_only;
	std::istringstream(ini.get("Game").get("Machinima")) >> std::boolalpha >> halo3::game::machinima_mode;
	std::istringstream(ini.get("Rendering").get("motion_blur_expected_dt")) >> *halo3::offsets::variables::motion_blur_expected_dt;
	std::istringstream(ini.get("Rendering").get("motion_blur_taps")) >> *halo3::offsets::variables::motion_blur_taps;
	std::istringstream(ini.get("Rendering").get("motion_blur_max_x")) >> *halo3::offsets::variables::motion_blur_max_x;
	std::istringstream(ini.get("Rendering").get("motion_blur_max_y")) >> *halo3::offsets::variables::motion_blur_max_y;
	std::istringstream(ini.get("Rendering").get("motion_blur_scale_x")) >> *halo3::offsets::variables::motion_blur_scale_x;
	std::istringstream(ini.get("Rendering").get("motion_blur_scale_y")) >> *halo3::offsets::variables::motion_blur_scale_y;
	std::istringstream(ini.get("Rendering").get("motion_blur_center_falloff")) >> *halo3::offsets::variables::motion_blur_center_falloff;

	return true;
}

bool config::games::halo_4::create()
{
	const mINI::INIFile file(main::config_folder + "\\Halo4.ini");

	mINI::INIStructure ini;

	// populate the structure

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}

bool config::games::halo_4::save()
{
	const mINI::INIFile file(main::config_folder + "\\Halo4.ini");

	mINI::INIStructure ini;

	// populate the structure

	// write to the INI file (overwrites)
	if (!file.write(ini, true))
	{
		// Failed to write ini
		return false;
	}
	return true;
}

bool config::games::halo_4::load()
{
	const mINI::INIFile file(main::config_folder + "\\Halo4.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	return true;
}

#pragma endregion