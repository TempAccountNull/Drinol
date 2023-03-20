#include "halo2_offsets.h"

#include "halo2.h"
#include "Memcury/memcury.h"

void halo2::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(hs_function_table_aob_sig.c_str()).RelativeOffset(3).Get());

	hs_null_evaluate = game::get_hs_function("data_mine_display_session_data");
	hs_null_evaluate2 = game::get_hs_function("core_save_name");

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(hs_external_globals_aob_sig.c_str()).RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(hs_type_names_aob_sig.c_str()).RelativeOffset(3).Get());

	//TODO: it would be nice to dynamically fill the imgui menu with all possible globals and functions, instead of manually defining them like below.
	//Blamscript Globals
	toggle_hud = static_cast<bool*>(game::get_hs_global("disable_hud"));

	//Print function
	void* hs_print_address = Memcury::Scanner::FindStringRef("get achievement: %i").GetAs<void*>();
	_terminal_printf = Memcury::Scanner(hs_print_address).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, 0).RelativeOffset(1).GetAs<void*>();

	//Blamscript Functions TODO: Figure out a way to call these without crashing the game or having to hook into the main thread of the game.
}