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

#include <gui_widget/frtk_input.h>
#include "frtk_secret_input.h"
#include <gui_widget/frtk_window.h>

namespace FR{

FR::Frtk_Secret_Input::Frtk_Secret_Input(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b): 
    Frtk_Input_Base(vg, X, Y, W,  H,lbl, b) 
{
    m_wdgType = FRTK_SECRET_INPUT;

}

void Frtk_Secret_Input::draw() {
    drawEditBoxBase(m_x, m_y, m_w, m_h);
    if(m_linkTofrtkWindow)
        drawTextInBox(m_vg, m_text.value, m_font, false, m_linkTofrtkWindow->getFontData(), MASK_CHAR);
    drawLabel();
    if (m_has_focus) {
        draw_focus();
        draw_cursor();
    }
    draw_selection();
}


}
