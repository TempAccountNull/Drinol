// This is our custom menu.
#include "menu.h"

#include "imgui.h"
#include "utils.h"
#include "games/halo1/halo1.h"
#include "games/halo1/halo1_offsets.h"

void menu::render()
{
	ImGui::Begin("Drinol");
	const ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("DrinolTabs", tab_bar_flags))
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
		// TODO: ideally we should show all the games and just grey out the stuff you cant interact with if a certain game is not running
		if (utils::running_game == "Halo 1 Anniversary")
		{
			if (ImGui::BeginTabItem("Halo 1"))
			{
				if (ImGui::BeginTabBar("DrinolTabs", tab_bar_flags))
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

						ImGui::Checkbox("Motion Sensor - Show All Units", halo1::offsets::motion_sensor_show_all_units);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Shows all units on your motion sensor, regardless if they are moving or not.");

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

		ImGui::EndTabBar();
	}
	ImGui::End();
}