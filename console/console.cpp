//TODO: maby account for CppClangTidyCertErr33C?
// This is for output and console related stuff.
#include "console.h"

#include <cstdio>
#include <memory>

#include "framework.h"

void console::init()
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