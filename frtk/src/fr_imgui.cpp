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

#include<fr_menu.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
#include<fr_window.h>

#include "ImGuizmo.h"


namespace FR {
    int Fr_Window::imguimzo_init()
    {
        return 0;
    }

    void Fr_Window::RenderGizmo(void) {
        Fr_Camera& cam = activeScene->getActiveCamera();
        userData_t data;
        ImGuiIO& io = ImGui::GetIO();
        cam.getCamData(data);
         ImGuizmo::SetRect(0.f, 0.f, (float)w(), (float)h());
        glm::mat4 view = cam.GetViewMatrix();
        float viewManipulateSize = 100.0f;
        
        ImVec2 pos(x() + w() - (int)viewManipulateSize, y() + 105);
        ImVec2 size(viewManipulateSize, viewManipulateSize);
        ImGuizmo::ViewManipulate(
            glm::value_ptr(view),               
            viewManipulateSize,                 
            pos,
            size,
            0x60606060                        
        );
        if (m_NaviCube){
            view = glm::inverse(view);
            data.cam_pos_= glm::vec3(view[3]);
            data.up_=(glm::vec3(view[1]));
            cam.setCamData(data);
        }
        //Axis under Navi Cube
        const float gizmoSize = 500.f;
        const float margin = 150.0f;
        const float* noSnap = nullptr;
        pos=ImVec2(pos.x -200, pos.y-50);
        ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
        ImGuizmo::SetRect(pos.x, pos.y, gizmoSize, gizmoSize);
        glm::mat4 identity(1.0f); //dummy 
        view[3] = glm::vec4(0, 0, 0, 1);
        ImGuizmo::Enable(true);

         glm::mat4 newViewMatrix = glm::mat4(glm::mat3(cam.GetViewMatrix()));// Extract rotation 
         newViewMatrix[3] = glm::vec4(0.0f, 0.0f, -150.0f, 1.0f);        // Translation 

        ImGuizmo::Manipulate(
            glm::value_ptr(newViewMatrix),
            glm::value_ptr(cam.getProjection()),
            ImGuizmo::TRANSLATE,
            ImGuizmo::LOCAL,
            glm::value_ptr(identity),
            nullptr,
            noSnap
        );

    }


    /************************
    *   Contains all ImGUI and ImGuimzo functions
    */
    int Fr_Window::renderimGUI(userData_t& data) {
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        //FR_PROFILE_FUNCTION();
        //FR_PROFILE_SCOPE("renderimGUI");

        // Get the current style
        //ImGuiStyle& style = ImGui::GetStyle();
        //style.WindowPadding = ImVec2(1, 1);
        //style.FramePadding = ImVec2(1, 1);
        RenderGizmo();
        if (imgui_menu() < 0) {
            return -1;
        }
        return 1;
    }
    
    
    float Fr_Window::getAspectRation() const
    {
        return Fr_Camera::m_aspect_ratio;
    }

    int Fr_Window::imgui_menu()
    {
        if (ImGui::BeginMainMenuBar()) //Start creating Main Window Menu.
        {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowMenuButtonPosition | ImGuiStyleVar_DockingSeparatorSize;

            if (ImGui::BeginMenu("File"))
            {
                //IMGUI_DEMO_MARKER("Examples/Menu");
                if (ImGui::MenuItem("New")) { mnuFileNew_cb(nullptr); }
                if (ImGui::MenuItem("Open", "Ctrl+O")) { mnuFileOpen_cb(nullptr); }
                if (ImGui::BeginMenu("Open Recent"))
                {
                    ImGui::MenuItem("---");
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { mnuFileSave_cb(nullptr); }
                if (ImGui::MenuItem("Save As..")) { mnuFileSaveAs_cb(nullptr); }
                ImGui::Separator();
                if (ImGui::MenuItem("Import")) { mnuFileImport_cb(nullptr); }
                if (ImGui::MenuItem("Export")) { mnuFileImport_cb(nullptr); }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) { mnuFileExit_cb(nullptr); }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) { mnuEditUndo(nullptr); }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) { mnuEditRedo(nullptr); }  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Copy", "CTRL+C")) { mnuEditCopy(nullptr); }
                if (ImGui::MenuItem("Cut", "CTRL+X")) { mnuEditCut(nullptr); }
                if (ImGui::MenuItem("Paste", "CTRL+V")) { mnuEditPaste(nullptr); }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Tools"))
            {
              //  ImGui::MenuItem("Show/Hide Camera Options", "", &CamerOptionVisible);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        m_menuHeight = ImGui::GetFrameHeight();
        return 0;
    }

}