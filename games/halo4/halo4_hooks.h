#pragma once

namespace halo4
{
	class hooks
	{
	public:
		inline static detour game_in_progress;

		static void init();
		static void deinit();
	};
}
