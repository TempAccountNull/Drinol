#pragma once
#include <string>

class utils
{
public:
	static inline std::string running_game;
	static inline std::string dll_path; // Path of the drinol dll.
	static void handle_game_init(int game_number);
#if defined _DEBUG
	static void list_game_base_addresses();
#endif
};
