#include "stdafx.h"
#include "groundhog.h"

#include "groundhog_hooks.h"
#include "groundhog_offsets.h"
#include "config/config.h"

void groundhog::game::init() // Initialize hooks and shit for Halo 2 Anniversary Multiplayer
{
	spdlog::info("Initializing Halo 2 Anniversary Multiplayer");

	Memcury::Scanner::SetTargetModule("groundhog.dll");

	offsets::init();

	hooks::init();

	//Load Settings
	if (!config::games::halo2_amp::load())
	{
		spdlog::error("Failed to load settings for Halo 2 Anniversary Multiplayer.\nEither the settings file does not exist or something bad has happened!\nYou can ignore this error if you did not save it in the past.");
	}
	else
	{
		spdlog::info("Loaded settings for Halo 2 Anniversary Multiplayer.");
	}

	spdlog::info("Halo 2 Anniversary Multiplayer initialized ☺");
}

#if defined _DEBUG
void groundhog::game::test_function()
{
}
#endif

void groundhog::game::deinit()
{
	hooks::deinit();
	spdlog::info("Uninitialized Halo 2 Anniversary Multiplayer");
}

//void* groundhog::game::get_restricted_region_member_address(int alias_index, int member_index, int index)
//{
//	engine::s_thread_local_storage* tls = reinterpret_cast<engine::s_thread_local_storage*>(utils::memory::get_tls_pointer(L"groundhog.dll"));
//
//	return &tls->g_restricted_address[alias_index][offsets::globals::g_restricted_regions[member_index].m_registered_member[index].offset];
//}