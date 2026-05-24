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

#define TAB_BUTTON_SIZE 15.0f
#define TAB_HPADDING     8.0f
#define TAB_VPADDING     3.0f
#define HEIGHT_FACTOR    1.3f

    Frtk_Tabwdg::Frtk_Tabwdg(NVGcontext* vg, float W, float H, std::string l, BOX_TYPE b) : Frtk_GrpWidget(vg, 0.0f, 0.0f, W, H, l, b),
        m_headSapce(1.0f), m_headDim{ 0.0f }, m_bodyDim{ 0.0f }, m_headWidth{ 0.0f }, m_tabParts{ false, false }
    {
        m_wdgType = FRTK_TABWDG;
        m_font.fontSize = 12.0f;
        m_font.lblAlign = NVG_ALIGN_MIDDLE_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        m_color = glm::vec4(FR_LIGHTGREY);
        m_bkg_color = glm::vec4(FR_DARKGREY1);
        m_body = std::make_shared<Frtk_GrpWidget>(vg, 0, m_font.fontSize * HEIGHT_FACTOR + 2, W, H - m_font.fontSize * HEIGHT_FACTOR + 5, "", FRTK_ROUNDED_BOX_UP);
        FRTK_CORE_APP_ASSERT(m_body, "obj allocation error!");
        Frtk_GrpWidget::addChild(m_body);
        m_cornerRadius = 0.2f;
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
    void Frtk_Tabwdg::addChild(std::shared_ptr<Frtk_Widget> wdg) {
        if (wdg) {
            m_body->addChild(wdg);
        }
    }

    std::shared_ptr<Frtk_GrpWidget> Frtk_Tabwdg::getChildren()
    {
        return m_body;
    }

    void Frtk_Tabwdg::show()
    {
        m_visible = true;
        show_children();
    }

    void Frtk_Tabwdg::hide()
    {
        m_visible = false;
        hide_children();
    }

    void Frtk_Tabwdg::hide_children()
    {
        m_body->hide();
    }

    void Frtk_Tabwdg::show_children()
    {
        m_body->show();
    }

    bool Frtk_Tabwdg::isTabClicked(dimPos_float_t& mousePos) {
        dimPos_float_t delta = { absX() - m_x, absY() - m_y };
        dimPos_float_t topLeft = { m_headDim.pos.x + delta.x, m_headDim.pos.y + delta.y };
        dimPos_float_t bottomRight = { topLeft.x + m_headDim.size.w, topLeft.y + m_headDim.size.h };
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        return (mousePos.x >= topLeft.x && mousePos.x <= bottomRight.x &&
            mousePos.y >= topLeft.y && mousePos.y <= bottomRight.y);
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
        if (!m_visible)
            return;
        if (m_active) {
            draw_box(m_vg, m_boxType, m_headDim, m_cornerRadius, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_bkg_color), glmToNVG(m_color), true);
            if (m_has_focus) {
                draw_focus();
            }
        }
        else {
            draw_box(m_vg, m_boxType, m_headDim, m_cornerRadius, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        }
        drawLabel();
    }

    void Frtk_Tabwdg::draw_body() {
        if (!m_visible)
            return;
        if (m_active)
            m_body->draw_children();
    }

    int Frtk_Tabwdg::handle(int ev)
    {
        if (!active() || !visible())
            auto children = m_body->getChildren();
        for (size_t i = 0; i < m_children.size(); ++i) {
            auto& wdg = m_children[i];
            if (!wdg->visible() || !wdg->active())
                continue;
            if (wdg->isMouse_inside()) {
                if (send_event(*wdg, ev) == 1)
                    return 1;
            }
        }
        return 0;
    }

    void Frtk_Tabwdg::draw()
    {
        if (!m_visible)
            return
            draw_head();
        draw_body();
    }

    void Frtk_Tabwdg::draw_focus()
    {
        if (m_has_focus)
            draw_box(m_vg, FRTK_THIN_UP_FRAME, m_headDim, m_cornerRadius, FRTK_EXTRA_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(m_bkg_color), true);
    }

    void Frtk_Tabwdg::draw_focus(BOX_TYPE t, float X, float Y, float W, float H)
    {
        if (m_has_focus)
            draw_box(m_vg, t, m_headDim, m_cornerRadius, FRTK_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(m_bkg_color), true);
    }

    void Frtk_Tabwdg::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)
    {
        if (m_has_focus)
            draw_box(m_vg, t, m_headDim, m_cornerRadius, FRTK_THIN_BORDER, nvgRGBAf(FR_LIGHTBLUE), glmToNVG(bkg), true);
    }

    void Frtk_Tabwdg::drawLabel()
    {
        if (!m_visible)
            return;
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
        m_content{ 0.0 }, m_viewOffs(0), m_needLayout(false),
        m_history{ nullptr,nullptr ,nullptr ,nullptr } {
        Frtk_Tabs* tab = this;  // store explicitly
        m_font.fontSize = 12.0f;
        m_font.pos = { m_x,m_y };
        m_font.size = { m_w,m_h };
        m_font.lblAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE;
        m_font.txtAlign = NVG_ALIGN_BOTTOM_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE;
        m_wdgType = FRTK_TABS;
        m_viewPort.pos.x = X + TAB_HPADDING;
        m_viewPort.pos.y = Y + TAB_VPADDING;
        m_viewPort.size.w = W - TAB_BUTTON_SIZE - TAB_HPADDING;
        m_viewPort.size.h = m_h;

        m_scrollwdg.Hor.btnInc = { 0 };
        m_scrollwdg.Hor.btnDec = { 0 };
        m_scrollwdg.Hor.btnColor = glm::vec4(0.f, 0.f, 0.f, 0.1254f);
        m_trackExtra = 1.0f;
        updteTabBTNpos();
        m_content.pos = { 0 , 0 };
        m_bkg_color = glm::vec4(FR_DARK_GRAY);
    }

    bool Frtk_Tabs::shouldClip() {
        return (m_viewPort.size.w < m_content.size.w);
    }
    int Frtk_Tabs::getIndex(std::shared_ptr < Frtk_Tabwdg> wdg) {
        std::shared_ptr<Frtk_Widget> basewdgt = std::static_pointer_cast<Frtk_Widget>(wdg);
        for (size_t i = 0; i < m_children.size(); ++i) {
            if (m_children[i] == basewdgt) {
                return i;
            }
        }
        return -1;
    }

    void Frtk_Tabs::layoutTabs()
    {
        float headerHeight = m_font.fontSize * 1.15f;
        float startX = TAB_BUTTON_SIZE;
        float currentX = startX;

        nvgSave(m_vg);
        nvgFontSize(m_vg, m_font.fontSize);
        nvgFontFace(m_vg, m_font.fName.c_str());

        for (auto& child : m_children)
        {
            auto tab = std::dynamic_pointer_cast<Frtk_Tabwdg>(child);
            if (!tab) continue;

            float bounds[4] = { 0 };
            nvgTextBounds(m_vg, 0, 0, tab->label().c_str(), nullptr, bounds);

            const float minWidth = 45.0f;
            const float maxWidth = m_w;
            float textWidth = bounds[2] - bounds[0];
            float width = std::clamp(textWidth, minWidth, maxWidth - TAB_HPADDING);
            tab->setHeaderDim(currentX, TAB_VPADDING, width, headerHeight);
            tab->getFont().pos.x = currentX;
            tab->getFont().pos.y = headerHeight / 4;
            tab->getFont().size.w = width;
            tab->getFont().size.h = headerHeight;
            tab->setBodyDim(0, TAB_VPADDING * 2 + headerHeight, m_w, m_h - TAB_VPADDING * 2 - headerHeight);
            currentX += width + 1;
            m_content.size.w += tab->m_headDim.size.w;
        }
        nvgRestore(m_vg);
        m_content.size.h = headerHeight;
        updateContentSize();
    }

    void Frtk_Tabs::updateContentSize()
    {
        float maxW = m_w - m_viewPort.size.w;
        for (auto& child : m_children)
        {
            std::shared_ptr<Frtk_Tabwdg> wdg = std::dynamic_pointer_cast<Frtk_Tabwdg>(child);
            if (wdg){
                if(wdg->label()=="Model"){
                float left = wdg->getHeadDim().pos.x + wdg->getHeadDim().size.w;
                if (left > maxW) {
                    maxW = left;
                }
                else {
                    m_history.m_last = wdg;
                }
            }
        }
        }
        if (m_content.size.w <= m_viewPort.size.w)
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
        if (!m_visible)
            return;
        if (m_needLayout) {
            /*
            Call this only when it needs to be updated, for example after adding tab.
            Must be here, since font width cannot be calculated without active context.
            */
            layoutTabs();
        }
        //Background color for the whole TAB widget
        draw_box(m_vg, m_boxType, { {m_x, m_y}, {m_w, m_h} }, m_cornerRadius, FRTK_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        draw_scrollH();

        // Draw all tab children-HEADERS
        nvgSave(m_vg);
        nvgScissor(m_vg, m_viewPort.pos.x + TAB_BUTTON_SIZE, m_viewPort.pos.y, m_viewPort.size.w - TAB_HPADDING - TAB_BUTTON_SIZE, m_viewPort.size.h);
        nvgTranslate(m_vg, m_viewPort.pos.x - m_viewOffs, m_viewPort.pos.y);
        for (size_t i = 0; i < m_children.size(); ++i) {
            std::shared_ptr<Frtk_Tabwdg> wdg = std::dynamic_pointer_cast<Frtk_Tabwdg>(m_children[i]);
            if (wdg)
                wdg->draw_head();
        }

        nvgRestore(m_vg);
        for (size_t i = 0; i < m_children.size(); ++i) {
            std::shared_ptr<Frtk_Tabwdg> wdg = std::dynamic_pointer_cast<Frtk_Tabwdg>(m_children[i]);
            if(wdg)
                wdg->draw();
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
        m_needLayout = true;
        if (!m_history.m_first) {
            m_history.m_first = tmpChild;
            m_history.m_current = tmpChild;
            m_history.m_prev = nullptr;
            m_history.m_last = tmpChild;
            m_history.m_current->focus(true);
            m_history.m_current->activate();
        }
        else
        {
            tmpChild->focus(false);
            tmpChild->disable(); //The tab child normally should be disabled
        }
        addChild(tmpChild);

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

        Dim_float_t dim = { 0.0f };
        int focusedIndex = -1;
        if (ev == FR_LEFT_PUSH) {
            auto& mouse = m_mainWindow->m_sysEvents.mouse;  // reference, not copy
            // Notice that, if all Tab-heads are visible, this will do nothing!!
            // don't think that the buttons are not working
            if (updateBtnPressed()) {
                size_t ind1 = getIndex(m_history.m_first);
                size_t ind2 = getIndex(m_history.m_last);
                if (m_activeBtns.right) {
                    if (ind2 < m_children.size() - 1) {
                        m_history.m_last = std::static_pointer_cast<Frtk_Tabwdg>(m_children[ind2 + 1]);
                        if (m_content.size.w > m_viewPort.size.w) {
                            dim = m_history.m_first->getHeadDim();
                            m_viewOffs += dim.size.w;
                            float maxOffset = m_content.size.w - m_viewPort.size.w;
                            if (m_viewOffs > maxOffset)
                                m_viewOffs = maxOffset;
                            m_history.m_first = std::static_pointer_cast<Frtk_Tabwdg>(m_children[ind1 + 1]);
                        }
                    }
                }
                else if (m_activeBtns.left) {
                    if (ind1 > 0) {
                        if (!m_history.m_last)
                            return 0;
                        dim = m_history.m_last->getHeadDim();
                        m_viewOffs -= dim.size.w;
                        if (m_viewOffs < 0)
                            m_viewOffs = 0;
                        m_history.m_first = std::static_pointer_cast<Frtk_Tabwdg>(m_children[ind1 - 1]);
                        m_history.m_last = std::static_pointer_cast<Frtk_Tabwdg>(m_children[ind2 - 1]);
                    }
                }
                return 1;
            }

            float savedX = mouse.activeX;
            mouse.activeX += m_viewOffs;

            int newIndex = -1;
            for (size_t i = 0; i < m_children.size(); ++i) {
                if (auto* tabwdg = dynamic_cast<Frtk_Tabwdg*>(m_children[i].get())) {
                    if (tabwdg->active())
                        focusedIndex = static_cast<int>(i);

                    dimPos_float_t activeM = { mouse.activeX, mouse.activeY };
                    if (tabwdg->isTabClicked(activeM))
                        newIndex = static_cast<int>(i);
                }
            }
            mouse.activeX = savedX;   // restore before any child forwarding
            if (newIndex != -1 && newIndex != focusedIndex) {
                if (focusedIndex != -1)
                    m_children[focusedIndex]->focus(false);
                activeTab(newIndex);
                return 1;
            }
        }
        else
            if (ev == FR_LEFT_RELEASE) {
                if (updateBtnPressed()) {
                }
            }

        if (label() == "Basic Shapes")
            FR_DEBUG_BREAK;

        return Frtk_GrpWidget::handle(ev);
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
        m_history.m_prev->disable();
        m_history.m_prev->focus(false);
        m_history.m_prev->color(FR_LIGHTGREY);
        m_history.m_current = std::dynamic_pointer_cast<Frtk_Tabwdg>(m_children[ind]);
        m_history.m_current->focus(true);
        m_history.m_current->activate();
        m_history.m_current->color(FR_DARKGREY1);
    }
}