#include "halo3_hooks.h"

#include <minhook/include/MinHook.h>

#include "framework.h"

#include "halo3_offsets.h"
#include <spdlog/spdlog.h>

#include "detour.h"

static bool (*game_in_progress_og)();

detour game_in_progress;

static bool game_in_progress_detour()
{
	if (game_in_progress.stub<bool>())
	{
		halo3::offsets::game_init();
		spdlog::info("Halo 3 game is in progress.");
		game_in_progress.disable();
		MH_ApplyQueued();
	}

	return game_in_progress.stub<bool>();
}

void halo3::hooks::init()
{
	game_in_progress.create(reinterpret_cast<uintptr_t>(offsets::game_in_progress), game_in_progress_detour);
	MH_ApplyQueued();
}

void halo3::hooks::deinit()
{
	game_in_progress.disable();
	MH_ApplyQueued();
}