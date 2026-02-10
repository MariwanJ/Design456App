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

#include <gui_widget/frtk_toolbar_button.h> 


namespace FR {
    Frtk_ToolBar_Button::Frtk_ToolBar_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Button(vg, x, y, w, h, l, b), m_divider(false), m_padding(2.0f),
        m_thickness(1.0f), m_lineColor(nvgRGBAf(FR_GRAY80)),m_name(""),m_tooltips("")
    {
        // USE "OR" SYMBOLE FOR DIVIDER BUTTON
        if (!l.empty() ){
            if (l.size() == 1 && l == "|") {
                m_divider = 1;
                disable(); // It's a divider
            }
        }
        m_wdgType = FRTK_TOOLBAR_BUTTON;
    }
    void Frtk_ToolBar_Button::drawVerticalDivider()
    {
        nvgBeginPath(m_vg);
        nvgMoveTo(m_vg, m_x+m_w/2-m_thickness, m_y + m_padding);          
        nvgLineTo(m_vg, m_x + m_w/2-m_thickness, m_y + m_h- m_padding);     
        nvgStrokeColor(m_vg, m_lineColor);
        nvgStrokeWidth(m_vg, m_thickness);
        nvgMoveTo(m_vg, m_x + m_w / 2 + m_thickness , m_y + m_padding);          
        nvgLineTo(m_vg, m_x + m_w / 2 + m_thickness , m_y + m_h - m_padding);    
        nvgStrokeColor(m_vg, nvgRGBAf(FR_GRAY50));
        nvgStrokeWidth(m_vg, m_thickness);
        nvgStroke(m_vg);
        
    }
    void Frtk_ToolBar_Button::name(const std::string& name) {
        m_name = name;
    }
    const std::string& Frtk_ToolBar_Button::name(void)  {
        return m_name;
    }
    void Frtk_ToolBar_Button::tooltips(const std::string& val) {
        m_tooltips = val;
    }
    const std::string& Frtk_ToolBar_Button::tooltips(void) {
        return m_tooltips;
    }


    void Frtk_ToolBar_Button::draw() {
        draw_box(m_vg, m_boxType, {{ m_x,m_y }, { m_w,m_h }}, 0.0f, NORMAL_BORDER, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a), nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
        if (m_divider) {
            drawVerticalDivider();
        }
        if (m_IconTexture != 0){
            if (!m_divider){
            drawImage();//Dimensions are already calculated using style
            }
        }
        else {
            applyStyle(); //We still need to apply style
        }
        if(!m_divider)
            drawLabel();
    }
    void Frtk_ToolBar_Button::setThicknessPadding(float padding, float thickness)
    {
        m_padding = padding;
        m_thickness = thickness;
    }

}