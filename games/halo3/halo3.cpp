#include "stdafx.h"
#include "halo3.h"

#include "halo3_hooks.h"
#include "halo3_offsets.h"
#include "utils.h"
#include "config/config.h"

void halo3::game::init() // Initialize hooks and shit for halo 1
{
	spdlog::info("Initializing Halo 3");

	Memcury::Scanner::SetTargetModule("halo3.dll");

	offsets::init();

	hooks::init();

	//Load Settings
	if (!config::games::halo_3::load())
	{
		spdlog::error("Failed to load settings for Halo 3.\nEither the settings file does not exist or something bad has happened!\nYou can ignore this error if you did not save it in the past.");
	}
	else
	{
		spdlog::info("Loaded settings for Halo 3.");
	}

	spdlog::info("Halo 3 initialized ☺");
}

void halo3::game::deinit()
{
	hooks::deinit();
	spdlog::info("Uninitialized Halo 3");
}

#if defined _DEBUG

void halo3::game::list_all_hs_functions()
{
	spdlog::info("Printing all eval functions inside the blamscript function table.");
	for (engine::_hs_script_op* function : offsets::blamscript::hs_function_table->table)
	{
		if (function->evaluate_func != nullptr && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate2)
		{
			spdlog::info("[HS Function] Return Type: {} Name: {} Offset: 0x{:X}", offsets::blamscript::hs_type_names->types[function->return_type], function->name, utils::memory::get_offset(reinterpret_cast<uintptr_t>(function->evaluate_func)));
		}
	}
	spdlog::info("Finished printing out the functions.");
}

void halo3::game::list_all_hs_globals()
{
	spdlog::info("Printing all globals inside the blamscript globals table.");
	for (engine::hs_external_global* global : offsets::blamscript::hs_external_globals->globals)
		if (global->address != nullptr) // Check if globals functionality has not been stripped from retail.
		{
			spdlog::info("[HS Global] Name: {} Offset: 0x{:X} Parameter Type: {}", global->name, utils::memory::get_offset(reinterpret_cast<uintptr_t>(global->address)), offsets::blamscript::hs_type_names->types[global->param_type]);
		}
	spdlog::info("Finished printing out the globals.");
}

#endif

void* halo3::game::get_hs_global(const char* global_name) // Gets the address of the specified global.
{
	for (const engine::hs_external_global* global : offsets::blamscript::hs_external_globals->globals)
	{
		if (strcmp(global->name, global_name) == 0)
		{
			// bool has been found
			if (global->address != nullptr)
			{
				return global->address;
			}

			spdlog::error("halo3::game::get_global: global has been found but does not have a working address");
			return nullptr;
		}
	}

	spdlog::error("halo3::game::get_global:: global was not found");
	return nullptr;
}

void* halo3::game::get_eval_hs_function(const char* func_name) // Gets the address of the specified function.
{
	for (const engine::_hs_script_op* function : offsets::blamscript::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate && function->evaluate_func != offsets::blamscript::functions::hs_null_evaluate2)
			{
				return function->evaluate_func;
			}

			spdlog::error("halo3::gameplayer_mapping_globals_get()::get_eval_hs_function: function has been found but does not have a working eval function");
			return nullptr;
		}
	}

	spdlog::error("halo3::game::get_eval_hs_function:: function was not found");
	return nullptr;
}

void* halo3::game::get_hs_function(const char* func_name, int to_skip)
{
	void* eval_function = get_eval_hs_function(func_name); // Get the address of the blamscript functions evaluate function.
	void* function = Memcury::Scanner(eval_function).ScanFor({ Memcury::ASM::Mnemonic("CALL") }, true, to_skip).RelativeOffset(1).GetAs<void*>(); // Get the function inside of the evaluate function.
	return function;
}

s_player_mapping_globals* halo3::game::player_mapping_globals_get()
{
	return offsets::globals::player_mapping_globals;
}

unsigned long player_mapping_first_active_output_user()
{
	long index = 0;
	for (long* active_output_user = halo3::game::player_mapping_globals_get()->output_user_player_mapping; *active_output_user == -1; ++active_output_user)
	{
		if (++index >= 4)
			return -1;
	}

	return index;
}

unsigned long player_mapping_get_unit_by_output_user(long output_user_index)
{
	assert(output_user_index != -1 && (output_user_index >= 0 && output_user_index < 4));

	return halo3::game::player_mapping_globals_get()->output_user_unit_mapping[output_user_index];
}

unsigned long halo3::game::grab_local_player_unit()
{
	long output_user = player_mapping_first_active_output_user();
	if (output_user == -1)
		return -1;

	long unit_index = player_mapping_get_unit_by_output_user(output_user);

	return unit_index;
}

//uintptr_t get_objecta(int index) {
//	int* tls_index = Memcury::Scanner::FindPattern(
//		"44 8B 05 ?? ?? ?? ?? 33 DB 65 48 8B 04 25 58 00 00 00 41 B9 38 00 00 00").RelativeOffset(3).GetAs<int*>();
//	uintptr_t rax = 0, rcx = 0, rdx = 0;
//	uint32_t ecx = 0;
//	rax = __readgsqword(0x00000058);
//	if (rax) {
//		rcx = *tls_index;
//		rax = *reinterpret_cast<uintptr_t*>(rax + (rcx * 8));
//		if (rax) {
//			rdx = *reinterpret_cast<uintptr_t*>(rax + 56);
//			if (rdx) {
//				rax = *reinterpret_cast<uintptr_t*>(rdx + 72);
//				if (rax) {
//					return *reinterpret_cast<uintptr_t*>((rax + (0x18 * index)) + 0x10);
//				}
//			}
//		}
//	}
//	return 0;
//}

//uintptr_t halo3::game::get_object(int object_index) {
//	//int* tls_index = Memcury::Scanner::FindPattern(
//	//	"44 8B 05 ?? ?? ?? ?? 33 DB 65 48 8B 04 25 58 00 00 00 41 B9 38 00 00 00").RelativeOffset(3).GetAs<int*>();
//
//	//uintptr_t uintptr = get_objecta(object_index);
//	//printf("Ass2: %p\n", uintptr);
//	return *(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(reinterpret_cast<uintptr_t>(utils::memory::get_tls_pointer(L"halo3.dll")) + 56i64) + 72i64) + 24i64 * object_index + 16);
//}

void halo3::game::object_scripting_cannot_die(int object_handle, bool cannot_die)
{
	return utils::memory::game_call<void>(offsets::functions::object_scripting_cannot_die)(object_handle, cannot_die);
}

void halo3::game::game_time_set_rate_scale_direct(float speed)
{
	return utils::memory::game_call<void>(offsets::functions::game_time_set_rate_scale_direct)(speed);
}

void* halo3::game::get_restricted_region_member_address(int alias_index, int member_index, int index)
{
	engine::s_thread_local_storage* tls = reinterpret_cast<engine::s_thread_local_storage*>(utils::memory::get_tls_pointer(L"halo3.dll"));

	return &tls->g_restricted_address[alias_index][offsets::globals::g_restricted_regions[member_index].m_registered_member[index].offset];
}

long halo3::game::weapon_get_owner_unit_index(long weapon_index)
{
	return utils::memory::game_call<long>(offsets::functions::weapon_get_owner_unit_index)(weapon_index);
}

bool halo3::game::game_team_is_enemy(long team_1, long team_2)
{
	return utils::memory::game_call<bool>(offsets::functions::game_team_is_enemy)(team_1, team_2);
}

struct struct_v6 // Dont know what the heck this is .-.
{
	BYTE gap0[372];
	DWORD team_index;
};

DWORD halo3::game::get_unit_team(int unit_index)
{
	struct_v6* ass = utils::memory::game_call<struct_v6*>(halo3::offsets::functions::object_try_and_get_and_verify_type)(unit_index, 0x1003u);

	if (ass)
	{
		return ass->team_index;
	}
	return -1;
}

void halo3::game::skulls::skull_primary_enable(int16_t skull_id, bool enable)
{
	engine::s_game_globals* game_globals = halo3::offsets::globals::game_globals;

	auto skull = 1 << skull_id;

	if (enable)
		game_globals->active_primary_skulls |= skull;
	else
		game_globals->active_primary_skulls &= ~skull;
}

void halo3::game::skulls::skull_secondary_enable(int16_t skull_id, bool enable)
{
	engine::s_game_globals* game_globals = halo3::offsets::globals::game_globals;

	auto skull = 1 << skull_id;

	if (enable)
		game_globals->active_secondary_skulls |= skull;
	else
		game_globals->active_secondary_skulls &= ~skull;
}

void halo3::game::render::draw_text(std::string text, int XPos, int YPos, float scale, real_argb_color colour = real_argb_color(255, 255, 255, 255))
{
	halo3::engine::c_rasterizer_draw_string draw_string;
	halo3::engine::c_font_cache_mt_safe font_cache;
	short_rectangle2d bounds{};

	//Game Calls
	utils::memory::game_call<halo3::engine::c_rasterizer_draw_string*>(Memcury::PE::GetModuleBase() + 0x28126c)(&draw_string); // c_rasterizer_draw_string rasterizer_draw_string;
	utils::memory::game_call<halo3::engine::c_font_cache_mt_safe*>(Memcury::PE::GetModuleBase() + 0x177dcc)(&font_cache); // c_font_cache_mt_safe font_cache;

	utils::memory::game_call<void>(Memcury::PE::GetModuleBase() + 0x1febcc)(&draw_string, halo3::engine::e_font_id::Conduit_32);

	draw_string.m_scale = scale; // Text Scale

	draw_string.m_color = colour; // Text colour

	utils::memory::game_call<void>(Memcury::PE::GetModuleBase() + 0x26430c)(&bounds); // set bounds

	//Position
	bounds.y0 += YPos;
	bounds.x0 += XPos;

	utils::memory::game_call<void>(Memcury::PE::GetModuleBase() + 0x1fece4)(&draw_string, &bounds); // set bounds
	utils::memory::game_call<bool>(Memcury::PE::GetModuleBase() + 0x1fed4c)(&draw_string, &font_cache, text.c_str());
	utils::memory::game_call<void>(Memcury::PE::GetModuleBase() + 0x177ae4)(&font_cache.m_locked); //Deinit font cache
}

int halo3::game::render::real_argb_color_to_pixel32(real_argb_color* colour)
{
	return ((static_cast<int>(colour->alpha * 255) << 24) | (static_cast<int>(colour->red * 255) << 16) | (static_cast<int>(colour->green * 255) << 8) | static_cast<int>(colour->blue * 255));
}