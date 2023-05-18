#pragma once

namespace halo3
{
	class hooks
	{
	public:
		inline static detour game_in_progress;

		inline static detour game_tick;

		inline static detour weapon_barrel_create_projectiles;

		inline static detour director_render;

		inline static bool game_tick_test = false;
		inline static bool player_weapon_projectiles_only;
		inline static bool player_ally_projectiles_only;
		static void init();
		static void deinit();
	};
}
