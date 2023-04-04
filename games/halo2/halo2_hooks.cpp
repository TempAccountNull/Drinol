#include "halo2_hooks.h"

#include <cstdio>
#include <minhook/include/MinHook.h>

#include "framework.h"
#include "halo2_offsets.h"
#include <spdlog/spdlog.h>

#include "detour.h"

static void (*terminal_printf_og)(int* a1, char* string, ...);

detour terminal_printf;
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

	return terminal_printf.stub<void>(a1, string);
}

void halo2::hooks::init()
{
	terminal_printf.create(reinterpret_cast<uintptr_t>(offsets::_terminal_printf), terminal_printf_detour);
	MH_ApplyQueued();
}

void halo2::hooks::deinit()
{
	terminal_printf.disable();
	MH_ApplyQueued();
}