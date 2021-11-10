#include "pch.h"
#include "halo3odst_offsets.h"

#include "memory_editing.h"

uint8_t* halo3odst::offsets::game_update;

uint8_t* halo3odst::offsets::game_time_set_rate_scale_direct;

void halo3odst::offsets::init()
{
	game_update = memory::pattern_scan(GetModuleHandle(L"halo3odst.dll"), "48 8b c4 48 89 58 ? 48 89 70 ? 48 89 78 ? 4c 89 70 ? 41 57 48 83 ec ? 8b 05 ? ? ? ? 4c 8b f2");
	game_time_set_rate_scale_direct = memory::pattern_scan(GetModuleHandle(L"halo3odst.dll"), "f3 0f 5f 05 ? ? ? ? 65 48 8b 04 25");
}
