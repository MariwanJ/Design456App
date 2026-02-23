#include "frtk_tab.h"
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

namespace FR {
    Frtk_Tab::Frtk_Tab(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_GrpWidget(vg, x, y, w, h, l, b),
        m_headSapce(2.0f)
    {
    m_headDim.pos  = {x + m_headSapce, y + m_headSapce};
    m_headDim.size = {w - m_headSapce, h * 0.2f };
    m_bodyDim.pos.x = m_headDim.pos.x;
    m_bodyDim.pos.y = m_headDim.pos.y + m_headDim.size.h + 1.0f;
    m_bodyDim.size.w = m_headDim.size.w ;
    m_bodyDim.size.h = h - m_headDim.size.h - 1;
    m_color = glm::vec4(FR_LIGHTGREY);
    m_bkg_color = glm::vec4(FR_DARKGREY1);
    }
    int Frtk_Tab::handle(int ev)
    {
        return 0;
    }
    void Frtk_Tab::draw()
    {
        draw_tabHeader();
        draw_tabBody();
        
    }
    void Frtk_Tab::draw_tabHeader()
    { 
        draw_box(m_vg, FRTK_UP_BOX, m_headDim, 0.5f, FRTK_NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
    }
    void Frtk_Tab::draw_tabBody()
    {
        draw_box(m_vg, FRTK_UP_BOX, m_bodyDim, 0.5f, FRTK_NORMAL_BORDER, nvgRGBAf( FR_GRAY), glmToNVG(m_color), true);
    }
}
