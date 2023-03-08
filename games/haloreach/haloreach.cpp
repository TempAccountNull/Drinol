#include "haloreach.h"

#include <iostream>

#include "haloreach_offsets.h"
#include "memcury/memcury.h"

void haloreach::game::init() // Initialize hooks and shit for halo 1
{
	std::cout << "Initializing Halo Reach" << std::endl;

	Memcury::Scanner::SetTargetModule("haloreach.dll");

	offsets::init();
}

#if defined _DEBUG
void haloreach::game::test_function()
{
}

void haloreach::game::list_all_hs_functions()
{
	for (engine::_hs_script_op* function : offsets::hs_function_table->table)
	{
		if (function->evaluate_func != nullptr && function->evaluate_func != offsets::hs_null_evaluate)
		{
			std::cout << "Return Type: " << offsets::hs_type_names->types[function->return_type] << " Name: " << function->name << " Address: " << std::hex << function->evaluate_func << std::endl;
		}
	}
}

void haloreach::game::list_all_hs_globals()
{
	for (engine::hs_external_global* global : offsets::hs_external_globals->globals)
		if (global->address != nullptr) // Check if globals functionality has not been stripped from retail.
		{
			std::cout << "Name: " << global->name << " Address: " << global->address << " Parameter Type:" << offsets::hs_type_names->types[global->param_type] << std::endl;
		}
}

#endif

void* haloreach::game::get_hs_global(const char* global_name) // Gets the address of the specified global.
{
	for (const engine::hs_external_global* global : offsets::hs_external_globals->globals)
	{
		if (strcmp(global->name, global_name) == 0)
		{
			// bool has been found
			if (global->address != nullptr)
			{
				return global->address;
			}

			throw std::runtime_error("haloreach::game::get_global: global has been found but does not have a working address");
		}
	}

	throw std::runtime_error("haloreach::game::get_global:: global was not found");
}

void* haloreach::game::get_hs_function(const char* func_name) // Gets the address of the specified function.
{
	for (const engine::_hs_script_op* function : offsets::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr || function->evaluate_func != offsets::hs_null_evaluate)
			{
				return function->evaluate_func;
			}

			throw std::runtime_error("haloreach::game::get_hs_function: function has been found but does not have a working address");
		}
	}

	throw std::runtime_error("haloreach::game::get_hs_function:: function was not found");
}