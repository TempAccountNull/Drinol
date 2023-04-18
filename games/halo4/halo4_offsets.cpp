#include "stdafx.h"

void halo4::offsets::init()
{
	globals::g_restricted_regions = Memcury::Scanner::FindPattern(sigs::list["g_restricted_regions"].c_str()).RelativeOffset(3).GetAs<c_restricted_memory*>();

	variables::region_member_indexes::physics_constants_member_index = Memcury::Scanner::FindPattern(sigs::list["physics_constants_member_index"].c_str()).RelativeOffset(2).GetAs<int*>();

	functions::game_in_progress = Memcury::Scanner::FindPattern(sigs::list["game_in_progress"].c_str()).RelativeOffset(1).GetAs<void*>();
}

void halo4::offsets::game_init()
{
	globals::physics_constants = static_cast<engine::s_physics_constants*>(game::get_restricted_region_member_address(2, 3, *variables::region_member_indexes::physics_constants_member_index));
}