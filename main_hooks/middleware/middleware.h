#pragma once

// This is for managing things related to the MCC UE4 middleware.
namespace middleware
{
	class hooks
	{
	public:

		/**
		 * \brief initializes MCC UE4 middleware hook stuff.
		 */
		static void init();
		static void deinit();
	};
};
