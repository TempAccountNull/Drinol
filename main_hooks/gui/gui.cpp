// Most of this code is from https://github.com/Gavpherk/Universal-IL2CPP-DX11-Kiero-Hook
#include "stdafx.h"


//---------------------------------------------------------------------------------------------------
// # Forward Declarations

typedef uintptr_t PTR;
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef void(__stdcall* DrawIndexed)(ID3D11DeviceContext* p_context, UINT index_count, UINT start_index_location, INT base_vertex_location);

HWND						window;
WNDPROC						oWndProc;
Present						oPresent;
DrawIndexed					oDrawIndexed;
ResizeBuffers				oResizeBuffers;
ID3D11Device*				pDevice;
ID3D11DeviceContext*		pContext;
ID3D11RenderTargetView*		mainRenderTargetView;


//---------------------------------------------------------------------------------------------------
//	# Hooks

//---------------------------------------------------------------------------------------------------
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//---------------------------------------------------------------------------------------------------
HRESULT hkResizeBuffers(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

//---------------------------------------------------------------------------------------------------
//dx11 ResizeBuffers Hook
HRESULT hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (mainRenderTargetView)
	{
		pContext->OMSetRenderTargets(0, 0, 0);
		mainRenderTargetView->Release();
	}

	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	DXGI_SWAP_CHAIN_DESC sd;
	pSwapChain->GetDesc(&sd);
	window = sd.OutputWindow;

	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	// Perform error handling here!

	pDevice->CreateRenderTargetView(pBuffer, NULL, &mainRenderTargetView);
	// Perform error handling here!
	pBuffer->Release();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(Width);
	vp.Height = static_cast<FLOAT>(Height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);

	g_Overlay->SyncWindow(window);	//	Synchronize new window settings for overlay context

	return hr;
}

//---------------------------------------------------------------------------------------------------
void hkDrawIndexed(ID3D11DeviceContext* p_context, const UINT index_count, const UINT start_index_location, const INT base_vertex_location)
{
	if (gui::render_wireframe)
	{
		ID3D11RasterizerState* r_state;
		D3D11_RASTERIZER_DESC r_desc;

		// cd3d is the ID3D11DeviceContext
		p_context->RSGetState(&r_state); // retrieve the current state
		if (r_state != nullptr)
		{
			r_state->GetDesc(&r_desc);    // get the desc of the state

			r_desc.FillMode = D3D11_FILL_WIREFRAME; // change the ONE setting
			// create a whole new rasterizer state
			// d3d is the ID3D11Device
			pDevice->CreateRasterizerState(&r_desc, &r_state);

			p_context->RSSetState(r_state);    // set the new rasterizer state
		}
	}

	return oDrawIndexed(p_context, index_count, start_index_location, base_vertex_location);
}


//---------------------------------------------------------------------------------------------------
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//	When menu is shown we want to utilize the imgui wndproc handler
	//	Likewise , when shutting down we do not want to get locked into DearImGuis WndProc Handler
	if (g_Overlay->bShowWindow && g_Running && !g_Killswitch)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

//---------------------------------------------------------------------------------------------------
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	//	Should be moved to its own initialization function
	if (!g_Overlay->binit)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			g_Overlay->InitImGui();
			g_Overlay->SyncWindow(window);
			g_Overlay->binit = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	if (g_Running && !g_Killswitch)
		g_Overlay->Overlay(g_Overlay->bShowWindow);	//	Render Overlay
	return oPresent(pSwapChain, SyncInterval, Flags);
}


//---------------------------------------------------------------------------------------------------
VOID WINAPI gui::InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.IniFilename = gui::ui_ini_path.c_str();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

//---------------------------------------------------------------------------------------------------
// Initializes the main Graphical User Interface
// Kiero is used for this procedure
// A Dear ImGui window is displayed
void gui::init()
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
#if defined _DEBUG
		spdlog::debug("kiero initialized.");
#endif
		kiero::bind(8, (void**)&oPresent, hkPresent);
		kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
		kiero::bind(73, (void**)&oDrawIndexed, hkDrawIndexed);
	}

#if defined _DEBUG
	spdlog::debug("DX11 Hooked.");
#endif
}

//---------------------------------------------------------------------------------------------------
//	Obtains window data and passes it to p_window pointer
void gui::SyncWindow(HWND window)
{
	RECT temprect;
	GetWindowRect(window, &temprect);
	float position[2]	= { temprect.left, temprect.top };
	float size[2]		= { (temprect.right - temprect.left), (temprect.bottom - temprect.top) };

	// Position
	for (int i = 0; i < 2; i++)
		p_window.Position[i] = position[i];

	// Size ( x , y)
	for (int i = 0; i < 2; i++)
		p_window.Size[i] = position[i];
}

//---------------------------------------------------------------------------------------------------
//	gets the current dxWindow Size
void gui::GetWindowSize(float* in)
{
	for (int i = 0; i < 2; i++)
		in[i] = p_window.Size[i];
}

//---------------------------------------------------------------------------------------------------
//	gets the current dxWindow Position
void gui::GetWindowPosition(float* in)
{
	for (int i = 0; i < 2; i++)
		in[i] = p_window.Position[i];
}

//---------------------------------------------------------------------------------------------------
//	gets the current dxWindow center screen point
void gui::GetCenterScreen(float* in)
{
	float result[2];
	GetWindowSize(result);

	for (int i = 0; i < 2; i++)
		in[i] = result[i] / 2;
}

//---------------------------------------------------------------------------------------------------
//	Main Overlay Render Function
VOID WINAPI gui::Overlay(bool bShowMenu)
{
	//	Begin Draw Scene
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = bShowMenu;		//	Draw Cursor

	//	Render Options
	switch (bShowMenu)
	{
	case TRUE: menu::render();		break;	//	Render Menu
	case FALSE: menu::RenderHUD();	break;	//	Render Drawing Elements (Can be used as a watermark and drawing other static elemnts on the HUD)
	}

	//	End Draw Scene
	ImGui::EndFrame();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//---------------------------------------------------------------------------------------------------
//  Text with a tooltip 
VOID IMGUI_API gui::TextWithToolTip(const char* text, const char* tip, ...)
{
	va_list args;
	va_start(args, tip);
	ImGui::TextV(text, args);
	va_end(args);

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(tip);
}

//---------------------------------------------------------------------------------------------------
//	Colored text with a tooltip
VOID IMGUI_API gui::TextColoredWithToolTip(const ImVec4& color, const char* text, const char* tip, ...)
{
	va_list args;
	va_start(args, tip);
	ImGui::TextColoredV(color, text, args);
	va_end(args);

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(tip);
}

//---------------------------------------------------------------------------------------------------
//	Button with a tooltip
BOOL IMGUI_API gui::ButtonWithToolTip(const char* title, const char* tip, const ImVec2& size)
{
	bool result = ImGui::Button(title, size);

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(tip);

	return result;
}

//---------------------------------------------------------------------------------------------------
//	Checkbox with a tooltip
BOOL IMGUI_API gui::CheckboxWithToolTip(const char* label, const char* tip, bool* v)
{
	bool result = ImGui::Checkbox(label, v);

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(tip);

	return result;
}

//---------------------------------------------------------------------------------------------------
//	Combo with a tooltip
BOOL IMGUI_API	gui::ComboWithToolTip(const char* label, const char* tip, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items)
{
	bool result = ImGui::Combo(label, current_item, items_separated_by_zeros, popup_max_height_in_items);

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(tip);

	return result;
}

//---------------------------------------------------------------------------------------------------
//	Drag Float with a tooltip
BOOL IMGUI_API gui::DragFloatWithToolTip(const char* label, const char* tip, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	bool result = ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, flags);

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(tip);

	return result;
}

//---------------------------------------------------------------------------------------------------
//	Simplified draw text call
VOID IMGUI_API gui::Text(const ImVec2& pos, float fontsize, const ImVec4& color, const char* text, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
	ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), fontsize, pos, ImColor(color), text, text_end, wrap_width, cpu_fine_clip_rect);
}

//---------------------------------------------------------------------------------------------------
// Draws a line from pointA to pointB
VOID IMGUI_API gui::Line(const ImVec2& pointA, const ImVec2& pointB, const ImVec4& color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(pointA, pointB, ImColor(color), thickness);
}

//---------------------------------------------------------------------------------------------------
//	Draws text with a black outline
VOID IMGUI_API gui::CleanText(const ImVec2& pos, const ImVec4& color, const char* text, float fontsize)
{
	Text(ImVec2(pos.x + 1.f, pos.y + 1.f), fontsize, ImColor(IM_COL32_BLACK), text, text + strlen(text), 800, 0);
	Text(ImVec2(pos.x - 1.f, pos.y - 1.f), fontsize, ImColor(IM_COL32_BLACK), text, text + strlen(text), 800, 0);
	Text(ImVec2(pos.x, pos.y - 1.f), fontsize, ImColor(IM_COL32_BLACK), text, text + strlen(text), 800, 0);
	Text(ImVec2(pos.x, pos.y + 1.f), fontsize, ImColor(IM_COL32_BLACK), text, text + strlen(text), 800, 0);
	Text(pos, fontsize, color, text, text + strlen(text), 800, 0);
}

//---------------------------------------------------------------------------------------------------
// Draws a line from pointA to pointB with a black outline
VOID IMGUI_API gui::CleanLine(const ImVec2& a, const ImVec2& b, const ImVec4& color, float thickness)
{
	Line(a, b, { 0.f, 0.f, 0.f, color.w }, (thickness + 0.25f));
	Line(a, b, { 1.f, 1.f, 1.f, (color.w - 0.2f)}, (thickness + 0.15f));
	Line(a, b, color, thickness);
}

// Custom Dear ImGui Style
void gui::ApplyImGuiStyle(bool is_dark_style, float alpha_threshold)
{
	//Use a ternary operator
	is_dark_style ? ImGui::StyleColorsDark() : ImGui::StyleColorsLight();

	ImGuiStyle& style = ImGui::GetStyle();

	// Adjusts the alpha values of the ImGui colors based on the alpha threshold.
	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		const auto color_id = static_cast<ImGuiCol>(i);
		auto& color = style.Colors[i];
		if (color.w < alpha_threshold || color_id == ImGuiCol_FrameBg || color_id == ImGuiCol_WindowBg || color_id == ImGuiCol_ChildBg)
		{
			color.w *= alpha_threshold;
		}
	}

	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 0.9399999976158142f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1568627506494522f, 0.2862745225429535f, 0.47843137383461f, 0.5400000214576721f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 0.4000000059604645f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 0.6705882549285889f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1568627506494522f, 0.2862745225429535f, 0.47843137383461f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.239999994635582f, 0.5199999809265137f, 0.8799999952316284f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2599999904632568f, 0.5899999737739563f, 0.9800000190734863f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.4000000059604645f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.8705882430076599f, 0.529411792755127f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3100000023841858f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.8705882430076599f, 0.4000000059604645f, 0.0f, 0.7803921699523926f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.8705882430076599f, 0.4000000059604645f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 0.6705882549285889f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 0.9490196108818054f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f, 0.5764706134796143f, 0.8619999885559082f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.8705882430076599f, 0.5882353186607361f, 0.0f, 0.800000011920929f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.8705882430076599f, 0.529411792755127f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}