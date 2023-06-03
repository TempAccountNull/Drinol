#pragma once

namespace halo2
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"hs_function_table", "48 8D 3D ?? ?? ?? ?? 48 89 74 24 30 0F 1F 40 00"},
			{"hs_external_globals", "48 8D 05 ?? ?? ?? ?? 0F 1F 40 00 48 0F BF D3"},
			{"hs_type_names", "48 8D 35 ?? ?? ?? ?? 48 8B 1C C6"},
			{"hs_macro_function_evaluate","48 0F BF C1 44 8B D2"},
			{"hs_return","48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B 05 ?? ?? ?? ?? 8B DA"},
			{"hs_parse","48 8B 15 ?? ?? ?? ?? 48 85 D2 75 38"}
		};
	};
}