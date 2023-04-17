#pragma once
#include <string>

#include "haloreach_engine.h"

namespace haloreach
{
	class offsets
	{
	public:
		/**
 * \brief blamscript related functions ,tables, etc
 */
		class blamscript
		{
		public:
			inline static engine::_hs_function_table* hs_function_table;
			inline static engine::_hs_type_names* hs_type_names;
			inline static engine::_hs_external_globals* hs_external_globals;

			class functions
			{
			public:
				inline static void* hs_null_evaluate;
				inline static void* hs_null_evaluate2;
			};
		};

		static void init();
	};
}
