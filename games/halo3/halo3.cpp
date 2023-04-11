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
		spdlog::error("Failed to load settings for Halo 3. Either the settings file does not exist or something bad has happened! You can ignore this error if you did not save it in the past.");
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
		if (function->evaluate_func != nullptr && function->evaluate_func != offsets::hs_null_evaluate)
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
			if (function->evaluate_func != nullptr || function->evaluate_func != offsets::hs_null_evaluate)
			{
				return function->evaluate_func;
			}

			spdlog::error("halo3::game::get_eval_hs_function: function has been found but does not have a working eval function");
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

uintptr_t halo3::game::get_object(int object_index) {
	//int* tls_index = Memcury::Scanner::FindPattern(
	//	"44 8B 05 ?? ?? ?? ?? 33 DB 65 48 8B 04 25 58 00 00 00 41 B9 38 00 00 00").RelativeOffset(3).GetAs<int*>();

	//uintptr_t uintptr = get_objecta(object_index);
	//printf("Ass2: %p\n", uintptr);
	return *(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(reinterpret_cast<uintptr_t>(utils::get_tls_pointer(L"halo3.dll")) + 56i64) + 72i64) + 24i64 * object_index + 16);
}