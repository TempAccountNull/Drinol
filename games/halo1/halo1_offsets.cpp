#include "halo1_offsets.h"

#include "halo1.h"
#include "Memcury/memcury.h"

void halo1::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(
		hs_function_table_aob_sig.c_str()).
		RelativeOffset(3).Get());

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(
		hs_external_globals_aob_sig.c_str()).
		RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(hs_type_names_aob_sig.c_str()).RelativeOffset(3).Get());

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

	game_ticks_per_second = Memcury::Scanner::FindPattern(game_ticks_per_second_aob_sig.c_str()).RelativeOffset(4).GetAs<float*>();

	// for some reason, game_ticks_per_second is protected from being changed
	DWORD old_prot;
	VirtualProtect(game_ticks_per_second, 4, PAGE_EXECUTE_READWRITE, &old_prot);

	//Print function
	void* hs_print_address = game::get_eval_hs_function("print");
	_terminal_printf = Memcury::Scanner(hs_print_address).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, 1).RelativeOffset(1).GetAs<void*>();
}