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

#include <gui_widget/frtk_input_base.h>
#include<nanovg.h>

namespace FR {
#define ICON_SEARCH 0x1F50D
#define ICON_CIRCLED_CROSS 0x2716

    Frtk_Input_Base::Frtk_Input_Base(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_Box(vg, X, Y, W, H, lbl, b), m_tab_nav(0), m_text{"", 0,0,0}
    {
        m_color = glm::vec4(FR_WHITE);
        m_color.a = 0.1254f;
        m_bkg_color = glm::vec4(0.1254f, 0.1254f, 0.1254f, 0.1254f);
        m_borderColor = glm::uvec4(FR_DARKGREY2);
        m_font.fontSize = 14.f;
        m_font.hAlign = FRTK_ALIGN_LEFT;
        m_font.vAlign = FRTK_ALIGN_TOP;
    }



    static char* cpToUTF8(int cp, char* str)
    {
        int n = 0;
        if (cp < 0x80) n = 1;
        else if (cp < 0x800) n = 2;
        else if (cp < 0x10000) n = 3;
        else if (cp < 0x200000) n = 4;
        else if (cp < 0x4000000) n = 5;
        else if (cp <= 0x7fffffff) n = 6;
        str[n] = '\0';
        switch (n) {
        case 6: str[5] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x4000000;
        case 5: str[4] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x200000;
        case 4: str[3] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x10000;
        case 3: str[2] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0x800;
        case 2: str[1] = 0x80 | (cp & 0x3f); cp = cp >> 6; cp |= 0xc0;
        case 1: str[0] = cp;
        }
        return str;
    }

    void Frtk_Input_Base::drawEditBoxBase(float x, float y, float w, float h)
    {
        NVGpaint bg;
        // Edit
        bg = nvgBoxGradient(m_vg, x + 1, y + 1 + 1.5f, w - 2, h - 2, 3, 4, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a), nvgRGBAf(m_bkg_color.r, m_bkg_color.g, m_bkg_color.b, m_bkg_color.a));
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, x + 1, y + 1, w - 2, h - 2, 4 - 1);
        nvgFillPaint(m_vg, bg);
        nvgFill(m_vg);

        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, x + 0.5f, y + 0.5f, w - 1, h - 1, 4 - 0.5f);
        nvgStrokeColor(m_vg, nvgRGBAf(0, 0, 0, 48));
        nvgStroke(m_vg);
    }

    void Frtk_Input_Base::draw() {
        drawEditBoxBase(m_x, m_y, m_w, m_h);
        nvgFontSize(m_vg, m_font.fontSize);
        nvgFontFace(m_vg, m_font.fName.c_str());
        nvgFillColor(m_vg, m_font.forgColor);
        nvgTextAlign(m_vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(m_vg, m_x + m_h * 0.3f, m_y + m_h * 0.5f, m_text.value.c_str(), NULL);
        if (m_has_focus) {
            draw_focus();
        }
    }

    void Frtk_Input_Base::value(int value) {
        m_text.value = std::to_string(value);
    }

    void Frtk_Input_Base::value(float value) {
        m_text.value = std::to_string(value);
    }
    void Frtk_Input_Base::value(double value) {
        m_text.value = std::to_string(value);
    }
    void Frtk_Input_Base::value(const char* value) {
        m_text.value = value;

    }
    void Frtk_Input_Base::value(std::string& value) {
        m_text.value = value;
    }
    int Frtk_Input_Base::ivalue() const {
           return std::stoi(m_text.value);
    }
    double Frtk_Input_Base::dvalue() const {
        return std::stod(m_text.value);
    }
    int  Frtk_Input_Base::size() const {
        return m_text.value.size();
    }
    int  Frtk_Input_Base::mark(int markIndex) {
        return 0;
    }
    int  Frtk_Input_Base::insert_position(int p, int m) {
        return 0;
    }
    int Frtk_Input_Base::replace(int beg, int end, const char* text, int ilen)
    {
        return 0;
    }
    int  Frtk_Input_Base::cut(int n) {
        return 0;
    }
    int  Frtk_Input_Base::cut(int beg, int end) {
        return 0;
    }
    int  Frtk_Input_Base::insert(const char* t, int length) {
        return 0;
    }
    int  Frtk_Input_Base::copy(int clipboard) {
        return 0;
    }
    int  Frtk_Input_Base::undo() {
        return 0;
    }
    bool Frtk_Input_Base::can_undo() const {
        return 0;
    }
    int  Frtk_Input_Base::redo() {
        return 0;
    }
    bool Frtk_Input_Base::readonly() const {
        return 0;
    }
    void Frtk_Input_Base::readonly(bool val) {

    }
    int  Frtk_Input_Base::wrap() const {
        return 0;
    }
    void Frtk_Input_Base::wratp(int b) {

    }

    int  Frtk_Input_Base::word_start(int ind) const {
        return 0;
    }
    int  Frtk_Input_Base::line_strart(int ind) const {
        return 0;
    }
    int  Frtk_Input_Base::line_end(int ind) const {
        return 0;
    }   
    
    int Frtk_Input_Base::handle(int ev)
    {
        /*
                    -Mouse click inside widget -> focus
                    -Typing characters ->insert at cursor, handle selection
                    -Arrow/Home/End -> move cursor
                    -Backspace/Delete -> remove selected or adjacent characters
                    -Clipboard/IME handling 
            
        
        */
       /* switch (ev) {
        }*/

        /*}*/
        return 0;
    }
}