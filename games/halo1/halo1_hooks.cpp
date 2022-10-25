#include "pch.h"
#include "halo1_hooks.h"

#include "halo1_offsets.h"

void halo1::hooks::init_function_calls()
{
	// Declaring these inline does not work! So this function has been made to properly assign these vars.
}

/// <summary>
/// game_update
/// </summary>
typedef char(__fastcall* game_update)(float a1);
inline game_update game_time_update_og = NULL;
inline game_update game_time_update_pointer;

static char __fastcall game_time_update_detour(float a1)
{
	return game_time_update_og(a1);
}

inline void halo1::hooks::hook_game_time_update()
{
	game_time_update_pointer = reinterpret_cast<game_update>(offsets::game_time_update);
	if (MH_CreateHook(game_time_update_pointer, &game_time_update_detour, reinterpret_cast<LPVOID*>(&game_time_update_og)) != MH_OK)
	{
		throw std::runtime_error("game_time_update hook no worky");
	}
	if (MH_EnableHook(game_time_update_pointer) == MH_OK)
	{
		std::cout << "game_time_update Hooked" << std::endl;
	}
}

inline void halo1::hooks::unhook_game_time_update()
{
	MH_DisableHook(game_time_update_pointer);
	MH_RemoveHook(game_time_update_pointer);
}

void halo1::hooks::init_hooks()
{
	hook_game_time_update();
}

void halo1::hooks::deinit_hooks()
{
	unhook_game_time_update();
}

void halo1::hooks::reinit_hooks()
{
	deinit_hooks();
	Sleep(1000);
	init_hooks();
}