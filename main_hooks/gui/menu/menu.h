#pragma once

class menu
{
public:

	static inline bool show_load_modal = false;

	static inline bool show_save_modal = false;

	static inline bool show_about_modal = false;

	static inline bool show_restore_defaults_modal = false;

	static inline bool show_detach_modal = false;

	static inline int test_int = 0;

	static inline bool settings_window_open = false;
	static void about_modal();
	static void restore_defaults_modal();
	static void detach_modal();
	static void load_changes_modal();
	static void save_changes_modal();
	static void render();		//	Top most render window		(shown with g_Overlay->bShowWindow == true)
	static void RenderHUD();	//	BAckground render window	(shown with g_Overlay->bShowWindow == false)
	/**
	 * \brief toggles the imgui console tab.
	 */
	inline static bool console_enabled;



	class HaloCombatEvolved
	{
	public:
		void static DrawMenu();
	};


	class Halo2
	{
	public:
		void static DrawMenu();
	};


	class Halo3
	{
	public:
		void static DrawMenu();
	};


	class Halo3ODST
	{
	public:
		void static DrawMenu();
	};


	class HaloReach
	{
	public:
		void static DrawMenu();
	};


	class Halo4
	{
	public:
		void static DrawMenu();
	};
};

