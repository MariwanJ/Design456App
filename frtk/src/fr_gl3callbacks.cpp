#include <frtk.h>
#include <FR.h>

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
















void Fr_GL3Window::mnuFileNew_cb(void* Data){
    std::cout << "File new callback\n";
}

void Fr_GL3Window::mnuFileOpen_cb( void* Data){
    std::cout << "File open callback\n";
}

void Fr_GL3Window::mnuFileClose_cb( void* Data){
    std::cout << "File close callback\n";
}

void Fr_GL3Window::mnuFileSave_cb(void* Data){
    std::cout << "File save callback\n";
}

void Fr_GL3Window::mnuFileSaveAs_cb(void* Data){
    std::cout << "File save as callback\n";
}

void Fr_GL3Window::mnuFileExport_cb( void* Data){
    std::cout << "File export callback\n";
}

void Fr_GL3Window::mnuFileImport_cb( void* Data){
    std::cout << "File import callback\n";
}

void Fr_GL3Window::mnuFileExit_cb(void* Data){
    Fr_GL3Window::getfr_Gl3Window()->Exit();
}

void Fr_GL3Window::mnuToolsOptionCamera_cb(userData_ &data){
    ImGui::Begin("Camera Options");
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
    ImGui::End();
}

void Fr_GL3Window::mnuEditUndo(void* Data){
    std::cout << "undo\n";
}

void Fr_GL3Window::mnuEditRedo(void* Data){
    std::cout << "Redo\n";
}

void Fr_GL3Window::mnuEditCopy(void* Data){
    std::cout << "Copy\n";
}

void Fr_GL3Window::mnuEditCut(void* Data){
    std::cout << "Cut\n";
}

void Fr_GL3Window::mnuEditPaste(void* Data){
    std::cout << "Paste\n";
}





void Fr_GL3Window::GLFWCallbackWrapper::mnuToolsOptionCamera_cb(userData_& Data)
{
    s_fr_glfwwindow->mnuToolsOptionCamera_cb(Data);
}
