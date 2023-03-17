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


#include <Fr_GL3Window.h>
#include<fr_menu.h>
#include<fr_toolbar.h>


//TODO FIX ME DOSENT WORK DON'T KNOW WHY
int Fr_GL3Window::imguimzo_init()
{
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    float windowsWidth = (float)ImGui::GetWindowWidth();
    float windowsHeight = (float)ImGui::GetWindowHeight();

    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowsWidth, windowsHeight);

    auto m_Gizmotype = ImGuizmo::OPERATION::TRANSLATE; //translate, scale or rotate
    auto activeCamera = cameras[(unsigned int)active_camera_];
    auto modelview = activeCamera.manipulator->GetMatrix();
    float trans[3] = { 0.0f, 0.0f, 0.0f };
    glm::mat4  delta;
    auto proje = glm::ortho(-1.f, 1.f, -1.f, 1.f, 1.f, -1.f);
    ImGuizmo::DrawGrid(&modelview[0][0], &proje[0][0], trans, 100.f);
    int gizmoCount = 1;
    ImGuizmo::DrawCubes(&modelview[0][0], &proje[0][0], trans, gizmoCount);
    ImGuizmo::DrawGrid(&modelview[0][0], &proje[0][0], &delta[0][0], 100.f);
    ImGuizmo::ViewManipulate(&modelview[0][0], 8.f, ImVec2( 128, 30), ImVec2(128, 128), 0x10101010);
    return 0;
}

/************************
*   Contains all ImGUI and ImGuimzo functions
*/
int Fr_GL3Window::renderimGUI(userData_& data) {
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        //        if (opt_fullscreen)

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        /*      else
              {
                  dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
              }
              */
              // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
              // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);

        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            printf("Error\n");
        }
        if (imgui_menu() < 0)
            return -1;

        if (imgui_TopPannel() < 0)
            return -1;
        if (imguimzo_init() < 0)
            return -1;
        if (imgui_ViewPort() < 0)
            return -1;
        if (imgui_LeftPanel() < 0)
            return -1;
        if (FR::CamerOptionVisible) {
            // IF the menu checked, render the camera option window
            CameraOptions();
        }
        if (imguimzo_init() < 0)
            return -1;
        SunOptions();

    }

    ImGui::End();

    return 1;
}

int Fr_GL3Window::imgui_LeftPanel()
{
    ImGui::Begin("LeftPannel");
    ImGui::Button(ICON_FA_BOX);
    ImGui::End();
    return 0;
}

int Fr_GL3Window::imgui_CameraConfiguration(userData_& data)
{
    //Demo code fix me

    static float f = 0.0f;
    static int counter = 0;
    bool show_demo_window = true;
    bool show_another_window = false;

    ImGui::Begin("Camera Configuration!");                          // Create a window called "Hello, world!" and append into it.

    f = data.camPosition_[0];
    ImGui::SliderFloat("Position_x", &f, -10.0f, 10.0f);
    data.camPosition_[0] = f;
    f = data.camPosition_[1];
    ImGui::SliderFloat("Position_y", &f, -10.0f, 10.0f);
    data.camPosition_[1] = f;
    f = data.camPosition_[2];
    ImGui::SliderFloat("Position_z", &f, -10.0f, 10.0f);
    data.camPosition_[2] = f;

    f = data.direction_[0];
    ImGui::SliderFloat("Target_x", &f, -10.0f, 10.0f);
    data.direction_[0] = f;
    f = data.direction_[1];
    ImGui::SliderFloat("Target_y", &f, -10.0f, 10.0f);
    data.direction_[1] = f;
    f = data.direction_[2];
    ImGui::SliderFloat("Target_z", &data.direction_[2], -10.0f, 10.0f);
    data.direction_[2] = f;

    static int type;
    f = data.aspectRatio_;
    ImGui::SliderFloat("aspectratio", &f, 0.0f, 100.0f);
    data.aspectRatio_ = f;

    ImGui::SliderInt("Cameratype", &type, 0, 5);
    data.camType_ = (CameraList)type;

    f = data.fovy_;
    ImGui::SliderFloat("FOVY", &f, 0.0f, 359.0f);
    data.fovy_ = f;

    f = data.up_[0];
    ImGui::SliderFloat("UP_x", &f, -1000.0f, 1000.0f);
    data.up_[0] = f;
    f = data.up_[1];
    ImGui::SliderFloat("UP_y", &f, -1000.0f, 1000.0f);
    data.up_[1] = f;
    f = data.up_[2];
    ImGui::SliderFloat("UP_z", &f, -1000.0f, 1000.0f);
    data.up_[2] = f;

    f = data.zfar_;
    ImGui::SliderFloat("Far", &f, -1000.0f, 1000.0f);
    data.zfar_ = f;
    f = data.znear_;
    ImGui::SliderFloat("Near", &f, -10.0f, 10.0f);
    data.znear_ = f;

    ImGui::Text("Use the sliders to configure the camera");               // Display some text (you can use a format strings too)
    ImGui::ColorEdit3("bkg color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Reset Camera to defaults")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
        auto camm = cameras[(int)active_camera_];
        camm.camera->setupCameraHomeValues();
        struct userData_ newdata;
        camm.camera->getUserData(newdata);
        data = newdata;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    return 0;
}
int Fr_GL3Window::imgui_ViewPort()
{
    ImGui::Begin("View Port");
    sceneBuffer->Bind();
    scene->RenderScene();
    ImGui::Image(
        (ImTextureID)sceneBuffer->getFrameTexture(),
        ImGui::GetContentRegionAvail(),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    ImGui::End();
    sceneBuffer->Unbind();
    return 0;
}

int Fr_GL3Window::imgui_menu()
{
    if (ImGui::BeginMainMenuBar()) //Start creating Main Window Menu.
    {
        if (ImGui::BeginMenu("File"))
        {
            //IMGUI_DEMO_MARKER("Examples/Menu");
            if (ImGui::MenuItem("New")) { mnuFileNew_cb( nullptr); }
            if (ImGui::MenuItem("Open", "Ctrl+O")) { mnuFileOpen_cb( nullptr); }
            if (ImGui::BeginMenu("Open Recent"))
            {
                ImGui::MenuItem("---");
             /*   ImGui::MenuItem("fish_hat.inl");
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
                }*/
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { GLFWCallbackWrapper::mnuFileSave_cb( nullptr); }
            if (ImGui::MenuItem("Save As..")) { GLFWCallbackWrapper::mnuFileSaveAs_cb( nullptr); }
            ImGui::Separator();
            if (ImGui::MenuItem("Import")) { GLFWCallbackWrapper::mnuFileImport_cb( nullptr); }
            if (ImGui::MenuItem("Export")) { GLFWCallbackWrapper::mnuFileImport_cb( nullptr); }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) { GLFWCallbackWrapper::mnuFileExit_cb( nullptr);  }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) { GLFWCallbackWrapper::mnuEditUndo(nullptr); }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) { GLFWCallbackWrapper::mnuEditRedo(nullptr); }  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "CTRL+C")) { GLFWCallbackWrapper::mnuEditCopy(nullptr); }
            if (ImGui::MenuItem("Cut", "CTRL+X")) { GLFWCallbackWrapper::mnuEditCut(nullptr); }
            if (ImGui::MenuItem("Paste", "CTRL+V")) { GLFWCallbackWrapper::mnuEditPaste(nullptr); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {

            ImGui::MenuItem("Show/Hide Camera Options", "", &FR::CamerOptionVisible);
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
    return 0;
}


void Fr_GL3Window::CameraOptions (){
    userData_ data;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags window_flags = 0
        | ImGuiWindowFlags_NoDocking
        //| ImGuiWindowFlags_NoTitleBar
       //| ImGuiWindowFlags_NoResize
   //   | ImGuiWindowFlags_NoMove
      //| ImGuiWindowFlags_NoScrollbar
      //| ImGuiWindowFlags_NoSavedSettings
        ;

    auto camm = cameras[(int)active_camera_];
    camm.camera->getUserData(data);
    imgui_CameraConfiguration(data);
    camm = cameras[(int)active_camera_];
    camm.camera->setUserData(data);
    camm.camera->setType(data.camType_);
    camm.camera->SetUp(data.up_[0], data.up_[1], data.up_[2]);
    camm.camera->SetCenter(data.direction_[0], data.direction_[1], data.direction_[2]);
    camm.camera->SetCamPosition(data.camPosition_[0], data.camPosition_[1], data.camPosition_[2]);
    active_camera_ = data.camType_;

}

void Fr_GL3Window::SunOptions() {
    ImGui::Begin("Sun Options");
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiWindowFlags window_flags = 0
        | ImGuiWindowFlags_NoDocking
        //| ImGuiWindowFlags_NoTitleBar
       //| ImGuiWindowFlags_NoResize
   //   | ImGuiWindowFlags_NoMove
      //| ImGuiWindowFlags_NoScrollbar
      //| ImGuiWindowFlags_NoSavedSettings
        ;

    glm::vec4 pos=sun->getPosition();

    float f;
    f = pos[0];
    ImGui::SliderFloat("Translate x", &f,-1000.f,1000.f);
    pos[0] = f;
    f = pos[1];
    ImGui::SliderFloat("Translate y", &f, -1000.f, 1000.f);
    pos[1] = f;
    f = pos[2];
    ImGui::SliderFloat("Translate z", &f, -1000.f, 1000.f);
    pos[2] = f;
    f = pos[3];
    ImGui::SliderFloat("Translate w", &f, -1000.f, 1000.f);
    pos[3] = f;
    sun->SetPosition(pos);
    ImGui::End();

    _spot old=sun->getSpot();
    f = old.spot_cutoff_Ang;
    ImGui::SliderFloat("Spot Cutoff Ang", &f, 0.f, 360.f);
    old.spot_cutoff_Ang = f;

    f = old.spot_direction_.a;
    ImGui::SliderFloat("Spot direction.a", &f, -1000.f, 1000.f);
    old.spot_direction_.a = f;

    f = old.spot_direction_.b;
    ImGui::SliderFloat("Spot direction.a", &f, -1000.f, 1000.f);
    old.spot_direction_.b = f;





}