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

#include <gui_widget/frtk_toolbarwin.h>

namespace FR {
#define DOCKING_BTN_SIZE FRTK_TOOLBAR_BUTTON_HEGHT/2
    Frtk_ToolBarWin::Frtk_ToolBarWin(float X, float Y, float W, float H, std::string lbl,
        const std::vector<toolbBTN_t>& tools, bool horizontal, BOX_TYPE b) : Frtk_Window(X, Y, W, H, lbl, FRTK_FLAT_BOX, false),
        m_dockable(false), m_padding(1.0f), m_horizontal(horizontal) {
        m_boxType = FRTK_FLAT_BOX;
        m_color = glm::vec4(FR_RED);

        init();
        m_wdgType = FRTK_TOOLBARWIN;
        if (m_horizontal)
            m_dockingSize = { {0.0,0.0},{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_HEIGHT} };
        else
            m_dockingSize = { {0.0,0.0},{FRTK_TOOLBAR_HEIGHT,FRTK_TOOLBAR_BUTTON_HEGHT} };

        //Create the buttons
        addButton(tools);
    }
    bool Frtk_ToolBarWin::dockable()
    {
        return m_dockable;
    }
    void Frtk_ToolBarWin::horizontal(bool val)
    {
        m_horizontal = val;
    }
    void Frtk_ToolBarWin::addButton(const std::vector<toolbBTN_t>& btns)
    {
        Dim_float_t btnDim;

        if (m_horizontal)
            btnDim = { { DOCKING_BTN_SIZE + 1.f, 0.f }, { m_dockingSize.size.w , m_dockingSize.size.h } };
        else
            btnDim = { { 0.f,FRTK_TOOLBAR_BUTTON_HEGHT + 1.f },{ m_dockingSize.size.w,m_dockingSize.size.h } };

        //Make sure that the toolbar has a correct dimension, user MUST make sure the dimension is correct
        if (m_horizontal)
            FRTK_CORE_APP_ASSERT((m_w) >= ((float)btns.size() * FRTK_TOOLBAR_HEIGHT));
        else
            FRTK_CORE_APP_ASSERT((m_h) >= ((float)btns.size() * FRTK_TOOLBAR_HEIGHT));
        
        for (const auto& item : btns) {
            auto btn = std::make_shared<Frtk_ToolBar_Button>(m_vg, btnDim.pos.x, btnDim.pos.y+m_padding, item.size.w, item.size.h, item.lbl);
            btn->name(item.name);
            btn->tooltips(item.tooltips);

            if (m_horizontal) {
                btnDim.pos.x += item.size.w + m_padding;
            }
            else
            {
                //Vertical Toolbar
                btnDim.pos.y += item.size.h + m_padding;
            }
            btn->wdgImage(item.icon);
            btn->cellStyle(FR_IMG_OVER_TEXT_CENTER);
            btn->set_callback(item.callback_);
            m_guiWindow->addChild(btn);
        }
    }
    int Frtk_ToolBarWin::removeButton(std::string& name)
    {
        auto btnchildren = m_guiWindow->getChildren();
        for (auto& wdg : btnchildren) {
            if (auto* btn = dynamic_cast<Frtk_ToolBar_Button*>(wdg.get()))
                if (btn->name() == name) {
                    remove_child(wdg);
                }
        }
        return 0;
    }

    void Frtk_ToolBarWin::dockable(bool val)
    {
        m_dockable = val;
    }
    bool Frtk_ToolBarWin::dockingBTN(void) {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse;
        bool result = mouse.activeX >= m_dockingSize.pos.x +m_x && mouse.activeX <= m_dockingSize.pos.x +m_x + m_dockingSize.size.w &&
            mouse.activeY >= m_dockingSize.pos.y + m_y && mouse.activeY <= m_dockingSize.pos.y + m_y + m_dockingSize.size.h;
        return result;
    }
    void Frtk_ToolBarWin::drawVerticalDivider()
    {
        const float cx = m_x + 20.f * 0.5f;
        const float top = m_y + m_padding;
        const float bottom = m_y + m_h - m_padding;
        const float lineSpacing = 4.0f;
        const float strokeWidth = 1.0f;
        FRTK_CORE_INFO("{} {} {} {}", cx, top, bottom, m_x);
        nvgStrokeWidth(m_vg, strokeWidth);
        nvgStrokeColor(m_vg, nvgRGBA(FR_RED));
        nvgBeginPath(m_vg);
        // Draw 3 vertical grip lines
        for (int i = -1; i <= 10; ++i)
        {
            float x = floorf(cx + i * lineSpacing) + 0.5f; // pixel aligned
            nvgMoveTo(m_vg, x, top);
            nvgLineTo(m_vg, x, bottom);
        }

        nvgStroke(m_vg);
    }

    void Frtk_ToolBarWin::draw() {
      
       Frtk_Window::draw();
       drawVerticalDivider();
     
    }
    int Frtk_ToolBarWin::handle(int ev)
    {
        if ( should_getEvent()) {
            if (dockingBTN() || m_dragging) {
                if (ev == FR_LEFT_DRAG_PUSH) {
                    m_dragging = true;
                    float dx, dy;
                    const auto& mouse = m_mainWindow->m_sysEvents.mouse; // content-space mouse
                    dx = (float)(mouse.prevX - mouse.activeX);
                    dy = (float)(mouse.prevY - mouse.activeY);
                    m_guiWindow->position(m_x - dx, m_y - dy);
                    this->position(m_x - dx, m_y - dy);
                    return 1;
                }
                else if (m_dragging && ev == FR_LEFT_RELEASE) {
                    m_dragging = false;
                    m_mainWindow->activateNavi();
                    return 1;
                }
            }
        }
        Frtk_Window::handle(ev);
    }
}