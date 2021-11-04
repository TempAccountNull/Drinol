#include "pch.h"
#include "haloreach_offsets.h"

#include "memory_editing.h"

uint8_t* haloreach::offsets::game_update;

uint8_t* haloreach::offsets::game_finish;

void haloreach::offsets::init()
{
	game_update = memory::pattern_scan(GetModuleHandle(L"haloreach.dll"), "48 8b c4 48 89 58 ? 48 89 70 ? 48 89 78 ? 4c 89 70 ? 41 57 48 83 ec ? 8b 05");

	game_finish = memory::pattern_scan(GetModuleHandle(L"haloreach.dll"), "48 83 ec ? 8b 0d ? ? ? ? 45 33 c9 65 48 8b 04 25 ? ? ? ? 41 b8 ? ? ? ? 48 8b 04 c8");
}