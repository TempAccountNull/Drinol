// Most of this code is from https://github.com/Gavpherk/Universal-IL2CPP-DX11-Kiero-Hook
#include "gui.h"

#include <algorithm>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>

#include "imgui.h"
#include "utils.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "kiero/kiero.h"
#include "menu/menu.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.IniFilename = gui::ui_ini_path.c_str();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool show = false;
bool init = false;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
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
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	// Tpggle our menu if the insert key is pressed
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show = !show;
	}

	//if (GetAsyncKeyState(VK_DELETE) & 1)
	//{
	//	kiero::shutdown();
	//	return 0;
	//}

	if (show)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Render our menu!
		menu::render();

		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent(pSwapChain, SyncInterval, Flags);
}

void gui::init()
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
#if defined _DEBUG
		std::cout << "kiero initialized." << std::endl;
#endif
		kiero::bind(8, (void**)&oPresent, hkPresent);
	}
}