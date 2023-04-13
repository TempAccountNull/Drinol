// This is for output and console related stuff.
#include "stdafx.h"

FILE* fDummy; // Dummy file for freopen_s

void console::init()
{
	//Initialize Console
#if defined _DEBUG
	AllocConsole();
#else
	AttachConsole(GetCurrentProcessId());
#endif

	SetConsoleTitleA("Drinol - WIP");

	//Redirect output to console
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
}

void console::deinit()
{
	if (_fcloseall() != 0)
	{
		MessageBox(NULL, L"Could not close the console.", L"Drinol Error!", 0);
	};
	FreeConsole();

	// Since for some reason we cannot close the console properly, we have to hide it :'(

	HWND Window;
	Window = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Window, SW_HIDE); //1 = closed
}