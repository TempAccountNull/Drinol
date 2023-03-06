#include "halo1_offsets.h"

#include "halo1.h"
#include "Memcury/memcury.h"

void halo1::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern("48 8D 1D ?? ?? ?? ?? 48 8D 35 ?? ?? ?? ?? 48 89 7C 24 30").
		RelativeOffset(3).Get());

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern("48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35").
		RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(3).Get());

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals and functions, instead of manually defining them like below.
	//Blamscript Globals
	bottomless_clip = static_cast<bool*>(game::get_hs_global("cheat_bottomless_clip"));
	infinite_ammo = static_cast<bool*>(game::get_hs_global("debug_ice_cream_flavor_status_bandanna"));
	god_mode = static_cast<bool*>(game::get_hs_global("cheat_deathless_player"));
	wireframe = static_cast<bool*>(game::get_hs_global("rasterizer_wireframe"));
	enviroment_diffuse = static_cast<bool*>(game::get_hs_global("rasterizer_environment_diffuse_textures"));
	atmosphere_fog = static_cast<bool*>(game::get_hs_global("rasterizer_fog_atmosphere"));
	fog_plane = static_cast<bool*>(game::get_hs_global("rasterizer_fog_plane"));
	fps_counter = static_cast<bool*>(game::get_hs_global("rasterizer_fps"));
	motion_sensor_show_all_units = static_cast<bool*>(game::get_hs_global("debug_motion_sensor_draw_all_units"));

	//Blamscript Functions TODO: Figure out a way to call these without crashing the game or having to hook into the main thread of the game.

	game_ticks_per_second = Memcury::Scanner::FindPattern("F3 0F 5C 05 ?? ?? ?? ?? F3 0F 2C F8").RelativeOffset(4).GetAs<float*>();

	// for some reason, game_ticks_per_second is protected from being changed
	DWORD old_prot;
	VirtualProtect(game_ticks_per_second, 4, PAGE_EXECUTE_READWRITE, &old_prot);

	//std::cout << std::hex << Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(1).Get() << std::endl;
}