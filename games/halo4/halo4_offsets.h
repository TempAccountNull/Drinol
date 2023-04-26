#pragma once

#include "halo4_engine.h"

namespace halo4
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
			};
		};

		/**
 * \brief offsets to the game functions
 */
		class functions
		{
		public:

			inline static void* game_in_progress;
		};

		/**
 * \brief game global stuff
 */
		class globals
		{
		public:
			inline static engine::s_physics_constants* physics_constants;

			inline static c_restricted_memory* g_restricted_regions;
		};

		static void init();

		/**
		 * \brief This only gets initialized when you are in-game.
		 */
		static void game_init();
	};
}
