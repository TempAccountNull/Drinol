#pragma once
#include "stdafx.h"

class gui
{
public:

	/**
	 * \brief initializes the gui
	 */
	static void init();
	/**
	 * \brief toggles hooking the DX11 api to show our menu.
	 */
	inline static bool enabled;
	/**
	 * \brief the path to the ini file that imgui will store its settings in.
	 */
	inline static std::string ui_ini_path;
	inline static unsigned long long toggle_ui_keybind = 0x0D;	//	VK_INSERT ?
	static inline int toggle_wireframe_keybind = 0x24;

	void ApplyImGuiStyle(bool is_dark_style, float alpha_threshold);

	/// <summary>
///
/// </summary>
	struct Window
	{
		std::string		TITLE;
		HWND			hHANDLE;
		float			PosX;
		float			PosY;
		float			Width;
		float			Height;
	};
	bool binit = false;	//	Is GUI Initialized
	bool bShowWindow = false;	//	Is Menu Shown

	/**
	 * \brief Forces DX11 to render everything in wireframe
	 */
	static inline bool render_wireframe = false;
	VOID WINAPI Overlay(bool bShowMenu);

	// Helper Functions for Canvas
	void SyncWindow(HWND window);	//	Obtains target process main window information
	void GetWindowSize(float* in);
	void GetWindowPosition(float* in);
	void GetCenterScreen(float* in);
private:
	Window p_window;
};
inline std::unique_ptr<gui> g_Overlay;