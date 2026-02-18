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

#include <gui_widget/frtk_search_box.h>
#include <nanovg.h>
#include "frtk_input_base.h"

namespace FR {
#define ICON_SEARCH 0x1F50D
#define ICON_CIRCLED_CROSS 0x2716
    Frtk_Search_Box::Frtk_Search_Box(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_Box(vg, X, Y, W, H, lbl, b), m_cornerRadius(m_h * .5f)
    {
        m_color = glm::vec4(FR_WHITE);
        m_bkg_color = glm::vec4(FR_GRAY);
        m_borderColor = glm::uvec4(FR_DARKGREY2);

        m_font.fontSize = 14.f;
        m_font.forgColor = nvgRGBAf(FR_BLACK);
        m_font.shadowCol = nvgRGBAf(FR_DARKGREY2);
        m_font.hAlign = FRTK_ALIGN_LEFT;
        m_font.vAlign = FRTK_ALIGN_TOP;

        m_SearchIconPos = { m_x, m_y + m_h / 2.0f };
        m_CloseIconPos = { m_x + m_w - (m_font.fontSize * 2.2f), m_y + m_h / 2.0f };
    }

    int Frtk_Search_Box::handle(int ev)
    {
        return 0;
    }

    std::string cpToUTF8(int cp) {
        if (cp < 0 || cp > 0x10FFFF || (cp >= 0xD800 && cp <= 0xDFFF)) {
            FRTK_CORE_FATAL("Invalid Unicode code point");
        }

        std::string str;
        int n = 0;

        // Determine the number of bytes needed
        if (cp < 0x80) n = 1;
        else if (cp < 0x800) n = 2;
        else if (cp < 0x10000) n = 3;
        else if (cp < 0x200000) n = 4;
        else if (cp < 0x4000000) n = 5;
        else n = 6;

        str.resize(n);  // Resize the string to hold the UTF-8 bytes

        switch (n) {
        case 6: str[5] = 0x80 | (cp & 0x3f); cp >>= 6; cp |= 0x4000000;
        case 5: str[4] = 0x80 | (cp & 0x3f); cp >>= 6; cp |= 0x200000;
        case 4: str[3] = 0x80 | (cp & 0x3f); cp >>= 6; cp |= 0x10000;
        case 3: str[2] = 0x80 | (cp & 0x3f); cp >>= 6; cp |= 0x800;
        case 2: str[1] = 0x80 | (cp & 0x3f); cp >>= 6; cp |= 0xc0;
        case 1: str[0] = static_cast<char>(cp);
        }
        return str;  // result in UTF-8 string
    }

    void Frtk_Search_Box::draw() {
        draw_nice_round_box(m_vg, { {m_x,m_y}, {m_w,m_h} }, m_cornerRadius, NORMAL_BORDER,
            glmToNVG(m_color),
            glmToNVG(m_bkg_color), true);

        //draw text :
        nvgFontSize(m_vg, m_font.fontSize);
        nvgFontFace(m_vg, m_font.fName.c_str());
        nvgFillColor(m_vg, m_font.forgColor);
        nvgTextAlign(m_vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(m_vg, m_x + m_font.fontSize / 2.0f + m_cornerRadius * .5f, m_y + m_font.fontSize, m_searchWords.c_str(), NULL);

        //  search icon drawing
        nvgFontSize(m_vg, m_font.fontSize + m_h * .5f);
        nvgFontFace(m_vg, "icons");
        nvgFillColor(m_vg, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f));
        nvgTextAlign(m_vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(m_vg, m_SearchIconPos.x, m_SearchIconPos.y, cpToUTF8(ICON_SEARCH).c_str(), NULL);

        //close icon drawing
        nvgFontSize(m_vg, m_font.fontSize + m_h * 0.5f);
        nvgFontFace(m_vg, "icons");
        nvgFillColor(m_vg, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f));
        nvgTextAlign(m_vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(m_vg, m_CloseIconPos.x, m_CloseIconPos.y, cpToUTF8(ICON_CIRCLED_CROSS).c_str(), NULL);

        draw_focus();
    }

    void Frtk_Search_Box::draw_focus() {
        if (!m_has_focus) 
            return;
        auto col = nvgRGBAf(0, 0.501f, 1.0f, FRTK_FOCUS_OPACITY_VALUE);
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_x + 0.5f, m_y + 0.5f, m_w - 1, m_h - 1, m_cornerRadius);
        nvgStrokeColor(m_vg, col);
        nvgStrokeWidth(m_vg, 2.0f);
        nvgStroke(m_vg);
    }
    void Frtk_Search_Box::draw_focus(BOX_TYPE t, float X, float Y, float W, float H) {
        if (!m_has_focus) return;
        FRTK_CORE_WARN("BOX_TYPE Is not supported by this widget");
        auto col = nvgRGBAf(0, 0.501f, 1.0f, 1.0f);
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, X + 0.5f, Y + 0.5f, W - 1, H - 1, m_cornerRadius);
        nvgStrokeColor(m_vg, col);
        nvgStrokeWidth(m_vg, 2.0f);
        nvgStroke(m_vg);
    }
    void Frtk_Search_Box::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) {
        if (!m_has_focus) return;
        FRTK_CORE_WARN("This FOCUS drawing is not supported, draw normal focus ");
        draw_focus();
    }

    int Frtk_Search_Box::value(const std::string& str)
    {
        m_searchWords = str;
        return 0;
    }
}