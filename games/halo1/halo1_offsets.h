#pragma once
#include <string>

#include "halo1_engine.h"
#include "Memcury/memcury.h"

namespace halo1
{
	class offsets
	{
	public:
		inline static engine::_hs_function_table* hs_function_table;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
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
		inline static std::string hs_function_table_aob_sig;
		inline static std::string hs_external_globals_aob_sig;
		inline static std::string hs_type_names_aob_sig;
		inline static std::string game_ticks_per_second_aob_sig;
		inline static void* _terminal_printf;

		static void init();
	};
}
