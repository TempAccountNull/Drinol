#include "stdafx.h"

void halo4::game::init() // Initialize hooks and shit for halo 1
{
	spdlog::info("Initializing Halo 4");

	Memcury::Scanner::SetTargetModule("halo4.dll");

	offsets::init();

	hooks::init();

	//Load Settings
	if (!config::halo4_load())
	{
		spdlog::error("Failed to load settings for Halo 4.\nEither the settings file does not exist or something bad has happened!\nYou can ignore this error if you did not save it in the past.");
	}
	else
	{
		spdlog::info("Loaded settings for Halo 4.");
	}

	spdlog::info("Halo 4 initialized ☺");
}

#if defined _DEBUG
void halo4::game::test_function()
{
}
#endif

void halo4::game::deinit()
{
	hooks::deinit();
	spdlog::info("Uninitialized Halo 4");
}

void* halo4::game::get_restricted_region_member_address(int alias_index, int member_index, int index)
{
	engine::s_thread_local_storage* tls = reinterpret_cast<engine::s_thread_local_storage*>(utils::get_tls_pointer(L"halo4.dll"));

	return &tls->g_restricted_address[alias_index][offsets::globals::g_restricted_regions[member_index].m_registered_member[index].offset];
}