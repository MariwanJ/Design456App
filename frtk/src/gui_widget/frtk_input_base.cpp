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
        Frtk_Box(vg, X, Y, W, H, lbl, b), m_tab_nav(0), m_text{ "", 0,0 }
    {
        m_color = glm::vec4(FR_WHITE);
        m_color.a = 0.1254f;
        m_bkg_color = glm::vec4(0.1254f, 0.1254f, 0.1254f, 0.1254f);
        m_borderColor = glm::uvec4(FR_DARKGREY2);
        m_font.fontSize = 14.f;
        m_font.hAlign = FRTK_ALIGN_LEFT;
        m_font.vAlign = FRTK_ALIGN_TOP;
    }


    std::string Frtk_Input_Base::cpToUTF8(uint32_t cp) {
        if (cp > 0x10FFFF || (cp >= 0xD800 && cp <= 0xDFFF)) {
            throw std::runtime_error("Invalid Unicode code point");
        }

        std::string str;
        if (cp <= 0x7F) {               // 1 byte
            str.push_back(static_cast<char>(cp));
        }
        else if (cp <= 0x7FF) {       // 2 bytes
            str.push_back(static_cast<char>(0xC0 | ((cp >> 6) & 0x1F)));
            str.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        }
        else if (cp <= 0xFFFF) {      // 3 bytes
            str.push_back(static_cast<char>(0xE0 | ((cp >> 12) & 0x0F)));
            str.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
            str.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        }
        else {                        // 4 bytes
            str.push_back(static_cast<char>(0xF0 | ((cp >> 18) & 0x07)));
            str.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
            str.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
            str.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        }
        return str;
    }


    void Frtk_Input_Base::drawEditBoxBase(float x, float y, float w, float h)
    {
        NVGpaint bg;
        // Edit
        bg = nvgBoxGradient(m_vg, x + 1, y + 1 + 1.5f, w - 2, h - 2, 3, 4, glmToNVG(m_color), glmToNVG(m_bkg_color));
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
            draw_cursor();
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
    int Frtk_Input_Base::copy() {

        if (m_text.selStart == m_text.cursorPos)
            return 0; // nothing selected

        int start = std::min(m_text.selStart, m_text.cursorPos);
        int end = std::max(m_text.selStart, m_text.cursorPos);
        std::string selected = m_text.value.substr(start, end - start);
        glfwSetClipboardString( m_mainWindow->getCurrentGLWindow(), selected.c_str());
        return 1;
    }

    int Frtk_Input_Base::paste()
    {
        const char* clip = glfwGetClipboardString(m_mainWindow->getCurrentGLWindow());
        if (!clip)
            return 0; // nothing to paste
        std::string textToInsert = clip;
        if (m_text.selStart != m_text.cursorPos)
            delSel();
        m_text.value.insert(m_text.cursorPos, textToInsert);
        m_text.cursorPos += (int)textToInsert.length();
        m_text.selStart = m_text.cursorPos;
        return 1;
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
    //    FRTK_BASE_INPUT = 0,
    //    FRTK_INT_INPUT,
    //    FRTK_FLOAT_INPUT,
    //    FRTK_INPUT,
    //    FRTK_INPUT_WRAP,          //one line only
    //    FRTK_MULTILINE_INPUT,     //mulit lines
    //    FRTK_MULTILINE_INPUT_WRAP,
    //    FRTK_SECRET_INPUT,
    //
    //    FRTK_NORMAL_OUTPUT,
    //    FRTK_MULTILINE_OUTPUT,
    //    FRTK_MULTILINE_OUTPUT_WRAP,
    //    FRTK_NORMAL_OUTPUT_READONLY,
    //    FRTK_MULTILINE_OUTPUT_READONLY,
    //    FRTK_MULTILINE_OUTPUT_WRAP_READONLY,

    bool Frtk_Input_Base::isEditable() const
    {
        return (
            m_wdgType == FRTK_INT_INPUT || FRTK_BASE_INPUT||
            m_wdgType == FRTK_FLOAT_INPUT ||
            m_wdgType == FRTK_INPUT ||
            m_wdgType == FRTK_INPUT_WRAP ||
            m_wdgType == FRTK_MULTILINE_INPUT ||
            m_wdgType == FRTK_MULTILINE_INPUT_WRAP ||
            m_wdgType == FRTK_SECRET_INPUT
            );
    }

    bool Frtk_Input_Base::isSelectable() const
    {
        return !((m_wdgType == FRTK_NORMAL_OUTPUT_READONLY ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_READONLY ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_WRAP_READONLY));
    }
    bool Frtk_Input_Base::isSingleLine() const {
        //notice that, the widget can be readonly but still multi-line
        return (!(m_wdgType == FRTK_MULTILINE_INPUT_WRAP ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_WRAP ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_READONLY ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_WRAP_READONLY));
    }
    bool Frtk_Input_Base::isWrapped() const
    {
        return (
            m_wdgType == FRTK_INPUT_WRAP ||
            m_wdgType == FRTK_MULTILINE_INPUT_WRAP ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_WRAP ||
            m_wdgType == FRTK_MULTILINE_OUTPUT_WRAP_READONLY);
    }

    bool Frtk_Input_Base::isSecret() const
    {
        return  (m_wdgType == FRTK_SECRET_INPUT);
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
    bool Frtk_Input_Base::delSel() {
        // Ensure selStart <= cursorPos
        if (m_text.selStart > m_text.cursorPos)
            std::swap(m_text.selStart, m_text.cursorPos);

        // Nothing to delete
        if (m_text.selStart >= m_text.value.size() && m_text.selStart == m_text.cursorPos)
            return false;

        if (m_text.selStart == m_text.cursorPos) {
            // Delete single character if within bounds
            if (m_text.selStart < m_text.value.size())
                m_text.value.erase(m_text.value.begin() + m_text.selStart);
        }
        else {
            // Delete selection range
            m_text.value.erase(
                m_text.value.begin() + m_text.selStart,
                m_text.value.begin() + std::min((int)m_text.cursorPos, (int)m_text.value.size())
            );
        }

        // Move cursor to start of deleted range
        m_text.cursorPos = m_text.selStart;
        m_text.selStart = m_text.cursorPos;  // selection collapsed
        return true;
    }
    void Frtk_Input_Base::draw_cursor()
    {
        if (!m_has_focus)
            return;

        NVGglyphPosition glyphs[512];
        int count = nvgTextGlyphPositions( m_vg, m_x, m_y, m_text.value.c_str(), nullptr, glyphs, 512);
        float cursorX;
        if (m_text.cursorPos < count)
            cursorX = glyphs[m_text.cursorPos].x;
        else if (count > 0)
            cursorX = glyphs[count - 1].maxx;
        else
            cursorX = m_x;
        float asc, desc, lineh;
        nvgTextMetrics(m_vg, &asc, &desc, &lineh);

        drawFilledRect(m_vg,{  cursorX, m_y +m_h/2 - asc, 2, lineh }, 0, NORMAL_BORDER, nvgRGBAf(FR_BLACK), glmToNVG(m_color_diabled) );
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


        switch (ev) {
        case (FR_FOCUS): {
            m_text.cursorPos = m_text.value.size();
            m_text.selStart = m_text.cursorPos;
            return 1;
        }
        case (FR_KEYBOARD): {
            FRTK_CORE_INFO("IAM HERE");
            if (!(m_active || m_visible))
                return 0;
            auto& ek = m_mainWindow->m_sysEvents.keyB;
            if (isEditable() && m_has_focus) {
                if (ek.lastKAction == GLFW_PRESS || ek.lastKAction == GLFW_REPEAT) {
                    switch (ek.lastKey) {
                        //Left key
                    case GLFW_KEY_LEFT: {
                        if (!ek.shiftDown) {
                            // collapse selection first
                            m_text.selStart = m_text.cursorPos;
                        }
                        if (m_text.cursorPos > 0)
                            m_text.cursorPos--;
                    } break;

                    case GLFW_KEY_RIGHT: {
                        if (!ek.shiftDown) {
                            m_text.selStart = m_text.cursorPos;
                        }
                        if (m_text.cursorPos < (int)m_text.value.size())
                            m_text.cursorPos++;
                    } break;

                    case GLFW_KEY_HOME: {
                        if (!ek.shiftDown) {
                            m_text.selStart = m_text.cursorPos;
                        }
                        m_text.cursorPos = 0;
                    } break;

                    case GLFW_KEY_END: {
                        if (!ek.shiftDown) {
                            m_text.selStart = m_text.cursorPos;
                        }
                        m_text.cursorPos = (int)m_text.value.size();
                    } break;

                    case GLFW_KEY_BACKSPACE: {
                        if (m_text.selStart != m_text.cursorPos) {
                            delSel();
                        }
                        else if (m_text.cursorPos > 0) {
                            m_text.value.erase(m_text.value.begin() + m_text.cursorPos - 1);
                            m_text.cursorPos--;
                        }
                    } break;
                    case GLFW_KEY_DELETE: {
                        if (m_text.selStart != m_text.cursorPos) {
                            delSel();
                        }
                        else if (m_text.cursorPos < (int)m_text.value.size()) {
                            m_text.value.erase(m_text.value.begin() + m_text.cursorPos);
                        }
                    } break;

                    case GLFW_KEY_ENTER:
                    case GLFW_KEY_KP_ENTER: {
                        if (isSingleLine()) {
                            m_text.selStart = 0;
                            m_text.cursorPos = 0;
                            do_callback();
                            m_has_focus = false;
                        }
                        else {
                            m_text.value.insert(m_text.value.begin() + m_text.cursorPos, '\n');
                            m_text.cursorPos++;
                            m_text.selStart = m_text.cursorPos;
                        }
                    }break;
                   }
                }
                if (ek.ctrlDown && ek.lastKAction == GLFW_KEY_A) {
                    m_text.cursorPos = (int) m_text.value.size();
                    m_text.selStart = 0;
                }else if (ek.ctrlDown && ek.lastKAction == GLFW_KEY_X) {
                    copy();
                    delSel();
                 }
                else if (ek.ctrlDown && ek.lastKAction == GLFW_KEY_C) {
                    copy();
                }
                else if (ek.ctrlDown && ek.lastKAction == GLFW_KEY_V) {
                    delSel();
                    paste();
                }
            }
            // We dont have special char .. unicode char to be processed

            if (!m_mainWindow->m_unicodeChars.empty()) {
                delSel(); // delete selection if any

                for (auto& item : m_mainWindow->m_unicodeChars) {
                    std::string utf8 = cpToUTF8(item.codepoint); // convert codepoint to UTF-8
                    m_text.value.insert(
                        m_text.value.begin() + m_text.cursorPos,
                        utf8.begin(),
                        utf8.end()
                    );
                    m_text.cursorPos += utf8.size(); 
                }

                m_text.selStart = m_text.cursorPos;   // update selection start
                m_mainWindow->m_unicodeChars.clear(); // clear queue after processing
            }
        }
        
        
        case (FR_LEFT_PUSH): {

        }
        }

        return 0;
    }
}