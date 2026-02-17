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

#include <gui_widget/frtk_return_button.h>
namespace FR {
    Frtk_Return_Button::Frtk_Return_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Button(vg, x, y, w, h, l, b), m_ReturnSymbolColor (glm::vec4(FR_BLUE)) {
        m_wdgType = FRTK_RETURN_BUTTON;
        m_cellStyle = FR_IMG_RIGHT_TO_TEXT;
        wdgImage(enter_sym);
    }
    void Frtk_Return_Button::changeImageColor(glm::vec4 col) {
        m_ReturnSymbolColor = col;
        std::vector<uint8_t> pngCopy = enter_sym;
        wdgImage(pngCopy, m_ReturnSymbolColor);
    }

    void Frtk_Return_Button::draw()
    {
        if (m_value == 0){
            draw_box(m_vg, m_boxType, {{ m_x,m_y }, { m_w,m_h }}, 0.0f, NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_borderColor), true);
        }
        else {
            draw_box(m_vg, m_boxType, {{ m_x,m_y }, { m_w,m_h }}, 0.0f, NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_borderColor), false);
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