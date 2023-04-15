#pragma once
#include <unordered_map>
#include <string>

namespace halo3odst
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "48 8D 35 ?? ?? ?? ?? 48 8B D5"},
			{"hs_external_globals", "48 8D 1D ?? ?? ?? ?? 4C 8B 59 48"},
			{"hs_type_names", "48 8D 05 ?? ?? ?? ?? 4D 8B 09"}
		};
	};
}