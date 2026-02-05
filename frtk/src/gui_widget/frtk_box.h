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
    typedef enum FRTK_PICTXT_STYLE             
    {	// align() values                                               
        // picture Over Text and (Center, Left & Right)                 
        /*
                L   C   R
                v   v   v
                .........
        */
        FR_PIC_OVER_TEXT_CENTER = 0,
        FR_PIC_OVER_TEXT_LEFT   = 1,
        FR_PIC_OVER_TEXT_RIGHT  = 2,

        /*
        L   C   R
        .........
        ^   ^   ^     <
        */

        // picture Under Text and (Center,  Left & Right)
        FR_PIC_UNDER_TEXT_CENTER  = 3,
        FR_PIC_UNDER_TEXT_LEFT    = 4,
        FR_PIC_UNDER_TEXT_RIGHT   = 5,

        // picture Left To Text and (Center,Left & Right)
        FR_PIC_LEFT_TO_TEXT        = 6,
        // picture Right To Text and (Center, Left & Right)
        FR_PIC_RIGHT_TO_TEXT       = 7
    };

   class Frtk_Box : public Frtk_Widget
    {
    public:
         Frtk_Box(NVGcontext* vg, float x, float y, float w, float h, std::string l="", BOX_TYPE=FRTK_UP_BOX);
        ~Frtk_Box();
        void applyStyle();
        virtual void draw() override;
        virtual int  handle(int e) override;
        void computeBoxLayout();

        int cellStyle() const;
        void cellStyle(FRTK_PICTXT_STYLE style);
        virtual int wdgImage(std::string path) override;
    protected:

        inline float centerX(float w) { return m_x + (m_w - w) * 0.5f; }
        inline float centerY(float h) { return m_y + (m_h - h) * 0.5f; }

        inline float leftX() { return m_x + padding; }
        inline float rightX(float w) { return m_x + m_w - padding - w; }

        inline float topY() { return m_y + padding; }
        inline float bottomY(float h) { return m_y + m_h - padding - h; }

        inline dimSize_float_t scaleToFit(dimSize_float_t src, float maxW, float maxH)
        {
            float rh, rw,r;
            rh = rw = r=0.0f;
            if (src.w !=0 && src.h !=0){
                rw = maxW / src.w;
                rh = maxH / src.h;
                r = (rw < rh) ? rw : rh;
            }
            dimSize_float_t out;
            out.w = src.w * r;
            out.h = src.h * r;
            return out;
        }
        Dim_float_t m_Text;

        FRTK_PICTXT_STYLE  m_cellStyle;
        const float padding = 6.0f;
        const float spacing = 4.0f;
   };
}
#endif // FL_CELL_H