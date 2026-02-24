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

#include <gui_widget/frtk_tab.h>
#include <gui_widget/frtk_window.h>
namespace FR {
    /* | [Btn] | Tabs Tabs Tabs Tabs | [Btn] |
               |     |
       ----------------------------------------
       |                                       |
       |                                       |
       |           Children widgets            |
       |                                       |
       |                                       |
       ----------------------------------------

    */

    Frtk_Tabwdg::Frtk_Tabwdg(NVGcontext* vg, float w, float h, std::string l, BOX_TYPE b) : Frtk_GrpWidget(vg, 0.0f, 0.0f, w, h, l, b),
        m_headSapce(2.0f), m_headDim{ 0.0f }, m_bodyDim{ 0.0f }, m_headWidth{ 0.0f }
    {
        m_font.fontSize = 14.0f;
        m_font.lblAlign = NVG_ALIGN_MIDDLE_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        m_color = glm::vec4(FR_LIGHTGREY);
        m_bkg_color = glm::vec4(FR_DARKGREY1);
        init_headwidth();
    }
    void Frtk_Tabwdg::setHeaderDim(float X, float Y, float W, float H)
    {
        m_headDim.pos.x = X;
        m_headDim.pos.y = Y;
        m_headDim.size.w = W;
        m_headDim.size.h = H;
    }
    void Frtk_Tabwdg::setBodyDim(float X, float Y, float W, float H)
    {
        m_bodyDim.pos.x = X;
        m_bodyDim.pos.y = Y;
        m_bodyDim.size.w = W;
        m_bodyDim.size.h = H;
    }
    Dim_float_t Frtk_Tabwdg::getHeadDim()
    {
        return m_headDim;
    }
    Dim_float_t Frtk_Tabwdg::getBodyDim()
    {
        return m_bodyDim;
    }
    int Frtk_Tabwdg::handle(int ev)
    {
        if (Frtk_GrpWidget::handle(ev) == 1)
            return 1;
        return 0;
    }
    void Frtk_Tabwdg::draw()
    {
        draw_tabHeader();
        draWBody();
        draw_focus();
        drawLabel();
    }

    void Frtk_Tabwdg::draWBody()
    {
        draw_box(m_vg, m_boxType, m_bodyDim, 0.0f, FRTK_NORMAL_BORDER, nvgRGBAf(FR_GRAY), glmToNVG(m_color), true);
    }

    void Frtk_Tabwdg::draw_tabHeader()
    {
        if (m_has_focus)
            draw_box(m_vg, m_boxType, m_headDim, 0.0f, FRTK_EXTRA_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(m_bkg_color), true);
        else
            draw_box(m_vg, m_boxType, m_headDim, 0.0f, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
    }
    void Frtk_Tabwdg::draw_focus()
    {
        if (m_has_focus)
            draw_box(m_vg, FRTK_THIN_UP_FRAME, m_headDim, 0.2f, FRTK_EXTRA_THIN_BORDER, nvgRGBAf(FR_CYAN), glmToNVG(m_bkg_color), true);
    }
    void Frtk_Tabwdg::draw_focus(BOX_TYPE t, float X, float Y, float W, float H)
    {
        draw_box(m_vg, t, { { X,Y }, { W,H } }, 0.2f, FRTK_THIN_BORDER, nvgRGBAf(FR_BEIGE), glmToNVG(m_bkg_color), true);
    }
    void Frtk_Tabwdg::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)
    {
        draw_box(m_vg, t, { { X,Y }, { W,H } }, 0.2f, FRTK_THIN_BORDER, nvgRGBAf(FR_BEIGE), glmToNVG(bkg), true);
    }

    void Frtk_Tabwdg::drawLabel()
    {
        if (m_linkTofrtkWindow)
            drawTextInBox(m_vg, m_label, m_font, true, m_linkTofrtkWindow->getFontData());
    }

    void Frtk_Tabwdg::init_headwidth()
    {
        float bounds[4];
        nvgTextBounds(m_vg, 0, 0, m_label.c_str(), nullptr, bounds);

        const float minWidth = 80.0f;
        const float maxWidth = 200.0f;

        float textWidth = bounds[2] - bounds[0];

        m_headWidth = std::clamp(textWidth + padding, minWidth, maxWidth);
    }

    //***********************************************************************************
    //                         Tabs container widget
    //***********************************************************************************
    Frtk_Tab::Frtk_Tab(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_GrpWidget(vg, x, y, w, h, l, b)
    {
        m_font.fontSize = 14.0f;
        m_font.pos = { m_x,m_y };
        m_font.size = { m_w,m_h };
        m_font.lblAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE;
        m_font.txtAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        const char* right = "\xE2\x96\xB6"; // >
        const char* left= "\xE2\x97\x80"; // <

        auto bt1 = std::make_shared<Frtk_Button>(m_vg, padding, padding, TAB_BUTTON_SIZE, m_font.fontSize * 2, left, FRTK_UP_BOX);
        auto bt2 = std::make_shared<Frtk_Button>(m_vg, m_w-padding- TAB_BUTTON_SIZE, padding, TAB_BUTTON_SIZE, m_font.fontSize*2, right, FRTK_UP_BOX);
        m_navButton.push_back(bt1);
        m_navButton.push_back(bt2);
        addChild(bt1);
        addChild(bt2);
    }
    std::shared_ptr<Frtk_Tabwdg> Frtk_Tab::addTab()
    {
        //Important!! : Do not forget that pos is relative- i.e. inside a new group, your tope corner pos is NOT m_x, m_y .. it is (0.0f,0.0f)!!!
        std::shared_ptr<Frtk_Tabwdg> tmpChild = std::make_shared<Frtk_Tabwdg>(m_vg, m_w, m_h);
        addChild(tmpChild);
        return tmpChild;
    }

    int Frtk_Tab::handle(int ev)
    {
        if (Frtk_GrpWidget::handle(ev)) {
            return 1;
        }
        return 0;
    }

    void Frtk_Tab::draw()
    {
        draw_box(m_vg, m_boxType, { {m_x,m_y}, {m_w,m_h} }, 0.0f, FRTK_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        Frtk_GrpWidget::draw();
        drawLabel();
    }

    void Frtk_Tab::layoutTabs()
    {
        float headerHeight = m_font.fontSize * 2 + padding;
        float startX = TAB_BUTTON_SIZE;
        float currentX = startX;
        for (auto& child : m_children)
        {
            if (child->widgetType() == FRTK_NORMAL_BUTTON) 
                continue;
            auto tab = std::dynamic_pointer_cast<Frtk_Tabwdg>(child);
            float bounds[4];
            nvgTextBounds(m_vg, 0, 0, tab->label().c_str(), nullptr, bounds);
            const float minWidth = 30.0f;
            const float maxWidth = m_w;
            float textWidth = bounds[2] - bounds[0];
            float width = std::clamp(textWidth, minWidth, maxWidth - padding);
            tab->setHeaderDim(currentX, 0, width, headerHeight);
            tab->setBodyDim(0, headerHeight, m_w, m_h - headerHeight);
            currentX += width;
        }
     }
}