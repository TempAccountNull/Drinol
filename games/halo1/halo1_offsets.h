#pragma once
#include "Memcury/memcury.h"

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
		inline static void* hs_external_globals;
		inline static void* hs_type_names;
		static void init();
	};
}
