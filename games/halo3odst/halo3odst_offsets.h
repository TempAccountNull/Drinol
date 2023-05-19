#pragma once
#include "games/halo3odst/halo3odst_engine.h"

namespace halo3odst
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
			};
		};

		static void init();
	};
}
