// This is our custom menu.
#include "stdafx.h"

#pragma region modal_funcs
void menu::about_modal()
{
	// about modal
	if (ImGui::BeginPopupModal("Drinol - About", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Drinol - A Halo modding utility.");
		ImGui::Separator();
		ImGui::Text("This tool is currently being tested on MCC version: %s", version_checking::COMPATIBLE_DRINOL_VERSION.c_str());
		ImGui::Separator();
		ImGui::Text("Credits:\n\nNBOTT42#6978: For assistance in developing this tool.\n\nApoxied#1337: Halo 3 Research information that I have yet to use.\n\nSilentRunner#6097: Information borrowed from his \"MCC Toolbox\" project.\n\n@theTwist84: Halo 3 struct information.\n\nOhItsDiiTz#1337: detour.h and detour.cpp and his undivided attention to this project when he has the time to help.\n\n@xCENTx: Initialization and heavy cleanup to make drinol run more efficently.");
		ImGui::Separator();
		ImGui::Text("Thanks to all the halo modders and reverse engineers responsible for projects like ElDewrito and the Blam Creation Suite, without them, i would not have been inspired to make this tool.");

		if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::SameLine();
		if (ImGui::Button("Github Repo", ImVec2(120, 0))) {
			ShellExecute(0, 0, L"https://github.com/matty45/Drinol", 0, 0, SW_SHOW);// I dont feel that this is a secure way of opening a web page but idk
		}
		ImGui::SameLine();
		if (ImGui::Button("Discord Server", ImVec2(120, 0))) {
			ShellExecute(0, 0, L"https://discord.gg/AkyKYTkPSJ", 0, 0, SW_SHOW);// I dont feel that this is a secure way of opening a web page but idk
		}
		ImGui::EndPopup();
	}
}

void menu::restore_defaults_modal()
{
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
}

void menu::detach_modal()
{
	if (ImGui::BeginPopupModal("Detach Drinol?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Do you want to detach Drinol?");

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			g_Killswitch = TRUE;	//	Hopefully triggers present fast enough to restore mouse to game context
			g_Running = FALSE;		//
			//	utils::detach();	//	 No longer needed , this will be handled at the end of the execution thread
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}
}

void menu::load_changes_modal()
{
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
}

void menu::save_changes_modal()
{
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
}

#pragma endregion
#pragma region window_funcs

std::string detach_key = utils::keys::get_key_name(utils::detach_keybind);
std::string toggle_wireframe_key = utils::keys::get_key_name(gui::toggle_wireframe_keybind);
std::string toggle_ui_key = utils::keys::get_key_name(gui::toggle_ui_keybind);
void settings_window(bool* show)
{
	ImGui::Begin("Settings", show);

	if (ImGui::BeginTabBar("DrinolTabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Keybinds"))
		{
			ImGui::Text("To change the hot-keys, just hold the key you want then click on the respective button.");
			ImGui::Text("NOTE: There is a bug which sometimes makes drinol think the insert key is the enter key, for some reason they both use the same hex value.");

			if (ImGui::Button(detach_key.c_str()))
			{
				int key = utils::keys::capture_next_key();
				if (key)
				{
					detach_key = utils::keys::get_key_name(key);
					utils::detach_keybind = key;
				}
			}
			ImGui::SameLine();
			ImGui::Text("Detach Key");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This is the keybind used for detaching drinol. Only really useful if you are injecting it.");

			if (ImGui::Button(toggle_wireframe_key.c_str()))
			{
				int key = utils::keys::capture_next_key();
				if (key)
				{
					toggle_wireframe_key = utils::keys::get_key_name(key);
					gui::toggle_wireframe_keybind = key;
				}
			}
			ImGui::SameLine();
			ImGui::Text("Toggle Wireframe Key");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This is the keybind used for toggling wireframe.");

			if (ImGui::Button(toggle_ui_key.c_str()))
			{
				int key = utils::keys::capture_next_key();
				if (key)
				{
					toggle_ui_key = utils::keys::get_key_name(key);
					gui::toggle_ui_keybind = key;
				}
			}
			ImGui::SameLine();
			ImGui::Text("Toggle UI Key");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This is the keybind used for toggling the Drinol menu.");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("UI"))
		{
			ImGui::Checkbox("Hook DX11", &gui::enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Toggle hooking DX11 if you dont want drinol to touch anything graphics api related.\nRequires a restart");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Console"))
		{
			ImGui::Checkbox("Display Console", &console::enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Displays the Drinol console. Requires a restart.");

			ImGui::Checkbox("Display ImGui Console", &menu::console_enabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Displays the Drinol ImGui console. Requires a restart.");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Logging"))
		{
			ImGui::Checkbox("Log to file", &logging::log_to_file);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Logs drinols output to a file. Requires a restart.");

			ImGui::Combo("Log Level", &logging::log_level, "trace\0debug\0info\0warn\0err\0critical\0off");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Changes drinols log level. Requires a restart.");

			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();

	ImGui::Separator();

	if (ImGui::Button("Save Changes"))
	{
		//TODO: Need to add a confirmation modal, however the modal system needs to be streamlined first.
		config::main::save();
	}

	ImGui::End();
}
#pragma endregion

void menu::render()
{
	g_Overlay->ApplyImGuiStyle(true, 0.5f);
	ImGui::Begin("Drinol", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	// Menu Bar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (utils::games::current_game_number != -1)
			{
				if (ImGui::MenuItem("Load Game Changes")) { show_load_modal = true; }
				if (ImGui::MenuItem("Save Game Changes")) { show_save_modal = true; }
				if (ImGui::MenuItem("Restore Game Defaults")) { show_restore_defaults_modal = true; }
			}

			if (ImGui::MenuItem("Settings")) { settings_window_open = true; }
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
			if (!utils::games::current_game_number == -1)
			{
				ImGui::Text("Currently running game: %i", utils::games::current_game_number);
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
				utils::memory::list_game_base_addresses();
			if (ImGui::Button("Print Game TLS Pointer"))
				utils::memory::print_game_tls_pointer();
			ImGui::EndTabItem();
		}
#endif

		// TODO: ideally we should show all the games and just grey out the stuff you cant interact with if a certain game is not running
#pragma region Halo 1 Menu
		if (utils::games::current_game_number == utils::games::halo1)
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
						ImGui::Checkbox("Bottomless Clip", halo1::offsets::variables::bottomless_clip);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Gives you infinite ammo without the need to reload or worry about your weapon overheating.");

						ImGui::Checkbox("Infinite Ammo", halo1::offsets::variables::infinite_ammo);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Same as bottomless clip but you have to reload, can still overheat and have infinite grenades.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Player"))
					{
						ImGui::Checkbox("God Mode", halo1::offsets::variables::god_mode);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Makes you unable to die.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Game"))
					{
						ImGui::DragFloat("Game ticks per second.", halo1::offsets::variables::game_ticks_per_second, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", ImGuiSliderFlags_None);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Basically the speed/time scale of the game. Default: 30.0");

						ImGui::DragFloat("Gravity", *halo1::offsets::variables::gravity, 0.005f, -FLT_MAX, +FLT_MAX, "%.5f", ImGuiSliderFlags_None);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("The gravity, nuff said. Note: Not savable.");

						ImGui::Checkbox("Motion Sensor - Show All Units", halo1::offsets::variables::motion_sensor_show_all_units);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Shows all units on your motion sensor, regardless if they are moving or not.");

						ImGui::Checkbox("Redirect Print", &halo1::hooks::redirect_print);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Redirects all blamscript text printing functions to the console.");

						if (ImGui::Checkbox("Toggle AI", &halo1::game::toggle_ai_bool))
						{
							halo1::game::toggle_ai(halo1::game::toggle_ai_bool);
						}
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Toggles the games AI.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Rendering"))
					{
						ImGui::Checkbox("FPS Counter", halo1::offsets::variables::fps_counter);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Displays a built-in fps counter. Does not work in remastered mode!");

						ImGui::Checkbox("Wireframe", halo1::offsets::variables::wireframe);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Renders the game in wireframe. Does not work in remastered mode!");

						ImGui::Checkbox("Fog", halo1::offsets::variables::atmosphere_fog);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Toggles the atmosphere fog.");

						ImGui::Checkbox("Fog Plane", halo1::offsets::variables::fog_plane);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Toggles the fog plane.");

						ImGui::Checkbox("Enviroment Diffuse Textures", halo1::offsets::variables::enviroment_diffuse);
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
		if (utils::games::current_game_number == utils::games::halo2)
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
						ImGui::DragFloat("Gravity", *halo2::offsets::variables::gravity, 0.005f, -FLT_MAX, +FLT_MAX, "%.5f", ImGuiSliderFlags_None);
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
		if (utils::games::current_game_number == utils::games::halo3)
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
						if (halo3::offsets::globals::physics_constants != NULL)
						{
							ImGui::DragFloat("Gravity", &halo3::offsets::globals::physics_constants->gravity, 0.005f, -FLT_MAX, +FLT_MAX, "%.5f", ImGuiSliderFlags_None);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("The gravity, nuff said. Note: Not savable. Default: 4.1712594");

							ImGui::DragFloat("Game Speed", &halo3::game::game_speed, 0.005f, 0.1f, 1.0f, "%.5f", ImGuiSliderFlags_None);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("This changes the games speed, default is 1.0 i think.");
							ImGui::SameLine();
							if (ImGui::Button("Change"))
							{
								halo3::hooks::game_tick_test = true;
							}
						}

						ImGui::Checkbox("Player weapon projectiles only", &halo3::hooks::player_weapon_projectiles_only);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Only the local player can fire bullets.");

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Rendering"))
					{
						ImGui::DragFloat("##motion_blur_scale_x", halo3::offsets::variables::motion_blur_scale_x, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_scale_x: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_scale_y", halo3::offsets::variables::motion_blur_scale_y, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_scale_y: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_max_x", halo3::offsets::variables::motion_blur_max_x, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_max_x: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_max_y", halo3::offsets::variables::motion_blur_max_y, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_max_y: %.5f", ImGuiSliderFlags_None);

						ImGui::DragInt("##motion_blur_taps", halo3::offsets::variables::motion_blur_taps, 1, 0, 100, "motion_blur_taps: %i", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_center_falloff", halo3::offsets::variables::motion_blur_center_falloff, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_center_falloff: %.5f", ImGuiSliderFlags_None);

						ImGui::DragFloat("##motion_blur_expected_dt", halo3::offsets::variables::motion_blur_expected_dt, 0.005f, -FLT_MAX, +FLT_MAX, "motion_blur_expected_dt: %.5f", ImGuiSliderFlags_None);

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}

				ImGui::EndTabItem();
			}
		}
#pragma endregion

#pragma region Halo 3: ODST Menu
		if (utils::games::current_game_number == utils::games::halo3odst)
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
		if (utils::games::current_game_number == utils::games::haloreach)
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

#pragma region windows

	// ImGui Console -- TODO: WIP
	if (console_enabled)
	{
		ImGui::Begin("Console");
		ImGui::Text("Blargh, this has not been implemented yet!");
		ImGui::End();
	}

	// Settings Window
	if (settings_window_open)
	{
		settings_window(&settings_window_open);
	}

#pragma endregion
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

	save_changes_modal();

	// Load confirmation modal

	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_load_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Load Changes?");
		show_load_modal = false;
	}

	load_changes_modal();

	// Detach confirmation modal
	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_detach_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Detach Drinol?");
		show_detach_modal = false;
	}

	detach_modal();

	// Restore defaults modal

	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_restore_defaults_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Restore Defaults?");
		show_restore_defaults_modal = false;
	}

	restore_defaults_modal();

	// About drinol modal

	// Always center this window when appearing
	center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (show_about_modal) // Yucky fix for not being able to open modals from menu bar entries: https://github.com/ocornut/imgui/issues/331#issuecomment-751372071
	{
		ImGui::OpenPopup("Drinol - About");
		show_about_modal = false;
	}

	about_modal();
#pragma endregion
}

// The goal of this window is to display important information to the user without handling any form of input / interactions
void menu::RenderHUD()
{
	float size[2];
	g_Overlay->GetWindowSize(size);

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	ImGuiStyle* style2 = &ImGui::GetStyle();
	style2->WindowRounding = NULL;

	//	Render Window
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);
	ImGui::SetNextWindowSize({ size[0], size[1] }, ImGuiCond_Always);
	if (!ImGui::Begin(("##HUDWindow"), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs))
	{
		ImGui::End();
		return;
	}

	ImDrawList* draw = ImGui::GetWindowDrawList();

#if defined _DEBUG
	std::string text = "Drinol - Debug - ";
	text += COMMIT_HASH;
	if (OLDEST_CHANGED_FILE_BEFORE_COMMIT)
		text += " - Mod";
#else
	std::string text = "Drinol - Release - ";
	text += COMMIT_HASH;
	if (OLDEST_CHANGED_FILE_BEFORE_COMMIT)
		text += " - Mod";
#endif

	draw->AddText(ImGui::GetFont(), 15.f, { 50.f, 10.f }, IM_COL32(255, 255, 255, 127), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);

	//	End
	ImGui::End();
}