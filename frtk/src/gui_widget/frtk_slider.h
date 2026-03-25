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

#ifndef FRTK_SLIDER_H
#define FRTK_SLIDER_H

#include <frtk.h>
#include <fr_core.h>
#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_draw.h>

typedef struct {
    float min;
    float max;
}range_t;

typedef struct {
    glm::vec4 nob;
    glm::vec4 inner;
    glm::vec4 shadow;
    glm::vec4 track;
}nobcolor_t;

typedef enum {
    V_SLIDER,
    H_SLIDER,
} slidertype_t;
namespace FR {

    class FRTK_API Frtk_Slider : public Frtk_Box {
    public:
        Frtk_Slider(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl = "Tab", BOX_TYPE b = FRTK_DOWN_BOX);
        ~Frtk_Slider();
        
        nobcolor_t m_nobColor;
        float value()const; 
        void vlaue(const float &v);
        void setRange(const range_t range);
        range_t Range() const;
        bool isMouseInsideSliderBar();
        void sliderType(const slidertype_t &t);
    protected:
        virtual int handle(int ev) override;
        virtual void draw() override;
        slidertype_t m_sliderType;
        range_t m_highlight;
        range_t m_range;
        float m_value;
        float m_speedFactor;
    };
}

#endif // FRTK_SLIDER_H