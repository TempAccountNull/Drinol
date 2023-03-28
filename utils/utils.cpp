#include "utils.h"

#include <cassert>

#include "games/halo1/halo1.h"

#include "games/halo2/halo2.h"

#include "games/halo3/halo3.h"

#include "games/halo3odst/halo3odst.h"
#include "games/haloreach/haloreach.h"

#if defined _DEBUG
#include "Memcury/memcury.h"
#endif

#include "config/config.h"
#include "spdlog/spdlog.h"

#include "ntpebteb.h"
#include "games/halo3/halo3_offsets.h"

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
	spdlog::debug("{} is active.", running_game.c_str());
#endif
}

void utils::handle_game_deinit()
{
	if (running_game == "Halo 1 Anniversary")
	{
		halo1::game::deinit();
		return;
	}

	if (running_game == "Halo 2 Anniversary")
	{
		halo2::game::deinit();
		return;
	}

	if (running_game == "Halo 3")
	{
		halo3::game::deinit();
		return;
	}
}

// Saves the currently running games settings.
void utils::save_running_game_settings()
{
	if (running_game == "Halo 1 Anniversary")
	{
		if (config::halo1_save())
		{
			spdlog::info("Saved settings for Halo 1!");
			return;
		}
	}

	if (running_game == "Halo 2 Anniversary")
	{
		if (config::halo2_save())
		{
			spdlog::info("Saved settings for Halo 2!");
			return;
		}
	}
}

void utils::reset_running_game_settings()
{
	if (running_game == "Halo 1 Anniversary")
	{
		if (!config::halo1_create())
		{
			spdlog::error("Failed to create fresh settings for Halo 1!");
			return;
		}
		if (!config::halo1_load())
		{
			spdlog::error("Failed to load fresh settings for Halo 1!");
			return;
		}

		spdlog::info("Reset settings for Halo 1");
	}

	if (running_game == "Halo 2 Anniversary")
	{
		if (!config::halo2_create())
		{
			spdlog::error("Failed to create fresh settings for Halo 2!");
			return;
		}
		if (!config::halo2_load())
		{
			spdlog::error("Failed to load fresh settings for Halo 2!");
			return;
		}

		spdlog::info("Reset settings for Halo 2");
	}
}

void utils::test_func()
{
	if (!*halo3::offsets::tls_index)
		spdlog::error("Error, shit happened");

	//uintptr_t aaa = *(INT64*)(*((INT64*)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)*halo3::offsets::tls_index) + 304i64);

	//spdlog::info("Correct Struct Pointer: {:x}", aaa);

	//uintptr_t aaa2 = utils::get_tls_pointer(*halo3::offsets::tls_index, 304);

	//spdlog::info("Struct Pointer: {:x}", aaa2);

	//halo3::engine::physics_constants physics_constants = *reinterpret_cast<halo3::engine::physics_constants*>(utils::get_tls_pointer(*halo3::offsets::tls_index, 304));

	//if (!physics_constants.gravity)
	//{
	//	spdlog::error("physics_constant not working");
	//	return;
	//}

	//spdlog::info("Gravity: {:f}", physics_constants.gravity);

	bool crap = false;

	BYTE* v1 = reinterpret_cast<BYTE*>(get_tls_pointer(*halo3::offsets::tls_index, 72));
	if (v1 && v1[0xFB70] && !*v1)
		crap = v1[1] != 0;

	spdlog::info("Crap = {}", crap);
}

#if defined _DEBUG
void utils::list_game_base_addresses()
{
	Memcury::Scanner::SetTargetModule("halo1.dll");

	spdlog::debug("Halo 1 base : {}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo2.dll");

	spdlog::debug("Halo 2 base : {}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo3.dll");

	spdlog::debug("Halo 3 base : {}", Memcury::PE::GetModuleBase());

	Memcury::Scanner::SetTargetModule("halo4.dll");

	spdlog::debug("Halo 4 base : {}", Memcury::PE::GetModuleBase());
}

#endif

uintptr_t utils::get_tls_pointer(unsigned int game_tls_index, int TLSIndex)
{
	uintptr_t addr = *(INT64*)(*((INT64*)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)game_tls_index) + TLSIndex);
	return addr;
}