#pragma once
#include <string>

class utils
{
public:
	/**
	 * \brief the currently running game.
	 */
	static inline std::string running_game;
	/**
	 * \brief full path of the drinol dll.
	 */
	static inline std::string dll_path;
	/**
	 * \brief initializes game stuff depending on what game got loaded.
	 * \param game_number the id of the game that is running.
	 */
	static void handle_game_init(int game_number);
#if defined _DEBUG
	/**
	 * \brief lists some of the base addresses of the halo game dlls.
	 */
	static void list_game_base_addresses();
#endif
};
