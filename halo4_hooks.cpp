#include "pch.h"
#include "halo4_hooks.h"
#include "halo4_offsets.h"

/// <summary>
/// game_update
/// </summary>
typedef __int64(__fastcall* game_update)(__int64 a1, float* a2, __int64 a3);
inline game_update game_update_og = NULL;
inline game_update game_update_pointer;

static __int64 __fastcall game_update_detour(int a1, float* a2, __int64 a3)
{
	std::cout << "game_update: " << a1 << " " << a2 << " " << a3 << std::endl;

	return game_update_og(a1, a2, a3);
}

inline void halo4::hooks::hook_game_update()
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

inline void halo4::hooks::unhook_game_update()
{
	MH_DisableHook(game_update_pointer);
	MH_RemoveHook(game_update_pointer);
}

void halo4::hooks::init_hooks()
{
	hook_game_update();
}

void halo4::hooks::deinit_hooks()
{
	unhook_game_update();
}

void halo4::hooks::reinit_hooks()
{
	deinit_hooks();
	Sleep(1000);
	init_hooks();
}