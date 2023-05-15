#pragma once
class menu
{
public:
	static void render();		//	Top most render window		(shown with g_Overlay->bShowWindow == true)
	static void RenderHUD();	//	BAckground render window	(shown with g_Overlay->bShowWindow == false)	
	/**
	 * \brief toggles the imgui console tab.
	 */
	inline static bool console_enabled;
};
