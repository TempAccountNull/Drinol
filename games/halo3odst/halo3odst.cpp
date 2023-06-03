#include "stdafx.h"
#include "halo3odst.h"

#include "halo3odst_engine.h"
#include "halo3odst_hooks.h"
#include "halo3odst_offsets.h"
#include "utils.h"
#include "config/config.h"

void halo3odst::game::init() // Initialize hooks and shit for halo 1
{
	spdlog::info("Initializing Halo 3: ODST");

	Memcury::Scanner::SetTargetModule("halo3odst.dll");

	offsets::init();

	hooks::init();

	//Load Settings
	if (!config::games::halo_3_odst::load())
	{
		spdlog::error("Failed to load settings for Halo 3: ODST.\nEither the settings file does not exist or something bad has happened!\nYou can ignore this error if you did not save it in the past.");
	}
	else
	{
		spdlog::info("Loaded settings for Halo 3: ODST.");
	}

	spdlog::info("Halo 3: ODST initialized ☺");
}

void halo3odst::game::deinit()
{
	hooks::deinit();
	spdlog::info("Uninitialized Halo 3: ODST");
}

#if defined _DEBUG
void halo3odst::game::test_function()
{
}

void halo3odst::game::list_all_hs_functions()
{
	spdlog::info("Printing all eval functions inside the blamscript function table.");
	for (engine::_hs_script_op* function : offsets::blamscript::hs_function_table->table)
	{
		if (function->evaluate_func != nullptr && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate)
		{
			spdlog::info("[HS Function] Return Type: {} Name: {} Offset: 0x{:X}", offsets::blamscript::hs_type_names->types[function->return_type], function->name, utils::memory::get_offset(reinterpret_cast<uintptr_t>(function->evaluate_func)));
		}
	}
	spdlog::info("Finished printing out the functions.");
}

void halo3odst::game::list_all_hs_globals()
{
	spdlog::info("Printing all globals inside the blamscript globals table.");
	for (engine::hs_external_global* global : offsets::blamscript::hs_external_globals->globals)
		if (global->address != nullptr) // Check if globals functionality has not been stripped from retail.
		{
			spdlog::info("[HS Global] Name: {} Offset: 0x{:X} Parameter Type: {}", global->name, utils::memory::get_offset(reinterpret_cast<uintptr_t>(global->address)), offsets::blamscript::hs_type_names->types[global->param_type]);
		}
	spdlog::info("Finished printing out the globals.");
}

#endif

void* halo3odst::game::get_hs_global(const char* global_name) // Gets the address of the specified global.
{
	for (const engine::hs_external_global* global : offsets::blamscript::hs_external_globals->globals)
	{
		if (strcmp(global->name, global_name) == 0)
		{
			// bool has been found
			if (global->address != nullptr)
			{
				return global->address;
			}

			spdlog::error("halo3odst::game::get_global: global has been found but does not have a working address");
			return nullptr;
		}
	}

	spdlog::error("halo3odst::game::get_global:: global was not found");
	return nullptr;
}

void* halo3odst::game::get_eval_hs_function(const char* func_name) // Gets the address of the specified function.
{
	for (const engine::_hs_script_op* function : offsets::blamscript::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr || function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate)
			{
				return function->evaluate_func;
			}

			spdlog::error("halo3odst::game::get_eval_hs_function: function has been found but does not have a working eval function");
			return nullptr;
		}
	}

	spdlog::error("halo3odst::game::get_eval_hs_function:: function was not found");
	return nullptr;
}

void* halo3odst::game::get_hs_function(const char* func_name, int to_skip)
{
	void* eval_function = get_eval_hs_function(func_name); // Get the address of the blamscript functions evaluate function.
	void* function = Memcury::Scanner(eval_function).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, to_skip).RelativeOffset(1).GetAs<void*>(); // Get the function inside of the evaluate function.
	return function;
}