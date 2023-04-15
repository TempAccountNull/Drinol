#include "stdafx.h"

void halo3::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(sigs::list["hs_function_table"].c_str()).RelativeOffset(3).Get());

	hs_null_evaluate = game::get_eval_hs_function("voice_set_force_match_configurations");

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(sigs::list["hs_external_globals"].c_str()).RelativeOffset(3).Get());
	motion_blur_expected_dt = static_cast<float*>(game::get_hs_global("motion_blur_expected_dt"));
	motion_blur_taps = static_cast<int*>(game::get_hs_global("motion_blur_taps"));
	motion_blur_max_x = static_cast<float*>(game::get_hs_global("motion_blur_max_x"));
	motion_blur_max_y = static_cast<float*>(game::get_hs_global("motion_blur_max_y"));
	motion_blur_scale_x = static_cast<float*>(game::get_hs_global("motion_blur_scale_x"));
	motion_blur_scale_y = static_cast<float*>(game::get_hs_global("motion_blur_scale_y"));
	motion_blur_center_falloff = static_cast<float*>(game::get_hs_global("motion_blur_center_falloff"));

	//Blamscript type names.
	hs_type_names = Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).GetAs<engine::_hs_type_names*>();

	g_restricted_regions = Memcury::Scanner::FindPattern(sigs::list["g_restricted_regions"].c_str()).RelativeOffset(3).GetAs<c_restricted_memory*>();

	game_in_progress = Memcury::Scanner::FindPattern(sigs::list["game_in_progress"].c_str()).RelativeOffset(1).GetAs<void*>();

	game_tick = Memcury::Scanner::FindPattern(sigs::list["game_tick"].c_str()).RelativeOffset(1).GetAs<void*>();

	weapon_barrel_create_projectiles = Memcury::Scanner::FindPattern(sigs::list["weapon_barrel_create_projectiles"].c_str()).RelativeOffset(1).GetAs<void*>();

	weapon_get_owner_unit_index = Memcury::Scanner::FindPattern(sigs::list["weapon_get_owner_unit_index"].c_str()).RelativeOffset(1).Get();

	object_scripting_cannot_die = Memcury::Scanner::FindPattern(sigs::list["object_scripting_cannot_die"].c_str()).Get();

	physics_constants_member_index = Memcury::Scanner::FindPattern(sigs::list["physics_constants_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	player_mapping_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["player_mapping_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	player_data_member_index = Memcury::Scanner::FindPattern(sigs::list["player_data_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();
}

uintptr_t halo3::offsets::get_game_address(uintptr_t rva)
{
	return (uintptr_t)GetModuleHandle(L"halo3.dll") + rva;
}

void halo3::offsets::game_init()
{
	physics_constants = static_cast<engine::s_physics_constants*>(game::get_restricted_region_member_address(2, 3, *physics_constants_member_index));
	player_mapping_globals = static_cast<s_player_mapping_globals*>(game::get_restricted_region_member_address(2, 3, *player_mapping_globals_member_index));
	player_data = static_cast<decltype(player_data)>(game::get_restricted_region_member_address(2, 3, *player_data_member_index));
}