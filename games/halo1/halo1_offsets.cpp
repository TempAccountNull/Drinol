#include "halo1_offsets.h"

#include <iostream>

#include "halo1.h"
#include "Memcury/memcury.h"

void halo1::offsets::init()
{
	//TODO: It would be cool if we could use the offset in this aob "48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35" to gather a list of all these global variables and to check if they have not been stripped from retail or not.

	Memcury::Globals::moduleName = "halo1.dll";

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern("48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35").
		RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(3).Get());

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals, instead of manually defining them like below.
	//Blamscript Globals
	bottomless_clip = static_cast<bool*>(game::get_global("cheat_bottomless_clip"));
	infinite_ammo = static_cast<bool*>(game::get_global("debug_ice_cream_flavor_status_bandanna"));
	god_mode = static_cast<bool*>(game::get_global("cheat_deathless_player"));
	wireframe = static_cast<bool*>(game::get_global("rasterizer_wireframe"));

	game_ticks_per_second = Memcury::Scanner::FindPattern("F3 0F 5C 05 ?? ?? ?? ?? F3 0F 2C F8").RelativeOffset(4).GetAs<float*>();

	// for some reason, game_ticks_per_second is protected from being changed
	DWORD old_prot;
	VirtualProtect(game_ticks_per_second, 4, PAGE_EXECUTE_READWRITE, &old_prot);

	//std::cout << std::hex << Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(1).Get() << std::endl;
}