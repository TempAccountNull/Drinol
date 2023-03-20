#pragma once

namespace halo2
{
	class hooks
	{
	public:
		inline static bool redirect_print; // WIP
		static void init();
		static void deinit();
	};
}
