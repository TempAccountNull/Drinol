#include "halo3_offsets.h"

#include "halo3.h"
#include "Memcury/memcury.h"
#include <utils.h>

void halo3::offsets::init()
{
	//Blamscript Functions Table
	hs_function_table = reinterpret_cast<engine::_hs_function_table*>(Memcury::Scanner::FindPattern(hs_function_table_aob_sig.c_str()).RelativeOffset(3).Get());

	hs_null_evaluate = game::get_eval_hs_function("voice_set_force_match_configurations");

	//Blamscript External Globals Table
	hs_external_globals = reinterpret_cast<engine::_hs_external_globals*>(Memcury::Scanner::FindPattern(hs_external_globals_aob_sig.c_str()).RelativeOffset(3).Get());
	motion_blur_expected_dt = static_cast<float*>(game::get_hs_global("motion_blur_expected_dt"));
	motion_blur_taps = static_cast<int*>(game::get_hs_global("motion_blur_taps"));
	motion_blur_max_x = static_cast<float*>(game::get_hs_global("motion_blur_max_x"));
	motion_blur_max_y = static_cast<float*>(game::get_hs_global("motion_blur_max_y"));
	motion_blur_scale_x = static_cast<float*>(game::get_hs_global("motion_blur_scale_x"));
	motion_blur_scale_y = static_cast<float*>(game::get_hs_global("motion_blur_scale_y"));
	motion_blur_center_falloff = static_cast<float*>(game::get_hs_global("motion_blur_center_falloff"));

	//Blamscript type names.
	hs_type_names = reinterpret_cast<engine::_hs_type_names*>(Memcury::Scanner::FindPattern(hs_type_names_aob_sig.c_str()).RelativeOffset(3).Get());

	game_in_progress = Memcury::Scanner::FindPattern(game_in_progress_aob_sig.c_str()).RelativeOffset(1).GetAs<void*>();
}

void halo3::offsets::game_init()
{
	//physics_constants = *reinterpret_cast<engine::physics_constants*>(utils::get_tls_pointer(*tls_index, 304));
}

//[2023 - 03 - 28 04:22 : 44.214][info] motion_blur_expected_dt: 0.03
//[2023 - 03 - 28 04:22 : 44.214][info] motion_blur_taps : 6
//[2023 - 03 - 28 04:22 : 44.214][info] motion_blur_max_x : 0.03
//[2023 - 03 - 28 04:22 : 44.214][info] motion_blur_max_y : 0.05
//[2023 - 03 - 28 04:22 : 44.215][info] motion_blur_scale_x : 0.05
//[2023 - 03 - 28 04:22 : 44.215][info] motion_blur_scale_y : 0.15
//[2023 - 03 - 28 04:22 : 44.215][info] motion_blur_center_falloff : 1.4