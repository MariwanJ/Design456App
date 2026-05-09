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

#include <fr_window.h>
#include <gui_widget/frtk_vwin.h>
#include <gui_widget/frtk_toolbar_vwin.h>
#include<fr_menu.h>
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
#include <gui_widget/frtk_tab.h>
namespace FR {
    std::shared_ptr<Frtk_Vwin> Fr_Window::leftPanel()
    {
        Dim_float_t dim = { {0.0f, 28.0f },{400, h() - 28.f} };
        std::shared_ptr<Frtk_Vwin> leftPanel = std::make_shared<Frtk_Vwin>(dim.pos.x, dim.pos.y, dim.size.w, dim.size.h, "");
        leftPanel->hasHeader(false);
        
        m_leftPanelTab = std::make_shared<Frtk_Tabs>(leftPanel->getContext(),0.0f, 0.0f, leftPanel->w(), leftPanel->h() / 2,"Main");
        auto newTab = m_leftPanelTab->addTab();
        newTab->label("Model");
        newTab->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);
        
        newTab = m_leftPanelTab->addTab();
        newTab->label("Basic Shapes");
        newTab->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);
        leftPanel->addChild(m_leftPanelTab);
        return leftPanel;
    }
}