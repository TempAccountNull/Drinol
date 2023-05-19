#pragma once

// THIS SHOULD HAVE HEADER FILES THAT DONT CHANGE

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include <cassert>
#include <commctrl.h>
#include <cstdio>
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <iostream>
#include <memory>
#include <ntpebteb.h>
#include <ostream>
#include <Psapi.h>
#include <regex>
#include <ShellAPI.h>
#include <cstdint>
#include <unordered_map>
#include <xstring>

#include "console.h"
#include "detour.h"
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "kiero/kiero.h"
#include "logging/logging.h"
#include "memcury/memcury.h"
#include "Memcury/memcury.h"
#include "middleware/middleware.h"
#include "middleware/middleware_sigs.h"
#include "minhook/include/MinHook.h"
#include "mINI/src/mini/ini.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/bundled/color.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "version_checking/version_checking.h"

// Included by NightFyre
//	Global BOOL, Should be used to handle execution flow. When the bit is flipped everything should begin shutting down.
//	Example: Initialize Console -> Initialize Hooks -> Initialize GUI -> DEinitialize GUI -> DEinitialize Hooks -> Deinitialize Console
//	Cleanup should be performed in reverse order
///	~
//	@TODO: kiero::shutdown currently has no method of restoring windowlongptr for mouse interaction (wndproc)
//	The issue with console causing a crash at exit has been resolved , this solution has revealed an error in the GUI deinitialization process
//	- Temporary killswitch has been included for now as a solution but a proper method should be implemented at some point as this may not always work as intended

inline std::atomic_bool g_Running = TRUE;
inline std::atomic_bool g_Killswitch = FALSE;