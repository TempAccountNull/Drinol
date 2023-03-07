#pragma once
#include "halo3_engine.h"

namespace halo3
{
	class offsets
	{
	public:
		inline static engine::_hs_function_table* hs_function_table;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
		inline static void* hs_null_evaluate;
		inline static bool* toggle_hud;

		static void init();
	};
}
