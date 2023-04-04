#pragma once

#include "framework.h"
#include <minhook/include/MinHook.h>

class detour {
public:
	detour();
	~detour();

	bool create(uintptr_t location, void* function);

	template <typename T = void, typename... Args>
	T stub(Args ... args)
	{
		return static_cast<T(*)(Args ...)>(_stub)(args...);
	}

	bool enable();
	bool disable();

private:
	uintptr_t _location;
	void* _function;
	void* _stub;
};
