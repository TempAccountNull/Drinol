#pragma once

namespace halo2
{
	class hooks
	{
	public:
		inline static bool redirect_print = true;
		static void init();
		static void deinit();
	};
}
