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

#include <frtk.h>
#include<fr_constants.h>

#include <fr_window.h>
#include "fr_gl3callbacks.h"

namespace FR {
    void Fr_Window::glfwWindosResize(GLFWwindow* window, int width, int height)
    {
        if (spWindow == nullptr)
            return;

        spWindow->m_ViewPort.size.w = width;
        spWindow->m_ViewPort.size.h = height;

        glfwGetWindowPos(pGLFWWindow,&m_ViewPort.pos.x, &m_ViewPort.pos.y); //update even position

        uint8_t index = spWindow->activeScene->m_active_camera;
        if(spWindow->m_ViewPort.size.h!=0){
            //Avoid divide by zero, keep the last ratio 
            spWindow->activeScene->m_cameras[index].m_aspect_ratio = static_cast<float>(spWindow->m_ViewPort.size.w) / spWindow->m_ViewPort.size.h;
        }
    }
    void Fr_Window::glfwWindPos(GLFWwindow* window, int pos_x, int pos_y)
    {
        if (spWindow == nullptr)
            return;
        spWindow->m_ViewPort.pos.x = pos_x;
        spWindow->m_ViewPort.pos.y = pos_y;
    }
    void Fr_Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        if (spWindow == nullptr)
            return;
        spWindow->m_ViewPort.size.w = width;
        spWindow->m_ViewPort.size.h = height;
        if (s_GladInitialized && s_GLFWInitialized) {
            glViewport(0, 0, width, width);
        }
        spWindow->handle(FR_WINDOW_RESIZE);
    }

    /*

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)

        window: A pointer to the GLFW window that received the event.
        key: The keyboard key that was pressed or released.
        scancode: The system-specific scancode of the key.
        action: The action that was performed on the key. It can be one of the following values:
            GLFW_PRESS: The key was pressed.
            GLFW_RELEASE: The key was released.
            GLFW_REPEAT: The key was held down and is being repeated.
        mods: Bit field describing which modifier keys (Shift, Control, Alt, Super) were held down.

    */
    void Fr_Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (spWindow == nullptr)
            return; //do nothing

        auto& e = spWindow->m_systemEvents;
        e.lastKey = key;
        e.scancode = scancode;
        e.lastAction = action;
        e.lastMod = mods;
        e.shiftDown = (mods & GLFW_MOD_SHIFT) != 0;
        e.ctrlDown = (mods & GLFW_MOD_CONTROL) != 0;
        e.altDown = (mods & GLFW_MOD_ALT) != 0;
        e.superDown = (mods & GLFW_MOD_SUPER) != 0;

        // Update the current key state
        if (key >= 0 && key <= GLFW_KEY_LAST)
            e.keyDown[key] = (action != GLFW_RELEASE);
    }

    void Fr_Window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
    {
        if (spWindow == nullptr)
            return; //do nothing

        auto& e = spWindow->m_systemEvents;
        
        //Avoid View jumping , we should initialize the current theta and phi 
        if (spWindow->runCode && button == GLFW_MOUSE_BUTTON_MIDDLE) {
            spWindow->runCode = false;
            Fr_Camera& cam = spWindow->activeScene->getActiveCamera();
            spWindow->theta = glm::degrees(atan2(cam.GetCamPosition().x, cam.GetCamPosition().y));
            spWindow->phi = glm::degrees(asin(cam.GetCamPosition().z / glm::length(cam.GetCamPosition())));
         }
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
            spWindow->runCode = true;
        }

        if (button == GLFW_MOUSE_BUTTON_LEFT)             e.L_Down = (action != GLFW_RELEASE);
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)       e.R_Down = (action != GLFW_RELEASE);
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE)      e.M_Down = (action != GLFW_RELEASE);
        spWindow->m_systemEvents.button = button;
        spWindow->m_systemEvents.lastAction = action;
        spWindow->m_systemEvents.lastMod = mods;
        spWindow->m_systemEvents.mouseEntered = true;
    }
    void Fr_Window::cursor_m_positioncallback(GLFWwindow* win, double xpos, double ypos)
    {
        if (!spWindow)
            return;
        auto& mouse = spWindow->m_systemEvents.mouse;
        mouse.activeX = xpos;
        mouse.activeY = ypos;
        spWindow->calculateScreenRay();
        // ----- SIGNALS -----
        spWindow->m_systemEvents.mouseMoved = true;
    }

    void Fr_Window::cursor_enter_callback(GLFWwindow* win, int entered)
    {
        if (spWindow == nullptr)
            return; //do nothing
        spWindow->m_systemEvents.mouseEntered = (entered != 0);
        //Reset DRAG
        spWindow->m_systemEvents.L_Drag = false;
        spWindow->m_systemEvents.R_Drag = false;
        spWindow->m_systemEvents.M_Drag = false;
    }

    void Fr_Window::scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
    {
        if (spWindow == nullptr)
            return;
        auto& m = spWindow->m_systemEvents.mouse;
        m.scrollX = xoffset;
        m.scrollY = yoffset;
    }

    //DON'T CHANGE ME WORKS GOOD !!!! 2025-10-22
    void Fr_Window::cameraPAN(GLFWwindow* win)
    {
        userData_ data;
        if (!spWindow)
            return;

        spWindow->activeScene->getActiveCamera().getCamData(data);
        auto& mouse = spWindow->m_systemEvents.mouse;
        double deltax = mouse.prevX - mouse.activeX;
        double deltay = mouse.prevY - mouse.activeY;
        // Only perform the panning if there is a significant change
        if (std::abs(deltax) < 1e-3 && std::abs(deltay) < 1e-3) {
            return; // Small movements are ignored
        }

        float xoffset = float(deltax) * spWindow->mouseDefaults.MouseXYScale;
        float yoffset = float(deltay) * spWindow->mouseDefaults.MouseXYScale;
        data.camm_position = glm::vec3(data.camm_position.x + xoffset, data.camm_position.y - yoffset, data.camm_position.z);
        data.direction_ = glm::vec3(data.direction_.x + xoffset, data.direction_.y - yoffset, data.direction_.z);
        spWindow->activeScene->getActiveCamera().setCamData(data);
    }
    //DON'T CHANGE ME WORKS GOOD !!!! 2025-10-22
    void Fr_Window::cameraRotate(GLFWwindow* win)
    {
        if (spWindow == nullptr)
            return;
        Fr_Camera& cam = spWindow->activeScene->getActiveCamera();

        spWindow->radiusXYZ = glm::length(cam.m_position);

        // Compute deltas
        auto& mouse = spWindow->m_systemEvents.mouse;
        float deltax = float(mouse.activeX - mouse.prevX) * spWindow->mouseDefaults.MouseXYScale;
        float deltay = float(mouse.activeY - mouse.prevY) * spWindow->mouseDefaults.MouseXYScale;

        spWindow->theta += deltax;
        spWindow->phi -= deltay;

        spWindow->phi = std::clamp(spWindow->phi, -89.99f, 89.99f);

        float radTheta = glm::radians(spWindow->theta);
        float radPhi = glm::radians(spWindow->phi);

        float x = spWindow->radiusXYZ * cos(radPhi) * sin(radTheta);
        float y = spWindow->radiusXYZ * cos(radPhi) * cos(radTheta);
        float z = spWindow->radiusXYZ * sin(radPhi);
        cam.m_position = glm::vec3(x, y, z);
    }

    void Fr_Window::cameraZoom(GLFWwindow* win)
    {
        userData_ data;
        activeScene->getActiveCamera().getCamData(data);
        if (spWindow->activeScene->getActiveCamera().getType() == ORTHOGRAPHIC) {
            data.orthoSize_ = data.orthoSize_ + float(m_systemEvents.mouse.scrollY) * spWindow->mouseDefaults.MouseScrollScale;
        }
        else
        {
            //Scroll zooming using the correct method of zooming. Use camera position by scaling the view-matrix
            float scale_;
            if (m_systemEvents.mouse.scrollY < 0) {
                scale_ = -1 * spWindow->mouseDefaults.MouseScrollScale;
            }
            else
            {
                scale_ = spWindow->mouseDefaults.MouseScrollScale;
            }
            glm::vec3 forward = glm::normalize(data.direction_ - data.camm_position); // forward direction
            data.camm_position += forward * scale_;   // move camera
            data.direction_ += forward * scale_;  // move target along with camera
        }
        spWindow->activeScene->getActiveCamera().setCamData(data);
    }

    void Fr_Window::createOpenDialog()
    {
        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiFileBrowserFlags_MultipleSelection;

        if (showOpenDialog) {
            ImGui::OpenPopup("File Browser");
        }

        if (ImGui::BeginPopupModal("File Browser", nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
        {
            if (!fileDialog) {
                fileDialog = std::make_shared<ImGui::FileBrowser>(window_flags, EXE_CURRENT_DIR);
                fileDialog->SetTitle("Open file");
                fileDialog->SetTypeFilters({ ".obj", ".off" });
            }

            fileDialog->Open();
            fileDialog->Display();

            if (!fileDialog->IsOpened() || fileDialog->isCanceled()) {
                showOpenDialog = false;
                fileDialog.reset();             
                ImGui::CloseCurrentPopup();
            }
            else if (fileDialog->HasSelected()) {
                for (const auto& obj : fileDialog->GetMultiSelected()) {
                    activeScene->add3DObject(obj.string());
                }
                fileDialog->ClearSelected();
                showOpenDialog = false;
                fileDialog.reset();             
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Close")) {
                showOpenDialog = false;
                fileDialog.reset();             
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }


    /**  callbacks */
    void Fr_Window::mnuFileNew_cb(void* Data) {
        std::cout << "File new callback\n";
    }

    void Fr_Window::mnuFileOpen_cb(void* Data) {
        showOpenDialog = true;
    }

    void Fr_Window::mnuFileClose_cb(void* Data) {
        std::cout << "File close callback\n";
    }

    void Fr_Window::mnuFileSave_cb(void* Data) {
        std::cout << "File save callback\n";
    }

    void Fr_Window::mnuFileSaveAs_cb(void* Data) {
        std::cout << "File save as callback\n";
    }

    void Fr_Window::mnuFileExport_cb(void* Data) {
        std::cout << "File export callback\n";
    }

    void Fr_Window::mnuFileImport_cb(void* Data) {
        std::cout << "File import callback\n";
    }

    void Fr_Window::mnuFileExit_cb(void* Data) {
        Exit();
    }

    //Selection toolbar callbacks
    void Fr_Window::mnuSelMesh_cb(void* data)
    {
    }

    void Fr_Window::mnuSelFace_cb(void* data)
    {
    }

    void Fr_Window::mnuSelEdges_cb(void* data)
    {
    }

    void Fr_Window::mnuSelVertex_cb(void* data)
    {
    }

    void Fr_Window::mnuEditUndo(void* Data) {
        std::cout << "undo\n";
    }

    void Fr_Window::mnuEditRedo(void* Data) {
        std::cout << "Redo\n";
    }

    void Fr_Window::mnuEditCopy(void* Data) {
        std::cout << "Copy\n";
    }

    void Fr_Window::mnuEditCut(void* Data) {
        std::cout << "Cut\n";
    }

    void Fr_Window::mnuEditPaste(void* Data) {
        std::cout << "Paste\n";
    }

    //Special Toolbars
    //Experimental code  -- just for debugging purpose
    void Fr_Window::mnuDrawLine_cb(void* Data) {
        //We assume that we work only on XY plane where Z=0 :
        //
        // TODO . Make this more general and possible to use any face of any object to draw
        std::shared_ptr<std::vector<float>> vert = std::make_shared<std::vector<float>>();
        std::shared_ptr<std::vector<unsigned int>> ind = std::make_shared<std::vector<unsigned int>>();
        //Temporary code .. make a line from (0x0x0) to (100,100,100)
        vert->push_back(10.0f);
        vert->push_back(10.0f);
        vert->push_back(0.0f);
        vert->push_back(100.0f);
        vert->push_back(100.0f);
        vert->push_back(0.0f);

        ind->push_back(0);
        ind->push_back(1);

        std::shared_ptr<Fr_Line_Widget> mline = std::make_shared<Fr_Line_Widget>(vert, ind);

        mline->pointPicker(true);
        mline->SetColor(glm::vec4(FR_RED));
        activeScene->addObject(mline, "Fr_Line_Widget");
        std::cout << "Line\n";

        std::shared_ptr<std::vector<float>> vert2 = std::make_shared<std::vector<float>>();
        std::shared_ptr<std::vector<unsigned int>> ind2 = std::make_shared<std::vector<unsigned int>>();

        vert2->push_back(-10.0f);
        vert2->push_back(-10.0f);
        vert2->push_back(0.0f);

        vert2->push_back(-30.0f);
        vert2->push_back(-10.0f);
        vert2->push_back(0.0f);

        vert2->push_back(-30.0f);
        vert2->push_back(-30.0f);
        vert2->push_back(0.0f);

        vert2->push_back(-10.0f);
        vert2->push_back(-30.0f);
        vert2->push_back(0.0f);

        ind2->push_back(0);
        ind2->push_back(1);
        ind2->push_back(2);
        ind2->push_back(3);

        std::shared_ptr<Fr_Face_Widget> mFace = std::make_shared<Fr_Face_Widget>(vert2, ind2);

        mFace->pointPicker(true);
        mFace->SetColor(glm::vec4(FR_GREENYELLOW));
        activeScene->addObject(mFace, "Fr_Face_Widget");
    }
}