#pragma once
#include <unordered_map>
#include <string>

namespace halo1
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "48 8D 1D ?? ?? ?? ?? 48 8D 35 ?? ?? ?? ?? 48 89 7C 24 30"},
			{"hs_external_globals", "48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35"},
			{"hs_type_names", "48 8D 35 ? ? ? ? ? ? ? ? 4C 8B 0B"},
			{"game_ticks_per_second","F3 0F 5C 05 ?? ?? ?? ?? F3 0F 2C F8" }
		};
	};
}