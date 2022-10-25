#pragma once
namespace halo1
{
	class offsets
	{
	public:
		static uint8_t* game_time_update;
		static float* game_speed_value;
		static uint8_t* infinite_grenades;
		static uint8_t* bottomless_clip;
		static uint8_t* infinite_ammo;
		static uint8_t* no_weapon_projectiles;
		static void init();
	};
}
