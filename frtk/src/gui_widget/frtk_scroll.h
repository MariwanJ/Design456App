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

#ifndef FRTK_SCROLL_H
#define FRTK_SCROLL_H
#include <gui_widget/frtk_grpwidget.h>

namespace FR {
    typedef struct {
        bool btnUp;
        bool btnDown;
        bool btnLeft;
        bool btnRight;
    } btnEvent;

    typedef struct {
        Dim_float_t track;
        Dim_float_t scroll;

        Dim_float_t bnUp;
        Dim_float_t bnDown;
        Dim_float_t bnLeft;
        Dim_float_t bnRight;
        
        glm::vec4 btnColor;
        glm::vec4 trackColor;
        dimPos_float_t m_scrolloffset;
        bool m_dragVscroll;
        bool m_dragHscroll;
        float m_sensitivity;
        bool m_Vscroll_visible;
        bool m_Hscroll_visible;
        btnEvent event;
    } scroll_t;

    class FRTK_API Frtk_Scroll : public Frtk_GrpWidget {
    public:
        Frtk_Scroll(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl = "Tab", BOX_TYPE b = FRTK_DOWN_BOX);

        void updateScrollGeometry();

    protected:
        virtual bool isBtnPressed(uint8_t btnInd);
        virtual int handle(int ev) override;
        virtual void draw() override;
        virtual void draw_scroll(); 
        dimSize_float_t getTotalViewPortDim() const;

        bool btnUpDownLeft;
        bool btnDownDownRight;
        
        Dim_float_t m_viewPort;             //(x,y,w,h)
        Dim_float_t m_content;             //(x,y,w,h)
        scroll_t m_scrollwdg;
    };
}

#endif //FRTK_SCROLL_H