#pragma once

class logging
{
public:
	static void init();
	/**
	 * \brief The loggers log level (debug,trace, etc)
	 */
	static inline int log_level;
	/**
	 * \brief Wherever to log to a file or not.
	 */
	static inline bool log_to_file;
};
