#pragma once
#include <unordered_map>
#include <string>

namespace middleware
{
	class sigs
	{
	public:
		static inline std::unordered_map<std::string, std::string> list = {
			{"start_game_engine_t", "83 FF 06 77 1A"},
			{"UICommandOverlayPush_t", "41 83 C9 FF 4C 8B C5"}
		};
	};
}