#include "stdafx.h"
#include "halo3_hooks.h"

#include "halo3.h"
#include "halo3_offsets.h"
#include <random>

#include "utils.h"

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

short ycoord0 = 96;

short xcoord0 = 34;

short ycoord1 = 1140;

short xcoord1 = 1892;

short testx = 96;

short texty = 34;

int test2 = 5;

int test3 = 12;

static void __cdecl director_render_detour()
{
	// Drawing text on screen example
	//ImVec4 crap = gui::SV_RAINBOW(255, 255, 1.0);

	//real_argb_color colour(0.42, 1, 0, 132);
	//halo3::game::render::draw_text("Draw quad test.", 80, 80, 1.0f, colour);

	//short_rectangle2d rect{ ycoord0,xcoord0,ycoord1,xcoord1 };

	//int colour = halo3::game::render::real_argb_color_to_pixel32(&colour);

	//utils::memory::game_call<void>(halo3::offsets::functions::render::draw_quad)(&rect, colour); //rect is coords, colour is pixel32 colour

	//short_point2d point2d{ testx,texty };
	//utils::memory::game_call<void>(halo3::offsets::functions::render::draw_linestrip_2d)(&point2d, test2, test3); //point2d is line coords, test 2 is unimplemented?, test 3 is pixel32 colour

	return halo3::hooks::director_render.stub<void>();
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

	if (halo3::hooks::player_ally_projectiles_only)
	{
		long unit_index = halo3::game::weapon_get_owner_unit_index(weapon_object_index);
		long local_player_unit_index = halo3::game::grab_local_player_unit();
		long local_player_team = halo3::game::get_unit_team(local_player_unit_index);
		int unit_team = halo3::game::get_unit_team(unit_index);
		bool unit_is_enemy = halo3::game::game_team_is_enemy(local_player_team, unit_team);
		if (unit_is_enemy)
		{
			return;
		}
	}

	return halo3::hooks::weapon_barrel_create_projectiles.stub<void>(weapon_object_index, barrel_index, fire_data, unk1, unk2);
}

void halo3::hooks::init()
{
	game_in_progress.create(reinterpret_cast<uintptr_t>(offsets::functions::game::game_in_progress), game_in_progress_detour);

	game_tick.create(reinterpret_cast<uintptr_t>(offsets::functions::game::game_tick), game_tick_detour);

	director_render.create(reinterpret_cast<uintptr_t>(offsets::functions::render::director_render), director_render_detour);

	weapon_barrel_create_projectiles.create(reinterpret_cast<uintptr_t>(offsets::functions::weapons::weapon_barrel_create_projectiles), weapon_barrel_create_projectiles_detour);

	MH_ApplyQueued();
}

void halo3::hooks::deinit()
{
	game_in_progress.disable();
	game_tick.disable();
	director_render.disable();
	weapon_barrel_create_projectiles.disable();
	MH_ApplyQueued();
}