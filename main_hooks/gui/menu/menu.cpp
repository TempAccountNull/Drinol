// This is our custom menu.
#include "stdafx.h"

bool show_load_modal = false;

bool show_save_modal = false;

bool show_about_modal = false;

bool show_restore_defaults_modal = false;

bool show_detach_modal = false;

int test_int = 0;

void menu::render()
{
	ImGui::Begin("Drinol", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	// Menu Bar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (!utils::running_game.empty())
			{
				if (ImGui::MenuItem("Load Game Changes")) { show_load_modal = true; }
				if (ImGui::MenuItem("Save Game Changes")) { show_save_modal = true; }
				if (ImGui::MenuItem("Restore Game Defaults")) { show_restore_defaults_modal = true; }
			}

			if (ImGui::MenuItem("Toggle Console")) { console_enabled = !console_enabled; }
			//if (ImGui::MenuItem("Save Menu Changes")) { show_save_menu_modal = true; }
			if (ImGui::MenuItem("Detach Drinol")) { show_detach_modal = true; }

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About")) { show_about_modal = true; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// The meat of the menu
	if (ImGui::BeginTabBar("DrinolTabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Status"))
		{
			// Status of Drinol, blah
			if (!utils::running_game.empty())
			{
				ImGui::Text("Currently running game: %s", utils::running_game.c_str());
			}
			else
			{
				ImGui::Text("No game is running currently.");
			}

			ImGui::EndTabItem();
		}

#if defined _DEBUG
		if (ImGui::BeginTabItem("Debug"))
		{
			ImGui::DragInt("Test Int", &test_int, 1, 0, 100, "%i", ImGuiSliderFlags_None);
			if (ImGui::Button("Trigger Test Function"))
				utils::test_func(test_int);
			if (ImGui::Button("List Game Base Addresses"))
				utils::list_game_base_addresses();
			ImGui::EndTabItem();
		}
#endif

		// TODO: ideally we should show all the games and just grey out the stuff you cant interact with if a certain game is not running
#pragma region Halo 1 Menu
		if (utils::running_game == "Halo 1 Anniversary")
		{
			if (ImGui::BeginTabItem("Halo 1"))
			{
				if (ImGui::BeginTabBar("Halo1Tabs", ImGuiTabBarFlags_None))
				{
#if defined _DEBUG
					if (ImGui::BeginTabItem("Debug"))
					{
						if (ImGui::Button("Trigger Test Function"))
							halo1::game::test_function();

						if (ImGui::Button("Print all blamscript functions."))
							halo1::game::list_all_hs_functions();

						if (ImGui::Button("Print all blamscript globals."))
							halo1::game::list_all_hs_globals();

						ImGui::EndTabItem();
					}
#endif

					if (ImGui::BeginTabItem("Weapons"))
					{
						ImGui::Checkbox("Bottomless Clip", halo1::offsets::bottomless_clip);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Gives you infinite ammo without the need to reload or worry about your weapon overheating.");

						ImGui::Checkbox("Infinite Ammo", halo1::offsets::infinite_ammo);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Same as bottomless clip but you have to reload, can still overheat and have infinite grenades.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Player"))
					{
						ImGui::Checkbox("God Mode", halo1::offsets::god_mode);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Makes you unable to die.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Game"))
					{
						ImGui::DragFloat("Game ticks per second.", halo1::offsets::game_ticks_per_second, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Basically the speed/time scale of the game. Default: 30.0");

						ImGui::DragFloat("Gravity", *halo1::offsets::gravity, 0.005f, -FLT_MAX, +FLT_MAX, "%.5f", ImGuiSliderFlags_None);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("The gravity, nuff said. Note: Not savable.");

						ImGui::Checkbox("Motion Sensor - Show All Units", halo1::offsets::motion_sensor_show_all_units);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Shows all units on your motion sensor, regardless if they are moving or not.");

						ImGui::Checkbox("Redirect Print", &halo1::hooks::redirect_print);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Redirects all blamscript text printing functions to the console.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Rendering"))
					{
						ImGui::Checkbox("FPS Counter", halo1::offsets::fps_counter);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Displays a built-in fps counter. Does not work in remastered mode!");

						ImGui::Checkbox("Wireframe", halo1::offsets::wireframe);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Renders the game in wireframe. Does not work in remastered mode!");

						ImGui::Checkbox("Fog", halo1::offsets::atmosphere_fog);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Toggles the atmosphere fog.");

						ImGui::Checkbox("Fog Plane", halo1::offsets::fog_plane);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Toggles the fog plane.");

						ImGui::Checkbox("Enviroment Diffuse Textures", halo1::offsets::enviroment_diffuse);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Toggles rendering diffuse textures on the enviroment.");

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}

				ImGui::EndTabItem();
			}
		}
#pragma endregion

#pragma region Halo 2 Menu
		if (utils::running_game == "Halo 2 Anniversary")
		{
			if (ImGui::BeginTabItem("Halo 2"))
			{
				if (ImGui::BeginTabBar("Halo2Tabs", ImGuiTabBarFlags_None))
				{
#if defined _DEBUG
					if (ImGui::BeginTabItem("Debug"))
					{
						if (ImGui::Button("Trigger Test Function"))
							halo2::game::test_function();

						if (ImGui::Button("Print all blamscript functions."))
							halo2::game::list_all_hs_functions();

						if (ImGui::Button("Print all blamscript globals."))
							halo2::game::list_all_hs_globals();

						ImGui::EndTabItem();
					}
#endif

					if (ImGui::BeginTabItem("Game"))
					{
						ImGui::DragFloat("Gravity", *halo2::offsets::gravity, 0.005f, -FLT_MAX, +FLT_MAX, "%.5f", ImGuiSliderFlags_None);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("The gravity, nuff said. Note: Not savable.");

						ImGui::Checkbox("Redirect Print", &halo2::hooks::redirect_print);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Redirects some engine printing functions to the console.");

						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}

				ImGui::EndTabItem();
			}
		}
#pragma endregion

#pragma region Halo 3 Menu
		if (utils::running_game == "Halo 3")
		{
			if (ImGui::BeginTabItem("Halo 3"))
			{
				if (ImGui::BeginTabBar("Halo3Tabs", ImGuiTabBarFlags_None))
				{
#if defined _DEBUG
					if (ImGui::BeginTabItem("Debug"))
					{
						if (ImGui::Button("Print all blamscript functions."))
							halo3::game::list_all_hs_functions();

						if (ImGui::Button("Print all blamscript globals."))
							halo3::game::list_all_hs_globals();

						ImGui::EndTabItem();
					}
#endif
					if (ImGui::BeginTabItem("Game"))
					{
						if (halo3::offsets::physics_constants != NULL)
						{
							ImGui::DragFloat("Gravity", &halo3::offsets::physics_constants->gravity, 0.005f, -FLT_MAX, +FLT_MAX, "%.5f", ImGuiSliderFlags_None);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("The gravity, nuff said. Note: Not savable. Default: 4.1712594");
						}

						ImGui::Checkbox("Player weapon projectiles only", &halo3::hooks::player_weapon_projectiles_only);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Only the local player can fire bullets.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Rendering"))
					{
						ImGui::DragFloat("##motion_blur_scale_x", halo3::offsets::motion_blur_scale_x, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_scale_x: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_scale_y", halo3::offsets::motion_blur_scale_y, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_scale_y: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_max_x", halo3::offsets::motion_blur_max_x, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_max_x: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_max_y", halo3::offsets::motion_blur_max_y, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_max_y: %.5f", ImGuiSliderFlags_None);

						ImGui::DragInt("##motion_blur_taps", halo3::offsets::motion_blur_taps, 1, 0, 100, "motion_blur_taps: %i", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_center_falloff", halo3::offsets::motion_blur_center_falloff, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_center_falloff: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_expected_dt", halo3::offsets::motion_blur_expected_dt, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_expected_dt: %.5f", ImGuiSliderFlags_None);

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}

				ImGui::EndTabItem();
			}
		}
#pragma endregion

#pragma region Halo 3: ODST Menu
		if (utils::running_game == "Halo 3: ODST")
		{
			if (ImGui::BeginTabItem("Halo 3: ODST"))
			{
				if (ImGui::BeginTabBar("Halo3ODSTTabs", ImGuiTabBarFlags_None))
				{
#if defined _DEBUG
					if (ImGui::BeginTabItem("Debug"))
					{
						if (ImGui::Button("Trigger Test Function"))
							halo3odst::game::test_function();

						if (ImGui::Button("Print all blamscript functions."))
							halo3odst::game::list_all_hs_functions();

						if (ImGui::Button("Print all blamscript globals."))
							halo3odst::game::list_all_hs_globals();

						ImGui::EndTabItem();
					}
#endif

					if (ImGui::BeginTabItem("Rendering"))
					{
						/*	ImGui::Checkbox("Toggle HUD", halo3::offsets::toggle_hud);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Toggles the heads up display.");*/

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}

				ImGui::EndTabItem();
			}
		}
#pragma endregion

#pragma region Halo Reach
		if (utils::running_game == "Halo Reach")
		{
			if (ImGui::BeginTabItem("Halo Reach"))
			{
				if (ImGui::BeginTabBar("HaloReachTabs", ImGuiTabBarFlags_None))
				{
#if defined _DEBUG
					if (ImGui::BeginTabItem("Debug"))
					{
						if (ImGui::Button("Trigger Test Function"))
							haloreach::game::test_function();

						if (ImGui::Button("Print all blamscript functions."))
							haloreach::game::list_all_hs_functions();

						if (ImGui::Button("Print all blamscript globals."))
							haloreach::game::list_all_hs_globals();

						ImGui::EndTabItem();
					}
#endif

					if (ImGui::BeginTabItem("Rendering"))
					{
						/*	ImGui::Checkbox("Toggle HUD", halo3::offsets::toggle_hud);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Toggles the heads up display.");*/

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}

				ImGui::EndTabItem();
			}
		}
#pragma endregion

		ImGui::EndTabBar();
	}
	ImGui::End();

	// All popups and other windows go below here. ------------------------------------------------>
	//TODO: i would like to extract some of these into their own methods so things are a bit tidier, but at the moment i do not know how without breaking things.

	// ImGui Console -- TODO: WIP
	if (console_enabled)
	{
		ImGui::Begin("Console");
		ImGui::Text("Blargh, this has not been implemented yet!");
		ImGui::End();
	}

#pragma region modals
	// Save confirmation modal

	// Always center this window when appearing
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_save_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Save Changes?");
		show_save_modal = false;
	}

	if (ImGui::BeginPopupModal("Save Changes?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Do you want to save your changes?");

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			utils::save_running_game_settings();
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	// Load confirmation modal

	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_load_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Load Changes?");
		show_load_modal = false;
	}

	if (ImGui::BeginPopupModal("Load Changes?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Do you want to load changes from storage?");

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			utils::load_running_game_settings();
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	// Detach confirmation modal
	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_detach_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Detach Drinol?");
		show_detach_modal = false;
	}

	if (ImGui::BeginPopupModal("Detach Drinol?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Do you want to detach Drinol?");

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			utils::detach();
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	// Restore defaults modal

	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_restore_defaults_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Restore Defaults?");
		show_restore_defaults_modal = false;
	}

	if (ImGui::BeginPopupModal("Restore Defaults?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Do you want to retore all settings to their default?");

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			utils::reset_running_game_settings();
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	// About drinol modal

	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_about_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Drinol - About");
		show_about_modal = false;
	}

	// about modal
	if (ImGui::BeginPopupModal("Drinol - About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Drinol - A Halo modding utility.");
		ImGui::Separator();
		ImGui::Text("Credits:\n\nNBOTT42#6978: For assistance in developing this tool.\n\nApoxied#1337: Halo 3 Research information that i have yet to use.\n\nSilentRunner#6097: Information borrowed from his \"MCC Toolbox\" project.");
		ImGui::Separator();
		ImGui::Text("Thanks to all the halo modders and reverse engineers responsible for projects like ElDewrito and the Blam Creation Suite, without them, i would not have been inspired to make this tool.");

		if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::SameLine();
		if (ImGui::Button("Github Page", ImVec2(120, 0))) {
			ShellExecute(0, 0, L"https://github.com/matty45/Drinol", 0, 0, SW_SHOW);// I dont feel that this is a secure way of opening a web page but idk
		}
		ImGui::EndPopup();
	}
#pragma endregion
}