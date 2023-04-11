#pragma once
#include "spdlog/common.h"

class logging
{
public:
	static void init();
	static inline int log_level;
};
