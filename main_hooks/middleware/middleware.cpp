// This has function hooks and other things related to the games UE4 middleware.
#include "stdafx.h"

//Crappily reverse engineered struct from the MCC UE4 binary.
typedef struct {
	char padding[180192];
	HMODULE module; // Handle to the games dll.
	DWORD  unkdword;
	int  number; // Games index number (a number between 0 and 6)
}struct_game;

bool game_running = false;

detour start_game_engine;
static void __fastcall start_game_engine_detour(struct_game a1, int game_number)
{
	//TODO: There is probably a better way to find the currently running game in memory, more research required.

	//Check if the game is already running
	if (a1.number == game_number)
		return start_game_engine.stub<void>(a1, game_number);

	// If this gets triggered, something is wrong.
	assert(game_number <= 6);

	if (game_running)
	{
		//TODO: Trigger game related hooks and stuff now that we know that a game has launched and what game it is.
		utils::handle_game_init(game_number);
	}

	return start_game_engine.stub<void>(a1, game_number);
}

detour  ui_command_overlay_push;
static __int64 __fastcall ui_command_overlay_push_detour(INT64 a1, char* a2, int a3)
{
	if (strcmp(a2, "RestartScreen") == 0 || strcmp(a2, "GlobalOverlay") == 0)
	{
		if (game_running)
		{
			game_running = false;
#if defined _DEBUG
			spdlog::debug("Game has ended.");
#endif
			//TODO: Deinit game related hooks and stuff now that we know that the game has ended.
			utils::handle_game_deinit();
			utils::running_game.clear();
		}
		return ui_command_overlay_push.stub<__int64>(a1, a2, a3);
	}

	if (strcmp(a2, "LoadingScreen") == 0)
	{
		game_running = true;
		return ui_command_overlay_push.stub<__int64>(a1, a2, a3);
	}

	return ui_command_overlay_push.stub<__int64>(a1, a2, a3);
}

void middleware::init()
{
	void* start_game_engine_t = Memcury::Scanner::FindPattern(start_game_engine_t_aob_sig.c_str()).FindFunctionBoundary(false).GetAs<void*>();

	void* UICommandOverlayPush_t = Memcury::Scanner::FindPattern(UICommandOverlayPush_t_aob_sig.c_str()).FindFunctionBoundary(false).GetAs<void*>();

	start_game_engine.create(reinterpret_cast<uintptr_t>(start_game_engine_t), start_game_engine_detour);
	ui_command_overlay_push.create(reinterpret_cast<uintptr_t>(UICommandOverlayPush_t), ui_command_overlay_push_detour);

	MH_ApplyQueued();
}

void middleware::deinit()
{
	start_game_engine.disable();
	ui_command_overlay_push.disable();

	MH_ApplyQueued();
}