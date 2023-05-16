#pragma once
#include <cstdint>

#include "games/engine.h"

namespace halo3::engine // Engine related structs, etc
{
	// search the string: hs_doc.txt to find the functions that contain the amount of globals, and functions

		//Generated by reclass.net
		/**
	 * \brief the table of functions that are used in halos scripting system.
	 */
	class _hs_function_table
	{
	public:
		class _hs_script_op* table[1528]; //0x0000
	}; //Size: 0x2FC0
	static_assert(sizeof(_hs_function_table) == 0x2FC0);

	class _hs_script_op
	{
	public:
		int16_t return_type; //0x0000
		int16_t flags; //0x0002
		int32_t unused; //0x0004
		char* name; //0x0008
		char pad_0010[8]; //0x0010
		void* parse_func; //0x0018
		void* evaluate_func; //0x0020
	}; //Size: 0x0028
	static_assert(sizeof(_hs_script_op) == 0x28);

	/**
	 * \brief the table of globals that are used in halos scripting system.
	 */
	class _hs_external_globals
	{
	public:
		class hs_external_global* globals[1318]; //0x0000 The list of globals.
		// 466 is the hardcoded total number of globals in this array TODO: Fetch this dynamically somehow?
	}; //Size: 0x2930
	static_assert(sizeof(_hs_external_globals) == 0x2930);

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
		char* types[83]; //0x0000 List of parameter types in the form of a string.
		// 83 is the total number of types in this array TODO: Fetch this dynamically somehow?
	}; //Size: 0x0298
	static_assert(sizeof(_hs_type_names) == 0x298);

	class s_game_tick_time_samples
	{
	public:
		uint32_t flags; //0x0000
		float N00000EAC; //0x0004
		float N00000EAE; //0x0008
		float N00000EB7; //0x000C
		uint32_t N00000EB9; //0x0010
	}; //Size: 0x0014
	static_assert(sizeof(s_game_tick_time_samples) == 0x14);

	class game_time_globals_definition
	{
	public:
		bool initialized; //0x0000
		uint8_t N00000E99; //0x0001
		uint16_t flags; //0x0002
		uint16_t tick_rate; //0x0004
		uint16_t N00000E9A; //0x0006
		float seconds_per_tick; //0x0008
		uint32_t elapsed_ticks; //0x000C
		float speed; //0x0010
		float game_ticks_leftover; //0x0014
		class s_game_tick_time_samples time_samples; //0x0018
	}; //Size: 0x002C
	static_assert(sizeof(game_time_globals_definition) == 0x2C);

	// Thanks to https://github.com/matty45/Drinol/commit/e454d79474b7923d0fc507a5efba6ddf705679f5#commitcomment-106396372
	struct s_physics_constants
	{
		real gravity;
		real water_density;
		real air_density;
		real_vector3d velocity_frame;
		long character_ground_adhesion_forces_enable_time;
		real lip_surface_maximum_k;
	};
	static_assert(sizeof(s_physics_constants) == 0x20);

	enum e_shield_recharge_rate_percentage_setting : unsigned char
	{
		_shield_recharge_rate_percentage_setting_unchanged = 0,

		_shield_recharge_rate_percentage_setting_negative_25_percent, // -0.25
		_shield_recharge_rate_percentage_setting_negative_10_percent, // -0.1
		_shield_recharge_rate_percentage_setting_negative_5_percent,  // -0.05
		_shield_recharge_rate_percentage_setting_0_percent,           // 0.0
		_shield_recharge_rate_percentage_setting_50_percent,          // 0.5
		_shield_recharge_rate_percentage_setting_90_percent,          // 0.9
		_shield_recharge_rate_percentage_setting_100_percent,         // 1.0
		_shield_recharge_rate_percentage_setting_110_percent,         // 1.1
		_shield_recharge_rate_percentage_setting_200_percent,         // 2.0

		k_shield_recharge_rate_percentage_settings,
		k_shield_recharge_rate_percentage_setting_default = _shield_recharge_rate_percentage_setting_100_percent
	};

	struct c_player_trait_shield_vitality
	{
		unsigned char m_damage_resistance_percentage_setting;
		e_shield_recharge_rate_percentage_setting m_shield_recharge_rate_percentage_setting;
		unsigned char m_vampirism_percentage_setting;
		unsigned char m_headshot_immunity_setting;
		unsigned char m_shield_multiplier_setting;
		unsigned char pad[3];
	};
	struct c_player_trait_weapons
	{
		short m_initial_grenade_count;
		char m_initial_primary_weapon_absolute_index;
		char m_initial_secondary_weapon_absolute_index;
		unsigned char m_damage_modifier_percentage_setting;
		unsigned char m_recharging_grenades_setting;
		unsigned char m_infinite_ammo_setting;
		unsigned char m_weapon_pickup_allowed_setting;
	};
	struct c_player_trait_movement
	{
		unsigned char m_speed_setting;
		unsigned char m_gravity_setting;
		unsigned char m_vehicle_usage_setting;
		unsigned char pad[1];
	};

	enum active_camo_settings : unsigned char
	{
		unchanged = 0,
		off,
		poor,
		good,
		invisible
	};

	enum e_waypoint_setting : unsigned char
	{
		// UNCHANGED
		_waypoint_setting_unchanged = 0,

		// OFF
		_waypoint_setting_off,

		// ALLIES
		_waypoint_setting_allies,

		// ALL
		_waypoint_setting_all,

		k_waypoint_settings
	};

	enum e_aura_setting : unsigned char
	{
		// UNCHANGED
		_aura_setting_unchanged = 0,

		// OFF
		_aura_setting_off,

		// TEAM COLOR
		_aura_setting_team_color,

		// BLACK
		_aura_setting_black,

		// WHITE
		_aura_setting_white,

		k_aura_settings
	};

	enum e_forced_change_color_setting : unsigned char
	{
		// UNCHANGED
		_forced_change_color_setting_unchanged = 0,

		// OFF
		_forced_change_color_setting_off,

		// RED
		_forced_change_color_setting_mp_team_red,

		// BLUE
		_forced_change_color_setting_mp_team_blue,

		// GREEN
		_forced_change_color_setting_mp_team_green,

		// YELLOW
		_forced_change_color_setting_mp_team_yellow,

		// PURPLE
		_forced_change_color_setting_mp_team_purple,

		// ORANGE
		_forced_change_color_setting_mp_team_orange,

		// BROWN
		_forced_change_color_setting_mp_team_brown,

		// GREY (PINK)
		_forced_change_color_setting_mp_team_grey,

		// XTRA 1 (PRIMARY COLOR)
		_forced_change_color_setting_extra1,

		// XTRA 2 (SECONDARY COLOR)
		_forced_change_color_setting_extra2,

		// XTRA 3 (TERTIARY COLOR)
		_forced_change_color_setting_extra3,

		// XTRA 4 (QUATERNARY COLOR)
		_forced_change_color_setting_extra4,

		k_forced_change_color_settings
	};

	struct c_player_trait_appearance
	{
		active_camo_settings m_active_camo_setting;
		e_waypoint_setting m_waypoint_setting;
		e_aura_setting m_aura_setting;
		e_forced_change_color_setting m_forced_change_color_setting;
	};
	struct c_player_trait_sensors
	{
		unsigned short m_motion_tracker_setting;
		unsigned short m_motion_tracker_range_setting;
	};

	struct c_player_traits
	{
		c_player_trait_shield_vitality m_shield_traits;
		c_player_trait_weapons m_weapon_traits;
		c_player_trait_movement m_movement_traits;
		c_player_trait_appearance m_appearance_traits;
		c_player_trait_sensors m_sensor_traits;
	};
	static_assert(sizeof(c_player_traits) == 0x1C);

	struct player_datum
	{
		char __data0[0x4];
		unsigned long flags;
		char player_identifier[8];
		unsigned long time;
		char machine_identifier[6];
		short machine_index;
		short machine_user_index;
		long machine_controller_index;
		long controller_index;
		unsigned long unit_index;
		unsigned long dead_unit_index;
		char __data30[0x14];
		char next_spawn_control_context;
		char __data45[0x13];
		char configuration[0xA0];
		char desired_configuration[0xA0];
		char __data2C8[0x56];
		unsigned short lives_remaining;
		unsigned long __unknown320;
		char __data324[0x4];
		c_player_traits player_traits;
		char __data344[0xC];
		long respawn_target_player_index;
		char __data[0xCC];
	};

	struct s_data_array
	{
		char name[32];
		unsigned long maximum_count;
		long size;
		unsigned char alignment_bits;
		unsigned char valid;
		unsigned short flags;
		unsigned long signature;
		void* allocation;
		long next_index;
		long first_unallocated;
		long actual_count;
		unsigned short next_identifier;
		unsigned short isolated_next_identifier;
		char* data;
		unsigned long* in_use_bit_vector;
		long offset_to_data;
		long offset_to_bit_vector;
	};

	struct s_thread_local_storage
	{
		void* __unknown0[2];
		s_data_array* player_data;
		int g_registered_thread_index;
		void* __unknown20[3];
		s_data_array* object_header;
		void* __unknown40[162];
		unsigned int* g_deterministic_random_seed_ptr;
		void* __unknown558[8];
		unsigned __int8* g_restricted_address[5];
		void* __unknown5C0[22];
	};

	enum game_tls_index // TLS indexes used in Halo 3
	{
		in_progress = 72,
		physics_constants = 304,
		player_mapping_globals = 272
	};
}
