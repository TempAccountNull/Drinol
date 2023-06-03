#include "stdafx.h"
#include "halo2_offsets.h"

#include "halo2.h"
#include "halo2_sigs.h"

void halo2::offsets::init()
{
	//Blamscript Functions Table
	spdlog::debug("Halo 2: Pattern scanning for: hs_function_table");
	blamscript::hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(sigs::list["hs_function_table"].c_str()).RelativeOffset(3).Get());

	blamscript::functions::hs_null_evaluate = game::get_eval_hs_function("data_mine_display_session_data");

	blamscript::functions::hs_null_evaluate_2 = game::get_eval_hs_function("print");

	//Blamscript External Globals Table
	spdlog::debug("Halo 2: Pattern scanning for: hs_external_globals");
	blamscript::hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(sigs::list["hs_external_globals"].c_str()).RelativeOffset(3).Get());

	//Blamscript type names.
	spdlog::debug("Halo 2: Pattern scanning for: hs_type_names");
	blamscript::hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(sigs::list["hs_type_names"].c_str()).RelativeOffset(3).Get());

	//_terminal_printf engine function
	spdlog::debug("Halo 2: Finding string: 'get achievement: %i'");
	void* terminal_printf_call_address = Memcury::Scanner::FindStringRef("get achievement: %i").GetAs<void*>();
	functions::_terminal_printf = Memcury::Scanner(terminal_printf_call_address).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, 0).RelativeOffset(1).GetAs<void*>();

	//Blamscript type names.
	spdlog::debug("Halo 2: Pattern scanning for: hs_macro_function_evaluate");
	blamscript::functions::hs_macro_function_evaluate = Memcury::Scanner::FindPattern(sigs::list["hs_macro_function_evaluate"].c_str()).Get();

	//Blamscript type names.
	spdlog::debug("Halo 2: Pattern scanning for: hs_return");
	blamscript::functions::hs_return = Memcury::Scanner::FindPattern(sigs::list["hs_return"].c_str()).Get();

	//Blamscript type names.
	spdlog::debug("Halo 2: Pattern scanning for: hs_parse");
	blamscript::functions::hs_parse = Memcury::Scanner::FindPattern(sigs::list["hs_parse"].c_str()).Get();

	variables::gravity = Memcury::Scanner(game::get_hs_function("physics_set_gravity")).RelativeOffset(11).GetAs<float**>();
}