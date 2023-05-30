#include "stdafx.h"
#include "groundhog_hooks.h"

#include "groundhog_offsets.h"

static bool __cdecl game_in_progress_detour()
{
	if (groundhog::hooks::game_in_progress.stub<bool>())
	{
		groundhog::offsets::game_init();
		spdlog::debug("Halo 2 Anniversary Multiplayer game is in progress.");
		groundhog::hooks::game_in_progress.disable();
		MH_ApplyQueued();
	}

	return groundhog::hooks::game_in_progress.stub<bool>();
}

void groundhog::hooks::init()
{
	game_in_progress.create(reinterpret_cast<uintptr_t>(offsets::functions::game_in_progress), game_in_progress_detour);

	MH_ApplyQueued();
}

void groundhog::hooks::deinit()
{
	game_in_progress.disable();
	MH_ApplyQueued();
}