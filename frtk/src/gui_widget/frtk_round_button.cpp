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

#include <gui_widget/frtk_round_button.h>

namespace FR {
    Frtk_Round_Button::Frtk_Round_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :Frtk_Button(vg, x, y, w, h, l, b)
    {
        m_wdgType = FRTK_ROUND_BUTTON;
        m_cellStyle = FR_IMG_RIGHT_TO_TEXT;
        m_specialDrawingSize = m_h * 0.4f;
    }
    void Frtk_Round_Button::draw()
    {
        Dim_float_t dim = { { m_x,m_y },{m_w,m_h} };
        NVGcolor lightCol = nvgRGBAf(FR_WHITE);

        //body
        draw_box(m_vg, FRTK_FLAT_BOX, dim, 0.0f, m_borderWidth,
            nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a),
            nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
        dim.pos.x = m_x + m_padding;
        dim.pos.y = m_y + m_h / 2 - m_specialDrawingSize / 2;
        dim.size = { m_specialDrawingSize,m_specialDrawingSize };

        //draw the round indicator
        if (m_value) {
            draw_box(m_vg, FRTK_ROUND_UP_BOX, dim, 0.0f, THIN_BORDER,
                lightCol,
                nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), false);
            dim.pos.x = m_x + m_padding + m_specialDrawingSize / 4;
            dim.pos.y = m_y + m_h / 2 - m_specialDrawingSize / 4;
            dim.size = { m_specialDrawingSize/2 ,m_specialDrawingSize/2 };

            draw_box(m_vg, FRTK_ROUND_UP_BOX, dim, 0.0f, THIN_BORDER,
                nvgRGBAf(FR_BLACK),
                nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), false);
        }
        else {
            draw_box(m_vg, FRTK_ROUND_UP_BOX, dim, 0.0f, THIN_BORDER,
                lightCol,
                nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), false);
        }
        if (m_IconTexture != 0) {
            drawImage();//Dimensions are already calculated using style
        }
        else {
            applyStyle(); //We still need to apply style
        }
        drawLabel();
    }
}