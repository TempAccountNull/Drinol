#include "halo3_hooks.h"

#include <minhook/include/MinHook.h>

#include "framework.h"
#include "halo3_offsets.h"
#include <spdlog/spdlog.h>

static bool (*game_in_progress_og)();

static bool game_in_progress_detour()
{
	if (game_in_progress_og())
	{
		halo3::offsets::game_init();
		MH_QueueDisableHook(halo3::offsets::game_in_progress);
		MH_ApplyQueued();
	}

	return game_in_progress_og();
}

void halo3::hooks::init()
{
	MH_STATUS game_in_progress_hook = MH_CreateHook(offsets::game_in_progress, &game_in_progress_detour, reinterpret_cast <LPVOID*> (&game_in_progress_og));
	if (game_in_progress_hook != MH_OK) {
		spdlog::error("Error hooking game_in_progress: {}", static_cast<int>(game_in_progress_hook));
	}

	MH_QueueEnableHook(offsets::game_in_progress);
	MH_ApplyQueued();
}

void halo3::hooks::deinit()
{
	MH_QueueDisableHook(offsets::game_in_progress);
	MH_ApplyQueued();
}