#include "pch.h"
#include "ui.h"
// DX11 imports
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }  // NOLINT(cppcoreguidelines-macro-usage)

//ImGUI imports

// D3X HOOK DEFINITIONS// D3X HOOK DEFINITIONS
typedef HRESULT(__fastcall* IDXGISwapChainPresent)(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags);
// Definition of WndProc Hook. Its here to avoid dragging dependencies on <windows.h> types.
// ReSharper disable once CppInconsistentNaming
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main D3D11 Objects
ID3D11DeviceContext* p_context = nullptr;
ID3D11Device* p_device = nullptr;
ID3D11RenderTargetView* main_render_target_view;
static IDXGISwapChain* p_swap_chain = nullptr;
static WNDPROC original_wnd_proc_handler = nullptr;
HWND window = nullptr;
IDXGISwapChainPresent fn_idxgi_swap_chain_present;
IDXGISwapChainPresent og_idxgi_swap_chain_present = nullptr;
DWORD_PTR* p_device_context_v_table = nullptr;
ImGuiContext* imgui_context;

// Boolean
bool g_b_initialized = false;
bool g_show_menu = false;
bool g_present_hooked = false;
bool show_wireframe = false;

//Resize Protection (fullscreen and that)
typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
ResizeBuffers fn_idxgi_swap_chain_resize_buffers;
ResizeBuffers oResizeBuffers = nullptr;
HRESULT hkResizeBuffers(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (main_render_target_view) {
		p_context->OMSetRenderTargets(0, 0, 0);
		main_render_target_view->Release();
	}

	HRESULT hr = oResizeBuffers(pThis, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ID3D11Texture2D* pBuffer;
	pThis->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(void**)&pBuffer);
	// Perform error handling here!

	p_device->CreateRenderTargetView(pBuffer, NULL,
		&main_render_target_view);
	// Perform error handling here!
	pBuffer->Release();

	p_context->OMSetRenderTargets(1, &main_render_target_view, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	p_context->RSSetViewports(1, &vp);
	return hr;
}

void detour_directx_resize_buffers()
{
	if (MH_CreateHook(fn_idxgi_swap_chain_resize_buffers, hkResizeBuffers, reinterpret_cast<void**>(&oResizeBuffers)) == MH_OK)
	{
		std::cout << "resize_buffers Hook Created" << std::endl;

		if (MH_EnableHook(fn_idxgi_swap_chain_resize_buffers) == MH_OK)
		{
			std::cout << "resize_buffers Hooked" << std::endl;

			DWORD old_protect;
			VirtualProtect(fn_idxgi_swap_chain_resize_buffers, 2, PAGE_EXECUTE_READWRITE, &old_protect);
		}
	}
}

LRESULT CALLBACK h_wnd_proc(const HWND h_wnd, const UINT u_msg, const WPARAM w_param, const LPARAM l_param)
{
	ImGuiIO& io = ImGui::GetIO();
	POINT m_pos;
	GetCursorPos(&m_pos);
	ScreenToClient(window, &m_pos);
	ImGui::GetIO().MousePos.x = m_pos.x;
	ImGui::GetIO().MousePos.y = m_pos.y;

	if (u_msg == WM_KEYUP)
	{
		io.MouseDrawCursor = false;

		if (w_param == VK_INSERT)
		{
			g_show_menu = !g_show_menu;
		}
	}

	if (g_show_menu)
	{
		ImGui_ImplWin32_WndProcHandler(h_wnd, u_msg, w_param, l_param);
		io.MouseDrawCursor = true;
		return true;
	}

	return CallWindowProc(original_wnd_proc_handler, h_wnd, u_msg, w_param, l_param);
}

HRESULT get_device_and_ctx_from_swapchain(IDXGISwapChain* p_swap_chain, ID3D11Device** pp_device, ID3D11DeviceContext** pp_context)
{
	const HRESULT ret = p_swap_chain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<PVOID*>(pp_device));

	if (SUCCEEDED(ret))
		(*pp_device)->GetImmediateContext(pp_context);

	return ret;
}

static void help_marker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

float game_speed = 1.0f;

void main_menu()
{
	ImGui::Begin("Drinol", &g_show_menu, ImGuiWindowFlags_None);

	const ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_Reorderable;
	if (ImGui::BeginTabBar("MainTabs", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Testing"))
		{
			ImGui::EndTabItem();
		}
		
		ImGui::EndTabBar();

		ImGui::End();
	}
}

void menu_style()
{
	// Style
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_None;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.00f, 0.00f, 0.94f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.00f, 0.00f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.34f, 0.00f, 0.00f, 0.50f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.19f, 0.00f, 0.00f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.00f, 0.00f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.55f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.67f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.42f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.34f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.18f, 0.00f, 0.00f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.44f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.66f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.88f, 0.24f, 0.24f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.98f, 0.26f, 0.26f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.98f, 0.26f, 0.26f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.43f, 0.43f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.10f, 0.10f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.75f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.98f, 0.26f, 0.26f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.58f, 0.18f, 0.18f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.07f, 0.07f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.35f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.25f, 0.23f, 0.23f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
}

HRESULT __fastcall Present(IDXGISwapChain* p_chain, UINT sync_interval, UINT flags)
{
	if (!g_b_initialized) {
		if (FAILED(get_device_and_ctx_from_swapchain(p_chain, &p_device, &p_context)))
			return fn_idxgi_swap_chain_present(p_chain, sync_interval, flags);
		p_swap_chain = p_chain;
		DXGI_SWAP_CHAIN_DESC sd;
		p_chain->GetDesc(&sd);

		imgui_context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableSetMousePos | ImGuiConfigFlags_NavEnableGamepad;
		// Not needed right now

		menu_style();

		window = sd.OutputWindow;

		//Set OriginalWndProcHandler to the Address of the Original WndProc function
		original_wnd_proc_handler = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(h_wnd_proc)));

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(p_device, p_context);

		ImGui_ImplDX11_CreateDeviceObjects();

		ImGui::GetIO().ImeWindowHandle = window;

		ImGui_ImplDX11_InvalidateDeviceObjects();

		ID3D11Texture2D* p_back_buffer;

		p_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_back_buffer));
		p_device->CreateRenderTargetView(p_back_buffer, nullptr, &main_render_target_view);
		p_back_buffer->Release();

		g_b_initialized = true;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	if (g_show_menu)
	{
		main_menu();
	}

	ImGui::EndFrame();

	ImGui::Render();

	p_context->OMSetRenderTargets(1, &main_render_target_view, nullptr);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return og_idxgi_swap_chain_present(p_chain, sync_interval, flags);
}

void detour_directx_present()
{
	if (MH_CreateHook(fn_idxgi_swap_chain_present, Present, reinterpret_cast<void**>(&og_idxgi_swap_chain_present)) == MH_OK)
	{
		std::cout << "DXGI Present Hook Created" << std::endl;

		if (MH_EnableHook(fn_idxgi_swap_chain_present) == MH_OK)
		{
			std::cout << "DXGI Present Hooked" << std::endl;

			DWORD old_protect;
			VirtualProtect(og_idxgi_swap_chain_present, 2, PAGE_EXECUTE_READWRITE, &old_protect);
		}
	}
}

void retrieve_values()
{
	const DWORD_PTR h_dxgi = reinterpret_cast<DWORD_PTR>(GetModuleHandle(L"dxgi.dll"));

	fn_idxgi_swap_chain_present = reinterpret_cast<IDXGISwapChainPresent>(static_cast<DWORD_PTR>(h_dxgi) + 0x4670);
}

LRESULT CALLBACK DXGIMsgProc(const HWND hwnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

void  get_present()
{
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 2;
	sd.BufferDesc.Height = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	D3D_FEATURE_LEVEL FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT numFeatureLevelsRequested = 1;
	D3D_FEATURE_LEVEL FeatureLevelsSupported;
	HRESULT hr;
	IDXGISwapChain* swapchain = 0;
	ID3D11Device* dev = 0;
	ID3D11DeviceContext* devcon = 0;
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&FeatureLevelsRequested,
		numFeatureLevelsRequested,
		D3D11_SDK_VERSION,
		&sd,
		&swapchain,
		&dev,
		&FeatureLevelsSupported,
		&devcon)))
	{
		return;
	}
	DWORD_PTR* pSwapChainVtable = (DWORD_PTR*)swapchain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	fn_idxgi_swap_chain_present = (IDXGISwapChainPresent)pSwapChainVtable[8];

	fn_idxgi_swap_chain_resize_buffers = (ResizeBuffers)pSwapChainVtable[13];
	g_present_hooked = true;
	Sleep(2000);

	SAFE_RELEASE(dev)
		SAFE_RELEASE(devcon);
	SAFE_RELEASE(swapchain);
}

void ui::hook_ui()
{
	get_present();

	// If GetPresent failed we have this backup method to get Present Address
	if (!g_present_hooked) {
		retrieve_values();
	}

	// After this call, Present should be hooked and controlled by me.
	detour_directx_resize_buffers();
	detour_directx_present();

	while (!g_b_initialized) {
		Sleep(1000);
	}
}

void ui::unhook_ui()
{
	MH_RemoveHook(fn_idxgi_swap_chain_resize_buffers);
	MH_RemoveHook(fn_idxgi_swap_chain_present);

	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	//ImGui::DestroyContext();

	p_device->Release();
	p_context->Release();
	p_swap_chain->Release();
}

//BOOL APIENTRY DllMain(HMODULE hModule,
//	DWORD  ul_reason_for_call,
//	LPVOID lpReserved
//)
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//	{
//		DisableThreadLibraryCalls(hModule);
//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
//	}
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		break;
//	}
//	return TRUE;
//}