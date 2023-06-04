#include "stdafx.h"
#include "groundhog_offsets.h"

#include "groundhog.h"
#include "groundhog_sigs.h"
#include "games/engine.h"

void groundhog::offsets::init()
{
	spdlog::debug("Halo 2 Anniversary Multiplayer: Pattern scanning for: hs_print");
	functions::hs_print = Memcury::Scanner::FindPattern(sigs::list["hs_print"].c_str()).GetAs<void*>();

	spdlog::debug("Halo 2 Anniversary Multiplayer: Pattern scanning for: game_in_progress");
	functions::game_in_progress = Memcury::Scanner::FindPattern(sigs::list["game_in_progress"].c_str()).RelativeOffset(1).GetAs<void*>();
}

void groundhog::offsets::game_init()
{
	game::settings_init();
	//TODO: HOOK GAME IN PROGRESS AND FIX THIS
	//globals::physics_constants = static_cast<engine::s_physics_constants*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::physics_constants_member_index));
}