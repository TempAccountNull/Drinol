#pragma once
namespace memory
{
	static void patch(char* dst, char* src, int size);
	std::uint8_t* pattern_scan(void* module, const char* signature);
	static void nop(char* dst, unsigned size);
	SIZE_T ReadPtr(SIZE_T Address, UINT Offset);
	;
}