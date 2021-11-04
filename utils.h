#pragma once

namespace utils
{
	inline std::string current_game;
	void check_for_game();
	int string_to_wstring(std::wstring& ws, const std::string& s);
	void init_game(std::string game);
	inline bool active = true;
}