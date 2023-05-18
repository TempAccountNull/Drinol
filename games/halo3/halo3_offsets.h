#pragma once

#include "halo3_engine.h"

namespace halo3
{
	class offsets
	{
	public:

		/**
		 * \brief offsets to variables
		 */
		class variables
		{
		public:
			class region_member_indexes
			{
			public:
				inline static int* physics_constants_member_index;
				inline static int* player_mapping_globals_member_index;
				inline static int* player_data_member_index;
				inline static int* game_time_globals_member_index;
			};

			inline static float* motion_blur_scale_y;
			inline static float* motion_blur_scale_x;
			inline static float* motion_blur_max_y;
			inline static float* motion_blur_max_x;
			inline static int* motion_blur_taps;
			inline static float* motion_blur_center_falloff;
			inline static float* motion_blur_expected_dt;
			inline static int* screen_res_x;
			inline static int* screen_res_y;
		};

		/**
		 * \brief offsets to the game functions
		 */
		class functions
		{
		public:

			inline static void* game_in_progress;
			inline static void* game_tick;

			inline static uintptr_t object_scripting_cannot_die;
			inline static void* weapon_barrel_create_projectiles;
			inline static uintptr_t weapon_get_owner_unit_index;
			inline static uintptr_t game_time_set_rate_scale_direct;
			inline static uintptr_t object_try_and_get_and_verify_type;
			inline static uintptr_t game_team_is_enemy;
			inline static  void* director_render;
		};

		/**
		 * \brief blamscript related functions ,tables, etc
		 */
		class blamscript
		{
		public:
			inline static engine::_hs_function_table* hs_function_table;
			inline static engine::_hs_type_names* hs_type_names;
			inline static engine::_hs_external_globals* hs_external_globals;

			class functions
			{
			public:
				inline static void* hs_null_evaluate;
				inline static void* hs_null_evaluate2;
			};
		};

		/**
		 * \brief game global stuff
		 */
		class globals
		{
		public:
			inline static engine::s_physics_constants* physics_constants;
			inline static s_player_mapping_globals* player_mapping_globals;
			inline static engine::s_data_array* player_data;

			inline static c_restricted_memory* g_restricted_regions;
			inline static engine::game_time_globals_definition* game_time_globals;
		};

	public:
		static uintptr_t get_game_address(uintptr_t rva);

		/**
		 * \brief This only gets initialized when you are in-game.
		 */
		static void game_init();

		static void init();
	};
}
