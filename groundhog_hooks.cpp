#include "pch.h"
#include "groundhog_hooks.h"

#include "groundhog_offsets.h"
#include "ui.h"

/// <summary>
/// game_time_set_rate_scale_direct
/// </summary>
typedef __int64(__fastcall* game_time_set_rate_scale_direct)(float a1);
static inline game_time_set_rate_scale_direct game_time_set_rate_scale_direct_og = nullptr;

void groundhog::hooks::init_function_calls()
{
	// Declaring these inline does not work! So this function has been made to properly assign these vars.
	game_time_set_rate_scale_direct_og = reinterpret_cast<game_time_set_rate_scale_direct>(reinterpret_cast<char*>(groundhog::offsets::game_time_set_rate_scale_direct));
}

/// <summary>
/// game_update
/// </summary>
typedef char(__fastcall* game_update)(int a1, float* a2);
inline game_update game_update_og = NULL;
inline game_update game_update_pointer;

static char __fastcall game_update_detour(int a1, float* a2)
{
	if (groundhog::hooks::change_speed)
	{
		game_time_set_rate_scale_direct_og(ui::game_speed);

		groundhog::hooks::change_speed = false;
	}

	return game_update_og(a1, a2);
}

inline void groundhog::hooks::hook_game_update()
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

inline void groundhog::hooks::unhook_game_update()
{
	MH_DisableHook(game_update_pointer);
	MH_RemoveHook(game_update_pointer);
}

void groundhog::hooks::init_hooks()
{
	hook_game_update();
}

void groundhog::hooks::deinit_hooks()
{
	unhook_game_update();
}

void groundhog::hooks::reinit_hooks()
{
	deinit_hooks();
	Sleep(1000);
	init_hooks();
}