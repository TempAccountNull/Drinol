#pragma once

class config
{
public:

	class main
	{
	public:
		/**
* \brief the folder containing all the config files.
*/
		inline static std::string config_folder;

		/**
		 * \brief creates a new config file containing the main settings of drinol.
		 * \return true if created successfully
		 */
		static bool create();
		/**
		 * \brief loads the config file containing the main settings of drinol.
		 * \return true if loaded successfully
		 */
		static bool load();
		/**
		 * \brief saves the config file containing the main settings of drinol.
		 * \return true if saved successfully
		 */
		static bool save();
		/**
		 * \brief Create a directory to store all the config files (keeps things tidy :p)
		 * \return true if created successfully
		 */
		static bool create_config_folder();
	};

	class sigs
	{
	public:
		/**
 * \brief loads the config file containing AOB signatures needed for drinol.
 * \return true if loaded successfully
 */
		static bool load();
		/**
	 * \brief creates a new config file containing AOB signatures needed for drinol.
	 * \return true if created successfully
	 */
		static bool create();
		/**
		 * \brief Checks the signatures to make sure they are valid (not empty)
		 * \return true if valid
		 */
		static bool validate();
	};

	class games
	{
	public:
		class halo_1
		{
		public:
			/**
			 * \brief creates a new config file containing settings related to Halo 1 Anniversary.
			 * \return true if created successfully
			 */
			static bool create();
			/**
		 * \brief saves to the config file containing settings related to Halo 1 Anniversary.
		 * \return true if saved successfully
		*/
			static bool save();
			/**
			 * \brief loads the config file containing settings related to Halo 1 Anniversary.
			 * \return true if loaded successfully
			 */
			static bool load();
		};

		class halo_2
		{
		public:
			/**
			 * \brief creates a new config file containing settings related to Halo 1 Anniversary.
			 * \return true if created successfully
			 */
			static bool create();
			/**
		 * \brief saves to the config file containing settings related to Halo 1 Anniversary.
		 * \return true if saved successfully
		*/
			static bool save();
			/**
			 * \brief loads the config file containing settings related to Halo 1 Anniversary.
			 * \return true if loaded successfully
			 */
			static bool load();
		};

		class halo_3
		{
		public:
			/**
			 * \brief creates a new config file containing settings related to Halo 1 Anniversary.
			 * \return true if created successfully
			 */
			static bool create();
			/**
		 * \brief saves to the config file containing settings related to Halo 1 Anniversary.
		 * \return true if saved successfully
		*/
			static bool save();
			/**
			 * \brief loads the config file containing settings related to Halo 1 Anniversary.
			 * \return true if loaded successfully
			 */
			static bool load();
		};

		class halo_4
		{
		public:
			/**
			 * \brief creates a new config file containing settings related to Halo 1 Anniversary.
			 * \return true if created successfully
			 */
			static bool create();
			/**
		 * \brief saves to the config file containing settings related to Halo 1 Anniversary.
		 * \return true if saved successfully
		*/
			static bool save();
			/**
			 * \brief loads the config file containing settings related to Halo 1 Anniversary.
			 * \return true if loaded successfully
			 */
			static bool load();
		};

		class halo2_amp
		{
		public:
			/**
			 * \brief creates a new config file containing settings related to Halo 1 Anniversary.
			 * \return true if created successfully
			 */
			static bool create();
			/**
		 * \brief saves to the config file containing settings related to Halo 1 Anniversary.
		 * \return true if saved successfully
		*/
			static bool save();
			/**
			 * \brief loads the config file containing settings related to Halo 1 Anniversary.
			 * \return true if loaded successfully
			 */
			static bool load();
		};
	};
};
