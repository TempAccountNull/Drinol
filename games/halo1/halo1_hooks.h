#pragma once

namespace halo1
{
	class hooks
	{
	public:
		static void hook_game_time_update();
		static void unhook_game_time_update();
		static void init_hooks();
		static void deinit_hooks();
		static void reinit_hooks();
		static void init_function_calls();
		static inline bool change_speed = false;
	};
}