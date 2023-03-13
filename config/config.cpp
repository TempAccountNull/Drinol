// This is used for the management of config files, etc
#include "config.h"

#include "framework.h"
#include "utils.h"
#include "gui/gui.h"
#include "mINI/src/mini/ini.h"

bool config::load()
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

	return true;
}

bool config::create_new()
{
	// Create a directory to store all the config files (keeps things tidy :p)

	if (CreateDirectoryA(config_folder.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		// CopyFile(...)
	}
	else
	{
		// Failed to create directory.
		return false;
	}

	const mINI::INIFile file(config_folder + "\\MainSettings.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["UI"]["hookdx11"] = "true";
	ini["UI"]["imguiinidir"] = config_folder + "\\UI.ini";

	ini["Halo1A"];

	ini["Halo2A"];

	ini["Halo3"];

	ini["Halo3ODST"];

	ini["HaloReach"];

	ini["Halo4"];

	ini["Halo2AMP"];

	// generate an INI file (overwrites any previous file)
	if (!file.generate(ini, true))
	{
		// Failed to generate ini
		return false;
	}
	return true;
}