//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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

//Wrapper Callbacks
namespace FR {
    void Fr_Window::glfwWindosResize(GLFWwindow* window, int width, int height)
    {
        if (spWindow == nullptr)
            return;
        spWindow->m_ViewPort.w = width;
        spWindow->m_ViewPort.h = height;
        glfwGetWindowPos(pGLFWWindow, 
                         &spWindow->m_ViewPort.x,
                         &spWindow->m_ViewPort.y); //update even position
        
        uint8_t index = spWindow->activeScene->m_active_camera;
        spWindow->activeScene->m_cameras[index].m_aspect_ratio = static_cast<float>(spWindow->m_ViewPort.w) / spWindow->m_ViewPort.h;
    }
    void Fr_Window::glfwWindPos(GLFWwindow* window, int pos_x, int pos_y)
    {
        if (spWindow == nullptr)
            return;
        spWindow->m_ViewPort.x = pos_x;
        spWindow->m_ViewPort.y = pos_y;
    }
    void Fr_Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        if (spWindow == nullptr)
            return;
        spWindow->m_ViewPort.w = width;
        spWindow->m_ViewPort.h = height;
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
        m_GLFWevents = { -1,-1,-1,-1,-1 };

        m_GLFWevents.lastKey = key;
        m_GLFWevents.lastAction = action;
        m_GLFWevents.lastMod = mods;
        m_GLFWevents.scancode = scancode;
        if (spWindow->handle(FR_KEYBOARD) == 1) { //TODO CHECK ME IF THIS IS CORRECT
            m_GLFWevents = { -1,-1,-1,-1,-1 };
            return;
        }
    }

    void Fr_Window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
    {
        //TODO FIX ME  - THIS IS NOT FINISHED - THIS AND MOUSE MOVEMENT IS NOT CORRECT
        if (spWindow == nullptr)
            return; //do nothing

        m_GLFWevents.button = button;          /* #define 	GLFW_MOUSE_BUTTON_1   0
                                                        #define 	GLFW_MOUSE_BUTTON_2   1
                                                        #define 	GLFW_MOUSE_BUTTON_3   2
                                                        #define 	GLFW_MOUSE_BUTTON_4
                                                        #define 	GLFW_MOUSE_BUTTON_5   4
                                                        #define 	GLFW_MOUSE_BUTTON_6   5
                                                        #define 	GLFW_MOUSE_BUTTON_7   6
                                                        #define 	GLFW_MOUSE_BUTTON_8   7
                                                        #define 	GLFW_MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_8
                                                        #define 	GLFW_MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_1
                                                        #define 	GLFW_MOUSE_BUTTON_RIGHT   GLFW_MOUSE_BUTTON_2
                                                        #define 	GLFW_MOUSE_BUTTON_MIDDLE   GLFW_MOUSE_BUTTON_3*/
        m_GLFWevents.lastAction = action;       //GLFW_RELEASE = The key or mouse button was released, GLFW_PRESS =The key or mouse button was pressed.  , GLFW_REPEAT=  The key was held down until it repeated.   , GLFW_KEY_UNKNOWN
        m_GLFWevents.lastMod = mods;          //GLFW_CURSOR, GLFW_STICKY_KEYS, GLFW_STICKY_MOUSE_BUTTONS, GLFW_LOCK_KEY_MODS or GLFW_RAW_MOUSE_MOTION.
        /*
                GLFW_CURSOR: Controls the appearance and behavior of the cursor.
                GLFW_STICKY_KEYS: Controls whether keys remain "pressed" after being released.
                GLFW_STICKY_MOUSE_BUTTONS: Controls whether mouse buttons remain "pressed" after being released.
             */


        glfwMouseEvent mouse_evnets = spWindow->getMouseEvents();

        //Limit handle area to the viewport only. Ignore other windows
        //bool a1, a2, a3, a4;
        //a1 = mouse_evnets.Old_x > viePort.relativeToScreen.x;
        //a2 = mouse_evnets.Old_x < (viePort.relativeToScreen.x + viePort.width);
        //a3 = mouse_evnets.Old_y > viePort.relativeToScreen.y;
        //a4 = mouse_evnets.Old_y < (viePort.relativeToScreen.y + viePort.height);
        
        //todo : DO WE NEED THIS AFTER REMOVING IMGUI? 
        bool activateHandle = true; // a1&& a2&& a3&& a4;

        if (GLFW_PRESS == action) {
            mouseEvent.Pressed = 1; //Pressed
        }
        else {
            mouseEvent.Pressed = 0; //Released
        }
        mouseEvent.Button = button;

        auto shftL = glfwGetKey(win, GLFW_KEY_LEFT_SHIFT);
        auto shftR = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT);

        if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT && mouseEvent.Pressed == 1)
        {        //FRTK_CORE_INFO("MOUSE LEFT");

            if (activateHandle) {
                if (spWindow->handle(FR_LEFT_PUSH) == 1) //Mouse click
                    return;  //Events is consumed - no more action required
            }
        }
        else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT && mouseEvent.Pressed == 0)
        {
            //FRTK_CORE_INFO("MOUSE LEFT");

            if (activateHandle) {
                if (spWindow->handle(FR_LEFT_RELEASE) == 1) //Mouse click
                    return;  //Events is consumed - no more action required
            }
        }

        else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_RIGHT && mouseEvent.Pressed == 1)
        {

            if (activateHandle) {
                if (spWindow->handle(FR_RIGHT_PUSH) == 1) //Mouse click
                    return;  //Events is consumed - no more action required
            }
        }
        else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_RIGHT && mouseEvent.Pressed == 0)
        {

            if (activateHandle) {
                if (spWindow->handle(FR_RIGHT_RELEASE) == 1) //Mouse click
                    return;  //Events is consumed - no more action required
            }
        }

        else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_MIDDLE && mouseEvent.Pressed == 1)
        {

            if (activateHandle) {
                if (spWindow->handle(FR_MIDDLE_PUSH) == 1) //Mouse click
                    return;
            }
        }

        else if (mouseEvent.Button == GLFW_MOUSE_BUTTON_MIDDLE && mouseEvent.Pressed == 0)
        {
            //TODO : Not sure if widgets needs this event

            if (activateHandle) {
                if (spWindow->handle(FR_MIDDLE_RELEASE) == 1) {//Mouse click
                    mouseEvent.Button = -1; //consumed§l+--
                    return;
                }
            }
        }
    }
    void Fr_Window::cursor_m_positioncallback(GLFWwindow* win, double xpos, double ypos)
    {
        // Ensure window is valid
        if (!spWindow)
            return;

        // Modifier keys
        bool shiftPressed = (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
            glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

        int saveButton = mouseEvent.Button;
        int res = 0;

        // Get state
        glfwMouseEvent mouse_events = spWindow->getMouseEvents();
 
        ray_t ray = spWindow->GetScreenToWorldRay();

        mouseEvent.MouseRay = { ray.position, ray.direction };

        // Limit handle area to viewport only
        bool activateHandle = true; 
        //TODO : Do we need this after removeing imgui??
        /*(mouse_events.Old_x > viewPort.relativeToScreen.x &&
            mouse_events.Old_x < (viewPort.relativeToScreen.x + viewPort.width) &&
            mouse_events.Old_y > viewPort.relativeToScreen.y &&
            mouse_events.Old_y < (viewPort.relativeToScreen.y + viewPort.height));*/

        // Helper lambdas
        auto updateMousePosition = [&](double x, double y) {
            mouseEvent.Old_x = x;
            mouseEvent.Old_y = y;
            };

        auto consumeEvent = [&](bool resetEvents = false) {
            if (resetEvents) {
                m_GLFWevents = { -1,-1,-1,-1,-1 };
            }
            else {
                mouseEvent.Button = 0;
            }
            };

        // ------------------------------
        // Left mouse
        if (saveButton == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (mouseEvent.Pressed == 1) // Drag
            {

                if (activateHandle) {
                    res = spWindow->handle(FR_LEFT_DRAG_PUSH);
                    updateMousePosition(xpos, ypos);
                    if (res) { consumeEvent(); return; }
                }
            }
            else if (mouseEvent.Pressed == 0) // Release
            {

                if (activateHandle) {
                    res = spWindow->handle(FR_LEFT_DRAG_RELEASE);
                    updateMousePosition(xpos, ypos);
                    if (res) { consumeEvent(true); return; }
                }
            }
        }
        // ------------------------------
        // Right mouse
        else if (saveButton == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (mouseEvent.Pressed == 1) // Drag
            {

                if (activateHandle) {
                    res = spWindow->handle(FR_RIGHT_DRAG_PUSH);
                    updateMousePosition(xpos, ypos);
                    if (res) { consumeEvent(); return; }
                }
            }
            else if (mouseEvent.Pressed == 0) // Release
            {

                if (activateHandle) {
                    res = spWindow->handle(FR_RIGHT_DRAG_RELEASE);
                    updateMousePosition(xpos, ypos);
                    if (res) { consumeEvent(true); return; }
                }
            }
        }
        // ------------------------------
        // Middle mouse
        else if (saveButton == GLFW_MOUSE_BUTTON_MIDDLE)
        {
            if (mouseEvent.Pressed == 1) // Drag
            {
                if (spWindow->runCode) {
                    updateMousePosition(xpos, ypos);  // FIXED: use current position, not (0,0)
                    spWindow->runCode = false;
                }

                if (shiftPressed) {
                    glfwSetCursor(win, spWindow->cursorHand);  // pre-created cursor
                    if (activateHandle) {
                        res = spWindow->handle(FR_MIDDLE_DRAG_PUSH);
                        if (res==1) {
                            updateMousePosition(xpos, ypos); 
                            return; 
                        }
                        cameraPAN(win, xpos, ypos);
                        updateMousePosition(xpos, ypos);
                        return;
                    }
                }
                else {
                    glfwSetCursor(win, spWindow->cursorCrosshair); // pre-created cursor
                    cameraRotate(win, xpos, ypos);
                    updateMousePosition(xpos, ypos);
                    return;
                }
            }
            else if (mouseEvent.Pressed == 0) // Release
            {
                glfwSetCursor(win, nullptr); // restore default


                if (activateHandle) {
                    res = spWindow->handle(FR_MIDDLE_RELEASE);
                    if (res) { consumeEvent(true); }
                    updateMousePosition(xpos, ypos);
                    spWindow->phi = spWindow->theta = 0.0f;
                    spWindow->runCode = true;
                    return;
                }
            }
        }
        // ------------------------------
        // General mouse move (no button pressed)
        if (activateHandle) {
            spWindow->handle(FR_MOUSE_MOVE);
        }
        updateMousePosition(xpos, ypos);
    }


    void Fr_Window::cursor_enter_callback(GLFWwindow*, int entered)
    {
    }

    void Fr_Window::scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
    {
        if (spWindow == nullptr)
            return;
        userData_ data;
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].getUserData(data);
        if (spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].getType() == ORTHOGRAPHIC) {
            data.orthoSize_ = data.orthoSize_ + float(yoffset) * spWindow->mouseDefaults.MouseScrollScale;
        }
        else
        {
            //Scroll zooming using the correct method of zooming. Use camera position by scaling the view-matrix
            float scale_;

            glm::mat4 matr = glm::lookAt(data.camm_position, data.direction_, data.up_);
            if (yoffset < 0) {
                scale_ = 1 / spWindow->mouseDefaults.MouseScrollScale;
            }
            else
            {
                scale_ = spWindow->mouseDefaults.MouseScrollScale;
            }
            matr = glm::scale(matr, glm::vec3(scale_, scale_, scale_));
            glm::mat4 inverseViewMatrix = glm::inverse(matr);
            data.camm_position = glm::vec3(inverseViewMatrix[3]);
            data.direction_ = -glm::vec3(inverseViewMatrix[2]);
            data.up_ = glm::vec3(inverseViewMatrix[1]);
        }
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].setUserData(data);
    }

    void Fr_Window::MouseMovement(double xoffset, double yoffset)
    {
    }

    void Fr_Window::cameraPAN(GLFWwindow* win, double xpos, double ypos)
    {
         userData_ data;

        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].getUserData(data);

        if (mouseEvent.Old_x == mouseEvent.Old_y && mouseEvent.Old_x == 0) {
            mouseEvent.Old_x = xpos;
            mouseEvent.Old_y = ypos;
        }

        double deltax = mouseEvent.Old_x - xpos;
        double deltay = mouseEvent.Old_y - ypos;

        // Only perform the panning if there is a significant change
        if (std::abs(deltax) < 1e-3 && std::abs(deltay) < 1e-3) {
            return; // Small movements are ignored
        }

        float xoffset = float(deltax) * spWindow->mouseDefaults.MouseXYScale;
        float yoffset = float(deltay) * spWindow->mouseDefaults.MouseXYScale;
        data.camm_position = glm::vec3(data.camm_position.x - xoffset, data.camm_position.y - yoffset, data.camm_position.z);
        data.direction_ = glm::vec3(data.direction_.x - xoffset, data.direction_.y - yoffset, data.direction_.z);
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].setUserData(data);

        ray_t ray= spWindow->GetScreenToWorldRay();
        mouseEvent.MouseRay.direction = ray.direction;
        mouseEvent.MouseRay.position= ray.position;
    }

    void Fr_Window::cameraRotate(GLFWwindow* win, double xpos, double ypos)
    {
        userData_ data;
        if (spWindow == nullptr)
            return;
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].getUserData(data);
        spWindow->radiusXYZ = sqrt(data.camm_position.x * data.camm_position.x +
            data.camm_position.y * data.camm_position.y +
            data.camm_position.z * data.camm_position.z);

        // Initialize
        if (mouseEvent.Old_x == mouseEvent.Old_y && mouseEvent.Old_x == 0) {
            mouseEvent.Old_x = xpos;
            mouseEvent.Old_y = ypos;
            //   radiusXYZ = glm::length(data.camm_position.x);
            //  theta = atan2(data.camm_position.y, data.camm_position.x); // Angle in radians
            //  phi = acos(data.camm_position.z / radiusXYZ); // Angle in radians
            //theta = glm::degrees(theta);
            //phi = glm::degrees(phi);
            //phi = glm::clamp(phi, -89.99f, 89.99f);
            spWindow->theta = 0.0f;
            spWindow->phi = 45.0f;        //TODO : STILL THIS IS NOT CORRECT TOTALLY 2025-02-13
        }

        float deltax = float(mouseEvent.Old_x - xpos);
        float deltay = float(mouseEvent.Old_y - ypos);
        deltax *= spWindow->mouseDefaults.MouseXYScale;
        deltay *= spWindow->mouseDefaults.MouseXYScale;

        spWindow->theta += deltax;
        spWindow->phi += deltay;

        // Clamp phi values
       // phi = glm::clamp(phi, -89.99f, 89.99f);

        // Update camera position using correct spherical coordinates
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].m_position.x = spWindow->radiusXYZ * sin(glm::radians(spWindow->phi)) * cos(glm::radians(spWindow->theta));
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].m_position.y = spWindow->radiusXYZ * sin(glm::radians(spWindow->phi)) * sin(glm::radians(spWindow->theta));
        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].m_position.z = spWindow->radiusXYZ * cos(glm::radians(spWindow->phi));

        spWindow->activeScene->m_cameras[spWindow->activeScene->m_active_camera].updateViewMatrix();
        ray_t ray= spWindow->GetScreenToWorldRay();
        mouseEvent.MouseRay.position = ray.position;
        mouseEvent.MouseRay.direction = ray.direction;
    }
    glfwMouseEvent Fr_Window::getMouseEvents()
    {
        return mouseEvent;
    }
    void Fr_Window::createOpenDialog(void)
    {
        ImGuiWindowFlags window_flags = 0
            | ImGuiWindowFlags_NoDocking
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoScrollbar;
            
 
        ImGui::Begin("File Browser", nullptr, ImGuiWindowFlags_NoDocking);
        // (optional) set browser properties
        this->fileDialog.SetTitle("Open file");
        fileDialog.SetTypeFilters({ ".obj", ".off" });
        fileDialog.Open();
        fileDialog.Display();
        // Close button
        
        if (!fileDialog.IsOpened()) {
            showOpenDialog = false; // User canceled or closed the dialog
        }
        if (fileDialog.HasSelected())
        {
            std::string fileName = fileDialog.GetSelected().string();
            activeScene->add3DObject(fileName);
            fileDialog.ClearSelected();
            showOpenDialog = false;
        }
  

        ImGui::End();
 
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
        vert2->push_back(-10.0f);

        vert2->push_back(-30.0f);
        vert2->push_back(-10.0f);
        vert2->push_back(-10.0f);

        vert2->push_back(-30.0f);
        vert2->push_back(-30.0f);
        vert2->push_back(-10.0f);

        vert2->push_back(-10.0f);
        vert2->push_back(-30.0f);
        vert2->push_back(-10.0f);

        ind2->push_back(0);
        ind2->push_back(1);
        ind2->push_back(2);
        ind2->push_back(3);

        std::shared_ptr<Fr_Face_Widget> mFace = std::make_shared<Fr_Face_Widget>(vert2, ind2);

        mFace->pointPicker(true);
        mFace->SetColor(glm::vec4(FR_GREENYELLOW));
        activeScene->addObject(mFace,"Fr_Face_Widget");
    }
}