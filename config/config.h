#pragma once
class config
{
public:
#if defined _DEBUG
	static void test();
#endif

	static bool create_new();
	static bool load();
};
