#include "halo2_offsets.h"

#include "halo2.h"
#include "Memcury/memcury.h"

void halo2::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern("48 8D 3D ?? ?? ?? ?? 48 89 74 24 30 0F 1F 40 00").RelativeOffset(3).Get());

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern("48 8D 05 ?? ?? ?? ?? 0F 1F 40 00 48 0F BF D3").RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 48 8B 1C C6").RelativeOffset(3).Get());

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals and functions, instead of manually defining them like below.
	//Blamscript Globals
	toggle_hud = static_cast<bool*>(game::get_hs_global("disable_hud"));

	//Blamscript Functions TODO: Figure out a way to call these without crashing the game or having to hook into the main thread of the game.

	//std::cout << std::hex << Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(1).Get() << std::endl;
}