#pragma once
#include <unordered_map>
#include <string>

namespace halo4
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"game_in_progress","E8 ?? ?? ?? ?? 84 C0 74 34 E8 ?? ?? ?? ?? 84 C0 74 2B E8"},
			{"g_restricted_regions","48 8D 2D ?? ?? ?? ?? 48 98 48 8D 15"},
			{"physics_constants_member_index","89 05 ?? ?? ?? ?? 48 98 4C 8B 04 D1 BA 00 00 80 3F"}
		};
	};
}