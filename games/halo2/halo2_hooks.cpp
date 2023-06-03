#include "stdafx.h"
#include "halo2_hooks.h"

#include "halo2_offsets.h"
#include "utils.h"

static void terminal_printf_detour(int* a1, char* string, ...)
{
	if (halo2::hooks::redirect_print)
	{
		char msgbuf[254];
		va_list args;

		va_start(args, string);

		vsnprintf(msgbuf, sizeof msgbuf, string, args);  // NOLINT(cert-err33-c)

		spdlog::info("[halo2] Print: {}", msgbuf);
		va_end(args);
	}

	return halo2::hooks::terminal_printf.stub<void>(a1, string);
}

void __fastcall hs_null_evaluate_2_detour(__int64 function_index, unsigned int a2, unsigned __int8 a3)
{
	if (halo2::hooks::redirect_print)
	{
		if (function_index != 27) // Do not execute if the function_index does not equal hs_print. (will cause crashes otherwise!)
			return halo2::hooks::hs_null_evaluate2.stub<void>(function_index, a2, a3);

		int* weirdint = utils::memory::game_call<int*>(halo2::offsets::blamscript::functions::hs_macro_function_evaluate) (function_index, a2, a3);

		if (!weirdint)
			return halo2::hooks::hs_null_evaluate2.stub<void>(function_index, a2, a3);

		char* crap = utils::memory::game_call<char*>(halo2::offsets::blamscript::functions::hs_parse)(weirdint);

		if (crap)
		{
			spdlog::info("[halo2] Print: {}", crap);

			utils::memory::game_call<void>(halo2::offsets::blamscript::functions::hs_return)(a2, 0);
		}
	}
	else
	{
		return halo2::hooks::hs_null_evaluate2.stub<void>(function_index, a2, a3);
	}
}

void halo2::hooks::init()
{
	terminal_printf.create(reinterpret_cast<uintptr_t>(offsets::functions::_terminal_printf), terminal_printf_detour);
	hs_null_evaluate2.create(reinterpret_cast<uintptr_t>(offsets::blamscript::functions::hs_null_evaluate_2), hs_null_evaluate_2_detour);
	MH_ApplyQueued();
}

void halo2::hooks::deinit()
{
	terminal_printf.disable();
	hs_null_evaluate2.disable();
	MH_ApplyQueued();
}