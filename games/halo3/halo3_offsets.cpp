#include "stdafx.h"

void halo3::offsets::init()
{
	//Blamscript Functions Table
	blamscript::hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(sigs::list["hs_function_table"].c_str()).RelativeOffset(3).Get());

	blamscript::functions::hs_null_evaluate = game::get_eval_hs_function("voice_set_force_match_configurations");

	blamscript::functions::hs_null_evaluate2 = game::get_eval_hs_function("debug_scripting");

	//Blamscript External Globals Table
	blamscript::hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(sigs::list["hs_external_globals"].c_str()).RelativeOffset(3).Get());

	variables::motion_blur_expected_dt = static_cast<float*>(game::get_hs_global("motion_blur_expected_dt"));
	variables::motion_blur_taps = static_cast<int*>(game::get_hs_global("motion_blur_taps"));
	variables::motion_blur_max_x = static_cast<float*>(game::get_hs_global("motion_blur_max_x"));
	variables::motion_blur_max_y = static_cast<float*>(game::get_hs_global("motion_blur_max_y"));
	variables::motion_blur_scale_x = static_cast<float*>(game::get_hs_global("motion_blur_scale_x"));
	variables::motion_blur_scale_y = static_cast<float*>(game::get_hs_global("motion_blur_scale_y"));
	variables::motion_blur_center_falloff = static_cast<float*>(game::get_hs_global("motion_blur_center_falloff"));

	//Blamscript type names.
	blamscript::hs_type_names = Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).GetAs<engine::_hs_type_names*>();

	globals::g_restricted_regions = Memcury::Scanner::FindPattern(sigs::list["g_restricted_regions"].c_str()).RelativeOffset(3).GetAs<c_restricted_memory*>();

	functions::game_in_progress = Memcury::Scanner::FindPattern(sigs::list["game_in_progress"].c_str()).RelativeOffset(1).GetAs<void*>();

	functions::game_tick = Memcury::Scanner::FindPattern(sigs::list["game_tick"].c_str()).RelativeOffset(1).GetAs<void*>();

	functions::weapon_barrel_create_projectiles = Memcury::Scanner::FindPattern(sigs::list["weapon_barrel_create_projectiles"].c_str()).RelativeOffset(1).GetAs<void*>();

	functions::weapon_get_owner_unit_index = Memcury::Scanner::FindPattern(sigs::list["weapon_get_owner_unit_index"].c_str()).RelativeOffset(1).Get();

	functions::object_scripting_cannot_die = Memcury::Scanner::FindPattern(sigs::list["object_scripting_cannot_die"].c_str()).Get();

	variables::region_member_indexes::physics_constants_member_index = Memcury::Scanner::FindPattern(sigs::list["physics_constants_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	variables::region_member_indexes::player_mapping_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["player_mapping_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	variables::region_member_indexes::player_data_member_index = Memcury::Scanner::FindPattern(sigs::list["player_data_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();
}

uintptr_t halo3::offsets::get_game_address(uintptr_t rva)
{
	return (uintptr_t)GetModuleHandle(L"halo3.dll") + rva;
}

void halo3::offsets::game_init()
{
	globals::physics_constants = static_cast<engine::s_physics_constants*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::physics_constants_member_index));
	globals::player_mapping_globals = static_cast<s_player_mapping_globals*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::player_mapping_globals_member_index));
	globals::player_data = static_cast<decltype(globals::player_data)>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::player_data_member_index));
}