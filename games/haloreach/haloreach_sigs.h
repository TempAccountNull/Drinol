#pragma once

namespace haloreach
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "4C 8D 35 ?? ?? ?? ?? 33 DB 49 8B FE"},
			{"hs_external_globals", "48 8D 1D ?? ?? ?? ?? BF BC 06 00 00 4C 8B 0B"},
			{"hs_type_names", "48 8D 05 ?? ?? ?? ?? 4D 8B 09"},
			{"player_mapping_get_unit_by_output_user","8B 84 88 C8 00 00 00"},
			{"game_tick","B8 C0 D7 00 00"},
			{"weapon_has_infinite_ammo","41 84 D3 74 05"}
		};
	};
}