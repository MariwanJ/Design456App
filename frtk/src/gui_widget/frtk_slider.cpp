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
#include <gui_widget/frtk_slider.h>

namespace FR {
    Frtk_Slider::Frtk_Slider(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_Box(vg, X, Y, W, H, lbl, b), m_range{ 0.0f,100.f },
        m_highlight{ 0.0f,0.0f }, m_value(0), m_sliderType(H_SLIDER), m_speedFactor(0.75f)
    {
        m_nobColor.nob = glm::vec4(FR_DARKGREY1);
        m_nobColor.inner = glm::vec4(FR_BEIGE);
        m_nobColor.shadow = glm::vec4(FR_DARK_SHADOW);
        m_nobColor.track = glm::vec4(FR_DARKSLATEGREY);
        m_cornerRadius = 3.0f;
        m_dragging = false;
        m_font.lblAlign = NVG_ALIGN_BOTTOM_CENTER;
    }

    Frtk_Slider::~Frtk_Slider()
    {
    }

    void Frtk_Slider::vlaue(const float& v)
    {
        m_value = std::clamp(v, m_range.min, m_range.max);
    }

    void Frtk_Slider::setRange(const range_t range)
    {
        m_range = range;
    }

    range_t Frtk_Slider::Range() const
    {
        return m_range;
    }

    bool Frtk_Slider::isMouseInsideSliderBar()
    {
        auto& mouse = m_mainWindow->m_sysEvents.mouse;
        bool testBound;
        float X = absX();
        float Y = absY();
        if (m_sliderType == H_SLIDER) {
            testBound = (
                mouse.activeX >= X &&
                mouse.activeX <= X + m_w &&
                mouse.activeY >= Y + m_h * 0.5f - m_h * 0.2f &&
                mouse.activeY <= Y + m_h * 0.5f + m_h * 0.2f
                );
        }
        else {
            testBound = (
                mouse.activeX >= X + m_w * 0.5f - m_w * 0.2f &&
                mouse.activeX <= X + m_w * 0.5f + m_w * 0.2f &&
                mouse.activeY >= Y &&
                mouse.activeY <= Y + m_h
                );
        }
        return testBound;
    }

    void Frtk_Slider::sliderType(const slidertype_t& t)
    {
        m_sliderType = t;
    }

    int Frtk_Slider::handle(int ev)
    {
        auto& mouse = m_mainWindow->m_sysEvents.mouse;
        bool testBound = isMouseInsideSliderBar();
        if (testBound || (ev == FR_LEFT_DRAG_MOVE && m_dragging)) {
            if (ev == FR_LEFT_DRAG_PUSH && testBound) {
                m_dragging = true;
                return 1;
            }
            else if (ev == FR_LEFT_DRAG_MOVE && m_dragging) {
                if (m_sliderType == H_SLIDER) {
                    float deltaX = mouse.activeX - mouse.prevX;
                    float kr = (int)(m_h * 0.4f);
                    float kshadow = 3;
                    float trackW = m_w - 2.0f * (kr + kshadow);
                    m_value += (deltaX / trackW) * (m_range.max - m_range.min) * m_speedFactor;
                }
                else {
                    float deltaY = mouse.prevY - mouse.activeY; // inverted: up = more
                    float kr = (int)(m_w * 0.4f);
                    float kshadow = 3;
                    float trackH = m_h - 2.0f * (kr + kshadow);
                    m_value += (deltaY / trackH) * (m_range.max - m_range.min) * m_speedFactor;
                }
                m_value = std::clamp(m_value, m_range.min, m_range.max);
                return 1;
            }
            else if ((ev == FR_LEFT_DRAG_RELEASE || ev == FR_LEAVE) && m_dragging) {
                m_dragging = false;
                do_callback();
                return 1;
            }
        }
        return 0;
    }

    void Frtk_Slider::draw()
    {
        draw_box(m_vg, m_boxType, { {m_x,m_y},{m_w,m_h} }, m_cornerRadius, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_nobColor.shadow), false);
        if (m_sliderType==H_SLIDER){
        float cx = m_x + m_w;
        float cy = m_y + m_h * 0.50f;
        float kr = (int)(m_h * 0.20f);
        float kshadow = 3;
        float startX = m_x + kr + kshadow;
        float widthX = m_w - 2.0f * (kr + kshadow);

        float knobX = startX + (m_value - m_range.min) / (m_range.max - m_range.min) * widthX;
        float knobY = cy + 0.5f;

        //  Track 
        NVGcolor track1 = glmToNVG(m_nobColor.track);;
        NVGcolor track2 = track1;
        if (m_active) {
            track1.a = 0.125f;
            track2.a = 0.5f;
        }
        else {
            track1.a = 0.039f;
            track2.a = 0.8203f;
        }
        NVGpaint bg = nvgBoxGradient(m_vg, startX, cy - 3 + 1, widthX, 6, 3, 3, track1, track2);
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, startX, cy - 3 + 1, widthX, 6, 2);
        nvgFillPaint(m_vg, bg);
        nvgFill(m_vg);

        // Highlight range
        if (m_highlight.max != m_highlight.min)
        {
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, startX + m_highlight.min * m_w, cy - kshadow + 1, widthX * (m_highlight.max - m_highlight.min), kshadow * 2, 2);
            nvgFillColor(m_vg, glmToNVG(m_color));
            nvgFill(m_vg);
        }

        NVGpaint knobShadow = nvgRadialGradient(m_vg, knobX, knobY, kr - kshadow, kr + kshadow, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f), nvgRGBAf(FR_BLACK));
        NVGpaint knob = nvgLinearGradient(m_vg, m_x, cy - kr, m_x, cy + kr, glmToNVG(m_nobColor.nob), glmToNVG(m_nobColor.shadow));
        NVGpaint knobReverse = nvgLinearGradient(m_vg, m_x, cy - kr, m_x, cy + kr, glmToNVG(m_color), glmToNVG(m_nobColor.shadow));

        nvgBeginPath(m_vg);
        nvgCircle(m_vg, knobX, knobY, kr);
        nvgStrokeColor(m_vg, glmToNVG(m_bkg_color));
        nvgFillPaint(m_vg, knob);
        nvgStroke(m_vg);
        nvgFill(m_vg);

        // Knob inner
        nvgBeginPath(m_vg);
        nvgCircle(m_vg, knobX, knobY, kr / 2.0f);
        nvgFillColor(m_vg, glmToNVG(m_nobColor.inner));
        nvgStrokePaint(m_vg, knobReverse);
        nvgStroke(m_vg);
        nvgFill(m_vg);
        }
        else // V_SLIDER
        {
            float cx = m_x + m_w * 0.5f;
            float cy = m_y;                          // top of widget
            float kr = (int)(m_w * 0.20f);
            float kshadow = 3;
            float startY = m_y + kr + kshadow;
            float heightY = m_h - 2.0f * (kr + kshadow);

            // knob travels top - bottom, but value increases upward 
            float knobY = startY + (1.0f - (m_value - m_range.min) / (m_range.max - m_range.min)) * heightY;
            float knobX = cx + 0.5f;

            // Track
            NVGcolor track1 = glmToNVG(m_nobColor.track);
            NVGcolor track2 = track1;
            if (m_active) {
                track1.a = 0.125f;
                track2.a = 0.5f;
            }
            else {
                track1.a = 0.039f;
                track2.a = 0.8203f;
            }

            NVGpaint bg = nvgBoxGradient(m_vg,
                cx - 3 + 1, startY, 6, heightY, 3, 3,
                track1, track2);
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, cx - 3 + 1, startY, 6, heightY, 2);
            nvgFillPaint(m_vg, bg);
            nvgFill(m_vg);

            // Highlight range
            if (m_highlight.max != m_highlight.min)
            {
                nvgBeginPath(m_vg);
                nvgRoundedRect(m_vg,
                    cx - kshadow + 1,
                    startY + m_highlight.min * m_h,
                    kshadow * 2,
                    heightY * (m_highlight.max - m_highlight.min),
                    2);
                nvgFillColor(m_vg, glmToNVG(m_color));
                nvgFill(m_vg);
            }

            // Knob shadow
            NVGpaint knobShadow = nvgRadialGradient(m_vg,
                knobX, knobY, kr - kshadow, kr + kshadow,
                nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f),
                nvgRGBAf(FR_BLACK));

            // Knob gradients 
            NVGpaint knob = nvgLinearGradient(m_vg,
                cx - kr, m_y,
                cx + kr, m_y,
                glmToNVG(m_nobColor.nob),
                glmToNVG(m_nobColor.shadow));

            NVGpaint knobReverse = nvgLinearGradient(m_vg,
                cx - kr, m_y,
                cx + kr, m_y,
                glmToNVG(m_color),
                glmToNVG(m_nobColor.shadow));

            nvgBeginPath(m_vg);
            nvgCircle(m_vg, knobX, knobY, kr);
            nvgStrokeColor(m_vg, glmToNVG(m_bkg_color));
            nvgFillPaint(m_vg, knob);
            nvgStroke(m_vg);
            nvgFill(m_vg);

            // Knob inner
            nvgBeginPath(m_vg);
            nvgCircle(m_vg, knobX, knobY, kr / 2.0f);
            nvgFillColor(m_vg, glmToNVG(m_nobColor.inner));
            nvgStrokePaint(m_vg, knobReverse);
            nvgStroke(m_vg);
            nvgFill(m_vg);
        }
        drawLabel();
    }
}