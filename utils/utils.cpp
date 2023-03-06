#include "utils.h"

#include <cassert>

#include "games/halo1/halo1.h"

#include "games/halo2/halo2.h"

#if defined _DEBUG
#include <iostream>
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
		break;
	case 3:
		running_game = "Halo 4";
		break;
	case 4:
		running_game = "Halo 2 Anniversary MP (Groundhog)";
		break;
	case 5:
		running_game = "Halo 3: ODST";
		break;
	case 6:
		running_game = "Halo Reach";
		break;
	default:
		assert(game_number <= 6);
	}

#if defined _DEBUG
	std::cout << running_game << " is active." << std::endl;
#endif
}

#if defined _DEBUG
void utils::list_game_base_addresses()
{
	Memcury::Scanner::SetTargetModule("halo1.dll");

	std::cout << "halo 1 " << std::hex << Memcury::PE::GetModuleBase() << std::endl;

	Memcury::Scanner::SetTargetModule("halo2.dll");

	std::cout << "halo 2 " << std::hex << Memcury::PE::GetModuleBase() << std::endl;

	Memcury::Scanner::SetTargetModule("halo3.dll");

	std::cout << "halo 3 " << std::hex << Memcury::PE::GetModuleBase() << std::endl;

	Memcury::Scanner::SetTargetModule("halo4.dll");

	std::cout << "halo 4 " << std::hex << Memcury::PE::GetModuleBase() << std::endl;
}
#endif