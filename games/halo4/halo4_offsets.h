#pragma once
namespace halo4
{
	class offsets
	{
	public:
		static uint8_t* game_update;
		static uint8_t* game_time_set_rate_scale_direct;
		static void init();
	};
}
