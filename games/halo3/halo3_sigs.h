#pragma once

namespace halo3
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "48 8D 35 ?? ?? ?? ?? 48 8B D5"},
			{"hs_external_globals", "48 8D 05 ?? ?? ?? ?? 48 0F BF D3"},
			{"hs_type_names", "48 8D 05 ?? ?? ?? ?? 4C 8B C3 48 8D 0D"},
			{"game_in_progress","E8 ?? ?? ?? ?? 84 C0 74 13 B8 C8 00 00 00"},
			{"g_restricted_regions","48 8D 3D ?? ?? ?? ?? 48 83 64 24 30 00 45 33 C0 89 05 ?? ?? ?? ?? 41 B9 00 02 00 00"},
			{"physics_constants_member_index","89 05 ?? ?? ?? ?? 48 98 4C 8B 04 D1 B9 18 00 00 00 42 8B 0C 01 89 0D ?? ?? ?? ?? 48 8D 0C 40 48 03 C9 48 8D 05 ?? ?? ?? ?? 8B 1C C8"},
			{"player_mapping_globals_member_index","89 05 ?? ?? ?? ?? 48 98 89 0D ?? ?? ?? ?? 48 8D 0C 40 48 03 C9 8B 84 CF 40 4B 00 00 49 03 44 1E 18 B9 10 01 00 00"},
			{"game_time_globals_member_index","89 05 ?? ?? ?? ?? 48 98 4C 8B 0C D1 33 D2 B9 18 00 00 00 44 8D 42 2C"},
			{"player_data_member_index","89 05 ?? ?? ?? ?? 41 B9 E8 00 00 00"},
			{"game_globals_member_index","89 05 ? ? ? ? 8B 15 ? ? ? ? 65 48 8B 0C 25 ? ? ? ? 48 8B 1C D1 41 BD"},
			{"player_control_globals_member_index","89 05 ?? ?? ?? ?? 48 98 48 8B 1C D1 48 8D 15 ?? ?? ?? ?? BE 18 00 00 00 BD 90 05 00 00"},
			{"game_allegiance_globals_member_index","89 05 ?? ?? ?? ?? 48 98 4C 8B 0C D1 33 D2 B9 18 00 00 00 42 8B 0C 09 89 0D ?? ?? ?? ?? 48 8D 0C 40 48 03 C9 48 8D 05 ?? ?? ?? ?? 8B 0C C8 B8 90 05 00 00 4A 8B 44 08 18 48 03 C8 B8 80 01 00 00"},
			{"game_tick","E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 84 C0 75 B7"},
			{"object_scripting_cannot_die","33 C0 83 F9 ? 74 ? 8B 15 ? ? ? ? 65 48 8B 04 25 ? ? ? ? 41 B8"},
			{"weapon_barrel_create_projectiles","E8 ?? ?? ?? ?? B8 FD FF 00 00 66 21 84 2F B4 01 00 00"},
			{"weapon_get_owner_unit_index","E8 ?? ?? ?? ?? 41 8B C9 44 8B D8"},
			{"game_time_set_rate_scale_direct","65 48 8B 04 25 58 00 00 00 8B 0D ?? ?? ?? ?? F3 0F 5F 05"},
			{"object_try_and_get_and_verify_type","40 53 48 83 EC 20 65 48 8B 04 25 58 00 00 00 8B DA 8B D1"},
			{"game_team_is_enemy","48 83 EC ? 44 8B 05 ? ? ? ? 41 B1"},
			{"director_render","48 8B C4 55 48 8D A8 F8 F6 FF FF"},
			{"screen_res_x","0F B7 05 ? ? ? ? 66 89 41 ? 0F B7 05 ? ? ? ? 66 89 41 ? 0F BF 41"},
			{"screen_res_y","0F B7 05 ? ? ? ? 66 89 41 ? 0F BF 41"},
			{"draw_string_set_font","48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 33 C0"},
			{"draw_string_draw","48 89 5C 24 08 48 89 6C 24 10 56 57 41 56 48 81 EC 30 04 00 00"},
			{"draw_string_set_bounds","48 85 D2 74 58 44 0F BF 4A 02"},
			{"get_screen_bounds","33 C0 89 01 0F B7 05"},
			{"deinit_font_cache","40 53 48 83 EC 20 80 39 00 48 8B D9 74 34 8B 15 ?? ?? ?? ?? 65 48 8B 04 25 58 00 00 00 B9 48 01 00 00"},
			{"draw_quad","4C 8B DC 48 83 EC ? 0F B7 41"},
			{"draw_linestrip_2d","48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 48 8B EC 48 83 EC 60 0F 29 70 E8"},
			{"ai_handle_effect_creation_check","0F 84 88 00 00 00 F3 0F 10 0D"},
			{"data_initialize","48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 44 8B 5C 24 70"}
		};
	};
}