#pragma once
#include <unordered_map>
#include <string>

namespace halo2
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "48 8D 3D ?? ?? ?? ?? 48 89 74 24 30 0F 1F 40 00"},
			{"hs_external_globals", "48 8D 05 ?? ?? ?? ?? 0F 1F 40 00 48 0F BF D3"},
			{"hs_type_names", "48 8D 35 ?? ?? ?? ?? 48 8B 1C C6"}
		};
	};
}