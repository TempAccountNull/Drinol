#pragma once

namespace groundhog
{
	class hooks
	{
	public:
		inline static detour game_in_progress;

		static void init();
		static void deinit();
	};
}
