#pragma once

namespace halo1
{
	class hooks
	{
	public:
		inline static bool redirect_print;
		static void init();
		static void deinit();
	};
}
