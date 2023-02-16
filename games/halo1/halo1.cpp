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
			std::cout << "Name: " << global->name << " Address: " << global->address << " Parameter Type: " << offsets::hs_type_names->types[global->param_type] << std::endl;
		}
}

#endif