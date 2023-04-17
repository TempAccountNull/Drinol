#include "stdafx.h"

void halo4::game::init() // Initialize hooks and shit for halo 1
{
	spdlog::info("Initializing halo 4");

	Memcury::Scanner::SetTargetModule("halo4.dll");

	offsets::init();
}

#if defined _DEBUG
void halo4::game::test_function()
{
}
#endif

void halo4::game::deinit()
{
	spdlog::info("Uninitialized Halo 4");
}