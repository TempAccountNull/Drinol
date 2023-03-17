#include "halo1.h"

#include <cinttypes>

#include "halo1_hooks.h"
#include "halo1_offsets.h"
#include "memcury/memcury.h"

void halo1::game::init() // Initialize hooks and shit for halo 1
{
	puts("Initializing Halo 1");

	Memcury::Scanner::SetTargetModule("halo1.dll");

	offsets::init();

	hooks::init();
}

void halo1::game::deinit()
{
	hooks::deinit();
	puts("Uninitialized Halo 1");
}

#if defined _DEBUG
void halo1::game::test_function()
{
}

void halo1::game::list_all_hs_functions()
{
	for (engine::hs_script_op* function : offsets::hs_function_table->table)
	{
		printf("Return Type: %s Name: %s Address: 0x%" PRIXPTR "\n", offsets::hs_type_names->types[function->return_type], function->name, reinterpret_cast<uintptr_t>(function->evaluate_func));
	}
}

void halo1::game::list_all_hs_globals()
{
	for (engine::hs_external_global* global : offsets::hs_external_globals->globals)
		if (global->address != nullptr) // Check if globals functionality has not been stripped from retail.
		{
			printf("Name: %s Address: 0x%" PRIXPTR " Parameter Type: %s \n", global->name, reinterpret_cast<uintptr_t>(global->address), offsets::hs_type_names->types[global->param_type]);
		}
}

#endif

void* halo1::game::get_hs_global(const char* global_name) // Gets the address of the specified global.
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

			throw std::runtime_error("halo1::game::get_global: global has been found but does not have a working address");
		}
	}

	throw std::runtime_error("halo1::game::get_global:: global was not found");
}

void* halo1::game::get_hs_function(const char* func_name) // Gets the address of the specified function.
{
	for (const engine::hs_script_op* function : offsets::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr)
			{
				return function->evaluate_func;
			}

			throw std::runtime_error("halo1::game::get_hs_function: function has been found but does not have a working address");
		}
	}

	throw std::runtime_error("halo1::game::get_hs_function:: function was not found");
}