#include "pch.h"
#include "halo3_hooks.h"
#include "halo3_offsets.h"
#include "memory_editing.h"


/// <summary>
/// game_tick
/// </summary>
typedef char(__fastcall* game_tick)();
game_tick game_tick_og = NULL;
game_tick game_tick_pointer = reinterpret_cast<game_tick>(memory::pattern_scan(GetModuleHandle(L"halo3.dll"), halo3::offsets::game_tick));

char __fastcall game_tick_detour(unsigned int a1, __int16 a2, __int64 a3, int a4, __int64 a5)
{
	std::cout << "TICK" << std::endl;

	return game_tick_og();
}

void hook_game_tick()
{
	if (MH_CreateHook(game_tick_pointer, &game_tick_detour, reinterpret_cast<LPVOID*>(&game_tick_og)) != MH_OK)
	{
		throw std::runtime_error("weapon_barrel_create_projectiles hook no worky");
	}
	if (MH_EnableHook(game_tick_pointer) == MH_OK)
	{
		std::cout << "weapon_barrel_create_projectiles Hooked" << std::endl;

	}
}

void unhook_game_tick()
{
	MH_DisableHook(game_tick_pointer);
	MH_RemoveHook(game_tick_pointer);
}


/// <summary>
/// weapon_barrel_create_projectiles
/// </summary>
typedef char(__fastcall* weapon_barrel_create_projectiles)(unsigned int a1, __int16 a2, __int64 a3, int a4, __int64 a5);
weapon_barrel_create_projectiles weapon_barrel_create_projectiles_og = NULL;
weapon_barrel_create_projectiles weapon_barrel_create_projectiles_pointer = reinterpret_cast<weapon_barrel_create_projectiles>(memory::pattern_scan(GetModuleHandle(L"halo3.dll"), halo3::offsets::weapon_barrel_create_projectiles));

char __fastcall weapon_barrel_create_projectiles_detour(unsigned int a1, __int16 a2, __int64 a3, int a4, __int64 a5)
{
	std::cout << "weapon_barrel_create_projectiles: " << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << std::endl;

	return weapon_barrel_create_projectiles_og(a1, a2, a3, a4, a5);
}

void hook_weapon_barrel_create_projectiles()
{
	if (MH_CreateHook(weapon_barrel_create_projectiles_pointer, &weapon_barrel_create_projectiles_detour, reinterpret_cast<LPVOID*>(&weapon_barrel_create_projectiles_og)) != MH_OK)
	{
		throw std::runtime_error("weapon_barrel_create_projectiles hook no worky");
	}
	if (MH_EnableHook(weapon_barrel_create_projectiles_pointer) == MH_OK)
	{
		std::cout << "weapon_barrel_create_projectiles Hooked" << std::endl;
		
	}
}

void unhook_weapon_barrel_create_projectiles()
{
	MH_DisableHook(weapon_barrel_create_projectiles_pointer);
	MH_RemoveHook(weapon_barrel_create_projectiles_pointer);
}

void halo3::hooks::init_hooks()
{
	//hook_weapon_barrel_create_projectiles();
	hook_game_tick();
}

void halo3::hooks::deinit_hooks()
{
	//unhook_weapon_barrel_create_projectiles();
	unhook_game_tick();
}

void halo3::hooks::reinit_hooks()
{
	deinit_hooks();
	Sleep(1000);
	init_hooks();
}