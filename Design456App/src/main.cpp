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


#include <FL/Fl_Button.H>
#include <Fr_GL3Window.h>
#include<Scene.h>
#include<Camera.h>
#include<Manipulator.h>


static void buttonPressed1(Fl_Widget* w, void* data) {
    Fr_GL3Window * b1 = (Fr_GL3Window*)(data);
    std::cout << "You clicked me1!!\n";
    b1->releaseGLfwWindow();
}
static void buttonPressed2(Fl_Widget* w, void* data) {
    Fr_GL3Window* b2 = (Fr_GL3Window*)(data);
    std::cout << "You clicked me2!!\n";
    b2->embeddGLfwWindow();
}

//
//static std::shared_ptr<Camera> CreateCamera(Group* parent, int cameraId) {
//    auto camera = std::make_shared<Camera>();
//    camera->SetPerspective(40, 0.5, 50);
//    camera->SetActive(false);
//    parent->AddNode(camera);
//    auto manipulator = new Manipulator();
//    camera->SetManipulator(std::unique_ptr<Manipulator>(manipulator));
//
//
// [cameraId].camera = camera.get();
//    cameras[cameraId].manipulator = manipulator;
//
//    return camera;
//}
#include<Application.h>

int main(int argc, char** argv)
{

    Fr_GL3Window* win = new Fr_GL3Window(0, 0, 1000, 800, "Modern OpenGL with FLTK support");
    win->setOpenGLWinowSize(70, 60, 900, 740);
    win->resizable(win);
    Fl_Button* b1 = new Fl_Button(10, 5, 50, 40, "Release");
    Fl_Button* b2 = new Fl_Button(100, 5, 50, 40, "CHILD");
    //win->CreateScene();
    b1->callback((Fl_Callback*)buttonPressed1, win);
    b2->callback((Fl_Callback*)buttonPressed2, win);
    win->show();
    win->GLFWrun();
    //return FakeMain(argc, argv);
}