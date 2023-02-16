// This is used for the management of config files, etc
#include "config.h"

#include "utils.h"
#include "gui/gui.h"
#include "mINI/src/mini/ini.h"

#if defined _DEBUG
//mINI example.
void config::test()
{
	// create a file instance
	const mINI::INIFile file(utils::dll_path + "\\Drinol.ini");

	// create a data structure
	mINI::INIStructure ini;

	// populate the structure
	ini["things"]["chairs"] = "20";
	ini["things"]["balloons"] = "100";

	// generate an INI file (overwrites any previous file)
	file.generate(ini);
}
#endif

bool config::load()
{
	const mINI::INIFile file(utils::dll_path + "\\Drinol.ini");

	mINI::INIStructure ini;

	if (!file.read(ini))
	{
		// Failed to read ini
		return false;
	}

	// read a value

	std::istringstream(ini.get("HookDX11").get("enabled")) >> std::boolalpha >> gui::enabled;

	// update a value
	//ini["fruits"]["oranges"] = "50";
	return true;
}

bool config::create_new()
{
	const mINI::INIFile file(utils::dll_path + "\\Drinol.ini");

	mINI::INIStructure ini;

	// populate the structure
	ini["HookDX11"]["enabled"] = "true";

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