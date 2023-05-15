// This is for output and console related stuff.
#include "stdafx.h"

FILE* fDummy; // Dummy file for freopen_s

void console::init()
{
	//Initialize Console
	AllocConsole();

#if defined _DEBUG
	SetConsoleTitleA("Drinol - WIP - Debug Build");
#else
	SetConsoleTitleA("Drinol - WIP - Release Build");
#endif

	//Redirect output to console
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	//https://stackoverflow.com/questions/75388829/how-to-get-the-output-console-screen-buffer-handle-for-getconsolemode-in-w
	// Make console support more colors
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Fetch existing console mode so we correctly add a flag and not turn off others
	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode))
	{
		DWORD error = ::GetLastError();
		std::wstring text = L"Could not get console mode. : ";
		text.append(std::to_wstring(error));
		MessageBox(NULL, text.c_str(), L"Drinol Error!", 0);
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// Try to set the mode.
	if (!SetConsoleMode(hStdOut, mode))
	{
		DWORD error = ::GetLastError();
		std::wstring text = L"Could not set console mode. : ";
		text.append(std::to_wstring(error));
		MessageBox(NULL, text.c_str(), L"Drinol Error!", 0);
	}
}

void console::deinit()
{
    fclose(stdin);
    fclose(stderr);
    fclose(stdout);
    FreeConsole();
}