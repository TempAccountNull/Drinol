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
	 * \brief creates a new config file containing the main settings of drinol.
	 * \return true if created successfully
	 */
	static bool create_new_main_settings();
	/**
	 * \brief loads the config file containing the main settings of drinol.
	 * \return true if loaded successfully
	 */
	static bool load_main_settings();
	/**
	 * \brief Create a directory to store all the config files (keeps things tidy :p)
	 * \return true if created successfully
	 */
	static bool create_config_folder();
	/**
	 * \brief loads the config file containing AOB signatures needed for drinol.
	 * \return true if loaded successfully
	 */
	static bool load_signatures();
	/**
 * \brief creates a new config file containing AOB signatures needed for drinol.
 * \return true if loaded successfully
 */
	static bool create_new_signatures();
};
