#pragma once

namespace groundhog
{
	class game
	{
	public:
		static void settings_init();
		static void init();
		static void deinit();

		/**
		* \brief Grabs the address from the restricted region member
		* \param alias_index
		* \param member_index
		* \param index
		* \return
		*/
		/*	static void* get_restricted_region_member_address(int alias_index, int member_index, int index);*/
		static void test_function();
	};
}
