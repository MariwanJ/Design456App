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

/* Main application code */

static void buttonPressed(Fl_Widget* w, void* data) {
    Fl_Button* bb = (Fl_Button*)(data);
    std::cout << "You clicked me!!\n";
}
int main(int argc, char** argv)
{
    Fr_GL3Window* win = new Fr_GL3Window(0, 0, 1000, 800, "Modern OpenGL with FLTK support");
    win->setOpenGLWinowSize(30, 30, 600, 600);
    win->resizable(win);
    Fl_Button* b = new Fl_Button(10, 5, 50, 40, "clickme");
    b->callback((Fl_Callback*)buttonPressed, b);
    win->show();
    win->GLFWrun();
}