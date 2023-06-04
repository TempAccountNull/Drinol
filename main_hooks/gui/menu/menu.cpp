#include "stdafx.h"
#include "menu.h"

#include "utils.h"
#include "config/config.h"
#include "gui/gui.h"
#include <version.h>

#include "games/halo1/halo1.h"
#include "games/halo1/halo1_hooks.h"
#include "games/halo1/halo1_offsets.h"
#include "games/halo2/halo2.h"
#include "games/halo2/halo2_hooks.h"
#include "games/halo2/halo2_offsets.h"
#include "games/halo3/halo3.h"
#include "games/halo3/halo3_hooks.h"
#include "games/halo3/halo3_offsets.h"
#include "games/halo3odst/halo3odst.h"
#include "games/haloreach/haloreach.h"
#include "games/groundhog/groundhog_hooks.h"
#include "games/halo3odst/halo3odst_hooks.h"
#include "games/halo4/halo4_hooks.h"
#include "games/haloreach/haloreach_hooks.h"
// This is our custom menu.

#pragma region modal_funcs
void menu::about_modal()
{
	// about modal
	if (ImGui::BeginPopupModal("Drinol - About", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration))
	{
		ImGui::Text("Drinol - A Halo modding utility.");
		ImGui::Separator();
		ImGui::Text("This tool is currently supported for MCC version: %s", version_checking::COMPATIBLE_DRINOL_VERSION.c_str());
		ImGui::Separator();
		ImGui::Text("Credits:\n\nNBOTT42#6978: For assistance in developing this tool.\n\nApoxied#1337: Halo 3 Research information that I have yet to use.\n\nSilentRunner#6097: Information borrowed from his \"MCC Toolbox\" project.\n\n@theTwist84: Halo 3 struct information.\n\nOhItsDiiTz#1337: detour.h and detour.cpp and his undivided attention to this project when he has the time to help.\n\n@xCENTx: Initialization and heavy cleanup to make drinol run more efficently.");
		ImGui::Separator();
		ImGui::TextWrapped("Thanks to all the halo modders and reverse engineers responsible for projects like ElDewrito and the Blam Creation Suite, without them, i would not have been inspired to make this tool.");
		ImGui::Separator();
		ImGui::Spacing();

		auto width = ImGui::GetWindowSize().x;
		ImVec2 size = { ((width - 32.f) / 3), 25.f };
		if (ImGui::Button("Close", size)) { ImGui::CloseCurrentPopup(); }
		ImGui::SameLine();
		if (ImGui::Button("Github Repo", size)) {
			ShellExecute(nullptr, nullptr, L"https://github.com/matty45/Drinol", nullptr, nullptr, SW_SHOW);// I dont feel that this is a secure way of opening a web page but idk
		}
		ImGui::SameLine();
		if (ImGui::Button("Discord Server", size)) {
			ShellExecute(nullptr, nullptr, L"https://discord.gg/AkyKYTkPSJ", nullptr, nullptr, SW_SHOW);// I dont feel that this is a secure way of opening a web page but idk
		}
		ImGui::SameLine();	//	prevents window from constantly expanding
		ImGui::SetWindowSize({ ImGui::GetWindowContentRegionWidth(), 0 });	//	sets window size
		ImGui::EndPopup();
	}
}

void menu::restore_defaults_modal()
{
	if (ImGui::BeginPopupModal("Restore Defaults?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
	if (ImGui::BeginPopupModal("Detach Drinol?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
	if (ImGui::BeginPopupModal("Load Changes?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
	if (ImGui::BeginPopupModal("Save Changes?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
	ImGui::Begin("Settings", show, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);

	if (ImGui::BeginTabBar("DrinolTabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Keybinds"))
		{
			ImGui::TextWrapped("To change the hot-keys, just hold the key you want then click on the respective button.");
			ImGui::TextWrapped("NOTE: There is a bug which sometimes makes drinol think the insert key is the enter key, for some reason they both use the same hex value.");

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
			g_Overlay->TextWithToolTip("Detach Key", "This is the keybind used for detaching drinol. Only really useful if you are injecting it.");

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
			g_Overlay->TextWithToolTip("Toggle Wireframe Key", "This is the keybind used for toggling wireframe.");

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
			g_Overlay->TextWithToolTip("Toggle UI Key", "This is the keybind used for toggling the Drinol menu.");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("UI"))
		{
			g_Overlay->CheckboxWithToolTip("Hook DX11",
				"Toggle hooking DX11 if you dont want drinol to touch anything graphics api related.\nRequires a restart",
				&gui::enabled
			);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Console"))
		{
			if (g_Overlay->CheckboxWithToolTip("Display Console",
				"Displays the Drinol console. Requires a restart.",
				&g_Console->bShowWindow
			))
				ShowWindow(GetConsoleWindow(), g_Console->bShowWindow ? SW_SHOW : SW_HIDE);

			g_Overlay->CheckboxWithToolTip("Display ImGui Console",
				"Displays the Drinol ImGui console.",
				&menu::console_enabled
			);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Logging"))
		{
			g_Overlay->CheckboxWithToolTip("Log to file",
				"Logs drinols output to a file. Requires a restart.",
				&logging::log_to_file
			);

			g_Overlay->ComboWithToolTip("Log Level",
				"Changes drinols log level. Requires a restart.",
				&logging::log_level,
				"trace\0debug\0info\0warn\0err\0critical\0off"
			);

			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();

	ImGui::Separator();
	ImGui::Spacing();

	if (g_Overlay->ButtonWithToolTip("Save Changes", "Saves all changes to user configuration file and closes this window.\nNOTE: Some changes may require a restart", { ImGui::GetContentRegionAvail().x, 25.f }))
	{
		menu::settings_window_open = FALSE;
		config::main::save();	//TODO: Need to add a confirmation modal, however the modal system needs to be streamlined first.
	}

	ImGui::Separator();
	ImGui::Spacing();

	if (g_Overlay->ButtonWithToolTip("Close Settings Window", "Closes this window without saving any changes.", { ImGui::GetContentRegionAvail().x, 25.f }))
		menu::settings_window_open = FALSE;

	ImGui::End();
}
#pragma endregion

bool someBool = false;
int someInteger = 4;
void menu::render()
{
	g_Overlay->ApplyImGuiStyle(true, 0.5f);
	ImGui::Begin("Drinol", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

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
			if (utils::games::current_game_number != -1)
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
			if (ImGui::Button("Print Game TLS Pointer and Suspend MCC"))
				utils::memory::print_game_tls_pointer(true);

			ImGui::SeparatorText("Debug Test ImGui Widgets");
			g_Overlay->TextWithToolTip("someText", "WithToolTip");
			g_Overlay->TextColoredWithToolTip({ 1.0f, 0.0f, 0.0f, 1.0f }, "someColorText", "WithToolTip");
			g_Overlay->ButtonWithToolTip("someButton", "WithToolTip");
			g_Overlay->CheckboxWithToolTip("someBoolean", "WithToolTip", &someBool);
			g_Overlay->ComboWithToolTip("TestCombo", "WithToolTip", &someInteger, "\0Option1\0Option2\0Options3");

			ImGui::EndTabItem();
		}
#endif

		// TODO: ideally we should show all the games and just grey out the stuff you cant interact with if a certain game is not running

		switch (utils::games::current_game_number)
		{
		case utils::games::halo1:
			HaloCombatEvolved::DrawMenu();
			break;

		case utils::games::halo2:
			Halo2::DrawMenu();
			break;

		case utils::games::halo3:
			Halo3::DrawMenu();
			break;

		case utils::games::halo3odst:
			Halo3ODST::DrawMenu();
			break;

		case utils::games::haloreach:
			HaloReach::DrawMenu();
			break;

		case utils::games::halo4:
			Halo4::DrawMenu();
			break;

		case utils::games::groundhog:
			Groundhog::DrawMenu();
			break;

		default:
			break;
		}

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
	if (!ImGui::Begin(("##HUDWindow"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs))
	{
		ImGui::End();
		return;
	}

	[[maybe_unused]] ImDrawList* draw = ImGui::GetWindowDrawList();

	char data[0x128];	//	296 chars max length
	const char* _data = "";
	const char* modified = "";
#if defined _DEBUG
	_data = "Drinol - Debug - %s";
	if constexpr (sizeof(OLDEST_CHANGED_FILE_BEFORE_COMMIT) > 1)
		modified = " - Mod";
#else
	_data = "Drinol - Release - %s";
	if constexpr (sizeof(OLDEST_CHANGED_FILE_BEFORE_COMMIT) > 1)
		modified = " - Mod";
#endif
	sprintf_s(data, _data, COMMIT_HASH, modified);
	g_Overlay->CleanText({ 50.f, 10.f }, { 1.0f, 1.0f, 1.0f, 0.49f }, data, 15.f);
	memset(data, NULL, sizeof(data));	//	free memory

#if DEBUG_LINE_HUD_DRAWING
	g_Overlay->CleanLine({ 0.0f, 0.0f }, { 100.0f, 50.0f }, { 1.0f, 0.0f, 0.0f, 0.50f }, 1.0f);
#endif

	//	End
	ImGui::End();
}

// Individual Game Menus

void menu::HaloCombatEvolved::DrawMenu()
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
				g_Overlay->CheckboxWithToolTip("Bottomless Clip",
					"Gives you infinite ammo without the need to reload or worry about your weapon overheating.",
					halo1::offsets::variables::bottomless_clip);

				g_Overlay->CheckboxWithToolTip("Infinite Ammo",
					"Same as bottomless clip but you have to reload, can still overheat and have infinite grenades.",
					halo1::offsets::variables::infinite_ammo);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Player"))
			{
				g_Overlay->CheckboxWithToolTip("God Mode",
					"Makes you unable to die.",
					halo1::offsets::variables::god_mode);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Game"))
			{
				g_Overlay->DragFloatWithToolTip("Game ticks per second.",
					"Basically the speed/time scale of the game. Default: 30.0",
					halo1::offsets::variables::game_ticks_per_second,
					0.005f,
					-FLT_MAX,
					+FLT_MAX);

				g_Overlay->DragFloatWithToolTip("Gravity",
					"The gravity, nuff said. Note: Not savable.",
					*halo1::offsets::variables::gravity,
					0.005f,
					-FLT_MAX,
					+FLT_MAX,
					"%.5f");

				g_Overlay->CheckboxWithToolTip("Motion Sensor - Show All Units",
					"Shows all units on your motion sensor, regardless if they are moving or not.",
					halo1::offsets::variables::motion_sensor_show_all_units);

				g_Overlay->CheckboxWithToolTip("Redirect Print",
					"Redirects all blamscript text printing functions to the console.",
					&halo1::hooks::redirect_print);

				if (g_Overlay->CheckboxWithToolTip("Toggle AI",
					"Toggles the games AI.",
					&halo1::game::toggle_ai_bool))
				{
					halo1::game::toggle_ai(halo1::game::toggle_ai_bool);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Rendering"))
			{
				g_Overlay->CheckboxWithToolTip("FPS Counter",
					"Displays a built-in fps counter. Does not work in remastered mode!",
					halo1::offsets::variables::fps_counter);

				g_Overlay->CheckboxWithToolTip("Wireframe",
					"Renders the game in wireframe. Does not work in remastered mode!",
					halo1::offsets::variables::wireframe);

				g_Overlay->CheckboxWithToolTip("Fog",
					"Toggles the atmosphere fog.",
					halo1::offsets::variables::atmosphere_fog);

				g_Overlay->CheckboxWithToolTip("Fog Plane",
					"Toggles the fog plane.",
					halo1::offsets::variables::fog_plane);

				g_Overlay->CheckboxWithToolTip("Enviroment Diffuse Textures",
					"Toggles rendering diffuse textures on the enviroment.",
					halo1::offsets::variables::enviroment_diffuse);

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::EndTabItem();
	}
}

void menu::Halo2::DrawMenu()
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

void menu::Halo3::DrawMenu()
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
				if (halo3::offsets::globals::physics_constants != nullptr)
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
						halo3::hooks::change_game_speed = true;
					}

					g_Overlay->CheckboxWithToolTip("Redirect Print", "Redirects some engine printing functions to the console.", &halo3::hooks::redirect_print);

					if (g_Overlay->CheckboxWithToolTip("Machinima Camera", "This enables the machinima debug camera, this will show your camera's coords on the screen.", &halo3::game::machinima_mode))
					{
						halo3::offsets::globals::player_control_globals->machinima_camera_debug = halo3::game::machinima_mode;
						halo3::offsets::globals::player_control_globals->machinima_camera_enabled = halo3::game::machinima_mode;
					}

					if (g_Overlay->CheckboxWithToolTip("Toggle spawning AI from effects.", "This removes a check to allow you to spawn any kind of AI through effects. (Only the host should use this! non-host clients will cause issues)", &halo3::game::toggle_ai_spawn_effects))
					{
						halo3::game::toggle_spawning_ai_from_effects(halo3::game::toggle_ai_spawn_effects);
					}
				}

				ImGui::Checkbox("Player weapon projectiles only", &halo3::hooks::player_weapon_projectiles_only);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Only the local player can fire bullets.");

				ImGui::Checkbox("Player ally weapon projectiles only", &halo3::hooks::player_ally_projectiles_only);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Only the local player and their allies can file bullets.");

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Rendering"))
			{
				ImGui::SeparatorText("Warning: Scripts can still take control of these!");

				g_Overlay->CheckboxWithToolTip("Motion Blur", "Toggles motion blur.", &halo3::offsets::globals::rasterizer_game_states->motion_blur_enabled);

				g_Overlay->CheckboxWithToolTip("Cinematic Motion Blur", "Toggles cinematic motion blur.", &halo3::offsets::globals::rasterizer_game_states->cinematic_motion_blur);

				g_Overlay->CheckboxWithToolTip("Atmospheric Fog", "Toggles rendering the fog.", &halo3::offsets::globals::rasterizer_game_states->render_atmosphere_fog);

				g_Overlay->CheckboxWithToolTip("Patchy Fog", "Toggles rendering patchy fog.", &halo3::offsets::globals::rasterizer_game_states->render_patchy_fog);

				g_Overlay->CheckboxWithToolTip("Weather", "Toggles rendering the weather.", &halo3::offsets::globals::rasterizer_game_states->render_weather);

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::EndTabItem();
	}
}

void menu::Halo3ODST::DrawMenu()
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

			//if (ImGui::BeginTabItem("Rendering"))
			//{
			//	/*	ImGui::Checkbox("Toggle HUD", halo3::offsets::toggle_hud);
			//		if (ImGui::IsItemHovered())
			//			ImGui::SetTooltip("Toggles the heads up display.");*/

			//	ImGui::EndTabItem();
			//}

			if (ImGui::BeginTabItem("Game"))
			{
				g_Overlay->CheckboxWithToolTip("Redirect Print", "Redirects some engine printing functions to the console.", &halo3odst::hooks::redirect_print);

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::EndTabItem();
	}
}

void menu::HaloReach::DrawMenu()
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

			if (ImGui::BeginTabItem("Game"))
			{
				ImGui::Checkbox("Redirect hs_print", &haloreach::hooks::redirect_print);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Redirects the blamscript print function output to the console.");

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::EndTabItem();
	}
}

void menu::Halo4::DrawMenu()
{
	if (ImGui::BeginTabItem("Halo 4"))
	{
		if (ImGui::BeginTabBar("Halo4Tabs", ImGuiTabBarFlags_None))
		{
			//#if defined _DEBUG
			//			if (ImGui::BeginTabItem("Debug"))
			//			{
			//				if (ImGui::Button("Trigger Test Function"))
			//					groundhog::game::test_function();
			//
			//				if (ImGui::Button("Print all blamscript functions."))
			//					groundhog::game::list_all_hs_functions();
			//
			//				if (ImGui::Button("Print all blamscript globals."))
			//					groundhog::game::list_all_hs_globals();
			//
			//				ImGui::EndTabItem();
			//			}
			//#endif

			//if (ImGui::BeginTabItem("Rendering"))
			//{
			//	/*	ImGui::Checkbox("Toggle HUD", halo3::offsets::toggle_hud);
			//		if (ImGui::IsItemHovered())
			//			ImGui::SetTooltip("Toggles the heads up display.");*/

			//	ImGui::EndTabItem();
			//}

			if (ImGui::BeginTabItem("Game"))
			{
				ImGui::Checkbox("Redirect hs_print", &halo4::hooks::redirect_print);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Redirects the blamscript print function output to the console.");

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::EndTabItem();
	}
}

void menu::Groundhog::DrawMenu()
{
	if (ImGui::BeginTabItem("Halo 2 Anniversary Multiplayer"))
	{
		if (ImGui::BeginTabBar("GroundhogTabs", ImGuiTabBarFlags_None))
		{
			//#if defined _DEBUG
			//			if (ImGui::BeginTabItem("Debug"))
			//			{
			//				if (ImGui::Button("Trigger Test Function"))
			//					groundhog::game::test_function();
			//
			//				if (ImGui::Button("Print all blamscript functions."))
			//					groundhog::game::list_all_hs_functions();
			//
			//				if (ImGui::Button("Print all blamscript globals."))
			//					groundhog::game::list_all_hs_globals();
			//
			//				ImGui::EndTabItem();
			//			}
			//#endif

			//if (ImGui::BeginTabItem("Rendering"))
			//{
			//	/*	ImGui::Checkbox("Toggle HUD", halo3::offsets::toggle_hud);
			//		if (ImGui::IsItemHovered())
			//			ImGui::SetTooltip("Toggles the heads up display.");*/

			//	ImGui::EndTabItem();
			//}

			if (ImGui::BeginTabItem("Game"))
			{
				ImGui::Checkbox("Redirect hs_print", &groundhog::hooks::redirect_print);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Redirects the blamscript print function output to the console.");

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::EndTabItem();
	}
}