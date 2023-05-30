#include "stdafx.h"
#include "halo4_offsets.h"

#include "halo4_sigs.h"
#include "games/engine.h"

void halo4::offsets::init()
{
	spdlog::debug("Halo 4: Pattern scanning for: g_restricted_regions");
	globals::g_restricted_regions = Memcury::Scanner::FindPattern(sigs::list["g_restricted_regions"].c_str()).RelativeOffset(3).GetAs<c_restricted_memory*>();

	spdlog::debug("Halo 4: Pattern scanning for: physics_constants_member_index");
	variables::region_member_indexes::physics_constants_member_index = Memcury::Scanner::FindPattern(sigs::list["physics_constants_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	spdlog::debug("Halo 4: Pattern scanning for: game_in_progress");
	functions::game_in_progress = Memcury::Scanner::FindPattern(sigs::list["game_in_progress"].c_str()).RelativeOffset(1).GetAs<void*>();

	spdlog::debug("Halo 4: Pattern scanning for: hs_print");
	functions::hs_print = Memcury::Scanner::FindPattern(sigs::list["hs_print"].c_str()).GetAs<void*>();
}

void halo4::offsets::game_init()
{
	//TODO: HOOK GAME IN PROGRESS AND FIX THIS
	//globals::physics_constants = static_cast<engine::s_physics_constants*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::physics_constants_member_index));
}