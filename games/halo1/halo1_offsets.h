#pragma once

#include "halo1_engine.h"

namespace halo1
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

			inline static bool* bottomless_clip;
			inline static bool* infinite_ammo;
			inline static float* game_ticks_per_second;
			inline static bool* god_mode;
			inline static bool* wireframe;
			inline static bool* enviroment_diffuse;
			inline static bool* atmosphere_fog;
			inline static bool* fog_plane;
			inline static bool* fps_counter;
			inline static bool* motion_sensor_show_all_units;
			inline static float** gravity;
		};

		/**
		* \brief offsets to the game functions
		*/
		class functions
		{
		public:

			inline static void* _terminal_printf;
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
		};

		static void init();
	};
}
