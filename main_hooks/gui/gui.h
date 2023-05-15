#pragma once
#include <xstring>

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
	bool binit			= false;	//	Is GUI Initialized
	bool bShowWindow	= false;	//	Is Menu Shown
};
inline std::unique_ptr<gui> g_Overlay;