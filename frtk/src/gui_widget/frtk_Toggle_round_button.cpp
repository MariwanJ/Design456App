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

#include <gui_widget/frtk_toggle_round_button.h>
namespace FR {
    Frtk_Toggle_Round_Button::Frtk_Toggle_Round_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b) {
        m_wdgType = FRTK_TOGGLE_ROUND_BUTTON;
        m_cellStyle = FR_IMG_RIGHT_TO_TEXT;
        m_specialDrawingSize = m_h * 0.5f;
    }

    void Frtk_Toggle_Round_Button::draw()
    {
        Dim_float_t dim = { { m_x,m_y },{m_w,m_h} };
        const float lightSize = m_specialDrawingSize;
        NVGcolor lightCol = nvgRGBAf(FR_ORANGE);
        if (m_value) {
            drawBoxUpDown(m_vg, dim, 0.0f, m_borderWidth,
                glmToNVG(m_color),
                glmToNVG(m_borderColor), true);
            dim.pos.x = m_x + m_padding;
            dim.pos.y = m_y + m_h / 2 - lightSize / 2;
            dim.size = { lightSize,lightSize };

            drawSolidCircleWithState(m_vg, dim, 0.0f, THIN_BORDER,lightCol,
                glmToNVG(m_borderColor), false);
        }
        else {
            drawBoxUpDown(m_vg, dim, 0.0f, m_borderWidth,
                glmToNVG(m_color),
                glmToNVG(m_borderColor), true);
            dim.pos.x = m_x + m_padding;
            dim.pos.y = m_y + m_h / 2 - lightSize / 2;
            dim.size = { lightSize,lightSize };
            lightCol = nvgRGBAf(FR_WHITE);
            drawSolidCircleWithState(m_vg, dim, 0.0f, THIN_BORDER,lightCol,
                glmToNVG(m_borderColor), true);
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
}