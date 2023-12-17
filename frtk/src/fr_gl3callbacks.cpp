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

#include <frtk.h>
#include<fr_constants.h>

#include <Fr_GL3Window.h>
#include "fr_gl3callbacks.h"

//Wrapper Callbacks

void Fr_GL3Window::GLFWCallbackWrapper::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    s_fr_glfwwindow->framebuffer_size_callback(window, width, height);
}

void Fr_GL3Window::GLFWCallbackWrapper::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    s_fr_glfwwindow->keyboard_callback(window, key, scancode, action, mods);
}

void Fr_GL3Window::GLFWCallbackWrapper::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    s_fr_glfwwindow->cursor_position_callback(window, xpos, ypos);
}

void Fr_GL3Window::GLFWCallbackWrapper::cursor_enter_callback(GLFWwindow* window, int entered)
{
    s_fr_glfwwindow->cursor_enter_callback(window, entered);
}

void Fr_GL3Window::GLFWCallbackWrapper::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    s_fr_glfwwindow->mouse_button_callback(window, button, action, mods);
}

void Fr_GL3Window::GLFWCallbackWrapper::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    s_fr_glfwwindow->scroll_callback(window, xoffset, yoffset);
}

void Fr_GL3Window::GLFWCallbackWrapper::joystick_callback(int jid, int events)
{
    s_fr_glfwwindow->joystick_callback(jid, events);
}

void Fr_GL3Window::GLFWCallbackWrapper::setGLFWwindow(Fr_GL3Window* glfwWindow)
{
    GLFWCallbackWrapper::s_fr_glfwwindow = glfwWindow;
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileNew_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileNew_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileOpen_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileOpen_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileClose_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileClose_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileSave_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileSave_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileSaveAs_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileSaveAs_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileExport_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileExport_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileImport_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileImport_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuFileExit_cb(void* Data)
{
    s_fr_glfwwindow->mnuFileExit_cb(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuEditUndo(void* Data)
{
    s_fr_glfwwindow->mnuEditUndo(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuEditRedo(void* Data)
{
    s_fr_glfwwindow->mnuEditRedo(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuEditCopy(void* Data)
{
    s_fr_glfwwindow->mnuEditCopy(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuEditCut(void* Data)
{
    s_fr_glfwwindow->mnuEditCut(Data);
}

void Fr_GL3Window::GLFWCallbackWrapper::mnuEditPaste(void* Data)
{
    s_fr_glfwwindow->mnuEditPaste(Data);
}

void Fr_GL3Window::mnuFileNew_cb(void* Data) {
    std::cout << "File new callback\n";
}

void Fr_GL3Window::mnuFileOpen_cb(void* Data) {
    showOpenDialog = true;
}

void Fr_GL3Window::mnuFileClose_cb(void* Data) {
    std::cout << "File close callback\n";
}

void Fr_GL3Window::mnuFileSave_cb(void* Data) {
    std::cout << "File save callback\n";
}

void Fr_GL3Window::mnuFileSaveAs_cb(void* Data) {
    std::cout << "File save as callback\n";
}

void Fr_GL3Window::mnuFileExport_cb(void* Data) {
    std::cout << "File export callback\n";
}

void Fr_GL3Window::mnuFileImport_cb(void* Data) {
    std::cout << "File import callback\n";
}

void Fr_GL3Window::mnuFileExit_cb(void* Data) {
    Fr_GL3Window::getfr_Gl3Window()->Exit();
}

void Fr_GL3Window::mnuEditUndo(void* Data) {
    std::cout << "undo\n";
}

void Fr_GL3Window::mnuEditRedo(void* Data) {
    std::cout << "Redo\n";
}

void Fr_GL3Window::mnuEditCopy(void* Data) {
    std::cout << "Copy\n";
}

void Fr_GL3Window::mnuEditCut(void* Data) {
    std::cout << "Cut\n";
}

void Fr_GL3Window::mnuEditPaste(void* Data) {
    std::cout << "Paste\n";
}

void Fr_GL3Window::createOpenDialog(void)
{
    ImGuiWindowFlags window_flags = 0
        | ImGuiWindowFlags_NoDocking
        //| ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize
        //   | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoScrollbar
        //| ImGuiWindowFlags_NoSavedSettings
        ;
    ImGui::Begin("File Browser", nullptr, ImGuiWindowFlags_NoDocking);
    // (optional) set browser properties
    this->fileDialog.SetTitle("Open file");
    fileDialog.SetTypeFilters({ ".obj", ".off" });
    fileDialog.Open();
    fileDialog.Display();

    if (fileDialog.HasSelected())
    {
        std::string fileName = fileDialog.GetSelected().string();
        scene->add3DObject(fileName);
        fileDialog.ClearSelected();
        showOpenDialog = false;
    }
    ImGui::End();
}