#pragma once

namespace halo3
{
	class hooks
	{
	public:
		inline static bool game_tick_test = false;
		inline static bool player_weapon_projectiles_only;
		static void init();
		static void deinit();
	};
}
