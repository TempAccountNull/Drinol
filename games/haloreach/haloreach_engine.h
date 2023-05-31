#pragma once

namespace haloreach::engine // Engine related structs, etc
{
	// search the string: hs_doc.txt to find the functions that contain the amount of globals, and functions

		//Generated by reclass.net

	enum e_hs_type : __int16 {
		hs_type_unparsed = 0,
		hs_type_special_form,
		hs_type_function_name,
		hs_type_passthrough,
		hs_type_void,
		hs_type_boolean,
		hs_type_real,
		hs_type_short,
		hs_type_long,
		hs_type_string,
		hs_type_script,
		hs_type_string_id,
		hs_type_unit_seat_mapping,
		hs_type_trigger_volume,
		hs_type_cutscene_flag,
		hs_type_cutscene_camera_point,
		hs_type_cutscene_title,
		hs_type_cutscene_recording,
		hs_type_device_group,
		hs_type_ai,
		hs_type_ai_command_list,
		hs_type_ai_command_script,
		hs_type_ai_behavior,
		hs_type_ai_orders,
		hs_type_ai_line,
		hs_type_starting_profile,
		hs_type_conversation,
		hs_type_player,
		hs_type_zone_set,
		hs_type_designer_zone,
		hs_type_point_reference,
		hs_type_style,
		hs_type_object_list,
		hs_type_folder,
		hs_type_sound,
		hs_type_effect,
		hs_type_damage,
		hs_type_looping_sound,
		hs_type_animation_graph,
		hs_type_damage_effect,
		hs_type_object_definition,
		hs_type_bitmap,
		hs_type_shader,
		hs_type_render_model,
		hs_type_structure_definition,
		hs_type_lightmap_definition,
		hs_type_cinematic_definition,
		hs_type_cinematic_scene_definition,
		hs_type_cinematic_transition_definition,
		hs_type_bink_definition,
		hs_type_cui_screen_definition,
		hs_type_any_tag,
		hs_type_any_tag_not_resolving,
		hs_type_game_difficulty,
		hs_type_team,
		hs_type_mp_team,
		hs_type_controller,
		hs_type_button_preset,
		hs_type_joystick_preset,
		hs_type_player_color,
		hs_type_player_model_choice,
		hs_type_voice_output_setting,
		hs_type_voice_mask,
		hs_type_subtitle_setting,
		hs_type_actor_type,
		hs_type_model_state,
		hs_type_event,
		hs_type_character_physics,
		hs_type_skull,
		hs_type_firing_point_evaluator,
		hs_type_damage_region,
		hs_type_object,
		hs_type_unit,
		hs_type_vehicle,
		hs_type_weapon,
		hs_type_device,
		hs_type_scenery,
		hs_type_effect_scenery,
		hs_type_object_name,
		hs_type_unit_name,
		hs_type_vehicle_name,
		hs_type_weapon_name,
		hs_type_device_name,
		hs_type_scenery_name,
		hs_type_effect_scenery_name,
		hs_type_cinematic_lightprobe,
		hs_type_animation_budget_reference,
		hs_type_looping_sound_budget_reference,
		hs_type_sound_budget_reference,
	};

	/**
 * \brief the table of functions that are used in halos scripting system.
 */
	class _hs_function_table
	{
	public:
		class hs_function_definition* table[1914]; //0x0000
	}; //Size: 0x3B78

	class hs_function_definition
	{
	public:
		e_hs_type return_type; //0x0000
		int16_t flags; //0x0002
		int32_t unused; //0x0004
		char* name; //0x0008
		uint64_t unk10; //0x0010
		void* parse_func; //0x0018
		void* evaluate_func; //0x0020
		int64_t UNK28; //0x0028
		int64_t UNK30; //0x0030
		int16_t argument_count; //0x0038
		e_hs_type params[0]; //0x003A
	}; //Size: 0x003C
	//static_assert(sizeof(hs_function_definition) == 0x3C);

	/**
	 * \brief the table of globals that are used in halos scripting system.
	 */
	class _hs_external_globals
	{
	public:
		class hs_external_global* globals[1724]; //0x0000 The list of globals.
		// 466 is the hardcoded total number of globals in this array TODO: Fetch this dynamically somehow?
	}; //Size: 0x2930
	static_assert(sizeof(_hs_external_globals) == 0x35E0);

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
		char* types[89]; //0x0000 List of parameter types in the form of a string.
		// 89 is the total number of types in this array TODO: Fetch this dynamically somehow?
	}; //Size: 0x0298
	static_assert(sizeof(_hs_type_names) == 0x2C8);
}
