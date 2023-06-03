#pragma once

namespace halo2
{
	class hooks
	{
	public:
		inline static bool redirect_print = false;

		inline static detour hs_null_evaluate2;
		inline static detour terminal_printf;

		static void init();
		static void deinit();
	};
}
