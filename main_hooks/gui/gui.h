#pragma once

// Define Custom Colors
#define IM_COL32_RED        IM_COL32(255,0,0,255)       // red		= 0xFF0000FF
#define IM_COL32_BLUE       IM_COL32(0,0,255,255)       // blue		= 0x0000FFFF
#define IM_COL32_GREEN      IM_COL32(0,255,0,255)       // green	= 0x00FF00FF
#define IM_COL32_YELLOW     IM_COL32(255,255,0,255)     // yellow	= 0xFFFF00FF
#define IM_COL32_PINK       IM_COL32(255,0,255,255)     // pink		= 0xFF00FFFF
#define IM_COL32_CYAN       IM_COL32(0,255,255,255)     // cyan		= 0x00FFFFFF

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

	/**
	 * \brief Forces DX11 to render everything in wireframe
	 */
	static inline bool render_wireframe = false;

	/**
	 * \brief Used to store information about a process window / canvas
	 */
	struct Window
	{
		const char* TITLE;
		HWND			wndwHandle;
		float			Position[2];
		float			Size[2];
	};
	bool binit = false;								//	Is GUI Initialized
	bool bShowWindow = false;						//	Is Menu Shown

	// Helper Functions for DirectX Canvas
	VOID WINAPI		InitImGui();					//	Initializes Dear ImGui
	VOID WINAPI		Overlay(bool bShowMenu);		//	Main Overlay Render Function
	void			SyncWindow(HWND window);		//	Obtains target process main window information
	void			GetWindowSize(float* in);		//	Obtains dxWindow Size
	void			GetWindowPosition(float* in);	//	Obtains dxWindow Position
	void			GetCenterScreen(float* in);		//	Obtains dxWindow Center Point

	// CUSTOM IMGUI FUNCTIONS
	void			ApplyImGuiStyle(bool is_dark_style, float alpha_threshold);
	static ImVec4 SV_RAINBOW(float saturation, float value, float opacity, float speed = 0.002f, float hue = 0);
	VOID IMGUI_API	TextWithToolTip(const char* text, const char* tip, ...);										//  Text with a tooltip
	VOID IMGUI_API	TextColoredWithToolTip(const ImVec4& color, const char* text, const char* tip, ...);			//	Colored text with a tooltip
	BOOL IMGUI_API	ButtonWithToolTip(const char* title, const char* tip, const ImVec2& size = { 0, 0 });			//	Button with a tooltip
	BOOL IMGUI_API	CheckboxWithToolTip(const char* label, const char* tip, bool* v);								//	Checkbox with a tooltip
	BOOL IMGUI_API	ComboWithToolTip(const char* label, const char* tip, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);				//	Combo with a tooltip
	BOOL IMGUI_API	DragFloatWithToolTip(const char* label, const char* tip, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);	//	Drag Float with tool tip
	VOID IMGUI_API	Text(const ImVec2& pos, float fontsize, const ImVec4& color, const char* text, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect);		//	Simplified draw text call
	VOID IMGUI_API	Line(const ImVec2& pointA, const ImVec2& pointB, const ImVec4& color, float thickness);			//	Draws a line from pointA to pointB
	VOID IMGUI_API	CleanText(const ImVec2& pos, const ImVec4& color, const char* text, float fontsize);			//	Draws text with a black outline
	VOID IMGUI_API	CleanLine(const ImVec2& pointA, const ImVec2& pointB, const ImVec4& color, float thickness);	//	Draws a line from pointA to pointB with an outline
private:
	Window p_window;
};
inline std::unique_ptr<gui> g_Overlay;