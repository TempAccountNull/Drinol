#include "stdafx.h"

void halo3odst::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(hs_function_table_aob_sig.c_str()).RelativeOffset(3).Get());

	hs_null_evaluate = game::get_eval_hs_function("voice_set_force_match_configurations");

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(hs_external_globals_aob_sig.c_str()).RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(hs_type_names_aob_sig.c_str()).RelativeOffset(3).Get());

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals and functions, instead of manually defining them like below.
	//Blamscript Globals
	//toggle_hud = static_cast<bool*>(game::get_hs_global("disable_hud"));

	//Blamscript Functions TODO: Figure out a way to call these without crashing the game or having to hook into the main thread of the game.
}