#include "stdafx.h"
#include "haloreach.h"

#include "haloreach_hooks.h"
#include "haloreach_offsets.h"
#include "utils.h"
#include "config/config.h"
#include "games/haloreach/haloreach_engine.h"

void haloreach::game::init() // Initialize hooks and shit for halo 1
{
	spdlog::info("Initializing Halo Reach");

	Memcury::Scanner::SetTargetModule("haloreach.dll");

	offsets::init();

	hooks::init();

	//Load Settings
	if (!config::games::halo_reach::load())
	{
		spdlog::error("Failed to load settings for Halo Reach.\nEither the settings file does not exist or something bad has happened!\nYou can ignore this error if you did not save it in the past.");
	}
	else
	{
		spdlog::info("Loaded settings for Halo Reach.");
	}

	spdlog::info("Halo Reach initialized ☺");
}

void haloreach::game::deinit()
{
	hooks::deinit();
	spdlog::info("Uninitialized Halo Reach");
}

#if defined _DEBUG
void haloreach::game::test_function()
{
	engine::hs_function_definition* hack_func = get_hs_function("chud_post_message_HACK");

	engine::hs_function_definition* print_func = get_hs_function("print");

	utils::memory::swap_table_pointer(&print_func->evaluate_func, &hack_func->evaluate_func);
}

void haloreach::game::list_all_hs_functions()
{
	spdlog::info("Printing all eval functions inside the blamscript function table.");
	for (engine::hs_function_definition* function : offsets::blamscript::hs_function_table->table)
	{
		if (function->evaluate_func != nullptr && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate2)
		{
			spdlog::info("[HS Function] Return Type: {} Name: {} Offset: 0x{:X}", offsets::blamscript::hs_type_names->types[function->return_type], function->name, utils::memory::get_offset(reinterpret_cast<uintptr_t>(function->evaluate_func)));
		}
	}
	spdlog::info("Finished printing out the functions.");
}

void haloreach::game::list_all_hs_globals()
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

void* haloreach::game::get_hs_global(const char* global_name) // Gets the address of the specified global.
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

			spdlog::error("haloreach::game::get_global: global has been found but does not have a working address");
			return nullptr;
		}
	}

	spdlog::error("haloreach::game::get_global:: global was not found");
	return nullptr;
}

void* haloreach::game::get_eval_hs_function(const char* func_name) // Gets the address of the specified function.
{
	for (const engine::hs_function_definition* function : offsets::blamscript::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr || function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate)
			{
				return function->evaluate_func;
			}

			spdlog::error("haloreach::game::get_eval_hs_function: function has been found but does not have a working eval function");
			return nullptr;
		}
	}

	spdlog::error("haloreach::game::get_eval_hs_function:: function was not found");
	return nullptr;
}

haloreach::engine::hs_function_definition* haloreach::game::get_hs_function(const char* func_name) // Gets the address of the specified function.
{
	for (engine::hs_function_definition* function : offsets::blamscript::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr || function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate)
			{
				return function;
			}

			spdlog::error("haloreach::game::get_hs_function: function has been found but does not have a working eval function");
			return nullptr;
		}
	}

	spdlog::error("haloreach::game::get_hs_function:: function was not found");
	return nullptr;
}

void* haloreach::game::get_eval_hs_function_address(const char* func_name, int to_skip)
{
	void* eval_function = get_eval_hs_function(func_name); // Get the address of the blamscript functions evaluate function.
	void* function = Memcury::Scanner(eval_function).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, to_skip).RelativeOffset(1).GetAs<void*>(); // Get the function inside of the evaluate function.
	return function;
}

long haloreach::game::player_mapping_get_unit_by_output_user(unsigned int output_user_index)
{
	return utils::memory::game_call<long>(offsets::functions::player_mapping_get_unit_by_output_user)(output_user_index);
}