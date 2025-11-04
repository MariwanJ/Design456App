#include <fr_window.h>
#include<fr_menu.h>
#include<fr_toolbar.h>
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
//TODO FIX ME DOSENT WORK DON'T KNOW WHY
namespace FR {
    int Fr_Window::imgui_LeftPanel()
    {
        ImGui::Begin("LeftPannel");

        // Get the current style
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(1, 1);
        style.FramePadding = ImVec2(1, 1);
        style.WindowMenuButtonPosition = ImGuiDir_None; ///remove docking button

        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

        ImGui::SameLine();
        panelWidth = ImGui::GetWindowWidth();
        if (ImGui::Button(ICON_FA_PEN_CLIP, ImVec2(ICON_SIZE)))
            mnuDrawLine_cb(nullptr);                          //FILE SAVE

        ImGui::Button(ICON_FA_BOX);

        // Display the relative position
        ray_t ray = activeScene->getRayValue();
        ImGui::Text("Mouse Position: (%.1f, %.1f)", mouseEvent.Old_x, mouseEvent.Old_y);
        ImGui::Text("Mouse World: (%.1f, %.1f, %.1f)", mouseEvent.WorldMouse.x, mouseEvent.WorldMouse.y, mouseEvent.WorldMouse.z);
        ImGui::Text("RAY pos : (%.1f, %.1f, %.1f)", ray.position.x, ray.position.y, ray.position.z);
        ImGui::Text("RAY dire : (%.1f, %.1f, %.1f)", ray.direction.x, ray.direction.y, ray.direction.z);
        ImGui::End();
        return 0;
    }
}