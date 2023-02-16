#pragma once

namespace halo1
{
	class game
	{
	public:
		static void init();
#if defined _DEBUG
		static void test_function();
		static void list_all_hs_globals();
#endif
	};
}
