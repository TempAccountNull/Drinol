#pragma once
class console
{
private:
	HANDLE	p_handle;			//	Console Handle
	HWND	p_wndwhandle;		//	Console Window Handle
	UINT	p_flags;			//	Console Flags
	FILE*	stream_in;			// Dummy file for freopen_s
	FILE*	stream_out;			// Dummy file for freopen_s
	FILE*	stream_err;			// Dummy file for freopen_s

public:

	//https://stackoverflow.com/questions/75388829/how-to-get-the-output-console-screen-buffer-handle-for-getconsolemode-in-w
	// Make console support more colors
	//	Attribute flags can be located -> consoleapi2.h
	enum TextColors 
	{
		BLACK				= 0,
		BLUE				= FOREGROUND_BLUE,
		GREEN				= FOREGROUND_GREEN,
		CYAN				= FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED					= FOREGROUND_RED,
		MAGENTA				= FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW				= FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE				= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY				= FOREGROUND_INTENSITY,
		LIGHT_BLUE			= FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		LIGHT_GREEN			= FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		LIGHT_CYAN			= FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		LIGHT_RED			= FOREGROUND_INTENSITY | FOREGROUND_RED,
		LIGHT_MAGENTA		= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		LIGHT_YELLOW		= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		BRIGHT_WHITE		= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		DEFAULT				= 15,
	};

	//	Attribute flags can be located -> consoleapi2.h
	enum BackgroundColors
	{
		BG_BLACK			= 0,
		BG_BLUE				= BACKGROUND_BLUE,
		BG_GREEN			= BACKGROUND_GREEN,
		BG_CYAN				= BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_RED				= BACKGROUND_RED,
		BG_MAGENTA			= BACKGROUND_RED | BACKGROUND_BLUE,
		BG_YELLOW			= BACKGROUND_RED | BACKGROUND_GREEN,
		BG_WHITE			= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_GRAY				= BACKGROUND_INTENSITY,
		BG_LIGHT_BLUE		= BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		BG_LIGHT_GREEN		= BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		BG_LIGHT_CYAN		= BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		BG_LIGHT_RED		= BACKGROUND_INTENSITY | BACKGROUND_RED,
		BG_LIGHT_MAGENTA	= BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		BG_LIGHT_YELLOW		= BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		BG_BRIGHT_WHITE		= BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
	};


	//	Should be located elsewhere , since the console being toggled determines whether or not the class is used
	//	Possibly create a location for global variables / toggles
	inline static bool enabled;
	bool bShowWindow = TRUE;

	//	Core Functions
	VOID WINAPI Initialize();
	VOID WINAPI Destroy();
	VOID WINAPI print(const char* text, TextColors color, ...);
	void WINAPI SetConsoleVisibility(bool isVisible) { ShowWindow(p_wndwhandle, isVisible ? SW_SHOW : SW_HIDE); }

	//	Helper functions
	void GetConsoleHandle(HANDLE& in) const { in = p_handle; }
	void GetConsoleHWND(HWND& in) const { in = p_wndwhandle; }
	void GetConsolePos(int in[2]);
	void SetConsolePos(int pos[2]) { SetWindowPos(p_wndwhandle, NULL, pos[0], pos[1], 0, 0, p_flags); }
	void GetConsoleSize(float in[2]);
	void SetConsoleSize(float dwSize[2], int pos[2]);
	void SetConsoleTextColor(TextColors color) { SetConsoleTextAttribute(p_handle, color); }
	void ResetConsoleTextColor() const { SetConsoleTextAttribute(p_handle, DEFAULT); }
	void SetConsoleBackgroundColor(BackgroundColors color) { SetConsoleTextAttribute(p_handle, color); }
	void ResetConsoleBackgroundColor() const { SetConsoleTextAttribute(p_handle, BLACK); }
	void HideConsole() { ShowWindow(p_wndwhandle, SW_HIDE); }
	void ShowConsole() { ShowWindow(p_wndwhandle, SW_SHOW); }
	void ClearConsole() { system("cls"); }
};
inline std::unique_ptr<console> g_Console;
