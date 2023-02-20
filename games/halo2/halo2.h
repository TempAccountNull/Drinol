#pragma once

namespace halo2
{
	class game
	{
	public:
		static void init();
		static void* get_hs_global(const char* global_name);
		static void* get_hs_function(const char* func_name);
#if defined _DEBUG
		static void test_function();
		static void list_all_hs_functions();
		static void list_all_hs_globals();
#endif
	};
}
