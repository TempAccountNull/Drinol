#pragma once
#include "halo3_engine.h"

namespace halo3
{
	class game
	{
	public:
		static void init();
		static void deinit();
		/**
		 * \brief gets the address of a global that is used in the blamscript/haloscript scripting system.
		 * \param global_name the name of the global.
		 * \return the globals address
		 */
		static void* get_hs_global(const char* global_name);
		/**
		 * \brief gets the evaluate function address of a function that is used in the blamscript/haloscript scripting system.
		 * \param func_name the name of the function.
		 * \return the functions address
		 */
		static void* get_eval_hs_function(const char* func_name);
		/**
* \brief gets the address of a function that is used in the blamscript/haloscript scripting system.
* \param func_name the name of the function.
* \param to_skip call instructions to skip (Change this if you are getting the wrong function address!)
* \return the functions address
*/
		static void* get_hs_function(const char* func_name, int to_skip = 1);
		/**
		 * \brief Gets the physics constants/globals
		 * \return a struct containing them
		 */
		static engine::s_physics_constants* global_physics_constants_get();

		/**
 * \brief Gets a handle of an object
 * \return object handle
 */
		static uintptr_t get_object(int object_index);

#if defined _DEBUG
		static void list_all_hs_functions();
		static void list_all_hs_globals();
#endif
	};
}
