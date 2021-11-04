#include "pch.h"
#include "haloreach_hooks.h"

#include "haloreach_offsets.h"

/// <summary>
/// game_update
/// </summary>
typedef char(__fastcall* game_update)(int a1, float near* a2);
inline game_update game_update_og = NULL;
inline game_update game_update_pointer;

static char __fastcall game_update_detour(int a1, float near* a2)
{
	std::cout << "game_update: " << a1 << " " << a2 << std::endl;

	return game_update_og(a1, a2);
}

inline void haloreach::hooks::hook_game_update()
{
	game_update_pointer = reinterpret_cast<game_update>(offsets::game_update);
	if (MH_CreateHook(game_update_pointer, &game_update_detour, reinterpret_cast<LPVOID*>(&game_update_og)) != MH_OK)
	{
		throw std::runtime_error("game_update hook no worky");
	}
	if (MH_EnableHook(game_update_pointer) == MH_OK)
	{
		std::cout << "game_update Hooked" << std::endl;
	}
}

inline void haloreach::hooks::unhook_game_update()
{
	MH_DisableHook(game_update_pointer);
	MH_RemoveHook(game_update_pointer);
}

void haloreach::hooks::init_hooks()
{
	hook_game_update();
}

void haloreach::hooks::deinit_hooks()
{
	unhook_game_update();
}

void haloreach::hooks::reinit_hooks()
{
	deinit_hooks();
	Sleep(1000);
	init_hooks();
}