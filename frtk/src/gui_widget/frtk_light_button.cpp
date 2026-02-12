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

#include <gui_widget/frtk_light_button.h>

namespace FR {
  
    Frtk_Light_Button::Frtk_Light_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_LIGHT_BUTTON;
        //m_cellStyle = FR_IMG_RIGHT_TO_TEXT;
        m_specialDrawingSize = m_h * 0.5f;
    }
    void Frtk_Light_Button::draw() {
       
        if (m_value) {
            drawToggleOn(m_vg, m_x, m_y, m_w, m_h, nvgRGB(180, 180, 180));
        }
        else {
            drawToggleOff(m_vg, m_x, m_y, m_w, m_h, nvgRGB(180, 180, 180));
        }
        if (m_IconTexture != 0){
            drawImage();//Dimensions are already calculated using style
        }
        else {
            applyStyle(); //We still need to apply style
        }
        drawLabel();
    }

    // Draw functions : 
    void Frtk_Light_Button::drawKnob(NVGcontext* vg, float cx, float cy, float r, NVGcolor color) {
        NVGpaint knob = nvgRadialGradient(vg, cx - r * 0.3f, cy - r * 0.3f, r * 0.2f, r, nvgRGBAf(1.0f, 1.0f, 1.0f, 0.88f), color);

        nvgBeginPath(vg);
        nvgCircle(vg, cx, cy, r);
        nvgFillPaint(vg, knob);
        nvgFill(vg);
    }
    void Frtk_Light_Button::drawToggleOn(NVGcontext* vg, float x, float y, float w, float h, NVGcolor knobColor) {
        drawToggleBase(vg, x, y, w, h, nvgRGBAf(0.4705f, 0.88f, 0.4705f, 1.0f),   /* top green*/ nvgRGBAf(0.1568f, 0.6274f, 0.1568f, 1.0f)      /* bottom green*/);

        float knobR = h * 0.4f;
        float cx = x + w - h * 0.5f;
        float cy = y + h * 0.5f;
        drawKnob(vg, cx, cy, knobR, knobColor);
        m_Image.dim.pos.x = cx - knobR;
    }
    void Frtk_Light_Button::drawToggleOff(NVGcontext* vg, float x, float y, float w, float h, NVGcolor knobColor) {
        drawToggleBase(vg, x, y, w, h, nvgRGBAf(0.8627f, 0.4705f, 0.4705f, 1.0f),   /* top red*/ nvgRGBAf(0.6274f, 0.1568f, 0.1568f, 1.0f)      /* bottom red*/);
        float knobR = h * 0.4f;
        float cx = x + h * 0.5f;
        float cy = y + h * 0.5f;
        m_Image.dim.pos.x=   cx - knobR ;
        drawKnob(vg, cx, cy, knobR, knobColor);
    }

    void Frtk_Light_Button::drawToggleBase(NVGcontext* vg, float x, float y, float w, float h, NVGcolor top, NVGcolor bottom) {
        float r = h * 0.5f;

        // Background gradient
        NVGpaint bg = nvgLinearGradient(vg, x, y, x, y + h, top, bottom);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillPaint(vg, bg);
        nvgFill(vg);

        // Inner shadow
        NVGpaint inner = nvgBoxGradient(vg, x, y + 1, w, h, r, 4, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3137f), nvgRGBAf(0.f, 0.0f, 0.0f, 0.0f));

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillPaint(vg, inner);
        nvgFill(vg);
    }
    
}