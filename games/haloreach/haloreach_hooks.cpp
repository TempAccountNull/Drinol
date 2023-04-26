#include "stdafx.h"

static void __cdecl game_tick_detour()
{
	if (haloreach::hooks::do_game_tick_stuff)
	{
		for (int i = 0; i < 16; i++) {
			long ass = haloreach::game::player_mapping_get_unit_by_output_user(i);

			if (ass != -1)
			{
				//do sghit here
			}
		}

		haloreach::hooks::do_game_tick_stuff = false;
	}
	return haloreach::hooks::game_tick.stub<void>();
}

static bool __cdecl weapon_has_infinite_ammo_detour(unsigned __int16 a1)
{
	if (haloreach::hooks::infinite_ammo)
	{
		return true;
	}
	return haloreach::hooks::weapon_has_infinite_ammo.stub<bool>(a1);
}

void haloreach::hooks::init()
{
	game_tick.create(offsets::functions::game_tick, game_tick_detour);
	weapon_has_infinite_ammo.create(offsets::functions::weapon_has_infinite_ammo, weapon_has_infinite_ammo_detour);

	MH_ApplyQueued();
}

void haloreach::hooks::deinit()
{
	game_tick.disable();
	weapon_has_infinite_ammo.disable();
	MH_ApplyQueued();
}