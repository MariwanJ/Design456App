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

#include <gui_widget/frtk_scroll.h>
#include <gui_widget/frtk_draw.h>
#include <nanovg.h>

namespace FR {
    Frtk_Scroll::Frtk_Scroll(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_GrpWidget(vg, X, Y, W, H, lbl, FRTK_FLAT_BOX),
        m_viewPort{ X,Y,W,H }, m_content{ X,Y,W,H }
    {
        m_scrollwdg.Ver.track = { 0 };
        m_scrollwdg.Ver.scroll = { 0 };
        m_scrollwdg.Ver.btnInc = { 0 };
        m_scrollwdg.Ver.btnDec = { 0 };
        m_scrollwdg.Ver.btnColor = glm::vec4(0.f, 0.f, 0.f, 0.1254f);
        m_scrollwdg.Ver.trackColor = glm::vec4(0.f, 0.f, 0.f, 0.360f);
        m_scrollwdg.Ver.scrollOffs = { 0.0f };
        m_scrollwdg.sensitivity = 0.5f;
        m_scrollwdg.Hor.visible = true;
        m_scrollwdg.Hor.track = { 0 };
        m_scrollwdg.Hor.scroll = { 0 };
        m_scrollwdg.Hor.btnInc = { 0 };
        m_scrollwdg.Hor.btnDec = { 0 };
        m_scrollwdg.Hor.btnColor = glm::vec4(0.f, 0.f, 0.f, 0.1254f);
        m_scrollwdg.Hor.trackColor = glm::vec4(0.f, 0.f, 0.f, 0.360f);
        m_scrollwdg.Hor.scrollOffs = { 0.0f };
        m_scrollwdg.sensitivity = 0.5f;
        m_scrollwdg.Ver.visible = true;
        scrollbarThickness = 9.0f;
        minThumbSize = 4.0f;
        trackExtra = 5.0f;
        squarePadding = scrollbarThickness + trackExtra;
        updateScrollGeometry();
    }
    void Frtk_Scroll::updateScrollGeometry()
    {
        if (m_scrollwdg.Ver.visible) {
            // V scrollbar
            // Buttons
            m_scrollwdg.Ver.btnInc.size.w = scrollbarThickness + trackExtra;
            m_scrollwdg.Ver.btnInc.size.h = scrollbarThickness;
            m_scrollwdg.Ver.btnInc.pos.x = m_x + m_w - scrollbarThickness - trackExtra / 2;
            m_scrollwdg.Ver.btnInc.pos.y = m_y + squarePadding;

            m_scrollwdg.Ver.btnDec.size.w = scrollbarThickness + trackExtra;
            m_scrollwdg.Ver.btnDec.size.h = scrollbarThickness;
            m_scrollwdg.Ver.btnDec.pos.x = m_x + m_w - scrollbarThickness - trackExtra / 2;
            m_scrollwdg.Ver.btnDec.pos.y = m_y + m_h - scrollbarThickness - squarePadding;

            //scroll bar - bkg
            m_scrollwdg.Ver.track.pos.x = m_x + m_w - scrollbarThickness - trackExtra / 2;
            m_scrollwdg.Ver.track.pos.y = m_y + scrollbarThickness + squarePadding;
            m_scrollwdg.Ver.track.size.w = scrollbarThickness + trackExtra;
            m_scrollwdg.Ver.track.size.h = m_h - 2 * scrollbarThickness - squarePadding * 2;

            // scroll-middle-button
            float fractionVisible = std::min(1.0f, 0.80f * m_viewPort.size.h / m_content.size.h);
            m_scrollwdg.Ver.scroll.size.w = scrollbarThickness;
            m_scrollwdg.Ver.scroll.size.h = std::max(minThumbSize, fractionVisible * m_scrollwdg.Ver.track.size.h);
            float scrollRatioY = m_scrollwdg.Ver.scrollOffs.y;
            m_scrollwdg.Ver.scroll.pos.x = m_scrollwdg.Ver.track.pos.x + trackExtra / 2;
            m_scrollwdg.Ver.scroll.pos.y = m_scrollwdg.Ver.track.pos.y + scrollRatioY * (m_scrollwdg.Ver.track.size.h - m_scrollwdg.Ver.scroll.size.h);
        }

        // H scrollbar
        if (m_scrollwdg.Hor.visible)
        {
            // Buttons
            m_scrollwdg.Hor.btnDec.size.w = scrollbarThickness;
            m_scrollwdg.Hor.btnDec.size.h = scrollbarThickness + trackExtra;
            m_scrollwdg.Hor.btnDec.pos.x = m_x + squarePadding;
            m_scrollwdg.Hor.btnDec.pos.y = m_y + m_h - scrollbarThickness;

            m_scrollwdg.Hor.btnInc.size.w = scrollbarThickness;
            m_scrollwdg.Hor.btnInc.size.h = scrollbarThickness + trackExtra;
            m_scrollwdg.Hor.btnInc.pos.x = m_x + m_w - scrollbarThickness - squarePadding;
            m_scrollwdg.Hor.btnInc.pos.y = m_y + m_h - scrollbarThickness;

            //track
            m_scrollwdg.Hor.track.pos.x = m_x + scrollbarThickness + squarePadding;
            m_scrollwdg.Hor.track.pos.y = m_y + m_h - scrollbarThickness;
            m_scrollwdg.Hor.track.size.w = m_w - 2 * scrollbarThickness - 2 * squarePadding;
            m_scrollwdg.Hor.track.size.h = scrollbarThickness + trackExtra;

            // middle-button
            float fractionVisible = std::min(1.0f, 0.8f * m_viewPort.size.w / m_content.size.w);
            m_scrollwdg.Hor.scroll.size.h = scrollbarThickness;
            m_scrollwdg.Hor.scroll.size.w = std::max(minThumbSize, fractionVisible * m_scrollwdg.Hor.track.size.w);
            float scrollRatioX = m_scrollwdg.Hor.scrollOffs.x;
            m_scrollwdg.Hor.scroll.pos.x = m_scrollwdg.Hor.track.pos.x + scrollRatioX * (m_scrollwdg.Hor.track.size.w - m_scrollwdg.Hor.scroll.size.w);
            m_scrollwdg.Hor.scroll.pos.y = m_scrollwdg.Hor.track.pos.y + trackExtra / 2;
        }
    }

    void Frtk_Scroll::draw()
    {
        draw_scrollV();
        draw_scrollH();
    }
    void Frtk_Scroll::draw_scrollH()
    {
        NVGpaint shadowPaint, fadePaint;

        // Up btn
        fadePaint = nvgLinearGradient(m_vg, m_scrollwdg.Hor.btnInc.pos.x,
            m_scrollwdg.Hor.btnInc.pos.y,
            m_scrollwdg.Hor.btnInc.size.w,
            m_scrollwdg.Hor.btnInc.size.h,
            nvgRGBAf(0.85f, 0.85f, 0.85f, 1.0f), nvgRGBAf(0.65f, 0.65f, 0.65f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_scrollwdg.Hor.btnInc.pos.x,
            m_scrollwdg.Hor.btnInc.pos.y,
            m_scrollwdg.Hor.btnInc.size.w,
            m_scrollwdg.Hor.btnInc.size.h, 2.0f);
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
        nvgFillColor(m_vg, nvgRGBAf(FR_BEIGE));
        nvgFill(m_vg);

        float X_, Y_, W_, H_;
        X_ = m_scrollwdg.Hor.btnDec.pos.x;
        Y_ = m_scrollwdg.Hor.btnDec.pos.y;
        W_ = m_scrollwdg.Hor.btnDec.size.w;
        H_ = m_scrollwdg.Hor.btnDec.size.h;

        // Down button
        fadePaint = nvgLinearGradient(m_vg, X_, Y_, X_, Y_ + H_, nvgRGBAf(0.85f, 0.85f, 0.85f, 1.0f), nvgRGBAf(0.65f, 0.65f, 0.65f, 1.0f));
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
        nvgFillColor(m_vg, nvgRGBAf(FR_BEIGE));
        nvgFill(m_vg);

        // Track
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_scrollwdg.Hor.track.pos.x, m_scrollwdg.Hor.track.pos.y,
            m_scrollwdg.Hor.track.size.w, m_scrollwdg.Hor.track.size.h, 2.0f);
        nvgFillColor(m_vg, glmToNVG(m_scrollwdg.Hor.trackColor));
        nvgFill(m_vg);

        X_ = m_scrollwdg.Hor.scroll.pos.x + m_scrollwdg.Hor.scrollOffs.x;
        Y_ = m_scrollwdg.Hor.scroll.pos.y + m_scrollwdg.Hor.scrollOffs.y;
        W_ = m_scrollwdg.Hor.scroll.size.w;
        H_ = m_scrollwdg.Hor.scroll.size.h;
        shadowPaint = nvgBoxGradient(m_vg, X_, Y_, W_, H_, 3, 4, nvgRGBAf(FR_GAINSBORO), nvgRGBAf(FR_GRAY));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X_, Y_, W_, H_, 3.0f);
        nvgFillPaint(m_vg, shadowPaint);
        nvgFill(m_vg);
    }
    void Frtk_Scroll::draw_scrollV()
    {
        NVGpaint shadowPaint, fadePaint;

        // Up btn
        fadePaint = nvgLinearGradient(m_vg, m_scrollwdg.Ver.btnInc.pos.x, m_scrollwdg.Ver.btnInc.pos.y, m_scrollwdg.Ver.btnInc.pos.x, m_scrollwdg.Ver.btnInc.pos.y + m_scrollwdg.Ver.btnInc.size.h, nvgRGBAf(0.85f, 0.85f, 0.85f, 1.0f), nvgRGBAf(0.65f, 0.65f, 0.65f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_scrollwdg.Ver.btnInc.pos.x, m_scrollwdg.Ver.btnInc.pos.y, m_scrollwdg.Ver.btnInc.size.w, m_scrollwdg.Ver.btnInc.size.h, 2.0f);
        nvgFillPaint(m_vg, fadePaint);
        nvgFill(m_vg);

        // Up arrow
        nvgBeginPath(m_vg);
        float midX = m_scrollwdg.Ver.btnInc.pos.x + m_scrollwdg.Ver.btnInc.size.w * 0.5f;
        float midY = m_scrollwdg.Ver.btnInc.pos.y + m_scrollwdg.Ver.btnInc.size.h * 0.5f;
        float triSize = 4.0f;
        nvgMoveTo(m_vg, midX, midY - triSize);
        nvgLineTo(m_vg, midX - triSize, midY + triSize);
        nvgLineTo(m_vg, midX + triSize, midY + triSize);
        nvgClosePath(m_vg);
        nvgFillColor(m_vg, nvgRGBAf(FR_BEIGE));
        nvgFill(m_vg);

        float X_, Y_, W_, H_;
        X_ = m_scrollwdg.Ver.btnDec.pos.x;
        Y_ = m_scrollwdg.Ver.btnDec.pos.y;
        W_ = m_scrollwdg.Ver.btnDec.size.w;
        H_ = m_scrollwdg.Ver.btnDec.size.h;

        // Down button
        fadePaint = nvgLinearGradient(m_vg, X_, Y_, X_, Y_ + H_, nvgRGBAf(0.85f, 0.85f, 0.85f, 1.0f), nvgRGBAf(0.65f, 0.65f, 0.65f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X_, Y_, W_, H_, 2.0f);
        nvgFillPaint(m_vg, fadePaint);
        nvgFill(m_vg);

        // Down arrow
        nvgBeginPath(m_vg);
        midX = m_scrollwdg.Ver.btnDec.pos.x + m_scrollwdg.Ver.btnDec.size.w * 0.5f;
        midY = m_scrollwdg.Ver.btnDec.pos.y + m_scrollwdg.Ver.btnDec.size.h * 0.5f;
        nvgMoveTo(m_vg, midX, midY + triSize);
        nvgLineTo(m_vg, midX - triSize, midY - triSize);
        nvgLineTo(m_vg, midX + triSize, midY - triSize);
        nvgClosePath(m_vg);
        nvgFillColor(m_vg, nvgRGBAf(FR_BEIGE));
        nvgFill(m_vg);

        // Track
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_scrollwdg.Ver.track.pos.x, m_scrollwdg.Ver.track.pos.y,
            m_scrollwdg.Ver.track.size.w, m_scrollwdg.Ver.track.size.h, 2.0f);
        nvgFillColor(m_vg, glmToNVG(m_scrollwdg.Ver.trackColor));
        nvgFill(m_vg);

        X_ = m_scrollwdg.Ver.scroll.pos.x + m_scrollwdg.Ver.scrollOffs.x;
        Y_ = m_scrollwdg.Ver.scroll.pos.y + m_scrollwdg.Ver.scrollOffs.y;
        W_ = m_scrollwdg.Ver.scroll.size.w;
        H_ = m_scrollwdg.Ver.scroll.size.h;
        shadowPaint = nvgBoxGradient(m_vg, X_, Y_, W_, H_, 3, 4, nvgRGBAf(FR_GAINSBORO), nvgRGBAf(FR_GRAY));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X_, Y_, W_, H_, 3.0f);
        nvgFillPaint(m_vg, shadowPaint);
        nvgFill(m_vg);
    }

    dimSize_float_t Frtk_Scroll::getTotalViewPortDim() const {
        dimSize_float_t result;
        result.w = m_w;
        result.h = m_h;
        if (m_scrollwdg.Ver.visible)
            result.w -= m_scrollwdg.Ver.scroll.size.w;
        if (m_scrollwdg.Hor.visible)
            result.h -= m_scrollwdg.Hor.scroll.size.h;
        result.w = std::max(0.f, result.w);
        result.h = std::max(0.f, result.h);
        return result;
    }

    int Frtk_Scroll::updateBtnPressed()
    {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse;

        // reset state each frame
        m_activeBtns = {};

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

        if (m_scrollwdg.Ver.visible)
        {
            if (hit(m_scrollwdg.Ver.btnInc))   m_activeBtns.up = true;
            if (hit(m_scrollwdg.Ver.btnDec)) m_activeBtns.down = true;
        }

        if (m_scrollwdg.Hor.visible)
        {
            if (hit(m_scrollwdg.Hor.btnInc))   m_activeBtns.right = true;
            if (hit(m_scrollwdg.Hor.btnDec)) m_activeBtns.left = true;
        }
        if (m_activeBtns.up || m_activeBtns.down || m_activeBtns.left || m_activeBtns.right)
            return 1;
        return 0;
    }

    int Frtk_Scroll::handle(int ev)
    {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse;
        if (!(isMouse_inside() || m_scrollwdg.Ver.dragging || m_scrollwdg.Hor.dragging))
            return 0;

        if (ev == FR_LEFT_PUSH || ev == FR_LEFT_DRAG_RELEASE ||
            ev == FR_LEFT_DRAG_PUSH || ev == FR_LEFT_DRAG_MOVE) {
            if (updateBtnPressed()) {
                //TODO FIX ME WE SHOULD HAVE DIFF CALLBACKS
                do_callback();
                return 1;
            }

            if (m_activeBtns.up)    m_scrollwdg.Ver.scrollOffs.y -= 10.f;
            if (m_activeBtns.down)  m_scrollwdg.Ver.scrollOffs.y += 10.f;
            if (m_activeBtns.left)  m_scrollwdg.Hor.scrollOffs.x -= 10.f;
            if (m_activeBtns.right) m_scrollwdg.Hor.scrollOffs.x += 10.f;

            if (m_scrollwdg.Ver.visible)
            {
                float offx = absX() + -m_x + m_scrollwdg.Ver.scroll.pos.x;
                float offy = absY() + -m_y + m_scrollwdg.Ver.scroll.pos.y;
                bool testBound = (mouse.activeX >= offx &&
                    mouse.activeX <= offx + m_scrollwdg.Ver.scroll.size.w &&
                    mouse.activeY >= offy &&
                    mouse.activeY <= offy + m_scrollwdg.Ver.scroll.size.h);
                if (testBound || ev == FR_LEFT_DRAG_MOVE && m_scrollwdg.Ver.dragging)
                {
                    float deltaY = (mouse.prevY - mouse.activeY) * m_scrollwdg.sensitivity;
                    if (ev == FR_LEFT_DRAG_PUSH) {
                        m_scrollwdg.Ver.dragging = true;
                    }
                    else
                        if (ev == FR_LEFT_DRAG_MOVE && m_scrollwdg.Ver.dragging)
                        {
                            float newPos = m_scrollwdg.Ver.scrollOffs.y - deltaY;
                            m_scrollwdg.Ver.scrollOffs.y = std::clamp(newPos, 0.f, m_h - m_scrollwdg.Ver.scroll.size.h - squarePadding - 4 * m_scrollwdg.Ver.btnInc.size.h);
                        }
                    return 1;
                }
                 else if (ev == FR_LEFT_DRAG_RELEASE)
                 {
                    m_scrollwdg.Ver.dragging = false;
                    return 1;
                  }
                }
            }
            if (m_scrollwdg.Hor.visible)
            {
                float offx = absX() + -m_x + m_scrollwdg.Hor.scroll.pos.x;
                float offy = absY() + -m_y + m_scrollwdg.Hor.scroll.pos.y;
                bool testBound = (mouse.activeX >= offx &&
                    mouse.activeX <= offx + m_scrollwdg.Hor.scroll.size.w &&
                    mouse.activeY >= offy &&
                    mouse.activeY <= offy + m_scrollwdg.Hor.scroll.size.h);
                if (testBound || ev == FR_LEFT_DRAG_MOVE && m_scrollwdg.Hor.dragging) {
                    float deltaX = (mouse.prevX - mouse.activeX) * m_scrollwdg.sensitivity;

                    if (ev == FR_LEFT_DRAG_PUSH) {
                        m_scrollwdg.Hor.dragging = true;
                    }
                    else
                        if (ev == FR_LEFT_DRAG_MOVE && m_scrollwdg.Hor.dragging)
                        {
                            m_scrollwdg.Hor.dragging = true;
                            float newPos = m_scrollwdg.Hor.scrollOffs.x - deltaX;
                            m_scrollwdg.Hor.scrollOffs.x = std::clamp(newPos, 0.f, m_w - m_scrollwdg.Hor.scroll.size.w- squarePadding - 4 * m_scrollwdg.Hor.btnInc.size.w);
                        }
                    return 1;
                }
                 else if (ev == FR_LEFT_DRAG_RELEASE)
                 {
                 m_scrollwdg.Hor.dragging = false;
                 return 1;
                 }
                
                }
            return 0;
        }
    
}

//nvgSave(ctx);
//
//// Clip to the viewport
//nvgScissor(ctx, viewportX, viewportY, viewportWidth, viewportHeight);
//
//// Translate by scroll offsets
//nvgTranslate(ctx, -mScrollX, -mScrollY);
//
//// Draw all children (as if nothing changed)
//for (auto child : children())
//child->draw(ctx);
//
//nvgRestore(ctx);