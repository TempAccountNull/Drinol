#include "halo1_hooks.h"

#include <cstdio>
#include <minhook/include/MinHook.h>

#include "framework.h"
#include "halo1_offsets.h"
#include <spdlog/spdlog.h>

#include "detour.h"

static void (*terminal_printf_og)(int* a1, char* string, ...);

detour terminal_printf_h1;
static void terminal_printf_detour(int* a1, char* string, ...)
{
	if (halo1::hooks::redirect_print)
	{
		char msgbuf[254];
		va_list args;

		va_start(args, string);

		vsnprintf(msgbuf, sizeof msgbuf, string, args);  // NOLINT(cert-err33-c)

		spdlog::info("[Halo1] Print: {}", msgbuf);
		va_end(args);
	}

	return terminal_printf_h1.stub<void>(a1, string);
}

void halo1::hooks::init()
{
	terminal_printf_h1.create(reinterpret_cast<uintptr_t>(offsets::_terminal_printf), terminal_printf_detour);
	MH_ApplyQueued();
}

void halo1::hooks::deinit()
{
	terminal_printf_h1.disable();
	MH_ApplyQueued();
}