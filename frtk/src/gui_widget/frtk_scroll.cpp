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
        Frtk_GrpWidget(vg, X, Y, W, H, lbl, b), m_viewPort{ X,Y,W,H }, m_content{ X,Y,W,H }
    {
        m_scrollwdg.track = { 0 };
        m_scrollwdg.scroll = { 0 };
        m_scrollwdg.bnUp = { 0 };
        m_scrollwdg.bnDown = { 0 };

        m_scrollwdg.btnColor = glm::vec4(0.f, 0.f, 0.f, 0.1254f);
        m_scrollwdg.trackColor = glm::vec4(0.f, 0.f, 0.f, 0.360f);
        m_scrollwdg.m_scrolloffset = { 0.0f };
        m_scrollwdg.m_dragVscroll = 0.0f;
        m_scrollwdg.m_dragHscroll = 0.0f;
        m_scrollwdg.m_sensitivity = 0.5f;
        m_scrollwdg.m_Vscroll_visible = true;
        m_scrollwdg.m_Hscroll_visible = false;
        updateScrollGeometry();
    }
    void Frtk_Scroll::updateScrollGeometry()
    {
        // --- Fixed sizes ---
        const float scrollbarThickness = 9.0f; // fixed width/height of scrollbar, buttons, thumb
        const float minThumbSize = 4.0f;       // minimum size of the thumb
        const float trackExtra = 5.0f;          // optional: track slightly bigger than thumb for border

        // --- Vertical scrollbar ---
        if (m_scrollwdg.m_Vscroll_visible)
        {
            // Buttons
            m_scrollwdg.bnUp.size.w = scrollbarThickness + trackExtra;
            m_scrollwdg.bnUp.size.h = scrollbarThickness;
            m_scrollwdg.bnUp.pos.x = m_x + m_w - scrollbarThickness - trackExtra / 2;
            m_scrollwdg.bnUp.pos.y = m_y;

            m_scrollwdg.bnDown.size.w = scrollbarThickness + trackExtra;
            m_scrollwdg.bnDown.size.h = scrollbarThickness;
            m_scrollwdg.bnDown.pos.x = m_x + m_w - scrollbarThickness - trackExtra / 2;
            m_scrollwdg.bnDown.pos.y = m_y + m_h - scrollbarThickness;

            // Track (between buttons)
            m_scrollwdg.track.pos.x = m_x + m_w - scrollbarThickness - trackExtra / 2;
            m_scrollwdg.track.pos.y = m_y + scrollbarThickness;
            m_scrollwdg.track.size.w = scrollbarThickness + trackExtra;
            m_scrollwdg.track.size.h = m_h - 2 * scrollbarThickness;

            // Thumb
            float fractionVisible = std::min(1.0f, 0.80f * m_viewPort.size.h / m_content.size.h);
            m_scrollwdg.scroll.size.w = scrollbarThickness;
            m_scrollwdg.scroll.size.h = std::max(minThumbSize, fractionVisible * m_scrollwdg.track.size.h);
            float scrollRatioY = m_scrollwdg.m_scrolloffset.y; // normalized 0..1
            m_scrollwdg.scroll.pos.x = m_scrollwdg.track.pos.x + trackExtra / 2;
            m_scrollwdg.scroll.pos.y = m_scrollwdg.track.pos.y + scrollRatioY * (m_scrollwdg.track.size.h - m_scrollwdg.scroll.size.h);
        }

        // --- Horizontal scrollbar ---
        if (m_scrollwdg.m_Hscroll_visible)
        {
            // Buttons
            m_scrollwdg.bnUp.size.w = scrollbarThickness;
            m_scrollwdg.bnUp.size.h = scrollbarThickness + trackExtra;
            m_scrollwdg.bnUp.pos.x = m_x;
            m_scrollwdg.bnUp.pos.y = m_y + m_h - scrollbarThickness - trackExtra / 2;

            m_scrollwdg.bnDown.size.w = scrollbarThickness;
            m_scrollwdg.bnDown.size.h = scrollbarThickness;
            m_scrollwdg.bnDown.pos.x = m_x + m_w - scrollbarThickness;
            m_scrollwdg.bnDown.pos.y = m_y + m_h - scrollbarThickness;

            // Track (between buttons)
            m_scrollwdg.track.pos.x = m_x + scrollbarThickness; // optional: leave space for left button
            m_scrollwdg.track.pos.y = m_y + m_h - scrollbarThickness;
            m_scrollwdg.track.size.w = m_w - 2 * scrollbarThickness;
            m_scrollwdg.track.size.h = scrollbarThickness + trackExtra;

            // Thumb
            float fractionVisible = std::min(1.0f, m_viewPort.size.w / m_content.size.w);
            m_scrollwdg.scroll.size.h = scrollbarThickness;
            m_scrollwdg.scroll.size.w = std::max(minThumbSize, fractionVisible * m_scrollwdg.track.size.w);
            float scrollRatioX = m_scrollwdg.m_scrolloffset.x;
            m_scrollwdg.scroll.pos.x = m_scrollwdg.track.pos.x + scrollRatioX * (m_scrollwdg.track.size.w - m_scrollwdg.scroll.size.w);
            m_scrollwdg.scroll.pos.y = m_scrollwdg.track.pos.y;
        }
    }
    void Frtk_Scroll::draw()
    {
        draw_scroll();
    }
    void Frtk_Scroll::draw_scroll()
    {
        NVGpaint shadowPaint, fadePaint;

        // --- Up button ---
        fadePaint = nvgLinearGradient(m_vg, m_scrollwdg.bnUp.pos.x, m_scrollwdg.bnUp.pos.y, m_scrollwdg.bnUp.pos.x, m_scrollwdg.bnUp.pos.y + m_scrollwdg.bnUp.size.h, nvgRGBAf(0.85f, 0.85f, 0.85f, 1.0f), nvgRGBAf(0.65f, 0.65f, 0.65f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_scrollwdg.bnUp.pos.x, m_scrollwdg.bnUp.pos.y, m_scrollwdg.bnUp.size.w, m_scrollwdg.bnUp.size.h, 2.0f);
        nvgFillPaint(m_vg, fadePaint);
        nvgFill(m_vg);

        // Up arrow
        nvgBeginPath(m_vg);
        float midX = m_scrollwdg.bnUp.pos.x + m_scrollwdg.bnUp.size.w * 0.5f;
        float midY = m_scrollwdg.bnUp.pos.y + m_scrollwdg.bnUp.size.h * 0.5f;
        float triSize = 4.0f;
        nvgMoveTo(m_vg, midX, midY - triSize);
        nvgLineTo(m_vg, midX - triSize, midY + triSize);
        nvgLineTo(m_vg, midX + triSize, midY + triSize);
        nvgClosePath(m_vg);
        nvgFillColor(m_vg, nvgRGBAf(FR_BEIGE));
        nvgFill(m_vg);

        float X_, Y_, W_, H_;
        X_ = m_scrollwdg.bnDown.pos.x;
        Y_ = m_scrollwdg.bnDown.pos.y;
        W_ = m_scrollwdg.bnDown.size.w;
        H_ = m_scrollwdg.bnDown.size.h;

        // --- Down button ---
        fadePaint = nvgLinearGradient(m_vg, X_, Y_, X_, Y_ + H_, nvgRGBAf(0.85f, 0.85f, 0.85f, 1.0f), nvgRGBAf(0.65f, 0.65f, 0.65f, 1.0f));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X_, Y_, W_, H_, 2.0f);
        nvgFillPaint(m_vg, fadePaint);
        nvgFill(m_vg);

        // Down arrow
        nvgBeginPath(m_vg);
        midX = m_scrollwdg.bnDown.pos.x + m_scrollwdg.bnDown.size.w * 0.5f;
        midY = m_scrollwdg.bnDown.pos.y + m_scrollwdg.bnDown.size.h * 0.5f;
        nvgMoveTo(m_vg, midX, midY + triSize);
        nvgLineTo(m_vg, midX - triSize, midY - triSize);
        nvgLineTo(m_vg, midX + triSize, midY - triSize);
        nvgClosePath(m_vg);
        nvgFillColor(m_vg, nvgRGBAf(FR_BEIGE));
        nvgFill(m_vg);

        // --- Track ---
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_scrollwdg.track.pos.x, m_scrollwdg.track.pos.y,
            m_scrollwdg.track.size.w, m_scrollwdg.track.size.h, 2.0f);
        nvgFillColor(m_vg, glmToNVG(m_scrollwdg.trackColor));
        nvgFill(m_vg);

        if (m_scrollwdg.m_Vscroll_visible)
        {
            float X_, Y_, W_, H_;
            X_ = m_scrollwdg.scroll.pos.x + m_scrollwdg.m_scrolloffset.x;
            Y_ = m_scrollwdg.scroll.pos.y + m_scrollwdg.m_scrolloffset.y;
            W_ = m_scrollwdg.scroll.size.w;
            H_ = m_scrollwdg.scroll.size.h;
            shadowPaint = nvgBoxGradient(m_vg, X_, Y_, W_, H_, 3, 4, nvgRGBAf(FR_GAINSBORO), nvgRGBAf(FR_GRAY));
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, X_, Y_, W_, H_, 3.0f);
            nvgFillPaint(m_vg, shadowPaint);
            nvgFill(m_vg);
        }

        if (m_scrollwdg.m_Hscroll_visible)
        {
            shadowPaint = nvgBoxGradient(m_vg, X_, Y_, W_, H_, 3, 4, nvgRGBAf(FR_GAINSBORO), nvgRGBAf(FR_GRAY));
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, X_, Y_, W_, H_, 3.0f);
            nvgFillPaint(m_vg, shadowPaint);
            nvgFill(m_vg);
        }
    }

    dimSize_float_t Frtk_Scroll::getTotalViewPortDim() const {
        dimSize_float_t result;
        result.w = m_w;
        result.h = m_h;
        if (m_scrollwdg.m_Vscroll_visible)
            result.w -= m_scrollwdg.scroll.size.w;
        if (m_scrollwdg.m_Hscroll_visible)
            result.h -= m_scrollwdg.scroll.size.h;
        result.w = std::max(0.f, result.w);
        result.h = std::max(0.f, result.h);
        return result;
    }
    bool Frtk_Scroll::isBtnPressed(uint8_t btnInd) {
        bool result;
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        Dim_float_t btnAbsUpPos , btnAbsDownPos;
        btnAbsUpPos.pos.x = absX() + (m_x - m_scrollwdg.bnUp.pos.x);
        btnAbsUpPos.pos.y = absY() + (m_y - m_scrollwdg.bnUp.pos.y);
        
        btnAbsDownPos.pos.x = absX() + (m_x - m_scrollwdg.bnUp.pos.x);
        btnAbsDownPos.pos.y = absY() + (m_y - m_scrollwdg.bnUp.pos.y);

        switch (btnInd) {
        case 0: {
            if (m_scrollwdg.m_Vscroll_visible) {
                if (mouse.activeX >= btnAbsUpPos.pos.x &&
                    mouse.activeY >= btnAbsUpPos.pos.y &&
                    mouse.activeX <= btnAbsUpPos.pos.x + m_scrollwdg.bnUp.size.w &&
                    mouse.activeY <= btnAbsUpPos.pos.y + m_scrollwdg.bnUp.size.h) {
                    result = true;
                }
            }
        }break;
        case 1: {
            if (m_scrollwdg.m_Vscroll_visible) {
                if (mouse.activeX >= btnAbsDownPos.pos.x &&
                    mouse.activeY >= btnAbsDownPos.pos.y &&
                    mouse.activeX <= btnAbsDownPos.pos.x + m_scrollwdg.bnDown.size.w &&
                    mouse.activeY <= btnAbsDownPos.pos.y + m_scrollwdg.bnDown.size.h) {
                    result = true;
                }
            }
        }break;

        }
       }

    }
    int Frtk_Scroll::handle(int ev) {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        float delta = (mouse.prevY - mouse.activeY) * m_scrollwdg.m_sensitivity;
        if (isMouse_inside() || m_scrollwdg.m_dragVscroll || m_scrollwdg.m_dragHscroll) {
            if (m_scrollwdg.m_Vscroll_visible) {
                if (ev == FR_LEFT_PUSH) {
                    
                }
                if (ev == FR_LEFT_DRAG_PUSH || (ev == FR_LEFT_DRAG_MOVE && m_scrollwdg.m_dragVscroll)) {
                    m_scrollwdg.m_dragVscroll = true;
                    m_scrollwdg.m_scrolloffset.y = std::clamp(m_scrollwdg.m_scrolloffset.y -= delta, 0.f, m_h - m_scrollwdg.scroll.size.h);
                }
                else if (ev == FR_LEFT_DRAG_RELEASE) {
                    m_scrollwdg.m_dragVscroll = false;
                }
            }
            else if (m_scrollwdg.m_Hscroll_visible) {
                if (ev == FR_LEFT_DRAG_PUSH || (ev == FR_LEFT_DRAG_MOVE && m_scrollwdg.m_dragHscroll)) {
                    m_scrollwdg.m_dragHscroll = true;
                    m_scrollwdg.m_scrolloffset.x = std::clamp(m_scrollwdg.m_scrolloffset.x -= delta, 0.f, m_w - m_scrollwdg.scroll.size.w);
                }
                else if (ev == FR_LEFT_DRAG_RELEASE) {
                    m_scrollwdg.m_dragVscroll = false;
                }
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