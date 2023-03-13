#pragma once
class config
{
public:
#if defined _DEBUG
	static void test();
#endif

	/**
	 * \brief creates a new config.
	 * \return true if created successfully
	 */
	static bool create_new();
	/**
	 * \brief loads the config
	 * \return true if loaded successfully
	 */
	static bool load();
};
