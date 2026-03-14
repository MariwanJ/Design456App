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
#include <fr_window.h>
#include "fr_gl3callbacks.h"
#include <gui_widget/frtk_window.h>

namespace FR {

    void Fr_Window::showRightClickMenu(){
    //Right click should activate the pop up windows which has a bunch of commands, and menus 
           //TODO : make this to be more elegant and create the right-click menu 
    if (m_rightClickMenu) {
        //if it was visible - remove it 
        m_rightClickMenu->Exit();
        m_rightClickMenu = nullptr;
    }
    m_rightClickMenu = std::make_shared <Frtk_Window>(100, 100, 400, 400, "PopuWindow");
    m_rightClickMenu->show();
}
}