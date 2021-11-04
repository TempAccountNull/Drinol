#include "pch.h"
#include "haloreach_offsets.h"

#include "memory_editing.h"

uint8_t* haloreach::offsets::game_update;

void haloreach::offsets::init()
{
	game_update = memory::pattern_scan(GetModuleHandle(L"haloreach.dll"), "48 8b c4 48 89 58 ? 48 89 70 ? 48 89 78 ? 4c 89 70 ? 41 57 48 83 ec ? 8b 05");
}