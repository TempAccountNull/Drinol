#include "halo1_hooks.h"

//static void (*terminal_printf_og)(int* a1, char* string, ...);
//
//static void terminal_printf_detour(int* a1, char* string, ...)
//{
//	va_list args;
//
//	char* theArg = string;
//
//	va_start(args, string);
//	while (theArg != NULL)
//	{
//		puts(theArg);
//		theArg = va_arg(args, char*);
//	}
//	va_end(args);
//
//	return terminal_printf_og(a1, string);
//}

void halo1::hooks::init()
{
	//MH_STATUS _terminal_printf_hook = MH_CreateHook(offsets::_terminal_printf, &terminal_printf_detour, reinterpret_cast <LPVOID*> (&terminal_printf_og));
	//if (_terminal_printf_hook != MH_OK) {
	//	if (_terminal_printf_hook == MH_ERROR_ALREADY_CREATED)
	//	{
	//		puts("_terminal_printf has already been hooked, you can ignore this message lol");
	//	}
	//	else
	//	{
	//		printf("Error hooking _terminal_printf: %d \n", _terminal_printf_hook);
	//	}
	//}
	//else
	//{
	//	MH_QueueEnableHook(offsets::_terminal_printf);
	//}

	//MH_ApplyQueued();
}

void halo1::hooks::deinit()
{
}
