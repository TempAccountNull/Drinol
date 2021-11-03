#pragma once

namespace utils
{
	std::string check_for_game();
	int string_to_wstring(std::wstring& ws, const std::string& s);
	inline bool active = true;
}