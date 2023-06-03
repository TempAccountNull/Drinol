#include "stdafx.h"
#include "halo3odst_offsets.h"

#include "halo3odst.h"
#include "halo3odst_engine.h"
#include "halo3odst_sigs.h"

void halo3odst::offsets::init()
{
	//Blamscript Functions Table
	spdlog::debug("Halo 3 ODST: Pattern scanning for: hs_function_table");
	blamscript::hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(sigs::list["hs_function_table"].c_str()).RelativeOffset(3).Get());

	blamscript::functions::hs_null_evaluate = game::get_eval_hs_function("voice_set_force_match_configurations");

	//Blamscript External Globals Table
	spdlog::debug("Halo 3 ODST: Pattern scanning for: hs_external_globals");
	blamscript::hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(sigs::list["hs_external_globals"].c_str()).RelativeOffset(3).Get());

	//Blamscript type names.
	spdlog::debug("Halo 3 ODST: Pattern scanning for: hs_type_names");
	blamscript::hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).Get());

	spdlog::debug("Halo 3 ODST: Pattern scanning for: terminal_printf");
	functions::game::terminal_printf = Memcury::Scanner::FindPattern(sigs::list["terminal_printf"].c_str()).GetAs<void*>();

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals and functions, instead of manually defining them like below.
	//Blamscript Globals
	//toggle_hud = static_cast<bool*>(game::get_hs_global("disable_hud"));

	//Blamscript Functions TODO: Figure out a way to call these without crashing the game or having to hook into the main thread of the game.
}