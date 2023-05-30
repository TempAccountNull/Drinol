#pragma once

namespace halo4
{
	class hooks
	{
	public:
		inline static detour game_in_progress;
		inline static detour hs_print;
		inline static bool redirect_print = false;

		static void init();
		static void deinit();
	};
}
