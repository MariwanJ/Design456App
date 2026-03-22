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
#include <gui_widget/frtk_vwin.h>
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

    Frtk_Tabwdg::Frtk_Tabwdg(NVGcontext* vg, float W, float H, std::string l, BOX_TYPE b) : Frtk_GrpWidget(vg, 0.0f, 0.0f, W, H, l, b),
        m_headSapce(1.0f), m_headDim{ 0.0f }, m_bodyDim{ 0.0f }, m_headWidth{ 0.0f }, m_tabParts{ false, false }
    {
        m_wdgType = FRTK_TABWDG;
        m_font.fontSize = 12.0f;
        m_font.lblAlign = NVG_ALIGN_MIDDLE_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        m_color = glm::vec4(FR_LIGHTGREY);
        m_bkg_color = glm::vec4(FR_DARKGREY1);
        m_body = std::make_shared<Frtk_GrpWidget>(vg, 0, m_font.fontSize * HEIGHT_FACTOR + 2, W, H - m_font.fontSize * HEIGHT_FACTOR + 5, "", FRTK_FLAT_BOX);
        FRTK_CORE_APP_ASSERT(m_body, "obj allocation error!");
        addChild(m_body);//Only one child , using group make the implementation easier
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
        m_body->resize(X, Y, W, H);
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
        m_tabParts = { true,true };
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
    void Frtk_Tabwdg::draw_head() {
        if (m_has_focus) {
            draw_box(m_vg, m_boxType, m_headDim, 1.0f, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_bkg_color), glmToNVG(m_color), true);
            draw_focus();
        }
        else {
            draw_box(m_vg, m_boxType, m_headDim, 1.0f, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        }
        drawLabel();
    }
    void Frtk_Tabwdg::draw_body() {
        if(m_has_focus){
            m_body->show();
            draw_children();
        }
        else{
            m_body->hide();
        }
    }
    void Frtk_Tabwdg::draw()
    {
        draw_head();
        draw_body();
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

    /** ***********************************************************************************************************************************************************/

     //***********************************************************************************
     //                         Tabs container widget
     //***********************************************************************************

    Frtk_Tabs::Frtk_Tabs(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_GrpWidget(vg, X, Y, W, H, lbl, b),
        m_viewPort{ { 0.0, 0.0 },{0.0, 0.0} },
        m_content{ 0.0 }, m_viewOffs(0), m_history{ nullptr,nullptr ,nullptr ,nullptr } {
        Frtk_Tabs* tab = this;  // store explicitly
        m_font.fontSize = 12.0f;
        m_font.pos = { m_x,m_y };
        m_font.size = { m_w,m_h };
        m_font.lblAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE;
        m_font.txtAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        const char* right = "\xE2\x96\xB6"; // >
        const char* left = "\xE2\x97\x80";    // <

        m_wdgType = FRTK_TABS;
        m_viewPort.pos.x = X + Hpadding;
        m_viewPort.pos.y = Y + Vpadding;
        m_viewPort.size.w = W - TAB_BUTTON_SIZE - Hpadding;
        m_viewPort.size.h = m_h;

        m_scrollwdg.Hor.btnInc = { 0 };
        m_scrollwdg.Hor.btnDec = { 0 };
        m_scrollwdg.Hor.btnColor = glm::vec4(0.f, 0.f, 0.f, 0.1254f);
        m_trackExtra = 1.0f;
        updteTabBTNpos();
        m_content.pos = { 0 , 0};
        m_bkg_color = glm::vec4(FR_DARK_GRAY);
    }

    bool Frtk_Tabs::shouldClip() {
        return (m_viewPort.size.w < m_content.size.w);
    }
    int Frtk_Tabs::getIndex(std::shared_ptr < Frtk_Tabwdg> wdg) {
        std::shared_ptr<Frtk_Widget> basewdgt = std::static_pointer_cast<Frtk_Widget>(wdg);
        for (size_t i = 0; i < m_children.size(); ++i) {
            if (m_children[i] == basewdgt) {
                return i ;
            }
        }
        return -1;
    }

    void Frtk_Tabs::layoutTabs()
    {
        float headerHeight = m_font.fontSize * 1.15f;
        float startX = TAB_BUTTON_SIZE;
        float currentX = startX;
        for (auto& child : m_children)
        {
            auto tab = std::dynamic_pointer_cast<Frtk_Tabwdg>(child);
            float bounds[4];
            nvgTextBounds(m_vg, 0, 0, tab->label().c_str(), nullptr, bounds);
            const float minWidth = 45.0f;
            const float maxWidth = m_w;
            float textWidth = bounds[2] - bounds[0];
            float width = std::clamp(textWidth, minWidth, maxWidth - Hpadding);
            tab->setHeaderDim(currentX, Vpadding, width, headerHeight);
            tab->getFont().pos.x = currentX;
            tab->getFont().pos.y = headerHeight /4;
            tab->getFont().size.w = width;
            tab->getFont().size.h = headerHeight;
            tab->setBodyDim(0, Vpadding+ headerHeight + Vpadding, m_w, m_h - Vpadding - headerHeight);
            currentX += width +1;
            m_content.size.w += tab->m_headDim.size.w;
        }
        m_content.size.h = headerHeight;
    }


    void Frtk_Tabs::updateContentSize()
    {
        float maxW = m_w - m_viewPort.size.w ;
        float maxH = m_h - Vpadding ;
        for (auto& child : m_children)
        {
            std::shared_ptr<Frtk_Tabwdg> wdg = std::dynamic_pointer_cast<Frtk_Tabwdg>(child);
            float left = wdg->getHeadDim().pos.x + wdg->getHeadDim().size.w;
            if (left > maxW) 
                maxW = left;
        }
        m_content.size.w = maxW;
    }

    bool Frtk_Tabs::checkOverflow() {
        return (m_overflow.H);
    }

    void Frtk_Tabs::updteTabBTNpos()
    {
        // Buttons
        m_scrollwdg.Hor.btnDec.size.w = TAB_BUTTON_SIZE;
        m_scrollwdg.Hor.btnDec.size.h = TAB_BUTTON_SIZE + m_trackExtra;
        m_scrollwdg.Hor.btnDec.pos.x = m_x + m_trackExtra;
        m_scrollwdg.Hor.btnDec.pos.y = m_y;

        m_scrollwdg.Hor.btnInc.size.w = TAB_BUTTON_SIZE;
        m_scrollwdg.Hor.btnInc.size.h = TAB_BUTTON_SIZE + m_trackExtra;
        m_scrollwdg.Hor.btnInc.pos.x = m_x + m_w - TAB_BUTTON_SIZE - m_trackExtra;
        m_scrollwdg.Hor.btnInc.pos.y = m_y;
    }

    void Frtk_Tabs::draw()
    {
        draw_box(m_vg, m_boxType, { {m_x, m_y}, {m_w, m_h} }, 1.0f, FRTK_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        draw_scrollH();

        // Draw all tab HEADERS
        nvgSave(m_vg);
        nvgScissor(m_vg, m_viewPort.pos.x + TAB_BUTTON_SIZE, m_viewPort.pos.y, m_viewPort.size.w -Hpadding- TAB_BUTTON_SIZE, m_viewPort.size.h);
        nvgTranslate(m_vg, m_viewPort.pos.x - m_viewOffs, m_viewPort.pos.y);

        for (size_t i = 0; i < m_children.size(); ++i) {
            std::shared_ptr<Frtk_Tabwdg> wdg =std::dynamic_pointer_cast<Frtk_Tabwdg>(m_children[i]);
            wdg->draw_head();
        }
        nvgRestore(m_vg);

        // Draw ONLY the active tab's body
        for (size_t i = 0; i < m_children.size(); ++i) {
            std::shared_ptr<Frtk_Tabwdg> wdg =std::dynamic_pointer_cast<Frtk_Tabwdg>(m_children[i]);
            if (wdg->has_focus()) {
                wdg->draw_body();
                break; // only one active tab at a time
            }
        }
    }

    void Frtk_Tabs::draw_scrollH()
    {
        NVGpaint shadowPaint, fadePaint;
        float X_, Y_, W_, H_;
        X_ = m_scrollwdg.Hor.btnInc.pos.x;
        Y_ = m_scrollwdg.Hor.btnInc.pos.y;
        W_ = m_scrollwdg.Hor.btnInc.size.w;
        H_ = m_scrollwdg.Hor.btnInc.size.h;

        // Up btn
        fadePaint = nvgLinearGradient(m_vg, X_, Y_, X_, Y_ + H_, nvgRGBAf(0.75f, 0.75f, 0.75f, 1.0f), nvgRGBAf(0.55f, 0.55f, 0.55f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X_, Y_, W_, H_, 2.0f);
        nvgFillPaint(m_vg, fadePaint);
        nvgFill(m_vg);

        nvgBeginPath(m_vg);

        float midX = m_scrollwdg.Hor.btnInc.pos.x + m_scrollwdg.Hor.btnInc.size.w * 0.5f;
        float midY = m_scrollwdg.Hor.btnInc.pos.y + m_scrollwdg.Hor.btnInc.size.h * 0.5f;
        float tri = 4.0f;
        //Triangle
        nvgMoveTo(m_vg, midX + tri, midY);
        nvgLineTo(m_vg, midX - tri, midY - tri);
        nvgLineTo(m_vg, midX - tri, midY + tri);
        nvgClosePath(m_vg);
        nvgFillColor(m_vg, nvgRGBAf(FR_BLACK));
        nvgFill(m_vg);

        X_ = m_scrollwdg.Hor.btnDec.pos.x;
        Y_ = m_scrollwdg.Hor.btnDec.pos.y;
        W_ = m_scrollwdg.Hor.btnDec.size.w;
        H_ = m_scrollwdg.Hor.btnDec.size.h;

        // Down button
        fadePaint = nvgLinearGradient(m_vg, X_, Y_, X_, Y_ + H_, nvgRGBAf(0.75f, 0.75f, 0.75f, 1.0f), nvgRGBAf(0.55f, 0.55f, 0.55f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X_, Y_, W_, H_, 2.0f);
        nvgFillPaint(m_vg, fadePaint);
        nvgFill(m_vg);

        // Down arrow
        nvgBeginPath(m_vg);
        midX = m_scrollwdg.Hor.btnDec.pos.x + m_scrollwdg.Hor.btnDec.size.w * 0.5f;
        midY = m_scrollwdg.Hor.btnDec.pos.y + m_scrollwdg.Hor.btnDec.size.h * 0.5f;
        float triSize = 4.0f;

        nvgBeginPath(m_vg);
        nvgMoveTo(m_vg, midX - triSize, midY);
        nvgLineTo(m_vg, midX + triSize, midY - triSize);
        nvgLineTo(m_vg, midX + triSize, midY + triSize);
        nvgClosePath(m_vg);
        nvgFillColor(m_vg, nvgRGBAf(FR_BLACK));
        nvgFill(m_vg);
    }

    int Frtk_Tabs::updateBtnPressed()
    {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse;

        // reset state each frame
        m_activeBtns = { false };
        auto hit = [&](const auto& btn)->bool
            {
                float x = absX();
                float y = absY();
                x += (-m_x + btn.pos.x);
                y += (-m_y + btn.pos.y);

                return mouse.activeX >= x &&
                    mouse.activeY >= y &&
                    mouse.activeX <= x + btn.size.w &&
                    mouse.activeY <= y + btn.size.h;
            };

        if (hit(m_scrollwdg.Hor.btnInc))   
            m_activeBtns.right = true;
        else if (hit(m_scrollwdg.Hor.btnDec))   
            m_activeBtns.left = true;
        if (m_activeBtns.left || m_activeBtns.right)
            return 1;
        return 0;
    }

    std::shared_ptr<Frtk_Tabwdg> Frtk_Tabs::addTab()
    {
        //Important!! : Do not forget that pos is relative- i.e. //
        // inside a new group, your tope corner pos is NOT m_x, m_y
        // .. it is (0.0f,0.0f)!!!
        std::shared_ptr<Frtk_Tabwdg> tmpChild = std::make_shared<Frtk_Tabwdg>(m_vg, m_w, m_h);

        if (!m_history.m_first) {
            m_history.m_first = tmpChild;
            m_history.m_current = tmpChild;
            m_history.m_last = tmpChild;
            m_history.m_current->focus(true);
        }
        else
        {
            tmpChild->focus(false);
        }

        addChild(tmpChild);
        layoutTabs();
        updateContentSize();

        if (m_content.size.w <= m_viewPort.size.w)
            m_history.m_last = tmpChild;
        return tmpChild;
    }

    int Frtk_Tabs::findIndex(Frtk_Tabwdg* w) {
        for (size_t i = 0; i < m_children.size(); ++i) {
            if (m_children[i].get() == w)
                return static_cast<int>(i);
        }
        return -1; // not found
    }
    size_t Frtk_Tabs::getWidthFirstLastTabs() {
        size_t ind1 = getIndex(m_history.m_first);
        size_t ind2 = getIndex(m_history.m_last);
        float TotalWidth = 0.0;
        for (size_t i = ind1; i < ind2; ++i) {
            std::shared_ptr<Frtk_Tabwdg > wdg = std::static_pointer_cast<Frtk_Tabwdg>(m_children[i]);
            TotalWidth += wdg->getHeadDim().size.w;
        }
        return TotalWidth;
    }
    int Frtk_Tabs::handle(int ev)
    {
        if (!isMouse_inside())
            return 0;


        if (ev == FR_LEFT_PUSH) {
            auto mouse = m_mainWindow->m_sysEvents.mouse;
            float saveX = mouse.activeX;
            if (updateBtnPressed()) {
                size_t ind1 = getIndex(m_history.m_first);
                size_t ind2 = getIndex(m_history.m_last);

                if (m_activeBtns.right) {
                    if (ind2 < m_children.size() - 1) {
                        m_history.m_last = std::static_pointer_cast<Frtk_Tabwdg> (m_children[ind2 + 1]);
                        if (m_content.size.w > m_viewPort.size.w) {
                            m_viewOffs += m_history.m_first->getHeadDim().size.w;
                            m_history.m_first = std::static_pointer_cast<Frtk_Tabwdg> (m_children[ind1 + 1]);
                        }
                    }
                }else 
                    if (m_activeBtns.left) {
                        if (ind1 > 0) {
                            auto dim = m_history.m_last->getHeadDim();
                            m_viewOffs -= dim.pos.x + dim.size.w;
                            if (m_viewOffs < 0)
                                m_viewOffs = 0;
                            m_history.m_first= std::static_pointer_cast<Frtk_Tabwdg> (m_children[ind1 - 1]);
                            m_history.m_last = std::static_pointer_cast<Frtk_Tabwdg> (m_children[ind2 - 1]);
                        }
                }
                return 1; 
            }

            int focusedIndex = -1;
            int newIndex = -1;
            mouse.activeX = m_viewOffs;
            for (size_t i = 0; i < m_children.size(); ++i) {
                if (auto* tabwdg = dynamic_cast<Frtk_Tabwdg*>(m_children[i].get())) {
                    if (tabwdg->isTabClicked()) {
                        newIndex = i;
                    }
                    if (newIndex != -1) {
                        if (focusedIndex != -1) {
                            m_children[focusedIndex]->focus(false);
                        }
                        activeTab(newIndex);
                    }
                }
            }
            mouse.activeX = saveX;
        }
        if (Frtk_GrpWidget::handle(ev) == 1)
            return 1;
        return 0;
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
    void Frtk_Tabs::activeTab(size_t ind)
    {
        m_history.m_prev = m_history.m_current;
        m_history.m_current->focus(false);
        m_history.m_current->color(FR_LIGHTGREY);
        m_history.m_current = std::dynamic_pointer_cast<Frtk_Tabwdg>(m_children[ind]);
        m_history.m_current->focus(true);
        m_history.m_current->color(FR_DARKGREY1);
    }
}