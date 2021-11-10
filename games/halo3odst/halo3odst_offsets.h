#pragma once
namespace halo3odst
{
	class offsets
	{
	public:
		static uint8_t* game_update;
		static uint8_t* game_time_get_speed;
		static uint8_t* game_time_set_rate_scale_direct;
		static void init();
	};
}
