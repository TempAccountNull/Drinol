#include "stdafx.h"
#include "halo3_offsets.h"

#include "halo3.h"
#include "halo3_sigs.h"
#include "utils.h"

void halo3::offsets::init()
{
	//Blamscript Functions Table
	spdlog::debug("Halo 3: Pattern scanning for: hs_function_table");
	blamscript::hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(sigs::list["hs_function_table"].c_str()).RelativeOffset(3).Get());

	blamscript::functions::hs_null_evaluate = game::get_eval_hs_function("voice_set_force_match_configurations");

	blamscript::functions::hs_null_evaluate2 = game::get_eval_hs_function("debug_scripting");

	//Blamscript External Globals Table
	spdlog::debug("Halo 3: Pattern scanning for: hs_external_globals");
	blamscript::hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(sigs::list["hs_external_globals"].c_str()).RelativeOffset(3).Get());

	variables::motion_blur_expected_dt = static_cast<float*>(game::get_hs_global("motion_blur_expected_dt"));
	variables::motion_blur_taps = static_cast<int*>(game::get_hs_global("motion_blur_taps"));
	variables::motion_blur_max_x = static_cast<float*>(game::get_hs_global("motion_blur_max_x"));
	variables::motion_blur_max_y = static_cast<float*>(game::get_hs_global("motion_blur_max_y"));
	variables::motion_blur_scale_x = static_cast<float*>(game::get_hs_global("motion_blur_scale_x"));
	variables::motion_blur_scale_y = static_cast<float*>(game::get_hs_global("motion_blur_scale_y"));
	variables::motion_blur_center_falloff = static_cast<float*>(game::get_hs_global("motion_blur_center_falloff"));

	//Blamscript type names.
	spdlog::debug("Halo 3: Pattern scanning for: hs_type_names");
	blamscript::hs_type_names = Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).GetAs<engine::_hs_type_names*>();

	spdlog::debug("Halo 3: Pattern scanning for: g_restricted_regions");
	globals::g_restricted_regions = Memcury::Scanner::FindPattern(sigs::list["g_restricted_regions"].c_str()).RelativeOffset(3).GetAs<c_restricted_memory*>();

	spdlog::debug("Halo 3: Pattern scanning for: game_in_progress");
	functions::game::game_in_progress = Memcury::Scanner::FindPattern(sigs::list["game_in_progress"].c_str()).RelativeOffset(1).GetAs<void*>();

	spdlog::debug("Halo 3: Pattern scanning for: game_tick");
	functions::game::game_tick = Memcury::Scanner::FindPattern(sigs::list["game_tick"].c_str()).RelativeOffset(1).GetAs<void*>();

	spdlog::debug("Halo 3: Pattern scanning for: director_render");
	functions::render::director_render = Memcury::Scanner::FindPattern(sigs::list["director_render"].c_str()).GetAs<void*>();

	spdlog::debug("Halo 3: Pattern scanning for: weapon_barrel_create_projectiles");
	functions::weapons::weapon_barrel_create_projectiles = Memcury::Scanner::FindPattern(sigs::list["weapon_barrel_create_projectiles"].c_str()).RelativeOffset(1).GetAs<void*>();

	spdlog::debug("Halo 3: Pattern scanning for: weapon_get_owner_unit_index");
	functions::weapons::weapon_get_owner_unit_index = Memcury::Scanner::FindPattern(sigs::list["weapon_get_owner_unit_index"].c_str()).RelativeOffset(1).Get();

	spdlog::debug("Halo 3: Pattern scanning for: object_scripting_cannot_die");
	functions::objects::object_scripting_cannot_die = Memcury::Scanner::FindPattern(sigs::list["object_scripting_cannot_die"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: game_time_set_rate_scale_direct");
	functions::game::game_time_set_rate_scale_direct = Memcury::Scanner::FindPattern(sigs::list["game_time_set_rate_scale_direct"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: object_try_and_get_and_verify_type");
	functions::objects::object_try_and_get_and_verify_type = Memcury::Scanner::FindPattern(sigs::list["object_try_and_get_and_verify_type"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: game_team_is_enemy");
	functions::game::game_team_is_enemy = Memcury::Scanner::FindPattern(sigs::list["game_team_is_enemy"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: draw_quad");
	functions::render::draw_quad = Memcury::Scanner::FindPattern(sigs::list["draw_quad"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: draw_string_init");
	functions::render::draw_string_init = Memcury::Scanner::FindPattern(sigs::list["draw_string_init"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: font_cache_init");
	functions::render::font_cache_init = Memcury::Scanner::FindPattern(sigs::list["font_cache_init"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: draw_string_set_font");
	functions::render::draw_string_set_font = Memcury::Scanner::FindPattern(sigs::list["draw_string_set_font"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: draw_string_draw");
	functions::render::draw_string_draw = Memcury::Scanner::FindPattern(sigs::list["draw_string_draw"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: draw_string_set_bounds");
	functions::render::draw_string_set_bounds = Memcury::Scanner::FindPattern(sigs::list["draw_string_set_bounds"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: get_screen_bounds");
	functions::render::get_screen_bounds = Memcury::Scanner::FindPattern(sigs::list["get_screen_bounds"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: deinit_font_cache");
	functions::render::deinit_font_cache = Memcury::Scanner::FindPattern(sigs::list["deinit_font_cache"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: draw_linestrip_2d");
	functions::render::draw_linestrip_2d = Memcury::Scanner::FindPattern(sigs::list["draw_linestrip_2d"].c_str()).Get();

	spdlog::debug("Halo 3: Pattern scanning for: data_initialize");
	functions::data::data_initialize = Memcury::Scanner::FindPattern(sigs::list["data_initialize"].c_str()).GetAs<void*>();

	spdlog::debug("Halo 3: Pattern scanning for: screen_res_x");
	variables::screen_res_x = Memcury::Scanner::FindPattern(sigs::list["screen_res_x"].c_str()).RelativeOffset(3).GetAs<int*>();
	spdlog::debug("Halo 3: Pattern scanning for: screen_res_y");
	variables::screen_res_y = Memcury::Scanner::FindPattern(sigs::list["screen_res_y"].c_str()).RelativeOffset(3).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: physics_constants_member_index");
	variables::region_member_indexes::physics_constants_member_index = Memcury::Scanner::FindPattern(sigs::list["physics_constants_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: player_mapping_globals_member_index");
	variables::region_member_indexes::player_mapping_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["player_mapping_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: player_control_globals_member_index");
	variables::region_member_indexes::player_control_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["player_control_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: game_time_globals_member_index");
	variables::region_member_indexes::game_time_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["game_time_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: game_globals_member_index");
	variables::region_member_indexes::game_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["game_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: player_data_member_index");
	variables::region_member_indexes::player_data_member_index = Memcury::Scanner::FindPattern(sigs::list["player_data_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: game_allegiance_globals_member_index");
	variables::region_member_indexes::game_allegiance_globals_member_index = Memcury::Scanner::FindPattern(sigs::list["game_allegiance_globals_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 3: Pattern scanning for: ai_handle_effect_creation_check");
	patches::ai_handle_effect_creation_check = Memcury::Scanner::FindPattern(sigs::list["ai_handle_effect_creation_check"].c_str()).GetAs<void*>();
	utils::memory::store_memory_bytes(patches::ai_handle_effect_creation_check_og_bytes, patches::ai_handle_effect_creation_check, 0x06);
}

uintptr_t halo3::offsets::get_game_address(uintptr_t rva)
{
	return reinterpret_cast<uintptr_t>(GetModuleHandle(L"halo3.dll")) + rva;
}

void halo3::offsets::game_init()
{
	globals::physics_constants = static_cast<engine::s_physics_constants*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::physics_constants_member_index));
	globals::players_globals = static_cast<engine::s_data_array*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::player_data_member_index));
	globals::player_control_globals = static_cast<engine::s_player_control_globals*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::player_control_globals_member_index));
	globals::player_mapping_globals = static_cast<s_player_mapping_globals*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::player_mapping_globals_member_index));
	globals::game_time_globals = static_cast<engine::game_time_globals_definition*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::game_time_globals_member_index));
	globals::game_globals = static_cast<engine::s_game_globals*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::game_globals_member_index));
	globals::game_allegiance_globals = static_cast<engine::game_allegiance_globals*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::game_allegiance_globals_member_index));

	//TODO: sometimes this does not work, no idea why
	if (game::machinima_mode)
	{
		globals::player_control_globals->machinima_camera_debug = true;
		globals::player_control_globals->machinima_camera_enabled = true;
	}
}