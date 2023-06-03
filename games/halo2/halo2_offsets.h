#pragma once
#include "halo2_engine.h"

namespace halo2
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
				inline static void* hs_null_evaluate_2;
				inline static uintptr_t hs_macro_function_evaluate;
				inline static uintptr_t hs_return;
				inline static uintptr_t hs_parse;
			};
		};

		/**
		* \brief offsets to variables
		*/
		class variables
		{
		public:
			inline static float** gravity;
		};

		/**
		* \brief offsets to the game functions
		*/
		class functions
		{
		public:

			inline static void* _terminal_printf;
		};

		static void init();
	};
}
