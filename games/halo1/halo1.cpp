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
	auto hs_external_globals = static_cast<char***>(offsets::hs_external_globals);
	auto hs_type_names = static_cast<char**>(offsets::hs_type_names);

	int i = 465; // This number is the amount of globals in the table, this could change if 343 adds anything new!

	while (i)
	{
		std::cout << "Table Address: " << std::hex << *hs_external_globals << " Name: " << *(*hs_external_globals) << " Type Name: " << hs_type_names[*(reinterpret_cast<int*>(*hs_external_globals) + 2)] << std::endl;
		++hs_external_globals;
		--i;
	}

	std::cout << "Table Address: " << std::hex << *hs_external_globals << " Name: " << *(*hs_external_globals) << " Type Name: " << hs_type_names[*(reinterpret_cast<int*>(*hs_external_globals) + 2)] << std::endl; // This is so the last table entry does not get ignored for some reaosn.
}

void halo1::game::list_all_hs_globals()
{
	auto hs_external_globals = static_cast<char***>(offsets::hs_external_globals);
	auto hs_type_names = static_cast<char**>(offsets::hs_type_names);

	int i = 465; // This number is the amount of globals in the table, this could change if 343 adds anything new!

	while (i)
	{
		std::cout << "Table Address: " << std::hex << *hs_external_globals << " Name: " << *(*hs_external_globals) << " Type Name: " << hs_type_names[*(reinterpret_cast<int*>(*hs_external_globals) + 2)] << std::endl;
		++hs_external_globals;
		--i;
	}

	std::cout << "Table Address: " << std::hex << *hs_external_globals << " Name: " << *(*hs_external_globals) << " Type Name: " << hs_type_names[*(reinterpret_cast<int*>(*hs_external_globals) + 2)] << std::endl; // This is so the last table entry does not get ignored for some reaosn.
}

#endif