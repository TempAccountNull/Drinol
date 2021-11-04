#pragma once

namespace groundhog
{
	class hooks
	{
	public:
		static void hook_game_update();
		static void unhook_game_update();
		static void init_hooks();
		static void deinit_hooks();
		static void reinit_hooks();
	};
}