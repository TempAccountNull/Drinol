#include "stdafx.h"

void halo3::game::init() // Initialize hooks and shit for halo 1
{
	spdlog::info("Initializing Halo 3");

	Memcury::Scanner::SetTargetModule("halo3.dll");

	offsets::init();

	hooks::init();

	//Load Settings
	if (!config::halo3_load())
	{
		spdlog::error("Failed to load settings for Halo 3.\nEither the settings file does not exist or something bad has happened!\nYou can ignore this error if you did not save it in the past.");
	}
	else
	{
		spdlog::info("Loaded settings for Halo 3.");
	}
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
	for (engine::_hs_script_op* function : offsets::hs_function_table->table)
	{
		if (function->evaluate_func != nullptr && function->evaluate_func != offsets::hs_null_evaluate && function->evaluate_func != offsets::hs_null_evaluate2)
		{
			spdlog::info("[HS Function] Return Type: {} Name: {} Address: {}", offsets::hs_type_names->types[function->return_type], function->name, function->evaluate_func);
		}
	}
	spdlog::info("Finished printing out the functions.");
}

void halo3::game::list_all_hs_globals()
{
	spdlog::info("Printing all globals inside the blamscript globals table.");
	for (engine::hs_external_global* global : offsets::hs_external_globals->globals)
		if (global->address != nullptr) // Check if globals functionality has not been stripped from retail.
		{
			spdlog::info("[HS Global] Name: {} Address: {} Parameter Type: {}", global->name, global->address, offsets::hs_type_names->types[global->param_type]);
		}
	spdlog::info("Finished printing out the globals.");
}

#endif

void* halo3::game::get_hs_global(const char* global_name) // Gets the address of the specified global.
{
	for (const engine::hs_external_global* global : offsets::hs_external_globals->globals)
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
	for (const engine::_hs_script_op* function : offsets::hs_function_table->table)
	{
		if (strcmp(function->name, func_name) == 0)
		{
			// bool has been found
			if (function->evaluate_func != nullptr && function->evaluate_func != offsets::hs_null_evaluate && function->evaluate_func != offsets::hs_null_evaluate2)
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

halo3::engine::s_physics_constants* halo3::game::global_physics_constants_get()
{
	auto physics_constants = reinterpret_cast<engine::s_physics_constants**>(utils::get_tls_pointer(L"halo3.dll", engine::game_tls_index::physics_constants));
	return *physics_constants;
}

s_player_mapping_globals* halo3::game::player_mapping_globals_get()
{
	return offsets::player_mapping_globals;
}

halo3::engine::s_data_array* halo3::game::player_data_get()
{
	engine::s_thread_local_storage* tls = (engine::s_thread_local_storage*)utils::get_tls_pointer(L"halo3.dll");
	return tls->player_data;
}

halo3::engine::player_datum* halo3::game::local_player_datum_get()
{
	engine::s_thread_local_storage* tls = (engine::s_thread_local_storage*)utils::get_tls_pointer(L"halo3.dll");
	return reinterpret_cast<halo3::engine::player_datum*>(tls->player_data->data);
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
//	return *(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(reinterpret_cast<uintptr_t>(utils::get_tls_pointer(L"halo3.dll")) + 56i64) + 72i64) + 24i64 * object_index + 16);
//}

void halo3::game::object_scripting_cannot_die(int object_handle, bool cannot_die)
{
	return utils::GameCall<void>(offsets::object_scripting_cannot_die)(object_handle, cannot_die);
}

void* halo3::game::get_restricted_region_member_address(int alias_index, int member_index, int index)
{
	engine::s_thread_local_storage* tls = reinterpret_cast<engine::s_thread_local_storage*>(utils::get_tls_pointer(L"halo3.dll"));

	return &tls->g_restricted_address[alias_index][offsets::g_restricted_regions[member_index].m_registered_member[index].offset];
}

long halo3::game::weapon_get_owner_unit_index(long weapon_index)
{
	return utils::GameCall<long>(halo3::offsets::weapon_get_owner_unit_index)(weapon_index);
}