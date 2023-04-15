#include "stdafx.h"

void halo2::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(sigs::list["hs_function_table"].c_str()).RelativeOffset(3).Get());

	hs_null_evaluate = game::get_eval_hs_function("data_mine_display_session_data");

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(sigs::list["hs_external_globals"].c_str()).RelativeOffset(3).Get());

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).Get());

	//_terminal_printf engine function
	void* terminal_printf_call_address = Memcury::Scanner::FindStringRef("get achievement: %i").GetAs<void*>();
	_terminal_printf = Memcury::Scanner(terminal_printf_call_address).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, 0).RelativeOffset(1).GetAs<void*>();

	gravity = Memcury::Scanner(game::get_hs_function("physics_set_gravity")).RelativeOffset(11).GetAs<float**>();
}