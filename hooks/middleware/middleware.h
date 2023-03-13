#pragma once
#include "mINI/src/mini/ini.h"

// This is for managing things related to the MCC UE4 middleware.
class middleware
{
public:
	/**
	 * \brief initializes MCC UE4 middleware hook stuff.
	 */
	static void init();
	static inline std::string start_game_engine_t_aob_sig;
	static inline std::string UICommandOverlayPush_t_aob_sig;
};
