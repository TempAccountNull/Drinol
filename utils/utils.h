#pragma once
#include <string>
#include <Windows.h>

class utils
{
public:
	static inline std::string running_game;
	static inline std::string dll_path; // Path of the drinol dll.
	static void handle_game_init(int game_number);
};
