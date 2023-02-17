#pragma once
#include <cstdint>

namespace halo1::engine // Engine related structs, etc
{
	//Generated by reclass.net
	class _hs_external_globals // This is the array of globals that halo uses for its scripting system.
	{
	public:
		class hs_external_global* globals[466]; //0x0000 The list of globals.
		// 466 is the hardcoded total number of globals in this array TODO: Fetch this dynamically somehow?
	}; //Size: 0x0E90
	static_assert(sizeof(_hs_external_globals) == 0xE90);

	class hs_external_global
	{
	public:
		char* name; //0x0000 Name of the global
		int64_t param_type; //0x0008 parameter type (unparsed, float, bool, etc)
		void* address; //0x0010 // The address of the global
	}; //Size: 0x0018
	static_assert(sizeof(hs_external_global) == 0x18);

	class _hs_type_names
	{
	public:
		char* types[49]; //0x0000 List of parameter types in the form of a string.
		// 49 is the total number of types in this array TODO: Fetch this dynamically somehow?
	}; //Size: 0x0188
	static_assert(sizeof(_hs_type_names) == 0x188);
}
