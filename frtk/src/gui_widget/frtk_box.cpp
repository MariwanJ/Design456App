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
        Frtk_Widget(x, y, w, h, l, b),  m_Text{ 0 },
        m_specialDrawingSize( 0.f), m_padding(2.0f)
    {
        m_vg = vg;
        assert(vg != NULL);
        m_font.size.w = w;
        m_font.size.h = h;
        m_font.hAlign = NVG_ALIGN_LEFT;
        m_font.vAlign = NVG_ALIGN_MIDDLE;
        m_borderColor = glm::vec4(FR_BLACK);
    }
    void Frtk_Box::applyStyle() {
        nvgFontSize(m_vg, m_font.fontSize);
        nvgFontFace(m_vg, m_font.fName.c_str());
        float bounds[4] = { 0.0f };
        nvgTextBounds(m_vg, 0, 0, m_label.c_str(), nullptr, bounds);
        float textWidth = bounds[2] - bounds[0];

        float asc, desc, lineh;
        nvgTextMetrics(m_vg, &asc, &desc, &lineh);
        float textHeight = lineh;

        m_Text.pos = { 0.0,0.0 };
        m_Text.size.w = textWidth;
        m_Text.size.h = textHeight;

        computeBoxLayout();
        m_font.pos = m_Text.pos;
        m_font.size = m_Text.size;
    }
    void Frtk_Box::draw()
    {
        //always check for all widgets
        if (!m_visible)
            return;
        draw_box(m_vg, m_boxType, {{ m_x,m_y }, { m_w,m_h }}, 0.0f, NORMAL_BORDER, 
            glmToNVG(m_color), 
            glmToNVG(m_borderColor), true);
        drawLabel();
        if (m_IconTexture != 0) {
            drawImage(m_x, m_y, m_w, m_h);
        }
        else {
            applyStyle(); //We still need to apply style
        }
    }
    int Frtk_Box::handle(int e)
    {
        //just as a reminder YOU SHOULD ALWAYS RUN THIS CHECK: 
       //  if (!m_active || !m_visible) return 0; //inactive widget - we don't care 
        
         //Does not handle any events... at least not at the moment
         return 0;
    }

    void Frtk_Box::computeBoxLayout()
    {
        //if (!m_Image.image)
        //    return;
        float paddingX = 4.f;
        float paddingY = 4.f;
        const float spacing = 4.0f;
        paddingX = m_padding ;

        const float origin_startX = m_x + m_padding;
        const float origin_startY = m_y + paddingY;
        const float origin_maxW = m_w - 2.f * paddingX;
        const float origin_maxH = m_h - 2.f * paddingY;

        dimSize_float_t iconSize = m_Image.dim.size;
        if (iconSize.w > 0.f && iconSize.h > 0.f)
        {
            float maxW = origin_maxW;
            float maxH = origin_maxH;

            if (m_cellStyle == FR_IMG_LEFT_TO_TEXT || m_cellStyle == FR_IMG_RIGHT_TO_TEXT)
                maxW = origin_maxW - m_Image.dim.size.w + paddingX * 2;
            else if (m_cellStyle <= FR_IMG_UNDER_TEXT_RIGHT)
                maxH = origin_maxH * 0.5f;
            iconSize = scaleToFit(iconSize, origin_maxW, maxH);
        }

        float textX = origin_startX;
        float textY = origin_startY;
        float textW = origin_maxW;
        float textH = origin_maxH;

        switch (m_cellStyle)
        {
        case FR_IMG_OVER_TEXT_CENTER:
        case FR_IMG_OVER_TEXT_LEFT:
        case FR_IMG_OVER_TEXT_RIGHT:
        {
            m_Image.dim.pos.y = origin_startY;
            if (m_cellStyle == FR_IMG_OVER_TEXT_LEFT)
                m_Image.dim.pos.x = origin_startX;
            else if (m_cellStyle == FR_IMG_OVER_TEXT_RIGHT)
                m_Image.dim.pos.x = origin_startX + origin_maxW - iconSize.w;
            else
                m_Image.dim.pos.x = origin_startX + (origin_maxW - iconSize.w) * 0.5f;

            m_Image.dim.size = iconSize;

            textY = m_Image.dim.pos.y + iconSize.h + spacing;
            textH = origin_startY + origin_maxH - textY;
        } break;

        case FR_IMG_UNDER_TEXT_CENTER:
        case FR_IMG_UNDER_TEXT_LEFT:
        case FR_IMG_UNDER_TEXT_RIGHT:
        {
            m_Image.dim.pos.y = origin_startY + origin_maxH - iconSize.h;

            if (m_cellStyle == FR_IMG_UNDER_TEXT_LEFT)
                m_Image.dim.pos.x = origin_startX;
            else if (m_cellStyle == FR_IMG_UNDER_TEXT_RIGHT)
                m_Image.dim.pos.x = origin_startX + origin_maxW - iconSize.w;
            else
                m_Image.dim.pos.x = origin_startX + (origin_maxW - iconSize.w) * 0.5f;

            m_Image.dim.size = iconSize;

            textH = m_Image.dim.pos.y - spacing - origin_startY;
        } break;

        case FR_IMG_LEFT_TO_TEXT:
        {
            
            m_Image.dim.pos.x = origin_startX + spacing + m_specialDrawingSize;
            m_Image.dim.pos.y = origin_startY + (origin_maxH - iconSize.h) * 0.5f;
            m_Image.dim.size = iconSize;
            textX = m_Image.dim.pos.x  + spacing+ m_specialDrawingSize;
            textW = origin_startX + origin_maxW - textX;
        } break;

        case FR_IMG_RIGHT_TO_TEXT:
        {
            
            m_Image.dim.pos.x = m_x + m_w - paddingX - iconSize.w ;
            m_Image.dim.pos.y = origin_startY + (origin_maxH - iconSize.h) * 0.5f;
            m_Image.dim.size = iconSize;
            textW = m_Image.dim.pos.x - spacing - origin_startX- m_specialDrawingSize;
            textX = textX + m_specialDrawingSize+m_padding;
            
        } break;
        }

        textW = std::max(0.f, textW);
        textH = std::max(0.f, textH);

        m_Text.pos = { textX, textY };
        m_Text.size = { textW, textH };
    }

    int Frtk_Box::wdgImage(std::string path, std::optional<glm::vec4> tint)
    {
        int result = Frtk_Widget::wdgImage(path, tint);
        if (result < 0)
            return result;
        applyStyle();
        return 0;
    }
    int Frtk_Box::wdgImage(const std::vector<uint8_t>& pngData, std::optional<glm::vec4> tint)
    {
        int result = Frtk_Widget::wdgImage(pngData, tint);
        if (result < 0)
            return result;
        applyStyle();
        return 0;
    }

}