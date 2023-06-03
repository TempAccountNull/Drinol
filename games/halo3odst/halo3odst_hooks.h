#pragma once

namespace halo3odst
{
	class hooks
	{
	public:
		inline static bool redirect_print;

		inline static detour terminal_printf;

		static void init();
		static void deinit();
	};
}
