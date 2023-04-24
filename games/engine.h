#pragma once
// This stores engine information that stays the same between all the halo games in MCC.

typedef float real; // Blam calls floats reals, idk why

typedef unsigned long long qword;
static_assert(sizeof(qword) == 0x8);

typedef unsigned long datum_index;
static_assert(sizeof(datum_index) == 0x4);

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

struct real_matrix4x3
{
	real scale;
	real_vector3d forward;
	real_vector3d left;
	real_vector3d up;
	real_vector3d center;
};
static_assert(sizeof(real_matrix4x3) == 0x34);

// From https://github.com/theTwist84/ManagedDonkey/blob/90f18b3000a9d5d3f54f4de1cb280656faf2a9c7/game/source/game/player_mapping.hpp
struct s_player_mapping_globals
{
	short active_input_user_count;
	short active_input_controller_count;
	long input_user_player_mapping[4];
	datum_index input_user_unit_mapping[4];
	long input_controller_player_mapping[4];
	long player_input_controller_mapping[16];
	datum_index player_input_user_mapping[16];
	short active_output_user_count;
	short : 16;
	long output_user_player_mapping[4];
	long output_user_unit_mapping[4];
	byte player_output_user_mapping[16];
};
static_assert(sizeof(s_player_mapping_globals) == 0xE8);

enum e_restricted_memory_region
{
	k_game_state_header_region = 0,
	k_game_state_update_region,
	k_game_state_render_region,
	k_game_state_shared_region,
	k_global_render_data_region,

	k_total_restricted_memory_regions
};

struct c_restricted_section
{
	unsigned long m_internal_flags;
	unsigned long __unknown4;
	unsigned long m_external_lock;
	unsigned char* m_address;
	unsigned long long m_size;
	unsigned long m_owner_thread;
};

struct c_restricted_memory
{
	struct s_mirror_slot
	{
		volatile long valid;
		volatile long readable_flag;
		volatile long __unknown8;
		c_restricted_section* restricted_section;
	};

#pragma pack(push, 4)
	struct s_registered_member
	{
		char __data0[0x4];
		unsigned long reserved_size;
		char __data8[0x4];
		unsigned long offset;
		long : 32;
		unsigned long size;
		long : 32;
		void* update_function;
		char __data24[0xC];
	};
#pragma pack(pop)

	volatile long m_mirror_read_in_progress;
	volatile long m_mirror_write_in_progress;
	s_mirror_slot m_mirrors[4];
	volatile long __unknown68;
	volatile long __unknown6C;
	char __data70[0x8];
	volatile long m_alias_allowed;
	volatile long m_alias_count;
	c_restricted_section* m_primary_section;
	unsigned long m_initialized; // flags
	char __data8C[0x4];
	unsigned long long m_subsection_size;
	unsigned long long m_reserved_size;
	long m_mirror_count;
	unsigned long m_mirror_section;
	long m_registered_member_count;
	s_registered_member m_registered_member[128];
	char __data18AC[0x4];
	struct c_restricted_memory_callbacks* m_callbacks; // this can be ignore _for now_
	char __data18B8[0x10];
	unsigned long m_region_index;
	char __data18CC[0x4];
	HANDLE m_mirror_available_event; // event handle
};
