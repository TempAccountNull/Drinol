#pragma once
#include <string>
#include <framework.h>

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
* \brief Loads the currently running games settings.
*/
	static void load_running_game_settings();
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
	 * \brief backtraces a function
	 * \param func
	 */
	static void backtrace(const char* func);
#endif
	/**
 * \brief This gets the pointer from TLS
 * \param module_name the name of the dll/exe that you want to get the pointer from
 * \param TLSFunctionIndex The index of the function/pointer/variable/whatever
 * \return
 */
	static char* get_tls_pointer(LPCWSTR module_name, int TLSFunctionIndex);
};
