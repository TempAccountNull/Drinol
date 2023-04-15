#pragma once
#include <string>

#include "halo2_engine.h"
#include "Memcury/memcury.h"

namespace halo2
{
	class offsets
	{
	public:
		inline static engine::_hs_function_table* hs_function_table;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
		inline static void* hs_null_evaluate;
		inline static void* _terminal_printf;
		inline static float** gravity;

		static void init();
	};
}
