//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <fr_window.h>
#include<fr_menu.h>
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
namespace FR {
    int Fr_Window::imgui_LeftPanel()
    {
        ImGuiWindowFlags window_flags = 0//ImGuiWindowFlags_NoTitleBar |
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoCollapse      ;

        m_menuHeight = ImGui::GetFrameHeight();
        int start = (int)m_menuHeight + 2 + FRTK_TOOLBAR_HEIGHT;
        ImGui::SetNextWindowPos(ImVec2(x(), y() + start));

        ImGui::Begin("LeftPannel", NULL, window_flags); {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowPadding = ImVec2(1, 1);
            style.FramePadding = ImVec2(1, 1);
            style.WindowMenuButtonPosition = ImGuiDir_None; ///remove docking button

            if (ImGui::BeginTabBar("Main")) {
                if (ImGui::BeginTabItem("Model")) {
                    ImGuiIO& io = ImGui::GetIO();
                    ImVec2 avail = ImGui::GetContentRegionAvail();

                    static float topHeight = 0.0f;
                    const float splitterThickness = 6.0f;
                    const float minPane = 50.0f;

                    if (topHeight <= 0.0f || topHeight > avail.y - minPane)
                        topHeight = avail.y * 0.5f;

                    ImGui::BeginChild("TopChild", ImVec2(0, topHeight), true);

                    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DefaultOpen;
                    ImGuiTreeNodeFlags leaf_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_NoTreePushOnOpen;

                    if (ImGui::TreeNodeEx("Root", base_flags))
                    {
                        for (int i = 0; i < activeScene->m_world.size(); ++i)
                        {
                            ImGui::PushID(activeScene->m_world[i].id);

                            ImGui::PushFont(SystemFont.toolbarFont.get());
                            std::string res = GLYPH_CUBE + activeScene->m_world[i].name + " - " + std::to_string(activeScene->m_world[i].id);

                            ImGui::TreeNodeEx(res.c_str(), leaf_flags);
                            ImGui::PopFont();

                            if (ImGui::IsItemClicked())
                            {
                                activeScene->m_world[i].Sceneitem->m_mesh.selectMesh(true);
                            }
                            ImGui::PopID();
                        }
                        ImGui::TreePop(); 
                    }

                    ImGui::EndChild();

                    ImDrawList* draw = ImGui::GetWindowDrawList();
                    ImVec2 splitterPos = ImGui::GetCursorScreenPos();
                    ImVec2 splitterEnd = ImVec2(splitterPos.x + avail.x, splitterPos.y + splitterThickness);
                    draw->AddRectFilled(splitterPos, splitterEnd, IM_COL32(120, 120, 120, 200));
                    ImGui::InvisibleButton("##h_splitter", ImVec2(avail.x, splitterThickness));
                    if (ImGui::IsItemActive())
                        topHeight += io.MouseDelta.y;

                    if (ImGui::IsItemHovered() || ImGui::IsItemActive())
                        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

                    ImGui::BeginChild("BottomChild", ImVec2(0, 0), true);
                    {
                        if (ImGui::BeginTabBar("Data")) {
                            if (ImGui::BeginTabItem("Data")) {
                                ImGui::Button(GLYPH_CAKE_CANDLES);
                                ImGui::EndTabItem();
                            }

                            ImGui::EndTabBar();
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndTabItem();
                }

                // First tab
                if (ImGui::BeginTabItem("Objects")) {
                    // Display the relative position
                    ray_t ray = activeScene->getRayValue();
                    auto& em = m_sysEvents.mouse;
                    ImGui::Text("Mouse Position: (%.1f, %.1f)", em.activeX, m_sysEvents.mouse.activeY);
                    ImGui::Text("Mouse World: (%.1f, %.1f, %.1f)", em.worldPos.x, em.worldPos.y, em.worldPos.z);
                    ImGui::Text("RAY pos : (%.1f, %.1f, %.1f)", ray.position.x, ray.position.y, ray.position.z);
                    ImGui::Text("RAY dire : (%.1f, %.1f, %.1f)", ray.direction.x, ray.direction.y, ray.direction.z);

                    if (ImGui::Button(GLYPH_CHART_PIE, ImVec2(FRTK_ICON_SIZE)))
                        mnuDrawLine_cb(nullptr);
                    ImGui::Button(GLYPH_BOX_1_FILL);
                    ImGui::EndTabItem();
                }

                CameraOptions();
                SunOptions();

                // End the tab bar
                ImGui::EndTabBar();
            }
        }
        ImGui::End();

        return 0;
    }
}