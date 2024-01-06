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
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
//TODO FIX ME DOSENT WORK DON'T KNOW WHY
int Fr_GL3Window::imguimzo_init()
{
    ImGuizmo::BeginFrame();
    auto activeCamera = cameraList[(unsigned int)active_camera_];

    if (activeCamera->getType() == CameraList::ORTHOGRAPHIC)
        ImGuizmo::SetOrthographic(true);
    else
        ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    ImGuizmo::Enable(true);

    auto getbu = Fr_GL3Window::getfr_Gl3Window()->tempBu;
    auto cameraView = (activeCamera->getModelView());

    glm::mat4 trnasfrom_ = getbu->GetMatrix();
    if (getbu != NULL)
    {
        auto Camproj = activeCamera->getPorjection();
        //float wWidth = (float)ImGui::GetWindowWidth();
        //float wHeight= (float)ImGui::GetWindowHeight();
        ImVec4 dim = getPortViewDimensions();

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        ImGuizmo::SetRect(dim.x, dim.y, dim.z - dim.x, dim.w - dim.y);
        //ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(Camproj), ImGuizmo::OPERATION::ROTATE, ImGuizmo::LOCAL, glm::value_ptr(trnasfrom_));
        ImGuizmo::Manipulate(glm::value_ptr(cameraView), 
                             glm::value_ptr(Camproj), 
                              ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, 
                                glm::value_ptr(trnasfrom_));
        //ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(Camproj), ImGuizmo::OPERATION::SCALE, ImGuizmo::LOCAL, glm::value_ptr(trnasfrom_));
    }

    if (ImGuizmo::IsUsing()) {
        auto resu = trnasfrom_[3];
        //tempBu->SetPosition(tranform[3]);
        glm::vec3 trans, scaling;
        glm::vec4 rot;
        ExtractTransformMatrix(trnasfrom_, trans, rot, scaling);
        if (0)
            tempBu->Rotate(rot.x, rot.y, rot.z, rot.w);
        if (0)
            tempBu->Scale(scaling);
        if (1)
            tempBu->Translate(trans);
        std::string resss = std::to_string(resu[0]) + " " + std::to_string(resu[1]) + " " + std::to_string(resu[2]);
    }
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
        //ImGui::ShowDemoWindow();          //demo window if you want to learn how imgui works.
        if (imgui_TopPannel() < 0)
            return -1;
        if (imgui_ViewPort() < 0)
            return -1;
        if (imgui_LeftPanel() < 0)
            return -1;
        if (CamerOptionVisible) {
            // IF the menu checked, render the camera option window
            CameraOptions();
        }

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

    // Get the position and size of the widget
    ImVec2 widgetPos = ImGui::GetWindowPos();
    ImVec2 widgetSize = ImGui::GetWindowSize();

    // Get the mouse position
    ImVec2 mousePos = ImGui::GetMousePos();

    // Calculate the relative position
    ImVec2 relativePos = ImVec2(mousePos.x - widgetPos.x, mousePos.y - widgetPos.y);

    // Display the relative position
    ImGui::Text("Mouse Position: (%.1f, %.1f)", relativePos.x, relativePos.y);

    ImGui::End();
    return 0;
}

int Fr_GL3Window::imgui_CameraConfiguration(userData_& data)
{
    //Demo code fix me

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Camera Configuration!");                          // Create a window called "Hello, world!" and append into it.

    f = data.orthoSize_;
    ImGui::DragFloat("OrthoSize", &f, 0.2, -1000.0f, 1000.0f);
    data.orthoSize_ = f;

    f = data.camPosition_[0];
    ImGui::DragFloat("Position_x", &f, 0.2, -1000.0f, 1000.0f);
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

    ImGui::SliderInt("Cameratype", &type, 0, MAX_CAMERAS - 1);
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
        auto camm = cameraList[(int)active_camera_];
        camm->setupCameraHomeValues();
        camm->getUserData(data);
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    return 0;
}
float Fr_GL3Window::getAspectRation() const
{
    return Camera::aspectRatio_;
}
eventData Fr_GL3Window::GLFWevents() const
{
    return m_GLFWevents;
}
int Fr_GL3Window::imgui_ViewPort()
{
    ImGui::Begin("View Port");
    float wWidth = (float)ImGui::GetWindowWidth();
    float wHeight = (float)ImGui::GetWindowHeight();

    ImVec2 windowPos = ImGui::GetWindowPos();

    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    ImVec2 Bound1, Bound2;
    Bound1 = ImVec2(viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y);
    Bound2 = ImVec2(viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y);

    //setPortViewDimension(ImVec4(windowPos.x, windowPos.y, wWidth, wHeight));
    setPortViewDimension(ImVec4(Bound1.x, Bound1.y, Bound2.x, Bound2.y));
    //Camera::aspectRatio_ = wWidth / wHeight;    //Must be updated always

    //WE MUST UPDATE THIS, OTHERWISE THE RENDERING WILL BE MISSING DATA, AND THE PICTURE SHOWN WILL BE WRONG!!
    sceneBuffer->RescaleFrameBuffer(wWidth, wHeight);
    sceneBuffer->Bind();
    scene->RenderScene();
    ImGui::Image(
        (ImTextureID)sceneBuffer->getFrameTexture(),
        ImGui::GetContentRegionAvail(),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    imguimzo_init();
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
            if (ImGui::MenuItem("New")) { mnuFileNew_cb(nullptr); }
            if (ImGui::MenuItem("Open", "Ctrl+O")) { mnuFileOpen_cb(nullptr); }
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
            if (ImGui::MenuItem("Save", "Ctrl+S")) { GLFWCallbackWrapper::mnuFileSave_cb(nullptr); }
            if (ImGui::MenuItem("Save As..")) { GLFWCallbackWrapper::mnuFileSaveAs_cb(nullptr); }
            ImGui::Separator();
            if (ImGui::MenuItem("Import")) { GLFWCallbackWrapper::mnuFileImport_cb(nullptr); }
            if (ImGui::MenuItem("Export")) { GLFWCallbackWrapper::mnuFileImport_cb(nullptr); }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) { GLFWCallbackWrapper::mnuFileExit_cb(nullptr); }
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
            ImGui::MenuItem("Show/Hide Camera Options", "", &CamerOptionVisible);
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
    return 0;
}

void Fr_GL3Window::CameraOptions() {
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

    auto camm = cameraList[(int)active_camera_];
    camm->getUserData(data);
    imgui_CameraConfiguration(data);
    if (active_camera_ != data.camType_) {
        camm->SetActive(false);
        active_camera_ = data.camType_;
        camm = cameraList[(int)active_camera_];
        camm->getUserData(data);
    }
    camm->setUserData(data);
    camm->SetActive(true);
}

void Fr_GL3Window::SunOptions() {
    // ImGui::Begin("Sun Options");
    // ImGuiViewport* viewport = ImGui::GetMainViewport();
    // ImGuiWindowFlags window_flags = 0
    //     | ImGuiWindowFlags_NoDocking
    //     //| ImGuiWindowFlags_NoTitleBar
    //    //| ImGuiWindowFlags_NoResize
    ////   | ImGuiWindowFlags_NoMove
    //   //| ImGuiWindowFlags_NoScrollbar
    //   //| ImGuiWindowFlags_NoSavedSettings
    //     ;

    // glm::vec4 pos=sun->getPosition();

    // float f;
    // float f1, f2, f3;
    // f1 = sunT->get_X();
    // f2 = sunT->get_Y();
    // f3 = sunT->get_Y();

    // f = pos[0];
    // ImGui::DragFloat("Translate x", &f, 0.2,-1000.f,1000.f);
    // pos[0] = f;
    // f = pos[1];
    // ImGui::DragFloat("Translate y", &f, 0.2, -1000.f, 1000.f);
    // pos[1] = f;
    // f = pos[2];
    // ImGui::DragFloat("Translate z", &f, 0.2, -1000.f, 1000.f);
    // sunT->Translate(f1, f2, f3);
    // pos[2] = f;
    //
    // f = pos[3];
    // ImGui::DragFloat("Translate w", &f, 0.02, -1.f, 1.f);
    // pos[3] = f;
    // sun->SetPosition(pos);

    // _spot old=sun->getSpot();
    // bool t;
    // t = old.spot_enabled_;
    // ImGui::Checkbox("Spot Enable ",&t);
    // old.spot_enabled_ = t;

    // f = glm::degrees(acos(old.spot_cutoff_Ang));
    // ImGui::DragFloat("Spot Cutoff Ang", &f, 0.2, -360.f, 360.f);
    // old.spot_cutoff_Ang = cos(glm::radians(f));
    // f = old.spot_exponent_;
    // ImGui::DragFloat("Spot exponent", &f, 0.02, -1.f, 1.f);
    // old.spot_exponent_=f ;

    // f = old.spot_direction_.x;
    // ImGui::DragFloat("Spot direction.x", &f, 0.2, -1000.0f, 1000.0f);
    // old.spot_direction_.x = f;

    // f = old.spot_direction_.y;
    // ImGui::DragFloat("Spot direction.y", &f, 0.2, -1000.0f, 1000.0f);
    // old.spot_direction_.y = f;

    // f = old.spot_direction_.z;
    // ImGui::DragFloat("Spot direction.z", &f, 0.2, -1000.0f, 1000.0f);
    // old.spot_direction_.z = f;
    // sun->SetupSpot(old);
    // auto amb= sun->gtAmbient();
    // f = amb.r;
    // ImGui::DragFloat("Ambient r", &f, 0.002, 0.0f, 1.0f);
    // amb.r = f;
    // f = amb.g;
    // ImGui::DragFloat("Ambient g", &f, 0.002, 0.0f, 1.0f);
    // amb.g=f;
    // f = amb.b;
    // ImGui::DragFloat("Ambient b", &f, 0.002, 0.f, 1.f);
    // amb.b = f;
    // f = amb.a;
    // ImGui::DragFloat("Ambient a", &f, 0.020, 0.f, 1.f);
    // amb.a = f;
    // sun->SetAmbient(amb.r, amb.g, amb.b, amb.a);

    // auto spec = sun->getSpecular();
    // f = spec.r;
    // ImGui::DragFloat("specular r", &f, 0.002, 0.f, 1.f);
    // spec.r = f;
    // f = spec.g;
    // ImGui::DragFloat("specular g", &f, 0.002, 0.f, 1.f);
    // spec.g = f;
    // f = spec.b;
    // ImGui::DragFloat("specular b", &f, 0.002, 0.f, 1.f);
    // spec.b = f;
    // f = spec.a;
    // ImGui::DragFloat("specular a", &f, 0.002, 0.f, 1.f);
    // spec.a = f;
    // sun->SetSpecular(spec.r, spec.g, spec.b, spec.a);

    // auto att = sun->getAttenuation();
    // f = att.r;
    // ImGui::DragFloat("Attenuation r", &f, 0.001,0.f, 1.f);
    // att.r = f;
    // f = att.g;
    // ImGui::DragFloat("attv g", &f, 0.001, 0.f, 1.f);
    // att.g = f;
    // f = att.b;
    // ImGui::DragFloat("att b", &f, 0.001, 0.f, 1.0f);
    // att.b = f;
    // sun->SetAttenuation(att.r, att.g, att.b);
    // ImGui::End();
}