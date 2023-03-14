#include "utils.h"

#include <cassert>
#include <cinttypes>

#include "games/halo1/halo1.h"

#include "games/halo2/halo2.h"

#include "games/halo3/halo3.h"

#include "games/halo3odst/halo3odst.h"
#include "games/haloreach/haloreach.h"

#if defined _DEBUG
#include "Memcury/memcury.h"
#endif

void utils::handle_game_init(int game_number)
{
	switch (game_number) {
	case 0:
		running_game = "Halo 1 Anniversary";
		halo1::game::init();
		break;
	case 1:
		running_game = "Halo 2 Anniversary";
		halo2::game::init();
		break;
	case 2:
		running_game = "Halo 3";
		halo3::game::init();
		break;
	case 3:
		running_game = "Halo 4";
		break;
	case 4:
		running_game = "Halo 2 Anniversary MP (Groundhog)";
		break;
	case 5:
		running_game = "Halo 3: ODST";
		halo3odst::game::init();
		break;
	case 6:
		running_game = "Halo Reach";
		haloreach::game::init();
		break;
	default:
		assert(game_number <= 6);
	}

#if defined _DEBUG
	printf("%s is active.\n", running_game.c_str());
#endif
}

#if defined _DEBUG
void utils::list_game_base_addresses()
{
	Memcury::Scanner::SetTargetModule("halo1.dll");

	printf("Halo 1 base : 0x%" PRIXPTR "\n", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo2.dll");

	printf("Halo 2 base : 0x%" PRIXPTR "\n", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo3.dll");

	printf("Halo 3 base : 0x%" PRIXPTR "\n", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo4.dll");

	printf("Halo 4 base : 0x%" PRIXPTR "\n", Memcury::PE::GetModuleBase());
}

void utils::handle_game_deinit()
{
	if (running_game == "Halo 1 Anniversary")
	{
		halo1::game::deinit();
		puts("Halo 1 Uninitialized");
	}
}
#endif