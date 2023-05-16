#include "stdafx.h"

static bool __cdecl game_in_progress_detour()
{
	if (halo3::hooks::game_in_progress.stub<bool>())
	{
		halo3::offsets::game_init();
		spdlog::debug("Halo 3 game is in progress.");
		halo3::hooks::game_in_progress.disable();
		MH_ApplyQueued();
	}

	return halo3::hooks::game_in_progress.stub<bool>();
}

static void __cdecl game_tick_detour()
{
	if (halo3::hooks::game_tick_test)
	{
		halo3::game::game_time_set_rate_scale_direct(halo3::game::game_speed);
		halo3::hooks::game_tick_test = false;
	}

	return halo3::hooks::game_tick.stub<void>();
}

void __cdecl weapon_barrel_create_projectiles_detour(long weapon_object_index, short barrel_index, struct s_predicted_weapon_fire_data const* fire_data, long unk1, bool unk2)
{
	if (halo3::hooks::player_weapon_projectiles_only)
	{
		long unit_index = halo3::game::weapon_get_owner_unit_index(weapon_object_index);
		long local_player_unit_index = halo3::game::grab_local_player_unit();
		if (local_player_unit_index != unit_index)
		{
			return;
		}
	}

	return halo3::hooks::weapon_barrel_create_projectiles.stub<void>(weapon_object_index, barrel_index, fire_data, unk1, unk2);
}

void halo3::hooks::init()
{
	game_in_progress.create(reinterpret_cast<uintptr_t>(offsets::functions::game_in_progress), game_in_progress_detour);

	game_tick.create(reinterpret_cast<uintptr_t>(offsets::functions::game_tick), game_tick_detour);

	weapon_barrel_create_projectiles.create(reinterpret_cast<uintptr_t>(offsets::functions::weapon_barrel_create_projectiles), weapon_barrel_create_projectiles_detour);

	MH_ApplyQueued();
}

void halo3::hooks::deinit()
{
	game_in_progress.disable();
	game_tick.disable();
	weapon_barrel_create_projectiles.disable();
	MH_ApplyQueued();
}