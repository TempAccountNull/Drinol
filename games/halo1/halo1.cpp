#include "halo1.h"

#include <iostream>

#include "halo1_offsets.h"

void halo1::game::init() // Initialize hooks and shit for halo 1
{
	std::cout << "Initializing Halo 1" << std::endl;

	offsets::init();
}

#if defined _DEBUG
void halo1::game::test_function()
{
}

void halo1::game::list_all_hs_globals()
{
	for (engine::hs_external_global* global : offsets::hs_external_globals->globals)
		if (global->address != nullptr) // Check if globals functionality has not been stripped from retail.
		{
			std::cout << "Name: " << global->name << " Address: " << global->address << " Parameter Type:" << offsets::hs_type_names->types[global->param_type] << std::endl;
		}
}

#endif

void* halo1::game::get_global(const char* global_name) // Gets the address of the specified global.
{
	for (const halo1::engine::hs_external_global* global : halo1::offsets::hs_external_globals->globals)
	{
		if (strcmp(global->name, global_name) == 0)
		{
			// bool has been found
			if (global->address != nullptr)
			{
				return global->address;
			}

			throw std::runtime_error("halo1::game::get_global: bool has been found but does not have a working address");
		}
	}

	throw std::runtime_error("halo1::game::get_global:: bool was not found");
}