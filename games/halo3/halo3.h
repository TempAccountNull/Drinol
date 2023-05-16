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
		 * \brief Gets the player mapping constants/globals
		 * \return a struct containing them
		 */
		static s_player_mapping_globals* player_mapping_globals_get();
		/**
		 * \brief Gets an array of the players
		 * \return
		 */
		static engine::s_data_array* player_data_get();
		static halo3::engine::player_datum* local_player_datum_get();
		/**
		 * \brief Gets the handle of your local players unit.
		 * \return
		 */
		static unsigned long grab_local_player_unit();
		/**
		 * \brief Does tings
		 * \param index
		 * \return
		 */
		static void object_scripting_cannot_die(int object_handle, bool cannot_die);
		/**
		 * \brief Lets you change the games speed.
		 * \param speed
		 */
		static void game_time_set_rate_scale_direct(float speed);

		/**
		 * \brief Grabs the address from the restricted region member
		 * \param alias_index
		 * \param member_index
		 * \param index
		 * \return
		 */
		static void* get_restricted_region_member_address(int alias_index, int member_index, int index);
		/**
		 * \brief Gets the unit index from the weapon index
		 * \param weapon_index
		 * \return
		 */
		static long weapon_get_owner_unit_index(long weapon_index);

		/**
 * \brief Gets a handle of an object
 * \return object handle
 */
 //static uintptr_t get_object(int object_index);

#if defined _DEBUG
		static void list_all_hs_functions();
		static void list_all_hs_globals();
#endif
		/**
		 * \brief the games speed
		 */
		static inline float game_speed;
	};
}
