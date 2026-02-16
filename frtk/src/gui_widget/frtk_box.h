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

#ifndef FRTK_BOX_H
#define FRTK_BOX_H

#include <frtk.h>
#include <fr_core.h>
#include <gui_widget/frtk_widget.h>

namespace FR {
    // Only Image alignment - text is aligned using font struct.
   

    class Frtk_Box : public Frtk_Widget
    {
    public:
        Frtk_Box(NVGcontext* vg, float x , float y , float w , float h , std::string l , BOX_TYPE = FRTK_UP_BOX);
        void applyStyle();

        void computeBoxLayout();


//        void cellStyle(FRTK_PICTXT_STYLE style);
        virtual int wdgImage(std::string path, std::optional<glm::vec4> tint = std::nullopt) override;
        virtual int wdgImage(const std::vector<uint8_t>& pngData, std::optional<glm::vec4> tint = std::nullopt)override;
    protected:
        Dim_float_t m_Text;
        float m_padding ;
        float m_specialDrawingSize;

        virtual void draw() override;
        virtual int  handle(int e) override;

        inline float centerX(float w) { return (m_x + (m_w - w) * 0.5f); }
        inline float centerY(float h) { return (m_y + (m_h - h) * 0.5f); }

        inline float leftX() { return (m_x + m_padding +   m_specialDrawingSize); }
        inline float rightX(float w) { return (m_x + m_w - m_specialDrawingSize-m_padding - w); }
        inline float topY() { return m_y + m_padding; }
        inline float bottomY(float h) { return (m_y + m_h - m_padding  - h); }

        //Never scale up as that causes issue. user should use bigger image/icon.
        inline dimSize_float_t scaleToFit(dimSize_float_t src,
            float maxW, float maxH)
        {
            if (src.w <= 0.f || src.h <= 0.f)
                return src;
            float rw = maxW / src.w;
            float rh = maxH / src.h;
            float r = std::min(rw, rh);
            r = std::min(r, 1.0f);
            return { src.w * r, src.h * r };
        }

    };
}
#endif // FL_CELL_H