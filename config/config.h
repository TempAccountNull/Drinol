#pragma once
#include <string>

class config
{
public:

	/**
 * \brief the folder containing all the config files.
 */
	static inline std::string config_folder;

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
