#include "stdafx.h"
#include "halo1_offsets.h"

#include "halo1.h"
#include "halo1_sigs.h"
#include "utils.h"

void halo1::offsets::init()
{
	//Blamscript Functions Table
	blamscript::hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(
		sigs::list["hs_function_table"].c_str()).
		RelativeOffset(3).Get());

	//Blamscript External Globals Table
	blamscript::hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(
		sigs::list["hs_external_globals"].c_str()).
		RelativeOffset(3).Get());

	//Blamscript type names.
	blamscript::hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).Get());

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals and functions, instead of manually defining them like below.
	//Blamscript Globals
	variables::bottomless_clip = static_cast<bool*>(game::get_hs_global("cheat_bottomless_clip"));
	variables::infinite_ammo = static_cast<bool*>(game::get_hs_global("debug_ice_cream_flavor_status_bandanna"));
	variables::god_mode = static_cast<bool*>(game::get_hs_global("cheat_deathless_player"));
	variables::wireframe = static_cast<bool*>(game::get_hs_global("rasterizer_wireframe"));
	variables::enviroment_diffuse = static_cast<bool*>(game::get_hs_global("rasterizer_environment_diffuse_textures"));
	variables::atmosphere_fog = static_cast<bool*>(game::get_hs_global("rasterizer_fog_atmosphere"));
	variables::fog_plane = static_cast<bool*>(game::get_hs_global("rasterizer_fog_plane"));
	variables::fps_counter = static_cast<bool*>(game::get_hs_global("rasterizer_fps"));
	variables::motion_sensor_show_all_units = static_cast<bool*>(game::get_hs_global("debug_motion_sensor_draw_all_units"));

	variables::game_ticks_per_second = Memcury::Scanner::FindPattern(sigs::list["game_ticks_per_second"].c_str()).RelativeOffset(4).GetAs<float*>();

	variables::gravity = Memcury::Scanner(game::get_eval_hs_function("physics_get_gravity")).RelativeOffset(3).GetAs<float**>();

	patches::ai_update = Memcury::Scanner::FindPattern(sigs::list["ai_update_call"].c_str()).GetAs<void*>();
	utils::memory::store_memory_bytes(patches::ai_update_og_bytes, patches::ai_update, 0x05);

	// for some reason, game_ticks_per_second is protected from being changed
	DWORD old_prot;
	VirtualProtect(variables::game_ticks_per_second, 4, PAGE_EXECUTE_READWRITE, &old_prot);

	//Print function
	void* hs_print_address = game::get_eval_hs_function("print");
	functions::_terminal_printf = Memcury::Scanner(hs_print_address).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, 1).RelativeOffset(1).GetAs<void*>();
}