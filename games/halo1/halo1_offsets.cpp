#include "halo1_offsets.h"

#include <iostream>

#include "Memcury/memcury.h"

void halo1::offsets::init()
{
	//TODO: It would be cool if we could use the offset in this aob "48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35" to gather a list of all these global variables and to check if they have not been stripped from retail or not.

	Memcury::Globals::moduleName = "halo1.dll";

	bottomless_clip = Memcury::Scanner::FindPattern("80 3D ?? ?? ?? ?? ?? 48 8B 4C 24 40").RelativeOffset(2).AbsoluteOffset(1).GetAs<bool*>();
	infinite_ammo = Memcury::Scanner::FindPattern("0F B6 05 ?? ?? ?? ?? EB 02 32 C0 88 05").RelativeOffset(3).GetAs<bool*>();
	game_ticks_per_second = Memcury::Scanner::FindPattern("F3 0F 5C 05 ?? ?? ?? ?? F3 0F 2C F8").RelativeOffset(4).GetAs<float*>();
	god_mode = Memcury::Scanner::FindPattern("80 3D ?? ?? ?? ?? ?? 0F 94 C0 88 05 ?? ?? ?? ?? 48 8D 0D").RelativeOffset(2).AbsoluteOffset(1).GetAs<bool*>();
	wireframe = Memcury::Scanner::FindPattern("0F B6 05 ?? ?? ?? ?? F6 D8 1B C9 83 C1 03 39 0D ?? ?? ?? ?? 74 2E").RelativeOffset(3).GetAs<bool*>();

	//Blamscript External Globals Table
	hs_external_globals = Memcury::Scanner::FindPattern("48 8D 1D ?? ?? ?? ?? BF D2 01 00 00 48 8D 35").RelativeOffset(3).GetAs<void*>();

	//Blamscript type names.
	hs_type_names = Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(3).GetAs<void*>();

	// for some reason, game_ticks_per_second is protected from being changed
	DWORD old_prot;
	VirtualProtect((void*)game_ticks_per_second, 4, PAGE_EXECUTE_READWRITE, &old_prot);

	//std::cout << std::hex << Memcury::Scanner::FindPattern("48 8D 35 ?? ?? ?? ?? 4C 8B 0B").RelativeOffset(1).Get() << std::endl;
}