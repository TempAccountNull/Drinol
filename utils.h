#pragma once

namespace utils
{
	std::string check_for_game();
	int string_to_wstring(std::wstring& ws, const std::string& s);
	void init_game_offsets(std::string game);
	inline bool active = true;
}