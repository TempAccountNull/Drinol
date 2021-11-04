#pragma once

namespace halo3
{
	class hooks
	{
	public:
		static void init_hooks();
		static void deinit_hooks();
		static void reinit_hooks();
	};
}