#pragma once
#include "games/halo3/halo3_engine.h"

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
				inline static int* game_globals_member_index;
				inline static int* player_control_globals_member_index;
				inline static int* game_allegiance_globals_member_index;
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
 * \brief if statments that need to be nopped out, etc
 */
		class patches
		{
		public:
			/**
			 * \brief Nop this for allowing ai to spawn through effects.
			 */
			inline static void* ai_handle_effect_creation_check;
			inline static BYTE* ai_handle_effect_creation_check_og_bytes = new BYTE[0x06];
		};

		/**
		 * \brief offsets to the game functions
		 */
		class functions
		{
		public:

			class game
			{
			public:
				inline static void* game_in_progress;
				inline static void* game_tick;
				inline static void* terminal_printf;
				inline static uintptr_t game_time_set_rate_scale_direct;
				inline static uintptr_t game_team_is_enemy;
			};

			class render
			{
			public:
				inline static void* director_render;
				inline static uintptr_t draw_quad;
				inline static uintptr_t draw_string_set_font;
				inline static uintptr_t draw_string_draw;
				inline static uintptr_t draw_string_set_bounds;
				inline static uintptr_t get_screen_bounds;
				inline static uintptr_t font_cache_init;
				inline static uintptr_t deinit_font_cache;
				inline static uintptr_t draw_linestrip_2d;
				inline static uintptr_t draw_string_init;
			};

			class weapons
			{
			public:
				inline static void* weapon_barrel_create_projectiles;
				inline static uintptr_t weapon_get_owner_unit_index;
			};

			class objects
			{
			public:
				inline static uintptr_t object_scripting_cannot_die;
				inline static uintptr_t object_try_and_get_and_verify_type;
			};

			class data
			{
			public:
				inline static void* data_initialize;
			};
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
			inline static engine::s_data_array* players_globals;
			inline static engine::s_data_array* players_header;

			inline static c_restricted_memory* g_restricted_regions;
			inline static engine::game_time_globals_definition* game_time_globals;
			inline static engine::s_game_globals* game_globals;
			inline static engine::s_player_control_globals* player_control_globals;
			inline static engine::game_allegiance_globals* game_allegiance_globals;
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
