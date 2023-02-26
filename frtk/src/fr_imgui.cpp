//                                                                      
// This file is a part of the Open Source Design456App                    
// MIT License
// 
// Copyright (c) 2023
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

#include <imgui.h>
#include <ImGuizmo.h>
#include <Fr_GL3Window.h>




int Fr_GL3Window::imguimzo_init()
{
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    float windowsWidth = (float)ImGui::GetWindowWidth();
    float windowsHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::BeginFrame();
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x,
        ImGui::GetWindowPos().y,
        windowsWidth, windowsHeight);

    auto m_Gizmotype = ImGuizmo::OPERATION::TRANSLATE; //translate, scale or rotate
    auto activeCamera= FR::globalP_pWindow->cameras[(unsigned int)FR::globalP_pWindow->active_camera_];
    auto modelview = activeCamera.manipulator->GetMatrix();
    float trans[3] = { 0.0f, 0.0f, 0.0f };
    auto proje = glm::ortho(-1.f, 1.f, -1.f, 1.f, 1.f, -1.f);
    ImGuizmo::DrawGrid(&modelview[0][0], &proje[0][0], trans, 100.f);
    int gizmoCount = 1;
    ImGuizmo::DrawCubes(&modelview[0][0], &proje[0][0], trans, gizmoCount);
    //ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
    //ImGuizmo::ViewManipulate(cameraView, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);




    //ImGuizmo::DrawGrid(&modelview[0][0], FR::globalP_pWindow->cameras[(unsigned int)FR::globalP_pWindow->active_camera_]->getPorjection(), trans, 100.f);
    //ImGuizmo::DrawCubes(modelview, camera->getProjection(), &objectMatrix[0][0], gizmoCount);

   /*ImGuizmo::Manipulate(&modelview[0][0],
                         camera->getProjection(),
                         (ImGuizmo::OPERATION)m_Gizmotype,
                         ImGuizmo::LOCAL,
                         glm::value_ptr(*trans));


   */

    return 0;
}



/************************
*   Contains all ImGUI and ImGuimzo functions
*/
int Fr_GL3Window::renderimGUI() {
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        auto camera = cameras[(int)active_camera_];
        //if (imgui_ViewPort() < 0)
           // return -1;
        if (imgui_toolbars() < 0)
            return -1;
        if (imgui_LeftPanel() < 0)
            return -1;
        if (imgui_TopPannel() < 0)
            return -1;
        if (imgui_NavigationBox(data) < 0)
            return -1;

        if (imgui_menu() < 0)
            return -1;
        if (imguimzo_init() < 0)
            return -1;
    }
    return 1;

}


int Fr_GL3Window::imgui_LeftPanel()
{
    return 0;
}
int Fr_GL3Window::imgui_TopPannel()
{
    bool show_demo_window = true;
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    return 0;
}
int Fr_GL3Window::imgui_NavigationBox(userData_ &data)
{
    //Demo code fix me

    static float f = 0.0f;
    static int counter = 0;
    bool show_demo_window = true;
    bool show_another_window = false;

    ImGui::Begin("Hello, Navigation!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::SliderFloat("pos_x", &data.camPosition_[0], 0.0f, 100.0f);
    ImGui::SliderFloat("pos_y", &data.camPosition_[1], 0.0f, 100.0f);
    ImGui::SliderFloat("pos_z", &data.camPosition_[2], 0.0f, 100.0f);

    ImGui::SliderFloat("pos_x", &data.center_[0], 0.0f, 100.0f);
    ImGui::SliderFloat("pos_y", &data.center_[1], 0.0f, 100.0f);
    ImGui::SliderFloat("pos_z", &data.center_[2], 0.0f, 100.0f);
    static int type;
    ImGui::SliderFloat("aspectratio", &data.aspectRatio_, 0.0f, 100.0f);
    ImGui::SliderInt("Cameratype", &type, 0, 5);
    data.camType_ = (CameraList)type;
    ImGui::SliderFloat("FOVY", &data.fovy_, 0.0f, 359.0f);

    ImGui::SliderFloat("UP_x", &data.up_[0], 0.0f, 100.0f);
    ImGui::SliderFloat("UP_y", &data.up_[1], 0.0f, 100.0f);
    ImGui::SliderFloat("UP_z", &data.up_[2], 0.0f, 100.0f);

    ImGui::SliderFloat("Far", &data.zfar_, 0.0f, 100.0f);
    ImGui::SliderFloat("Near", &data.znear_, 0.0f, 100.0f);

/*
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    */



    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    return 0;
}
int Fr_GL3Window::imgui_ViewPort()
{   //Demo code fix me
    //ImGui::Begin("ViewPort");
   // ImGui::Text("View Port");               // Display some text (you can use a format strings too)
    scene->RenderScene();
    //  ImGui::End();
    return 0;
}

int Fr_GL3Window::imgui_menu()
{

    if (ImGui::BeginMainMenuBar()) //Start creating Main Window Menu.
    {
        if (ImGui::BeginMenu("File"))
        {

            //IMGUI_DEMO_MARKER("Examples/Menu");
            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New")) { mnuFileNew_cb(this, nullptr); }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::MenuItem("fish_hat.c");
                ImGui::MenuItem("fish_hat.inl");
                ImGui::MenuItem("fish_hat.h");
                if (ImGui::BeginMenu("More.."))
                {
                    ImGui::MenuItem("Hello");
                    ImGui::MenuItem("Sailor");
                    if (ImGui::BeginMenu("Recurse.."))
                    {
                        //ShowExampleMenuFile();
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {}

            ImGui::Separator();
            //IMGUI_DEMO_MARKER("Examples/Menu/Options");
            if (ImGui::BeginMenu("Options"))
            {
                static bool enabled = true;
                ImGui::MenuItem("Enabled", "", &enabled);
                ImGui::BeginChild("child", ImVec2(0, 60), true);
                for (int i = 0; i < 10; i++)
                    ImGui::Text("Scrolling Text %d", i);
                ImGui::EndChild();
                static float f = 0.5f;
                static int n = 0;
                if (ImGui::SliderFloat("Value", &f, 0.0f, 1.0f)) {
                    printf("wrong slide\n");
                }
                ImGui::InputFloat("Input", &f, 0.1f);
                ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                ImGui::EndMenu();
            }

            //IMGUI_DEMO_MARKER("Examples/Menu/Colors");
            if (ImGui::BeginMenu("Colors"))
            {
                float sz = ImGui::GetTextLineHeight();
                for (int i = 0; i < ImGuiCol_COUNT; i++)
                {
                    const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
                    ImVec2 p = ImGui::GetCursorScreenPos();
                    ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
                    ImGui::Dummy(ImVec2(sz, sz));
                    ImGui::SameLine();
                    ImGui::MenuItem(name);
                }
                ImGui::EndMenu();
            }

            // Here we demonstrate appending again to the "Options" menu (which we already created above)
            // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
            // In a real code-base using it would make senses to use this feature from very different code locations.
            if (ImGui::BeginMenu("Options")) // <-- Append!
            {
                //IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
                static bool b = true;
                ImGui::Checkbox("SomeOption", &b);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Disabled", false)) // Disabled
            {
                IM_ASSERT(0);
            }
            if (ImGui::MenuItem("Checked", NULL, true)) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Alt+F4")) {}


            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
    return 0;
}



int Fr_GL3Window::imgui_toolbars()
{
    unsigned int myImageTextureId2 = 0;
    bool show_another_window = true;
    static ImGui::Toolbar toolbar;
    if (toolbar.getNumButtons() == 0) {
        char tmp[1024]; ImVec2 uv0(0, 0), uv1(0, 0);
        for (int i = 0; i < 9; i++) {
            strcpy(tmp, "toolbutton ");
            sprintf(&tmp[strlen(tmp)], "%d", i + 1);
            uv0 = ImVec2((float)(i % 3) / 3.f, (float)(i / 3) / 3.f);
            uv1 = ImVec2(uv0.x + 1.f / 3.f, uv0.y + 1.f / 3.f);
            toolbar.addButton(ImGui::Toolbutton(tmp, (void*)NULL, uv0, uv1, ImVec2(32, 32)));
        }
        toolbar.addSeparator(16);
        toolbar.addButton(ImGui::Toolbutton("toolbutton 11" ICON_FA_ARROW_LEFT, (void*)NULL, uv0, uv1, ImVec2(16, 16), true, true, ImVec4(0.8, 0.8, 1.0, 1)));  // Note that separator "eats" one toolbutton index as if it was a real button
        toolbar.addButton(ImGui::Toolbutton("toolbutton 12" ICON_FA_ARROW_ALT_CIRCLE_RIGHT, (void*)NULL, uv0, uv1, ImVec2(16, 16), true, false, ImVec4(1.0, 0.8, 0.8, 1)));  // Note that separator "eats" one toolbutton index as if it was a real button

        toolbar.setProperties(true, false, false, ImVec2(0.0f, 0.f), ImVec2(0.25, 1));
    }
    const int pressed = toolbar.render();
    if (pressed >= 0)
        fprintf(stderr, "Toolbar1: pressed:%d\n", pressed);
    if (ImGui::Button(ICON_FAD_ZOOMOUT)) {
        printf("button pressed\n");
    }
    
    return 0;
}