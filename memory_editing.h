#pragma once
namespace memory
{
		static void patch(char* dst, char* src, int size);
		static void nop(char* dst, unsigned size);
;
}