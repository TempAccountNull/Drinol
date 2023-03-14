#pragma once
#include <string>

#include "haloreach_engine.h"

namespace haloreach
{
	class offsets
	{
	public:
		inline static engine::_hs_function_table* hs_function_table;
		inline static engine::_hs_external_globals* hs_external_globals;
		inline static engine::_hs_type_names* hs_type_names;
		inline static void* hs_null_evaluate;
		inline static bool* toggle_hud;
		inline static std::string hs_function_table_aob_sig;
		inline static std::string hs_external_globals_aob_sig;
		inline static std::string hs_type_names_aob_sig;

		static void init();
	};
}
