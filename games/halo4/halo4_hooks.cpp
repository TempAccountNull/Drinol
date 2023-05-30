#include "stdafx.h"
#include "halo4_hooks.h"

#include "halo4_offsets.h"

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

static void __fastcall hs_print_detour(const char* a1)
{
	if (halo4::hooks::redirect_print)
	{
		spdlog::info("[halo4] hs_print: {}", a1);
	}

	return halo4::hooks::hs_print.stub<void>(a1);
}

void halo4::hooks::init()
{
	game_in_progress.create(reinterpret_cast<uintptr_t>(offsets::functions::game_in_progress), game_in_progress_detour);

	hs_print.create(reinterpret_cast<uintptr_t>(offsets::functions::hs_print), hs_print_detour);

	MH_ApplyQueued();
}

void halo4::hooks::deinit()
{
	game_in_progress.disable();
	hs_print.disable();
	MH_ApplyQueued();
}