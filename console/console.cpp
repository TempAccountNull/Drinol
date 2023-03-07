//TODO: maby account for CppClangTidyCertErr33C?
#include "console.h"
#include "framework.h"
#include <cstdio>

void console::initialize()
{
	//Initialize Console
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitleA("Drinol - WIP");

	//Redirect output to console
	static FILE* fDummy; // Dummy file for freopen_s

	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
}