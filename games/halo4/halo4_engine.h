#pragma once
#include "games/engine.h"

namespace halo4::engine // Engine related structs, etc
{
	struct s_physics_constants
	{
		real gravity;
		real water_density;
		real air_density;
		real_vector3d velocity_frame;
		int character_ground_adhesion_forces_enable_time;
		real lip_surface_maximum_k;
	};

	struct s_thread_local_storage
	{
		BYTE gap0[32];
		int g_registered_thread_index;
		BYTE gap24[524];
		qword qword230;
		BYTE gap238[1256];
		unsigned __int8* g_restricted_address[5];
	};
}
