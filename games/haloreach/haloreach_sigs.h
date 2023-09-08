#pragma once

namespace haloreach
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "4C 8D 35 ?? ?? ?? ?? 33 DB 49 8B FE"},
			{"hs_external_globals", "48 8D 1D ?? ?? ?? ?? BF ?? ?? ?? ?? 48 8B 0B 48 8B 09"},
			{"hs_type_names", "48 8D 05 ?? ?? ?? ?? 4D 8B 09"},
			{"player_mapping_get_unit_by_output_user","8B 84 88 C8 00 00 00"},
			{"game_tick","B8 C0 D7 00 00"},
			{"weapon_has_infinite_ammo","41 84 D3 74 05"},
			{"hs_macro_function_evaluate","48 89 5C 24 08 48 89 6C 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 83 EC 30 45 8A F9"},
			{"hs_return","48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 8B EA 8B F1 E8 ?? ?? ?? ?? 4C 8B C8"},
			{"hs_parse","48 8B 15 ?? ?? ?? ?? 48 85 D2 75 22"}
		};
	};
}