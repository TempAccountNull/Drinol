// This has function hooks and other things related to the games UE4 middleware.
#include "middleware.h"

#include <cassert>
#include <iostream>
#include <Memcury/memcury.h>
#include <minhook/include/MinHook.h>

#include "utils.h"

//Crappily reverse engineered struct from the MCC UE4 binary.
typedef struct {
	char padding[180192];
	HMODULE module; // Handle to the games dll.
	DWORD  unkdword;
	int  number; // Games index number (a number between 0 and 6)
}struct_game;

static void (*start_game_engine_og)(struct_game a1, int game_number);

static void __fastcall start_game_engine_detour(struct_game a1, int game_number)
{
	//TODO: There is probably a better way to find the currently running game in memory, more research required.

	//Check if the game is already running
	if (a1.number == game_number)
		return start_game_engine_og(a1, game_number);

	// If this gets triggered, something is wrong.
	assert(game_number <= 6);

	//TODO: Trigger game related hooks and stuff now that we know that a game has launched and what game it is.
	utils::handle_game_init(game_number);

	return start_game_engine_og(a1, game_number);
}

static __int64 (*UICommandOverlayPush_og)(INT64 a1, char* a2, int a3);

static __int64 __fastcall ui_command_overlay_push_detour(INT64 a1, char* a2, int a3)
{
	if (strcmp(a2, "RestartScreen") == 0)
	{
#if defined _DEBUG
		puts("Game has ended.\n");
#endif
		//TODO: Deinit game related hooks and stuff now that we know that the game has ended.
		utils::running_game.clear();
		//utils::handle_game_deinit();
	}

	return UICommandOverlayPush_og(a1, a2, a3);
}

void middleware::init()
{
	void* start_game_engine_t = Memcury::Scanner::FindPattern("83 FF 06 77 1A").FindFunctionBoundary(false).GetAs<void*>();

	if (MH_CreateHook(start_game_engine_t, &start_game_engine_detour, reinterpret_cast <LPVOID*> (&start_game_engine_og)) != MH_OK) {
		throw std::runtime_error("failed to hook start_game_engine");
	}

	void* UICommandOverlayPush_t = Memcury::Scanner::FindPattern("41 83 C9 FF 4C 8B C5").FindFunctionBoundary(false).GetAs<void*>();

	if (MH_CreateHook(UICommandOverlayPush_t, &ui_command_overlay_push_detour, reinterpret_cast <LPVOID*> (&UICommandOverlayPush_og)) != MH_OK) {
		throw std::runtime_error("failed to hook UICommandOverlayPush");
	}

	MH_QueueEnableHook(start_game_engine_t);
	MH_QueueEnableHook(UICommandOverlayPush_t);
	MH_ApplyQueued();
}