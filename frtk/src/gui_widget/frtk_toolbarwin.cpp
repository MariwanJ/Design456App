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

#include <gui_widget/frtk_toggle_button.h>
#include <gui_widget/frtk_Toggle_light_button.h>
#include <gui_widget/frtk_Toggle_round_button.h>
#include <gui_widget/frtk_check_button.h>
#include <gui_widget/frtk_switch_button.h>
#include <gui_widget/frtk_light_button.h>
#include <gui_widget/frtk_round_button.h>

namespace FR {
#define DOCKING_BTN_SIZE FRTK_TOOLBAR_BUTTON_HEGHT/2
    Frtk_ToolBarWin::Frtk_ToolBarWin(float X, float Y, float W, float H, std::string lbl,
        const std::vector<toolbBTN_t>& tools, bool horizontal, BOX_TYPE b, WIDGTYPE btnType) : Frtk_Window(X, Y, W, H, lbl, b, false),
        m_dockable(false), m_padding(1.0f), m_horizontal(horizontal), m_parent(NULL), m_buttonsType(btnType) {
        m_boxType = b;
        init();
        m_wdgType = FRTK_TOOLBARWIN;
        if (m_horizontal)
            m_dockingSize = { {0.0,0.0},{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_HEIGHT} };
        else
            m_dockingSize = { {0.0,0.0},{FRTK_TOOLBAR_HEIGHT,FRTK_TOOLBAR_BUTTON_HEGHT} };
        //Create the buttons
        addButton(tools);
    }
    Fr_Window* Frtk_ToolBarWin::parent(void) {
        return m_parent;
    }
    void Frtk_ToolBarWin::parent(Fr_Window* w) {
        m_parent = w;
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
        bool first = false;
        for (const auto& item : btns) {
            std::shared_ptr<Frtk_Button> btn;

            switch (m_buttonsType) {
            case FRTK_LIGHT_BUTTON: {
                btn = std::make_shared<Frtk_Light_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            case FRTK_SWITCH_BUTTON: {
                btn = std::make_shared<Frtk_Switch_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            case FRTK_TOGGLE_BUTTON: {
                btn = std::make_shared<Frtk_Toggle_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            case FRTK_CHECK_BUTTON: {
                btn = std::make_shared<Frtk_Check_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            case FRTK_ROUND_BUTTON: {
                btn = std::make_shared<Frtk_Round_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            case FRTK_TOGGLE_ROUND_BUTTON: {
                btn = std::make_shared<Frtk_Toggle_Round_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            case FRTK_TOGGLE_LIGHT_BUTTON: {
                btn = std::make_shared<Frtk_Toggle_Light_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            } break;
            default: {
                btn = std::make_shared<Frtk_ToolBar_Button>(m_vg, btnDim.pos.x, btnDim.pos.y + m_padding, item.size.w, item.size.h, item.lbl);
            }
            }
            btn->name(item.name);
            if (first) {
                btn->value(1);
                first = true;//First get ON value
            }
            btn->boxType(item.boxType);
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
            btn->cellStyle(FR_IMG_LEFT_TO_TEXT);
            btn->set_callback(item.callback_);
            m_guiWindow->addChild(btn);
        }
    }

    int Frtk_ToolBarWin::removeButton(const std::string& name)
    {
        auto btnchildren = m_guiWindow->getChildren();
        for (auto& wdg : btnchildren) {
            if (auto* btn = dynamic_cast<Frtk_Button*>(wdg.get()))
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
        bool result = mouse.activeX >= m_dockingSize.pos.x + m_x && mouse.activeX <= m_dockingSize.pos.x + m_x + m_dockingSize.size.w &&
            mouse.activeY >= m_dockingSize.pos.y + m_y && mouse.activeY <= m_dockingSize.pos.y + m_y + m_dockingSize.size.h;
        return result;
    }
    void Frtk_ToolBarWin::addButtonAtPos(const std::shared_ptr<Frtk_ToolBar_Button>& w)
    {
        m_guiWindow->addChild(w);
    }
    void Frtk_ToolBarWin::drawVerticalDivider()
    {
        const float cx = m_x + DOCKING_BTN_SIZE * 0.5f;
        const float cy = m_y + DOCKING_BTN_SIZE * 0.5f;

        const float strokeWidth = 1.5f;
        const float lineSpacing = 4.0f;

        nvgStrokeWidth(m_vg, strokeWidth);
        nvgStrokeColor(m_vg, nvgRGBAf(0.6274f, 0.6274f, 0.6274f, 1.0f));
        nvgBeginPath(m_vg);

        float top, bottom;

        if (m_horizontal) {
            top = m_y + m_padding;
            bottom = m_y + m_h - m_padding;
        }
        else
        {
            top = m_x + m_padding;
            bottom = m_x + m_w - m_padding;
        }

        // Draw 3 vertical grip lines
        for (int i = -1; i <= 1; ++i)
        {
            if (m_horizontal) {
                float x = floorf(cx + i * lineSpacing) + 0.5f; // pixel aligned
                nvgMoveTo(m_vg, x, top);
                nvgLineTo(m_vg, x, bottom);
            }
            else
            {
                float y = floorf(cy + i * lineSpacing) + 0.5f;
                nvgMoveTo(m_vg, top, y);
                nvgLineTo(m_vg, bottom, y);
            }
        }
        nvgStroke(m_vg);
    }

    void Frtk_ToolBarWin::draw() {
        if (!m_visible)
            return;
        Fr_Camera& camera = m_mainWindow->activeScene->getActiveCamera();
        float ratio = camera.getRatio();
        FRTK_CORE_APP_ASSERT(m_vg != nullptr);
        float cornerRadius = 3.0f;
        m_guiWindow->redraw();
        drawVerticalDivider();
        if (!m_label.empty())
            drawLabel();
        draw_focus();
    }

    void Frtk_ToolBarWin::setLayoutHorizontal() {
        m_font.Rotate = 0.0f;

        float temp = m_h;
        h(m_w);
        w(temp);
        m_guiWindow->h(m_h);
        m_guiWindow->w(m_w);

        m_horizontal = true;
        float offsetX = DOCKING_BTN_SIZE;
        float offsetY = 0.0f;
        auto children = m_guiWindow->getChildren();
        std::vector<std::shared_ptr<Frtk_Widget>> tempChildren(children.begin(), children.end());
        m_guiWindow->remove_all();

        for (auto& item : tempChildren) {
            item->position(offsetX, offsetY + m_padding);
            item->cellStyle(FR_IMG_OVER_TEXT_CENTER);
            offsetX += item->w() + m_padding;
            m_guiWindow->addChild(item);
        }
        redraw();
    }

    void Frtk_ToolBarWin::setLayoutVertical() {
        m_font.Rotate = 90.0f;
        float temp = m_h;
        h(m_w);
        w(temp);
        m_guiWindow->h(m_h);
        m_guiWindow->w(m_w);

        m_horizontal = false;

        float offsetX = 0.0f;
        float offsetY = DOCKING_BTN_SIZE;
        auto children = m_guiWindow->getChildren();
        std::vector<std::shared_ptr<Frtk_Widget>> tempChildren(children.begin(), children.end());
        m_guiWindow->remove_all();
        for (auto& item : tempChildren) {
            item->position(offsetX, offsetY + m_padding);
            item->cellStyle(FR_IMG_OVER_TEXT_CENTER);
            offsetY += item->h() + m_padding;
            m_guiWindow->addChild(item);
        }
    }

    void Frtk_ToolBarWin::applyDocking() {
        float snapThreshold = 20.0f;            // how close to edge to dock
        float winWidth = m_mainWindow->w();
        float winHeight = m_mainWindow->h();
        Fr_Window* win = (Fr_Window*)m_parent; //make it clear what m_parent is
        FRTK_CORE_APP_ASSERT(win);

        /*
        This functionality is highly dependent on the application.
        All four types are implemented;
        however, I've disabled left docking because
        I will have other widgets in the left panel.
        */
        if (m_y <= snapThreshold) {
            // Snap to top
            if (!m_horizontal) {
                m_horizontal = true;
                setLayoutHorizontal();
            }
            m_y = win->menuHeight() + 1.0f;
            m_x = 0.0f;
        }
        else if (m_y + m_h >= winHeight - snapThreshold) {
            // Snap to bottom

            if (!m_horizontal) {
                m_horizontal = true;
                setLayoutHorizontal();
            }
            m_horizontal = true;
            m_y = m_parent->h() - m_h - 1.0f;
            m_x = 0.0f;
        }
        else
            if (m_x <= snapThreshold) {
                //For this application, treat it as snap-to-top
                {
                    if (!m_horizontal)
                    {
                        m_horizontal = true;
                        setLayoutHorizontal();
                    }
                    m_y = win->menuHeight() + 1.0f;
                    m_x = 0.0f;
                }
                /*
                 -- TODO: Use me if you want snap-to-left and remove the above 5 lines of code
                */
                // Snap to left
                 /*
                    if (m_horizontal) {
                        m_horizontal = false;
                        setLayoutVertical();
                    }
                    m_x = 0.0f;
                    m_y = m_parent->menuHeight()+1.0f;
                */
            }
            else if (m_x + m_w >= winWidth - snapThreshold) {
                // Snap to right
                if (m_horizontal) {
                    m_horizontal = false;
                    setLayoutVertical();
                }
                m_x = winWidth - m_w + 1;
                m_y = m_parent->h() - m_h; //We have navibox at the right side, we cannot take the toolbar at the top
            }

        m_guiWindow->position(m_x, m_y);
        this->position(m_x, m_y);
    }

    int Frtk_ToolBarWin::handle(int ev)
    {
        Fr_Window* win = m_parent; //just to make it clear what m_parent is here
        FRTK_CORE_APP_ASSERT(m_parent);

        float snapThreshold = 10.0f; // pixels
        float winWidth = m_mainWindow->w();
        float winHeight = m_mainWindow->h();


        bool snapLeft = (m_x <= snapThreshold);
        bool snapRight = (m_x + m_w >= winWidth - snapThreshold);
        bool snapTop = (m_y <= snapThreshold);
        bool snapBottom = (m_y + m_w >= winHeight - snapThreshold);

        if (dockingBTN() && ev == FR_LEFT_DRAG_PUSH) {
            m_dragging = true;
        }

        if (dockingBTN() || m_dragging) {
            if (ev == FR_LEFT_DRAG_PUSH) {
                float dx, dy;
                const auto& mouse = m_mainWindow->m_sysEvents.mouse; // content-space mouse
                dx = (float)(mouse.prevX - mouse.activeX);
                dy = (float)(mouse.prevY - mouse.activeY);
                m_x = m_x - dx;
                m_y = m_y - dy;
                m_guiWindow->position(m_x, m_y);
                return 1;
            }
            else if (m_dragging && ev == FR_LEFT_RELEASE) {
                m_dragging = false;
                applyDocking();
                m_mainWindow->activateNavi();
                return 1;
            }
        }

        auto& mouse = m_mainWindow->m_sysEvents.mouse;
        int result = 0;
        if (isMouse_inside() || m_dragging) {
            m_mainWindow->deactivateNavi();
            result = 1;
            if (m_hasHeader) {
                if (Header_clicked() || m_dragging) {
                    if (ev == FR_LEFT_DRAG_PUSH) {
                        m_dragging = true;
                        float dx, dy;
                        dx = (float)(mouse.prevX - mouse.activeX);
                        dy = (float)(mouse.prevY - mouse.activeY);
                        position(m_x - dx, m_y - dy);
                        m_guiWindow->position(m_guiWindow->x() - dx, m_guiWindow->y() - dy);
                        return 1;
                    }
                    else if (m_dragging && ev == FR_LEFT_RELEASE) {
                        m_dragging = false;
                        m_mainWindow->activateNavi();
                        return 1;
                    }
                }
            }
            // WE MUST RETURN ALWAYS 1 .. events over the window should be consumed
            // we dont care if the group dosen't consume the events
            // Scene should not get events if the mouse was over a frtk-window!!!! IMPORTANT TO REMEMBER!!!
            if (!m_dragging)
                m_mainWindow->activateNavi();
            size_t index = 0;
            size_t noOfChildren = m_guiWindow->getChildrenNo();
            bool allZero = false;
            if (m_wdgType == FRTK_TOOLBARWIN_TOOGLE) {
                //ONLY ACTIVE WHEN WE HAVE TOOGLE BUTTONS TOOLBAR  
                for (size_t i = 0; i < noOfChildren; ++i) {
                    auto wdg = m_guiWindow->getChildAt(i);
                    std::shared_ptr<Frtk_Button> btn = std::dynamic_pointer_cast<Frtk_Button>(wdg);
                    if (ev == FR_LEFT_PUSH) {
                        if (btn->isMouse_inside()) {
                            if (btn->value() == 1) {
                                ;
                            }
                            else {
                                btn->value(1);
                                btn->activate(); //do-callback
                            }
                        }
                        else {
                            btn->value(0);
                        }
                    }
                }
            }
            else {
                return Frtk_Window::handle(ev);
            }
        }
        return result;
    }
}