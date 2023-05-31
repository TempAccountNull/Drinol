#include "stdafx.h"
#include "haloreach_hooks.h"

#include "haloreach.h"
#include "haloreach_offsets.h"
#include "utils.h"

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

void __fastcall hs_null_evaluate2_detour(__int16 a1, unsigned int a2, char a3)
{
	//*((_WORD *)hs_function_table[a1] + 28)
	//(__int64)hs_function_table[a1] + 58
	int* weirdint = utils::memory::game_call<int*>(haloreach::offsets::functions::hs_macro_function_evaluate)(a2, *(reinterpret_cast<WORD*>(haloreach::offsets::blamscript::hs_function_table->table[a1]) + 0x1C), reinterpret_cast<__int64>(haloreach::offsets::blamscript::hs_function_table->table[a1]) + 0x3A, a3);

	if (weirdint)
	{
		if (char* crap = utils::memory::game_call<char*>(haloreach::offsets::functions::hs_parse)(weirdint))
		{
			spdlog::info("[haloreach] Print: {}", crap);

			utils::memory::game_call<void>(haloreach::offsets::functions::hs_return)(a2, 0);
		}
	}
}

void haloreach::hooks::init()
{
	game_tick.create(offsets::functions::game_tick, game_tick_detour);
	weapon_has_infinite_ammo.create(offsets::functions::weapon_has_infinite_ammo, weapon_has_infinite_ammo_detour);
	hs_null_evaluate2.create(uintptr_t(offsets::blamscript::functions::hs_null_evaluate2), hs_null_evaluate2_detour);

	MH_ApplyQueued();
}

void haloreach::hooks::deinit()
{
	game_tick.disable();
	weapon_has_infinite_ammo.disable();
	hs_null_evaluate2.disable();
	MH_ApplyQueued();
}