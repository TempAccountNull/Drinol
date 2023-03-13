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
	static inline bool enabled;
	/**
	 * \brief the path to the ini file that imgui will store its settings in.
	 */
	static inline std::string ui_ini_path;
};
