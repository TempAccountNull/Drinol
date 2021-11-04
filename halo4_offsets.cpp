#include "pch.h"
#include "halo4_offsets.h"

#include "memory_editing.h"

uint8_t* halo4::offsets::game_update;

void halo4::offsets::init()
{
	game_update = memory::pattern_scan(GetModuleHandle(L"halo4.dll"), "48 89 5c 24 ? 48 89 6c 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 ec ? 8b 05 ? ? ? ? 4c 8b fa");
}