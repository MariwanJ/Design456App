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

#ifndef FRTK_FRTK_COLOR_PICKER_H
#define FRTK_FRTK_COLOR_PICKER_H

#include <frtk.h>
#include <fr_core.h>
#include <gui_widget/frtk_box.h>

namespace FR {
    typedef struct {
        float c, m, y, k;
    }CMYK_t;

    typedef struct {
        float h, s, v;
    } HSV_t;

    class FRTK_API  Frtk_Color_Picker : public Frtk_Box {
        typedef struct {
            float ax;
            float ay;
            float bx;
            float by;
            Dim_float_t center;
        } triang_t;

    public:
        Frtk_Color_Picker(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b);
        glm::vec4 pickedColorRGBA();
        HSV_t pickedColorHSV();
        CMYK_t pickedColorCMYK();
        NVGcolor  pickedColorNVG();

        void draw_pad_cursor();

        void drawOuterCircleColorPad();

        void draw_colPad();

        void baseTriangle();

        float pickerDeg();

        void updateMousePos();

    protected:
        void pickerInsideTriangle();
        virtual void draw() override;
        virtual int handle(int ev) override;
        glm::vec4 colorFromTriangle();

        bool insideColorPad();
        bool insideTriangle();
        float m_pickerDeg;
        glm::vec4 m_picked;
        Dim_float_t m_baseDim;
        Dim_float_t m_pickerDim;
        circle_posRadius_t m_Tripicker;
        triang_t triangelDim;
        float m_padWidt;
        bool m_Tdraggin;
        bool m_Cdraggin;
        float r;
    };
}
#endif //FRTK_FRTK_COLOR_PICKER_H