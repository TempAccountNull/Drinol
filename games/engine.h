#pragma once
// This stores engine information that stays the same between all the halo games in MCC.

typedef float real; // Blam calls floats reals, idk why

union real_vector3d
{
	struct
	{
		real i;
		real j;
		real k;
	};
	real n[3];
};
static_assert(sizeof(real_vector3d) == 0xC);