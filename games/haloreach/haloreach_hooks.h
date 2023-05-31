#pragma once

namespace haloreach
{
	class hooks
	{
	public:
		inline static detour game_tick;

		inline static detour weapon_has_infinite_ammo;

		inline static detour hs_null_evaluate2;

		/**
		 * \brief if set to true, will call some functions inside of game_tick then set itself to false.
		 */
		inline static bool do_game_tick_stuff = false;

		inline static bool infinite_ammo = false;
		static void init();
		static void deinit();
	};
}
