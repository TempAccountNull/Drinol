#pragma once
#include <string>

#include "halo3_engine.h"
#include "Memcury/memcury.h"

namespace halo3
{
	class offsets
	{
	public:
		inline static engine::_hs_function_table* hs_function_table;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
		inline static void* hs_null_evaluate;
		inline static bool* toggle_hud;
		inline static void* game_in_progress;
		inline static std::string tls_index_aob_sig;
		inline static std::string game_in_progress_aob_sig;
		inline static std::string hs_function_table_aob_sig;
		inline static std::string hs_external_globals_aob_sig;
		inline static std::string hs_type_names_aob_sig;
		inline static engine::physics_constants physics_constants;
		inline static float* motion_blur_scale_y;
		inline static float* motion_blur_scale_x;
		inline static float* motion_blur_max_y;
		inline static float* motion_blur_max_x;
		inline static int* motion_blur_taps;
		inline static float* motion_blur_center_falloff;
		inline static float* motion_blur_expected_dt;
		/**
		 * \brief This only gets initialized when you are in-game.
		 */
		static void game_init();

		static void init();
	};
}
