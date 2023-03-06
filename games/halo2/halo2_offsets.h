#pragma once
#include "halo2_engine.h"

namespace halo2
{
	class offsets
	{
	public:
		inline static engine::_hs_function_table* hs_function_table;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
		inline static bool* toggle_hud;

		static void init();
	};
}
