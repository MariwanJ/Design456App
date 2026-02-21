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

#include <gui_widget/frtk_switch_button.h>

namespace FR {
  
    Frtk_Switch_Button::Frtk_Switch_Button(NVGcontext* m_vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(m_vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_SWITCH_BUTTON;
        m_bkg_color = glm::vec4(FR_CHARCOAL);
        m_font.fName="sans-bold";
        m_specialDrawingSize = m_h * 0.5f;
    }
    void Frtk_Switch_Button::draw() {
       
        if (m_value) {
            drawSegmentToggleOn( );
            
        }
        else {
            drawSegmentToggleOff();
            
        }
        if (m_IconTexture != 0){
            drawImage();//Dimensions are already calculated using style
        }
        else {
            applyStyle(); //We still need to apply style
        }
        drawLabel();
        draw_focus();
    }
    // draw functions: 
    void Frtk_Switch_Button::drawToggleFrame() {
        float r = m_h * 0.25f;
        NVGpaint bg = nvgLinearGradient( m_vg, m_x, m_y, m_x, m_y + m_h, glmToNVG(m_color), glmToNVG(m_bkg_color));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_x, m_y, m_w, m_h, r);
        nvgFillPaint(m_vg, bg);
        nvgFill(m_vg);

        nvgStrokeWidth(m_vg, 1.0f);
        nvgStrokeColor(m_vg, glmToNVG(m_borderColor));
        nvgStroke(m_vg);
        m_font.lblAlign = NVG_ALIGN_MIDDLE_CENTER;
        m_font.txtAlign = NVG_ALIGN_MIDDLE_CENTER;
    }

    void Frtk_Switch_Button::drawActiveSegment(float x, float y, float w, float h, float radius){
        NVGpaint active = nvgLinearGradient( m_vg, x, y, x, y + h, nvgRGBAf(FR_WHITE), nvgRGBAf(FR_GAINSBORO));

        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, x, y, w, h, radius);
        nvgFillPaint(m_vg, active);
        nvgFill(m_vg);

        NVGpaint inner = nvgBoxGradient( m_vg, x, y + 1, w, h, radius, 14, nvgRGBAf(FR_PAYNE_GRAY), nvgRGBAf(FR_WHITE));

        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, x, y, w, h, radius);
        nvgFillPaint(m_vg, inner);
        nvgFill(m_vg);
        
        m_Image.dim.pos.x = x +  /*-m_padding*/ + FRTK_ICON_SIZE.x / 2;
    }
    void Frtk_Switch_Button::drawLabels( float cxOn, float cxOff, float cy, float size, int onActive) {
        nvgFontFace(m_vg, m_font.fName.c_str());
        nvgFontSize(m_vg, m_font.fontSize);

        nvgTextAlign(m_vg, m_font.lblAlign|NVG_ALIGN_BASELINE);
        // ON
        nvgFillColor(m_vg, onActive ? nvgRGBAf(FR_GREEN) : nvgRGBAf(FR_DIM_GRAY));
        nvgText(m_vg, cxOn, cy, "ON", NULL);

        // OFF
        nvgFillColor(m_vg, onActive ? nvgRGBAf(FR_WHITE)  : nvgRGBAf(FR_RED)  );
        nvgText(m_vg, cxOff, cy, "OFF", NULL);
    }

    void Frtk_Switch_Button::drawSegmentToggleOn(  ) {
        drawToggleFrame();

        float pad = 3.0f;
        float ix = m_x + pad;
        float iy = m_y + pad;
        float iw = m_w - pad * 2;
        float ih = m_h - pad * 2;
        float half = iw * 0.5f;
        float r = ih * 0.4f;

        drawActiveSegment(ix, iy, half, ih, r);
        // Divider
        nvgBeginPath(m_vg);
        nvgMoveTo(m_vg, ix + half, iy);
        nvgLineTo(m_vg, ix + half, iy + ih);
        nvgStrokeColor(m_vg, nvgRGBAf(FR_BLUE));
        nvgStrokeWidth(m_vg, 2.0f);
        nvgStroke(m_vg);
        
        drawLabels( ix + half * 0.5f, ix + half * 1.5f, iy + ih * 0.5f, ih * 0.5f,1);

        
    }

    void Frtk_Switch_Button::drawSegmentToggleOff( ) {
        drawToggleFrame();

        float pad = 3.0f;
        float ix = m_x + pad;
        float iy = m_y + pad;
        float iw = m_w - pad * 2;
        float ih = m_h - pad * 2;
        float half = iw * 0.5f;
        float r = ih * 0.4f;

        drawActiveSegment(ix + half, iy, half, ih, r);
        // Divider
        nvgBeginPath(m_vg);
        nvgMoveTo(m_vg, ix + half, iy);
        nvgLineTo(m_vg, ix + half, iy + ih);
        nvgStrokeColor(m_vg, nvgRGBAf(FR_BLUE));
        nvgStrokeWidth(m_vg, 2.0f);
        nvgStroke(m_vg);

        drawLabels( ix + half * 0.5f, ix + half * 1.5f, iy + ih * 0.5f, ih * 0.5f,0);
    }


}