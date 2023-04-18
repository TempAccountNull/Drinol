#include "stdafx.h"

static bool __cdecl game_in_progress_detour()
{
	if (halo4::hooks::game_in_progress.stub<bool>())
	{
		halo4::offsets::game_init();
		spdlog::debug("Halo 4 game is in progress.");
		halo4::hooks::game_in_progress.disable();
		MH_ApplyQueued();
	}

	return halo4::hooks::game_in_progress.stub<bool>();
}

void halo4::hooks::init()
{
	game_in_progress.create(reinterpret_cast<uintptr_t>(offsets::functions::game_in_progress), game_in_progress_detour);

	MH_ApplyQueued();
}

void halo4::hooks::deinit()
{
	game_in_progress.disable();
	MH_ApplyQueued();
}