#pragma once

namespace halo1
{
	class game
	{
	public:
		static void init();
		static void* get_global(const char* global_name);
#if defined _DEBUG
		static void test_function();
		static void list_all_hs_globals();
#endif
	};
}
