#pragma once
#include "halo1_engine.h"

namespace halo1
{
	class offsets
	{
	public:
		inline static bool* bottomless_clip;
		inline static bool* infinite_ammo;
		inline static float* game_ticks_per_second;
		inline static bool* god_mode;
		inline static bool* wireframe;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
		static void init();
	};
}
