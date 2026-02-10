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

#include <gui_widget/frtk_button.h>

namespace FR {
    Frtk_Button::Frtk_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Box(vg, x, y, w, h, l, b), m_value(-1)
    {
        assert(vg != NULL);
        m_value = m_oldValue = 0;
        m_wdgType = FRTK_NORMAL_BUTTON;
        m_color = glm::vec4(FR_GRAY80);
    }

    void Frtk_Button::value(uint8_t val) {
        val = val ? 1 : 0;
        m_oldValue = val;
    }
    uint8_t Frtk_Button::oldValue()const {
        return m_oldValue;
    }
    uint8_t Frtk_Button::value() const {
        return m_value;
    }

    void Frtk_Button::draw()
    {
        glm::vec4 actualColor = m_color;
        if (!m_active)
            actualColor = m_color_diabled;
        if (m_value == 0) {
            //UP
            draw_box(m_vg, m_boxType, {{ m_x,m_y }, { m_w,m_h }}, 0.0f, THICK_BORDER, 
                nvgRGBAf(actualColor.r, actualColor.g, actualColor.b, actualColor.a), 
                nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
        }
        else if (m_value == 1)
        {
            //DOWN
            draw_box(m_vg, (BOX_TYPE)((int)(m_boxType)+1), {{ m_x,m_y }, { m_w,m_h }}, 0.0f, THICK_BORDER, 
                nvgRGBAf(actualColor.r, actualColor.g, actualColor.b, actualColor.a), 
                nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), false);
        }
        else
        {
            //Inactive
        }

        if (m_IconTexture != 0) {
            drawImage();//Dimensions are already calculated using style
        }
        else {
            applyStyle(); //We still need to apply style
        }

        drawLabel();
    }
    int Frtk_Button::handle(int e) {
        if (e == FR_LEFT_PUSH) {
            if (m_wdgType == FRTK_CHECK_BUTTON ||
                m_wdgType == FRTK_TOGGLE_LIGHT_BUTTON ||
                m_wdgType == FRTK_LIGHT_BUTTON ||
                m_wdgType == FRTK_TOGGLE_ROUND_BUTTON ||
                m_wdgType == FRTK_SWITCH_BUTTON ||
                m_wdgType == FRTK_ROUND_BUTTON) {
                m_value = ~m_value;
                if (m_value == 1) {
                    m_Image.opacity = 0.5;
                }
                else {
                    m_Image.opacity = 1.0;
                }
            }
            else {
                m_value = 1;
                m_Image.opacity = 0.5;
            }
            do_callback();
            return 1;
        }
        else if (e == FR_LEFT_RELEASE) {
            if (!(m_wdgType == FRTK_CHECK_BUTTON ||
                m_wdgType == FRTK_TOGGLE_LIGHT_BUTTON ||
                m_wdgType == FRTK_TOGGLE_ROUND_BUTTON ||
                m_wdgType == FRTK_SWITCH_BUTTON ||
                m_wdgType == FRTK_LIGHT_BUTTON ||
                m_wdgType == FRTK_ROUND_BUTTON)) {
                m_value = 0;
                m_Image.opacity = 1.0f;
                //callback(); Optional if you want to execute the callback even when mouse is released.
                return 1;
            }
        }
        //TODO : FIX ME .. THIS SHOULD EXECUTE ONLY WHEN IT LOOSES FOCUS WHICH IS NOT DONE HERE!! IN GROUP WIDGET OR WINDOWS
    //Lost focus we should make the value 0
      /*  if (!(m_wdgType == FRTK_CHECK_BUTTON ||
            m_wdgType == FRTK_TOGGLE_LIGHT_BUTTON ||
            m_wdgType == FRTK_TOGGLE_ROUND_BUTTON ||
            m_wdgType == FRTK_SWITCH_BUTTON ||
            m_wdgType == FRTK_LIGHT_BUTTON ||
            m_wdgType == FRTK_ROUND_BUTTON)) {
            m_value = 0;
        }*/
        return 0;
    }
}