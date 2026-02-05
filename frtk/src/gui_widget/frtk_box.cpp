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

#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_draw.h>

// class constructor
namespace FR {
    Frtk_Box::Frtk_Box(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Widget(x, y, w, h, l, b), m_cellStyle(FR_PIC_LEFT_TO_TEXT), m_Text{ 0 } 
    {
        m_vg = vg;
        assert(vg != NULL);
        m_font.size.w = w;
        m_font.size.h = h;
        m_font.hAlign = NVG_ALIGN_LEFT;
        m_font.vAlign = NVG_ALIGN_MIDDLE;
        m_borderColor = glm::vec4(FR_BLACK);
       // applyStyle();
    }
    Frtk_Box::~Frtk_Box() {
    }
    void Frtk_Box::applyStyle() {
        // Set NanoVG font first
        nvgFontSize(m_vg, m_font.fontSize);
        nvgFontFace(m_vg, m_font.fName.c_str());

        // Measure text width
        float bounds[4];
        nvgTextBounds(m_vg, 0, 0, m_label.c_str(), nullptr, bounds);
        float textWidth = bounds[2] - bounds[0];

        // Measure text height (line height)
        float asc, desc, lineh;
        nvgTextMetrics(m_vg, &asc, &desc, &lineh);
        float textHeight = lineh;

        // Fill txtNatural
        m_Text.pos = { 0.0,0.0 };
        m_Text.size.w = textWidth;
        m_Text.size.h = textHeight;

        computeBoxLayout();
        m_font.pos = m_Text.pos;
        m_font.size = m_Text.size;
        
    }
    void Frtk_Box::draw()
    {
        //alwas check for all widgets
        if (!m_visible)
            return;
            draw_box(m_vg, m_boxType, m_dim,0.0f,NORMAL_BORDER,  nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a),nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
            drawLabel();
            if(m_IconTexture!=0)
                drawImage(m_x, m_y, m_w, m_h);
    }
    int Frtk_Box::handle(int e)
    {
        //Dose not do any events .. at least at the moment.
        return 0;
    }

    void Frtk_Box::computeBoxLayout()
    {
        if (!m_Image.image)
            return;

        const float paddingx = 10.f;
        const float paddingy = 5.0f;
        const float spacing = 5.f;

        const float contentX = m_x + paddingx;
        const float contentY = m_y + paddingy;
        const float contentW = m_w - 2.f * paddingx;
        const float contentH = m_h - 2.f * paddingy;

        // Image scaling
        if (m_Image.dim.size.w > 0.f && m_Image.dim.size.h > 0.f)
        {
            if (m_cellStyle <= FR_PIC_UNDER_TEXT_RIGHT)
            {
                // Vertical layouts
                float maxW = contentW;
                float maxH = contentH * 0.75f;
                m_Image.dim.size = scaleToFit(m_Image.dim.size, maxW, maxH);
            }
            else
            {
                // Horizontal layouts
                float maxW = contentW * 0.5f;
                float maxH = contentH;
                m_Image.dim.size = scaleToFit(m_Image.dim.size, maxW, maxH);
            }
        }


        float textX = contentX;
        float textY = contentY;
        float textW = contentW;
        float textH = contentH;

        switch (m_cellStyle)
        {
            // IMAGE OVER TEXT
        case FR_PIC_OVER_TEXT_CENTER:
        case FR_PIC_OVER_TEXT_LEFT:
        case FR_PIC_OVER_TEXT_RIGHT:
        {
            m_Image.dim.pos.y = contentY;

            if (m_cellStyle == FR_PIC_OVER_TEXT_LEFT)
                m_Image.dim.pos.x = contentX;
            else if (m_cellStyle == FR_PIC_OVER_TEXT_RIGHT)
                m_Image.dim.pos.x = contentX + contentW - m_Image.dim.size.w;
            else
                m_Image.dim.pos.x = contentX + (contentW - m_Image.dim.size.w) * 0.5f;

            textY = m_Image.dim.pos.y + m_Image.dim.size.h + spacing;
            textH = contentY + contentH - textY;
        } break;

        // IMAGE UNDER TEXT
        case FR_PIC_UNDER_TEXT_CENTER:
        case FR_PIC_UNDER_TEXT_LEFT:
        case FR_PIC_UNDER_TEXT_RIGHT:
        {
            m_Image.dim.pos.y = contentY + contentH - m_Image.dim.size.h;

            if (m_cellStyle == FR_PIC_UNDER_TEXT_LEFT)
                m_Image.dim.pos.x = contentX;
            else if (m_cellStyle == FR_PIC_UNDER_TEXT_RIGHT)
                m_Image.dim.pos.x = contentX + contentW - m_Image.dim.size.w;
            else
                m_Image.dim.pos.x = contentX + (contentW - m_Image.dim.size.w) * 0.5f;

            textH = m_Image.dim.pos.y - spacing - contentY;
        } break;

        // IMAGE LEFT OF TEXT 
        case FR_PIC_LEFT_TO_TEXT:
        {
            m_Image.dim.pos.x = contentX;
            m_Image.dim.pos.y = contentY + (contentH - m_Image.dim.size.h) * 0.5f;

            textX = m_Image.dim.pos.x + m_Image.dim.size.w + spacing;
            textW = contentX + contentW - textX;
        } break;

        // IMAGE RIGHT OF TEXT 
        case FR_PIC_RIGHT_TO_TEXT:
        {
            m_Image.dim.pos.x = contentX + contentW - m_Image.dim.size.w;
            m_Image.dim.pos.y = contentY + (contentH - m_Image.dim.size.h) * 0.5f;

            textW = m_Image.dim.pos.x - spacing - contentX;
        } break;
        }

        // Clamp text size
        textW = std::max(0.f, textW);
        textH = std::max(0.f, textH);

        // Final text layout
        m_Text.pos = { textX, textY };
        m_Text.size = { textW, textH };
    }


    void Frtk_Box::cellStyle(FRTK_PICTXT_STYLE StyleType)
    {
        m_cellStyle = StyleType;
        applyStyle();
        redraw();
    }
    int Frtk_Box::wdgImage(std::string path)
    {
        int result =Frtk_Widget::wdgImage(path);
        if (result < 0)
            return result;
            applyStyle();
        return 0;
    }
    int Frtk_Box::cellStyle() const
    {
        return m_cellStyle;
    }
    
}