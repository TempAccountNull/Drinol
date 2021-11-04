#include "pch.h"
#include "halo3_hooks.h"
#include "halo3_offsets.h"

/// <summary>
/// game_update
/// </summary>
typedef char(__fastcall* game_update)(int a1, float* a2);
game_update game_update_og = NULL;
game_update game_update_pointer;

char __fastcall game_update_detour(int a1, float* a2)
{
	std::cout << "game_update: " << a1 << " " << a2 << std::endl;

	return game_update_og(a1, a2);
}

void hook_game_update()
{
	game_update_pointer = reinterpret_cast<game_update>(halo3::offsets::game_update);
	if (MH_CreateHook(game_update_pointer, &game_update_detour, reinterpret_cast<LPVOID*>(&game_update_og)) != MH_OK)
	{
		throw std::runtime_error("game_update hook no worky");
	}
	if (MH_EnableHook(game_update_pointer) == MH_OK)
	{
		std::cout << "game_update Hooked" << std::endl;
	}
}

void unhook_game_update()
{
	MH_DisableHook(game_update_pointer);
	MH_RemoveHook(game_update_pointer);
}

void halo3::hooks::init_hooks()
{
	hook_game_update();
}

void halo3::hooks::deinit_hooks()
{
	unhook_game_update();
}

void halo3::hooks::reinit_hooks()
{
	deinit_hooks();
	Sleep(1000);
	init_hooks();
}