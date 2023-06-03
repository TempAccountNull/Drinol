#include "stdafx.h"
#include "halo3odst_hooks.h"

#include "halo3odst_offsets.h"

static void terminal_printf_detour(int* a1, char* string, ...)
{
	if (halo3odst::hooks::redirect_print)
	{
		char msgbuf[254];
		va_list args;

		va_start(args, string);

		vsnprintf(msgbuf, sizeof msgbuf, string, args);  // NOLINT(cert-err33-c)

		spdlog::info("[halo3odst] Print: {}", msgbuf);
		va_end(args);
	}

	return halo3odst::hooks::terminal_printf.stub<void>(a1, string);
}

void halo3odst::hooks::init()
{
	terminal_printf.create(reinterpret_cast<uintptr_t>(offsets::functions::game::terminal_printf), terminal_printf_detour);
	MH_ApplyQueued();
}

void halo3odst::hooks::deinit()
{
	terminal_printf.disable();
	MH_ApplyQueued();
}