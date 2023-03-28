#pragma once
#include <string>

class utils
{
public:
	/**
	 * \brief the currently running game.
	 */
	inline static std::string running_game;
	/**
	 * \brief full path of the drinol dll.
	 */
	inline static std::string dll_path;
	/**
	 * \brief initializes game stuff depending on what game got loaded.
	 * \param game_number the id of the game that is running.
	 */
	static void handle_game_init(int game_number);
	/**
	 * \brief deinitializes game stuff depending on what game got loaded.
	 */
	static void handle_game_deinit();
	/**
* \brief Saves the currently running games settings.
*/
	static void save_running_game_settings();
	/**
* \brief Resets the currently running games settings.
*/
	static void reset_running_game_settings();
	/**
	 * \brief debug function for testing stuff.
	 */
	static void test_func();
#if defined _DEBUG
	/**
	 * \brief lists some of the base addresses of the halo game dlls.
	 */
	static void list_game_base_addresses();
	/**
	 * \brief This gets the pointer from TLS
	 * \param game_tls_index The number from the games tls pointer
	 * \param TLSIndex The index of the function/pointer/variable/whatever
	 * \return
	 */
	static uintptr_t get_tls_pointer(unsigned int game_tls_index, int TLSIndex);

#endif
};
