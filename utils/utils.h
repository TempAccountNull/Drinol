#pragma once
#include <string>

class utils
{
public:

	class games
	{
	public:
		inline static int current_game_number = -1;

		/**
		 * \brief list of games
		 */
		enum e_games
		{
			halo1 = 0,
			halo2,
			halo3,
			halo4,
			groundhog,
			halo3odst,
			haloreach,
		};
	};

	/**
	 * \brief full path of the drinol dll.
	 */
	inline static std::string dll_path;
	/**
	 * \brief the handle of the drinol dll
	 */
	inline static HINSTANCE dll_module;

	inline static int detach_keybind = 0x23;
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

#if defined _DEBUG

	/**
 * \brief debug function for testing stuff.
 */
	static void test_func(int test_int = 0);

#endif

	/**
	 * \brief Detaches drinol.
	 */
	static void detach();
	/**
	 * \brief A message that pops up on the first use of drinol, that warns the user not to use this tool to gain an unfair advantage.
	 */
	static void cheat_nag();

	class memory
	{
	public:
		/**
		 * \brief
		 * \tparam T Type Cast
		 * \param Calls a function from inside the game. GameCall<uintptr_t>(0x00);
		 * \return
		 */
		template <class T>
		static inline T(*game_call(uintptr_t address))(...)
		{
			auto func = reinterpret_cast<T(*)(...)>(address);
			return func;
		}

		/**
	* \brief This gets the pointer from TLS
	* \param module_name the name of the dll/exe that you want to get the pointer from
	* \param TLSFunctionIndex The index of the function/pointer/variable/whatever
	* \return the tls pointer
	*/
		static char* get_tls_pointer(LPCWSTR module_name, int TLSFunctionIndex = NULL);

		/**
		 * \brief Patches bytes, nuff said.
		 * \param dst
		 * \param src
		 * \param size
		 */
		static void patch(BYTE* dst, BYTE* src, unsigned int size);

		/**
		 * \brief Reads bytes from a memory address and stores them into stored_bytes
		 * \return the bytes, fool
		 */
		static void store_memory_bytes(BYTE* stored_bytes, void* src_address, unsigned size);

#if defined _DEBUG
		static uintptr_t get_offset(uintptr_t address);

		/**
		 * \brief Prints the tls pointer of your currently running game, it will change so its best to pause the game so the address stays still, then suspend the mcc process.
		 */
		static void print_game_tls_pointer();

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
	};
};
