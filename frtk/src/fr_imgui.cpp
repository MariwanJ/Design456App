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
    ImGuizmo::SetRect(PortViewDimensions.x, PortViewDimensions.y, PortViewDimensions.z, PortViewDimensions.w);
    auto activeCamera = cameras[(unsigned int)active_camera_];
    auto modelview = activeCamera.manipulator->GetMatrix();
    ImGuizmo::IsUsing();
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
        ImGui::Begin("MainWindow", nullptr, window_flags);

        if (!opt_padding)
            ImGui::PopStyleVar();
       
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MainWindow");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            printf("Error\n");
        }
        if (imgui_menu() < 0)
            return -1;
        ImGui::ShowDemoWindow();
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
        bool m;      
        SunOptions();
        if (showOpenDialog) {
            createOpenDialog();
        }
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
 

    ImGui::Begin("Camera Configuration!");                          // Create a window called "Hello, world!" and append into it.

    f = data.camPosition_[0];
    ImGui::DragFloat("Position_x", &f, 0.2, -10000.0f, 1000.0f);
    data.camPosition_[0] = f;
    f = data.camPosition_[1];
    ImGui::DragFloat("Position_y", &f, 0.2, -1000.0f, 1000.0f);
    data.camPosition_[1] = f;
    f = data.camPosition_[2];
    ImGui::DragFloat("Position_z", &f, 0.2, -1000.0f, 1000.0f);
    data.camPosition_[2] = f;

    f = data.direction_[0];
    ImGui::DragFloat("Target_x", &f, 0.2, -1000.0f, 1000.0f);
    data.direction_[0] = f;
    f = data.direction_[1];
    ImGui::DragFloat("Target_y", &f, 0.2, -1000.0f, 1000.0f);
    data.direction_[1] = f;
    f = data.direction_[2];
    ImGui::DragFloat("Target_z", &f, 0.2, -1000.0f, 1000.0f);
    data.direction_[2] = f;

    static int type;
    f = data.aspectRatio_;
    ImGui::DragFloat("aspectratio", &f, 0.2, 0.0f, 5);
    data.aspectRatio_ = f;

    ImGui::SliderInt("Cameratype", &type, 0, MAX_CAMERAS-1);
    data.camType_ = (CameraList)type;

    f = data.fovy_;
    ImGui::DragFloat("FOVY", &f, 0.2, -120.0f, 120.0f);
    data.fovy_ = f;

    f = data.up_[0];
    ImGui::DragFloat("UP_x", &f, 0.2, -100000.0f, 100000.0f);
    data.up_[0] = f;
    f = data.up_[1];
    ImGui::DragFloat("UP_y", &f, 0.2, -100000.0f, 100000.0f);
    data.up_[1] = f;
    f = data.up_[2];
    ImGui::DragFloat("UP_z", &f, 0.2, -100000.0f, 100000.0f);
    data.up_[2] = f;

    f = data.zfar_;
    ImGui::DragFloat("Far", &f, 0.2, -10000.0f, 100000.0f);
    data.zfar_ = f;
    f = data.znear_;
    ImGui::DragFloat("Near", &f, 0.2, -10.0f, 100000.0f);
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

    //Keep size of the window for further usage at other places.
    PortViewDimensions = ImVec4(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
    
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
    if (active_camera_ != data.camType_) {
        camm.camera->SetActive(false);
        active_camera_ = data.camType_;
        camm = cameras[(int)active_camera_];
        camm.camera->getUserData(data);
    }
    camm.camera->setUserData(data);
    camm.camera->SetActive(true);
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
    ImGui::DragFloat("Translate x", &f, 0.2,-1000.f,1000.f);
    pos[0] = f;
    f = pos[1];
    ImGui::DragFloat("Translate y", &f, 0.2, -1000.f, 1000.f);
    pos[1] = f;
    f = pos[2];
    ImGui::DragFloat("Translate z", &f, 0.2, -1000.f, 1000.f);
    pos[2] = f;
    f = pos[3];
    ImGui::DragFloat("Translate w", &f, 0.2, -1000.f, 1000.f);
    pos[3] = f;
    sun->SetPosition(pos);


    _spot old=sun->getSpot();
    bool t;
    t = old.spot_enabled_;
    ImGui::Checkbox("Spot Enable ",&t);
    old.spot_enabled_ = t;

    f = glm::degrees(acos(old.spot_cutoff_Ang));
    std::cout << "value -->" << f << std::endl;
    ImGui::DragFloat("Spot Cutoff Ang", &f, 0.2, -360.f, 360.f);
    std::cout << "value -->" << f << std::endl;
    old.spot_cutoff_Ang = cos(glm::radians(f));
    f = old.spot_exponent_;
    ImGui::DragFloat("Spot exponent", &f, 0.2, -50.f, 50.f);
    old.spot_exponent_=f ;

    f = old.spot_direction_.x;
    ImGui::DragFloat("Spot direction.x", &f, 0.2, -100.0f, 1000.0f);
    old.spot_direction_.x = f;

    f = old.spot_direction_.y;
    ImGui::DragFloat("Spot direction.y", &f, 0.2, -1000.0f, 1000.0f);
    old.spot_direction_.y = f;

    f = old.spot_direction_.z;
    ImGui::DragFloat("Spot direction.z", &f, 0.2, -1000.0f, 1000.0f);
    old.spot_direction_.z = f;
    sun->SetupSpot(old);
    auto amb= sun->gtAmbient();
    f = amb.r;
    ImGui::DragFloat("Ambient r", &f, 0.02, -100.0f, 100.0f);
    amb.r = f;
    f = amb.g;
    ImGui::DragFloat("Ambient g", &f, 0.02, -100.0f, 100.0f);
    amb.g=f;
    f = amb.b;
    ImGui::DragFloat("Ambient b", &f, 0.02, -100.f, 100.f);
    amb.b = f;
    f = amb.a;
    ImGui::DragFloat("Ambient a", &f, 0.020, -100.f, 100.f);
    amb.a = f;
    sun->SetAmbient(amb.r, amb.g, amb.b, amb.a);


    auto spec = sun->getSpecular();
    f = spec.r;
    ImGui::DragFloat("specular r", &f, 0.02, -100.f, 100.f);
    spec.r = f;
    f = spec.g;
    ImGui::DragFloat("specular g", &f, 0.02, -100.f, 100.f);
    spec.g = f;
    f = spec.b;
    ImGui::DragFloat("specular b", &f, 0.02, -100.f, 100.f);
    spec.b = f;
    f = spec.a;
    ImGui::DragFloat("specular a", &f, 0.02, -100.f, 100.f);
    spec.a = f;
    sun->SetSpecular(spec.r, spec.g, spec.b, spec.a);


    auto att = sun->getAttenuation();
    f = att.r;
    ImGui::DragFloat("Attenuation r", &f, 0.01,-1.f, 1.f);
    att.r = f;
    f = att.g;
    ImGui::DragFloat("attv g", &f, 0.01, -1.f, 1.f);
    att.g = f;
    f = att.b;
    ImGui::DragFloat("att b", &f, 0.01, -1.f, 1.0f);
    att.b = f;
    sun->SetAttenuation(att.r, att.g, att.b);
    ImGui::End();



}