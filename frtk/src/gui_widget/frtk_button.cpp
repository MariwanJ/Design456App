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
#include <gui_widget/frtk_check_button.h>
#include <gui_widget/frtk_round_button.h>
#include <gui_widget/frtk_return_button.h>
#include <gui_widget/frtk_repeat_button.h>
#include <gui_widget/frtk_light_button.h>
#include <gui_widget/frtk_toggle_round_button.h>
#include <gui_widget/frtk_toggle_light_button.h>

namespace FR {
    Frtk_Button::Frtk_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Box(vg, x, y, w, h, l, b), m_value(-1)
    {
        assert(vg != NULL);
        m_value = m_oldValue = 0;
        m_wdgType = FRTK_NORMAL_BUTTON;
        m_color = glm::vec4(FR_LIGHTGRAY);
      //  m_cellStyle = FR_PIC_OVER_TEXT_RIGHT;
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
        if (m_value == 0) {
            //UP
            draw_box(m_vg, m_boxType, m_dim, 0.0f, THICK_BORDER, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a), nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
        }
        else if (m_value == 1)
        {
            //DOWN
            draw_box(m_vg, (BOX_TYPE)((int)(m_boxType)+1), m_dim, 0.0f, THICK_BORDER, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a), nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), false);
        }
        else
        {
            //Inactive
        }
        
        if (m_IconTexture != 0)
            drawImage();//Dimensions are already calculated using style
        
        drawLabel();

    }
    int Frtk_Button::handle(int e) {
        if (should_getEvent(false)) {
            if (e == FR_LEFT_PUSH) {
                if (m_wdgType == FRTK_CHECK_BUTTON) {
                    m_value = ~m_value;
                    if (m_value == 1) {
                        m_Image.opacity = 0.5;
                    }else{
                        m_Image.opacity = 1.0;
                    }
                }else{
                    m_value = 1;
                    m_Image.opacity = 0.5;
                }
                callback();
                return 1;
            }
            else if (e == FR_LEFT_RELEASE) {
                if (m_wdgType != FRTK_CHECK_BUTTON){
                m_value = 0;
                m_Image.opacity = 1.0f;
                    //callback(); Optional if you want to execute the callback even when mouse is released.
                return 1;
                }
            }
        }
        return 0;
    }

    // implementations for all other button types, drawing is done in the base class:

    Frtk_Round_Button::Frtk_Round_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_ROUND_BUTTON;
    }
    Frtk_Return_Button::Frtk_Return_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_RETURN_BUTTON;
    }
    Frtk_Repeat_Button::Frtk_Repeat_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_REPEAT_BUTTON;
    }
    Frtk_Light_Button::Frtk_Light_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_LIGHT_BUTTON;
    }
    Frtk_Toggle_Round_Button::Frtk_Toggle_Round_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_TOGGLE_ROUND_BUTTON;
    }
    Frtk_Toggle_Light_Button::Frtk_Toggle_Light_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_TOGGLE_LIGHT_BUTTON;
    }
}