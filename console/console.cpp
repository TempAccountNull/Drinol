// This is for output and console related stuff.
#include "stdafx.h"

void console::Initialize()
{
	AllocConsole();									//	Initialize Console
	g_Console->p_handle = GetStdHandle(STD_OUTPUT_HANDLE);		//	
	g_Console->p_wndwhandle = GetConsoleWindow();				//	set console handle { static as it should never change }

#if defined _DEBUG
	std::string text = "Drinol - Debug - ";
	text += COMMIT_HASH;
	if (sizeof(OLDEST_CHANGED_FILE_BEFORE_COMMIT) > 1)
		text += " - Mod";
	SetConsoleTitleA(text.c_str());
#else
	std::string text = "Drinol - Release - ";
	text += COMMIT_HASH;
	if (sizeof(OLDEST_CHANGED_FILE_BEFORE_COMMIT) > 1)
		text += " - Mod";
	SetConsoleTitleA(text.c_str());
#endif

	//Redirect output to console
	freopen_s(&g_Console->stream_in, "CONIN$", "r", stdin);
	freopen_s(&g_Console->stream_out, "CONOUT$", "w", stderr);
	freopen_s(&g_Console->stream_err, "CONOUT$", "w", stdout);

	// Fetch existing console mode so we correctly add a flag and not turn off others
	DWORD mode = 0;
	if (!GetConsoleMode(g_Console->p_handle, &mode))
	{
		DWORD error = ::GetLastError();
		std::wstring text = L"Could not get console mode. : ";
		text.append(std::to_wstring(error));
		MessageBox(NULL, text.c_str(), L"Drinol Error!", 0);
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// Try to set the mode.
	if (!SetConsoleMode(g_Console->p_handle, mode))
	{
		DWORD error = ::GetLastError();
		std::wstring text = L"Could not set console mode. : ";
		text.append(std::to_wstring(error));
		MessageBox(NULL, text.c_str(), L"Drinol Error!", 0);
	}
}

void console::Destroy()
{
	fclose(stream_in);
	fclose(stream_out);
	fclose(stream_err);
	DestroyWindow(p_wndwhandle);
	FreeConsole();
}

void console::GetConsolePos(int in[2])
{
	RECT consoleRect;
	GetWindowRect(p_wndwhandle, &consoleRect);
	in[0] = static_cast<int>(consoleRect.left);
	in[1] = static_cast<int>(consoleRect.top);
}

void console::GetConsoleSize(float in[2])
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	GetConsoleScreenBufferInfo(p_handle, &screenBufferInfo);
	COORD size = screenBufferInfo.dwSize;
	in[0] = static_cast<float>(size.X);
	in[1] = static_cast<float>(size.Y);
}

void console::SetConsoleSize(float size[2], int pos[2])
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT rect;
	rect.Left = pos[0];
	rect.Top = pos[1];
	rect.Right = size[0] - 1;
	rect.Bottom = size[1] - 1;

	COORD bufferSize;
	bufferSize.X = size[0];
	bufferSize.Y = size[1];

	SetConsoleWindowInfo(p_handle, TRUE, &rect);
	SetConsoleScreenBufferSize(p_handle, bufferSize);
}

void console::print(const char* text, TextColors color, ...)
{
	SetConsoleTextAttribute(p_handle, color);
	va_list args;
	va_start(args, color);
	vfprintf(stream_out, text, args);
	va_end(args);
	SetConsoleTextAttribute(p_handle, DEFAULT);
}