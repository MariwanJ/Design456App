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
    //Left-Right buttons callbacks

    static void tabButtonPressed_callback(uint8_t index, Frtk_Widget* w) {
        if (!w) return;

        auto tab = dynamic_cast<Frtk_Tabs*>(w);
        if (!tab) return;

        auto tabwdgs = tab->getChildren();
        if (tabwdgs.empty()) return;

        // Find the currently focused widget
        size_t focusedIndex = 0;
        bool found = false;
        for (size_t i = 0; i < tabwdgs.size(); ++i) {
            if (tabwdgs[i]->has_focus()) {
                focusedIndex = i;
                found = true;
                break;
            }
        }
        size_t newIndex = 0;
        if (found) {
            if (index == 0) {                           // <----
                newIndex = (focusedIndex == 2) ? 2 : focusedIndex - 1;
            }
            else if (index == 1) {        //  ---->
                newIndex = (focusedIndex + 1 < tabwdgs.size()) ? focusedIndex + 1 : 2;
            }
        }
        // Set focus to the new widget
        tab->activeTab(newIndex);
        tabwdgs[focusedIndex]->focus(false);
        tabwdgs[newIndex]->focus(true);
    }

    Frtk_Tabwdg::Frtk_Tabwdg(NVGcontext* vg, float W, float H, std::string l, BOX_TYPE b) : Frtk_GrpWidget(vg, 0.0f, 0.0f, W, H, l, b),
        m_headSapce(1.0f), m_headDim{ 0.0f }, m_bodyDim{ 0.0f }, m_headWidth{ 0.0f }
    {
        m_wdgType = FRTK_TABWDG;
        m_font.fontSize = 14.0f;
        m_font.lblAlign = NVG_ALIGN_MIDDLE_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        m_color = glm::vec4(FR_LIGHTGREY);
        m_bkg_color = glm::vec4(FR_DARKGREY1);
        init_headwidth();
        m_body = std::make_shared<Frtk_GrpWidget>(m_vg, 0, m_font.fontSize * HEIGHT_FACTOR + 2, W,H-m_font.fontSize * HEIGHT_FACTOR+5, "", FRTK_FLAT_BOX);
        addChild(m_body);
        FRTK_CORE_APP_ASSERT(m_body, "obj allocation error!");
    }
    //make this function protected as user should not add widgets to header group
    void Frtk_Tabwdg::addChild(std::shared_ptr<Frtk_Widget> wdg)
    {
        Frtk_GrpWidget::addChild(wdg);
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
        m_body->resize(X, Y, H, W);
    }
    void Frtk_Tabwdg::addChildToTab(std::shared_ptr<Frtk_Widget> wdg) {
        if (wdg) {
            m_body->addChild(wdg);
        }
    }

    void Frtk_Tabwdg::show()
    {
        m_visible = true;
        m_body->show();
    }

    void Frtk_Tabwdg::hide()
    {
        m_visible = false;
        m_body->hide();
    }

    void Frtk_Tabwdg::hide_children()
    {
        m_body->hide();
    }

    void Frtk_Tabwdg::show_children()
    {
        m_body->show();
    }

    bool Frtk_Tabwdg::isTabClicked()
    {
        Dim_float_t realDim;
        dimPos_float_t delta = { absX() - m_x, absY() - m_y };

        dimPos_float_t topLeft = { m_headDim.pos.x + delta.x, m_headDim.pos.y + delta.y };
        dimPos_float_t bottomRight = { topLeft.x + m_headDim.size.w, topLeft.y + m_headDim.size.h };

        auto mouse = m_mainWindow->m_sysEvents.mouse;
        return (mouse.activeX >= topLeft.x &&
            mouse.activeX <= bottomRight.x &&
            mouse.activeY >= topLeft.y &&
            mouse.activeY <= bottomRight.y);
    }

    Dim_float_t Frtk_Tabwdg::getHeadDim()
    {
        return m_headDim;
    }
    Dim_float_t Frtk_Tabwdg::getBodyDim()
    {
        return m_bodyDim;
    }
    void Frtk_Tabwdg::draw()
    {
        if (m_has_focus) {
            draw_box(m_vg, m_boxType, m_headDim, 0.0f, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_bkg_color), glmToNVG(m_color), true);
            m_body->show();
        }
        else {
            draw_box(m_vg, m_boxType, m_headDim, 0.0f, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
            m_body->hide();
        }
        draw_box(m_vg, BOX_TYPE(m_boxType + 1), { 0,m_headDim.pos.y + m_headDim.size.h, m_w,2.0f }, 0.0f, FRTK_EXTRA_THIN_BORDER, nvgRGBAf(FR_BLUE), glmToNVG(m_bkg_color), false);
        draw_focus();
        drawLabel();
        // draw widgets container - children of this tab widget
        draw_children();
    }

    void Frtk_Tabwdg::draw_focus()
    {
        if (m_has_focus)
            draw_box(m_vg, FRTK_THIN_UP_FRAME, m_headDim, 0.2f, FRTK_EXTRA_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(m_bkg_color), true);
    }

    void Frtk_Tabwdg::draw_focus(BOX_TYPE t, float X, float Y, float W, float H)
    {
        draw_box(m_vg, t, m_headDim, 0.2f, FRTK_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(m_bkg_color), true);
    }

    void Frtk_Tabwdg::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)
    {
        draw_box(m_vg, t, m_headDim, 0.2f, FRTK_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(bkg), true);
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
    Frtk_Tabs::Frtk_Tabs(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_GrpWidget(vg, X, Y, W, H, lbl, b), m_currentActiveTab(0)
    {
        Frtk_Tabs* tab = this;  // store explicitly
        m_font.fontSize = 14.0f;
        m_font.pos = { m_x,m_y };
        m_font.size = { m_w,m_h };
        m_font.lblAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE;
        m_font.txtAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        const char* right = "\xE2\x96\xB6"; // >
        const char* left = "\xE2\x97\x80";    // <

        auto bt1 = std::make_shared<Frtk_Button>(m_vg, padding, padding, TAB_BUTTON_SIZE, TAB_BUTTON_SIZE, left, FRTK_THIN_UP_BOX);
        auto bt2 = std::make_shared<Frtk_Button>(m_vg, m_w - padding - TAB_BUTTON_SIZE, padding, TAB_BUTTON_SIZE, TAB_BUTTON_SIZE, right, FRTK_THIN_UP_BOX);

        bt1->parent(this);
        bt1->getFont().fName = "emoji";
        bt1->getFont().pos.x = 0;
        bt1->getFont().pos.y = 0;
        bt1->getFont().size.w = TAB_BUTTON_SIZE;
        bt1->getFont().size.h = TAB_BUTTON_SIZE;
        bt1->set_callback([tab](Frtk_Widget* w) { tabButtonPressed_callback(0, tab); });

        bt2->parent(this);
        bt2->getFont().fName = "emoji";
        bt2->getFont().pos.x = 0;
        bt2->getFont().pos.y = 0;
        bt2->getFont().size.w = TAB_BUTTON_SIZE;
        bt2->getFont().size.h = TAB_BUTTON_SIZE;
        bt2->set_callback([tab](Frtk_Widget* w) { tabButtonPressed_callback(1, tab); });

        addChild(bt1);
        addChild(bt2);
        m_wdgType = FRTK_TABS;
        m_currentActiveTab = 2;
    }
    std::shared_ptr<Frtk_Tabwdg> Frtk_Tabs::addTab()
    {
        //Important!! : Do not forget that pos is relative- i.e. //
        // inside a new group, your tope corner pos is NOT m_x, m_y
        // .. it is (0.0f,0.0f)!!!
        std::shared_ptr<Frtk_Tabwdg> tmpChild = std::make_shared<Frtk_Tabwdg>(m_vg, m_w, m_h);
        addChild(tmpChild);
        if (getChildren().size() >= 3) {
            getChildren().at(2)->focus(true);
            m_currentActiveTab = 0;
        }
        return tmpChild;
    }
    int Frtk_Tabs::findIndex(Frtk_Tabwdg* w) {
        for (size_t i = 0; i < m_children.size(); ++i) {
            if (m_children[i].get() == w)
                return static_cast<int>(i);
        }
        return -1; // not found
    }

    void Frtk_Tabs::draw()
    {
        //draw_children();
        Frtk_GrpWidget::draw();
    }

    int Frtk_Tabs::handle(int ev)
    {
        if (ev == FR_LEFT_PUSH) {
            int focusedIndex = -1;
            int newIndex = -1;
            for (size_t i = 0; i < m_children.size(); ++i) {
                if (m_children[i]->has_focus()) {
                    focusedIndex = i;
                    break;
                }
            }

            for (size_t i = 0; i < m_children.size(); ++i) {
                if (auto* tabwdg = dynamic_cast<Frtk_Tabwdg*>(m_children[i].get())) {
                    if (tabwdg->isTabClicked()) {
                        newIndex = i;
                    }

                    if (newIndex != -1) {
                        if (focusedIndex != -1){
                            m_children[focusedIndex]->focus(false);
                        }
                        activeTab(newIndex);
                        m_children[newIndex]->focus(true);
                    }
                }
            }
        }
        if (Frtk_GrpWidget::handle(ev) == 1)
            return 1;
        return 0;
    }

    void Frtk_Tabs::layoutTabs()
    {
        float headerHeight = TAB_BUTTON_SIZE;
        float startX = TAB_BUTTON_SIZE + padding;
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
            tab->setHeaderDim(currentX, padding, width, padding + headerHeight);
            tab->setBodyDim(0, padding + headerHeight + 2, m_w, m_h - padding + headerHeight + 2);
            tab->getFont().pos.x = currentX;
            tab->getFont().pos.y = padding;
            tab->getFont().size.w = width;
            tab->getFont().size.h = headerHeight;
            currentX += width + padding;
        }
    }
    void Frtk_Tabs::show() {
        m_visible = true;
        Frtk_GrpWidget::show();
    }
    void Frtk_Tabs::hide() {
        m_has_focus = false;
        m_visible = false;
        Frtk_GrpWidget::hide();
    }
    size_t Frtk_Tabs::activeTabIndex()
    {
        return m_currentActiveTab;;
    }
    void Frtk_Tabs::activeTab(size_t ind)
    {
        m_currentActiveTab = ind;
    }
}