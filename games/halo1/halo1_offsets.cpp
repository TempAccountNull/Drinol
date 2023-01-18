#include "pch.h"
#include "halo1_offsets.h"
#include "memory_editing.h"

uint8_t* halo1::offsets::game_time_update;

float* halo1::offsets::game_speed_value;

uint8_t* halo1::offsets::infinite_grenades;

uint8_t* halo1::offsets::bottomless_clip;

char* halo1::offsets::infinite_ammo;

uint8_t* halo1::offsets::no_weapon_projectiles;

void halo1::offsets::init()
{
	HMODULE baseaddress = GetModuleHandle(L"halo1.dll");
	game_time_update = memory::pattern_scan(baseaddress, "48 8B C4 55 56 57 41 56 48 8D");
	bottomless_clip = memory::pattern_scan(baseaddress, "80 3D ?? ?? ?? ?? ?? 48 8B 4C 24 40"); //80 3D ?? ?? ?? ?? ?? 48 8B 4C 24 40 (in cs:)
	infinite_ammo = reinterpret_cast<char*>(memory::pattern_scan(baseaddress, "80 3D ?? ?? ?? ?? ?? 48 8B 4C 24 40") + 1); //0F B6 05 ?? ?? ?? ?? EB 02 32 C0 88 05
	no_weapon_projectiles = memory::pattern_scan(baseaddress, "E8 ?? ?? ?? ?? 45 0F B7 44 24 2E"); //nop these to work
	game_speed_value = reinterpret_cast<float*>(reinterpret_cast<UINT_PTR>(baseaddress) + 0x1CDA5E4); // F3 0F 10 0D ?? ?? ?? ?? 0F 2E C8 TODO: fix this optimization error shit
}