#include "halo2_hooks.h"

#include <cstdio>
#include <minhook/include/MinHook.h>

#include "framework.h"
#include "halo2_offsets.h"
#include <spdlog/spdlog.h>

static void (*terminal_printf_og)(int* a1, char* string, ...);

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

	return terminal_printf_og(a1, string);
}

void halo2::hooks::init()
{
	MH_STATUS _terminal_printf_hook = MH_CreateHook(offsets::_terminal_printf, &terminal_printf_detour, reinterpret_cast <LPVOID*> (&terminal_printf_og));
	if (_terminal_printf_hook != MH_OK) {
		spdlog::error("Error hooking _terminal_printf: {}", static_cast<int>(_terminal_printf_hook));
	}

	MH_QueueEnableHook(offsets::_terminal_printf);
	MH_ApplyQueued();
}

void halo2::hooks::deinit()
{
	MH_QueueDisableHook(offsets::_terminal_printf);
	MH_ApplyQueued();
}