#pragma once
#include "games/haloreach/haloreach_engine.h"

namespace haloreach
{
	class offsets
	{
	public:
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
				inline static uintptr_t hs_macro_function_evaluate;
				inline static uintptr_t hs_return;
				inline static uintptr_t hs_parse;
			};
		};

		/**
 * \brief offsets to the game functions
 */
		class functions
		{
		public:
			inline static uintptr_t player_mapping_get_unit_by_output_user;
			inline static uintptr_t game_tick;
			inline static uintptr_t weapon_has_infinite_ammo;
		};

		static void init();
	};
}
