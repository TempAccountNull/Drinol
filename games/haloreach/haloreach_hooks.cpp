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

void __fastcall hs_null_evaluate2_detour(__int16 function_index, unsigned int a2, char a3)
{
	if (haloreach::hooks::redirect_print)
	{
		if (function_index != 40) // Do not execute if the function_index does not equal hs_print. (will cause crashes otherwise!)
			return haloreach::hooks::hs_null_evaluate2.stub<void>(function_index, a2, a3);

		int* weirdint = utils::memory::game_call<int*>(haloreach::offsets::blamscript::functions::hs_macro_function_evaluate)(a2, *(reinterpret_cast<WORD*>(haloreach::offsets::blamscript::hs_function_table->table[function_index]) + 0x1C), reinterpret_cast<__int64>(haloreach::offsets::blamscript::hs_function_table->table[function_index]) + 0x3A, a3);

		if (!weirdint)
			return haloreach::hooks::hs_null_evaluate2.stub<void>(function_index, a2, a3);

		char* crap = utils::memory::game_call<char*>(haloreach::offsets::blamscript::functions::hs_parse)(weirdint);

		if (crap)
		{
			spdlog::info("[haloreach] Print: {}", crap);

			utils::memory::game_call<void>(haloreach::offsets::blamscript::functions::hs_return)(a2, 0);
		}
	}
	else
	{
		return haloreach::hooks::hs_null_evaluate2.stub<void>(function_index, a2, a3);
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