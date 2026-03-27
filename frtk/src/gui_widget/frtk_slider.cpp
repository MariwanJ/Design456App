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
        Frtk_Box(vg, X, Y, W, H, lbl, b), m_range{ 0.0f,100.f }, m_knobDim{ 0 },
        m_highlight{ 0.0f,0.0f }, m_value(0), m_sliderType(H_SLIDER),
        m_speedFactor(0.75f), m_stepSize(0.1f), m_accumulated(0.f)
    {
        m_nobColor.knob = glm::vec4(FR_DARKGREY1);
        m_nobColor.inner = glm::vec4(FR_BEIGE);
        m_nobColor.shadow = glm::vec4(FR_DARK_SHADOW);
        m_nobColor.track = glm::vec4(FR_DARKSLATEGREY);
        m_cornerRadius = 3.0f;
        m_dragging = false;
        m_font.lblAlign = NVG_ALIGN_BOTTOM_CENTER;
        m_knobDim.radious = 11.2;
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
                mouse.activeY >= Y + m_h * 0.5f - m_knobDim.radious * 2 &&
                mouse.activeY <= Y + m_h * 0.5f + m_knobDim.radious * 2
                );
        }
        else {
            testBound = (
                mouse.activeX >= X + m_w * 0.5f - m_knobDim.radious * 2 &&
                mouse.activeX <= X + m_w * 0.5f + m_knobDim.radious * 2 &&
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

    knob_posSize_t& Frtk_Slider::knobDim()
    {
        return m_knobDim;
    }

    const knob_posSize_t& Frtk_Slider::knobDim() const
    {
        return m_knobDim;
    }

    void Frtk_Slider::stepSize(const float& step)
    {
        m_stepSize = step;
    }

    float Frtk_Slider::stepSize()
    {
        return m_stepSize;
    }

    int Frtk_Slider::handle(int ev)
    {
        auto& mouse = m_mainWindow->m_sysEvents.mouse;
        bool testBound = isMouseInsideSliderBar();
        if (testBound || (ev == FR_LEFT_DRAG_MOVE && m_dragging)) {
            if (ev == FR_LEFT_DRAG_PUSH && testBound && !m_dragging) {
                m_dragging = true;
                return 1;
            }
            if (ev == FR_LEFT_DRAG_MOVE && m_dragging) {
                if (m_sliderType == H_SLIDER) {
                    float deltaX = mouse.activeX - mouse.prevX;
                    float kshadow = 3;
                    float trackW = m_w - 2.0f * (m_knobDim.radious + kshadow);
                    float sign = (deltaX < 0) ? -1.0f : 1.0f;

                    m_speedFactor = m_stepSize / m_w;
                    if (m_stepSize > 0.5f) {
                        m_accumulated += deltaX;
                        if (abs(m_accumulated) > m_w / m_stepSize) {
                            m_value += m_stepSize * sign;
                            m_accumulated = 0.0f;
                        }
                    }
                    else {
                        m_value += (deltaX / trackW) * (m_range.max - m_range.min) * m_speedFactor;
                    }
                }
                else if (m_sliderType == V_SLIDER) {
                    float deltaY = mouse.prevY - mouse.activeY; // inverted: up = more

                    float kshadow = 3;
                    float trackH = m_h - 2.0f * (m_knobDim.radious + kshadow);
                    float sign = (deltaY < 0) ? -1.0f : 1.0f;

                    if (m_stepSize > 0.5f) {
                        if (deltaY > m_h / m_stepSize)
                            m_accumulated += deltaY;
                        if (abs(m_accumulated) > m_h / m_stepSize) {
                            m_value += m_stepSize * sign;
                            m_accumulated = 0.0f;
                        }
                    }
                    else {
                        m_value += (deltaY / trackH) * (m_range.max - m_range.min) * m_speedFactor;
                    }
                }
                m_value = std::clamp(m_value, m_range.min, m_range.max);

                do_callback();
                return 1;
            }
        }
        else
        {
            m_dragging = false;
        }
        return 0;
    }

    void Frtk_Slider::drawSliderSteps()
    {
        if (!(m_stepSize > 0.5f))
            return;

        float padding = m_stepSize;

        if (m_sliderType == H_SLIDER) {
            float usableW = m_w - 2 * padding;
            int steps = (int)(usableW / m_stepSize);

            float startX = m_x + padding;
            float centerY = m_y + m_h * 0.5f;
            float tickH = m_h * 0.3f; // total tick height

            for (int i = 0; i <= steps; i++) {
                float px = startX + i * m_stepSize;

                if (px > m_x + m_w - padding)
                    break;

                px = floor(px) + 0.5f;

                Dim_float_t dim;
                dim.pos = { px, centerY - tickH * 0.5f };
                dim.size = { 0.0f, tickH }; // vertical line

                drawLineWithState(m_vg, dim, 1.0f, nvgRGBAf(0.7f, 0.7f, 0.7f, 1.0f),
                    nvgRGBAf(0.2f, 0.2f, 0.2f, 1.0f), true);
            }
        }
        else {
            if (!(m_stepSize > 0.5f))
                return;
            //TODO FIXME
            float usableH = m_h - 2 * padding;
            int steps = (int)(usableH / m_stepSize);
            float startY = m_y + padding;
            float centerX = m_x + m_w * 0.5f;
            float tickW = m_w * 0.3f;
            for (int i = 0; i <= steps; i++) {
                float py = startY + i * m_stepSize;
                if (py > m_y + m_h - padding)
                    break;
                py = floor(py) + 0.5f;
                Dim_float_t dim;
                dim.pos = { centerX - tickW * 0.5f, py };
                dim.size = { tickW, 0.0f }; // horizontal line
                drawLineWithState(m_vg, dim, 1.0f, nvgRGBAf(0.7f, 0.7f, 0.7f, 1.0f),
                    nvgRGBAf(0.2f, 0.2f, 0.2f, 1.0f), true);
            }
        }
    }
    void Frtk_Slider::draw()
    {
        draw_box(m_vg, m_boxType, { {m_x,m_y},{m_w,m_h} }, m_cornerRadius, FRTK_EXTRA_THIN_BORDER, glmToNVG(m_color), glmToNVG(m_nobColor.shadow), false);
        drawSliderSteps();

        if (m_sliderType == H_SLIDER) {
            m_knobDim.pos.x = m_x + m_w;
            m_knobDim.pos.y = m_y + m_h * 0.50f;
            float kshadow = 3;
            float startX = m_x + m_knobDim.radious + kshadow;
            float widthX = m_w - 2.0f * (m_knobDim.radious + kshadow);

            float knobX = startX + (m_value - m_range.min) / (m_range.max - m_range.min) * widthX;
            float knobY = m_knobDim.pos.y + 0.5f;

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
            NVGpaint bg = nvgBoxGradient(m_vg, startX, m_knobDim.pos.y - 3 + 1, widthX, 6, 3, 3, track1, track2);
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, startX, m_knobDim.pos.y - 3 + 1, widthX, 6, 2);
            nvgFillPaint(m_vg, bg);
            nvgFill(m_vg);

            // Highlight range
            if (m_highlight.max != m_highlight.min)
            {
                nvgBeginPath(m_vg);
                nvgRoundedRect(m_vg, startX + m_highlight.min * m_w, m_knobDim.pos.y - kshadow + 1, widthX * (m_highlight.max - m_highlight.min), kshadow * 2, 2);
                nvgFillColor(m_vg, glmToNVG(m_color));
                nvgFill(m_vg);
            }

            NVGpaint knobShadow = nvgRadialGradient(m_vg, knobX, knobY, m_knobDim.radious - kshadow, m_knobDim.radious + kshadow, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f), nvgRGBAf(FR_BLACK));
            NVGpaint knob = nvgLinearGradient(m_vg, m_x, m_knobDim.pos.y - m_knobDim.radious, m_x, m_knobDim.pos.y + m_knobDim.radious, glmToNVG(m_nobColor.knob), glmToNVG(m_nobColor.shadow));
            NVGpaint knobReverse = nvgLinearGradient(m_vg, m_x, m_knobDim.pos.y - m_knobDim.radious, m_x, m_knobDim.pos.y + m_knobDim.radious, glmToNVG(m_color), glmToNVG(m_nobColor.shadow));

            nvgBeginPath(m_vg);
            nvgCircle(m_vg, knobX, knobY, m_knobDim.radious);
            nvgStrokeColor(m_vg, glmToNVG(m_bkg_color));
            nvgFillPaint(m_vg, knob);
            nvgStroke(m_vg);
            nvgFill(m_vg);

            // Knob inner
            nvgBeginPath(m_vg);
            nvgCircle(m_vg, knobX, knobY, m_knobDim.radious / 2.0f);
            if (!m_dragging)
                nvgFillColor(m_vg, glmToNVG(m_nobColor.inner));
            else
                nvgFillColor(m_vg, glmToNVG(glm::vec4(FR_YELLOW)));
            nvgStrokePaint(m_vg, knobReverse);
            nvgStroke(m_vg);
            nvgFill(m_vg);
        }
        else // V_SLIDER
        {
            m_knobDim.pos.x = m_x + m_w * 0.5f;
            m_knobDim.pos.y = m_y;                          // top of widget
            float kshadow = 3;
            float startY = m_y + m_knobDim.radious + kshadow;
            float heightY = m_h - 2.0f * (m_knobDim.radious + kshadow);

            // knob travels top - bottom, but value increases upward
            float knobY = startY + (1.0f - (m_value - m_range.min) / (m_range.max - m_range.min)) * heightY;
            float knobX = m_knobDim.pos.x + 0.5f;

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

            NVGpaint bg = nvgBoxGradient(m_vg, m_knobDim.pos.x - 3 + 1, startY, 6, heightY, 3, 3, track1, track2);
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, m_knobDim.pos.x - 3 + 1, startY, 6, heightY, 2);
            nvgFillPaint(m_vg, bg);
            nvgFill(m_vg);

            // Highlight range
            if (m_highlight.max != m_highlight.min)
            {
                nvgBeginPath(m_vg);
                nvgRoundedRect(m_vg, m_knobDim.pos.x - kshadow + 1, startY + m_highlight.min * m_h, kshadow * 2, heightY * (m_highlight.max - m_highlight.min), 2);
                nvgFillColor(m_vg, glmToNVG(m_color));
                nvgFill(m_vg);
            }

            // Knob shadow
            NVGpaint knobShadow = nvgRadialGradient(m_vg, knobX, knobY, m_knobDim.radious - kshadow,
                m_knobDim.radious + kshadow, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f), nvgRGBAf(FR_BLACK));

            // Knob gradients
            NVGpaint knob = nvgLinearGradient(m_vg, m_knobDim.pos.x - m_knobDim.radious, m_y, m_knobDim.pos.x + m_knobDim.radious, m_y,
                glmToNVG(m_nobColor.knob), glmToNVG(m_nobColor.shadow));
            NVGpaint knobReverse = nvgLinearGradient(m_vg, m_knobDim.pos.x - m_knobDim.radious, m_y, m_knobDim.pos.x + m_knobDim.radious,
                m_y, glmToNVG(m_color), glmToNVG(m_nobColor.shadow));

            nvgBeginPath(m_vg);
            nvgCircle(m_vg, knobX, knobY, m_knobDim.radious);
            nvgStrokeColor(m_vg, glmToNVG(m_bkg_color));
            nvgFillPaint(m_vg, knob);
            nvgStroke(m_vg);
            nvgFill(m_vg);

            // Knob inner
            nvgBeginPath(m_vg);
            nvgCircle(m_vg, knobX, knobY, m_knobDim.radious / 2.0f);

            if (!m_dragging)
                nvgFillColor(m_vg, glmToNVG(m_nobColor.inner));
            else
                nvgFillColor(m_vg, glmToNVG(glm::vec4(FR_YELLOW)));

            nvgStrokePaint(m_vg, knobReverse);
            nvgStroke(m_vg);
            nvgFill(m_vg);
        }
        drawLabel();
    }
}