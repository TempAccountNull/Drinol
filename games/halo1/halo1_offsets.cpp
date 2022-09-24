#include "pch.h"
#include "halo1_offsets.h"
#include "memory_editing.h"

uint8_t* halo1::offsets::game_time_update;

uint8_t* halo1::offsets::game_speed_value;

void halo1::offsets::init()
{
	game_time_update = memory::pattern_scan(GetModuleHandle(L"halo1.dll"), "E8 ? ? ? ? E8 ? ? ? ? 0F BF 15 ? ? ? ?") + 1;
	game_speed_value = memory::pattern_scan(GetModuleHandle(L"halo1.dll"), "F3 0F 10 0D ? ? ? ? 0F 2E C8");
}