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

#include<gui_widget/examples/demo3.h>
#include <gui_widget/frtk_slider.h>
#include <gui_widget/frtk_color_picker.h>
namespace FR {
    //Default callback function.Replace with your custom callback.Arguments are possible.
    static void pickcolor(Frtk_Widget& w, Frtk_Widget& win) {
        auto* wid = dynamic_cast<Frtk_Color_Picker*>(&w);
        glm::vec4 col = wid->pickedColorRGBA();
        FRTK_CORE_INFO("{} {} {} {}", col.r, col.g, col.b, col.a);
        win.color(col);
    }

    std::shared_ptr<Frtk_Vwin> runFRTKdemo3() {
        auto window = std::make_shared<Frtk_Vwin>(500.f, 200.f, 500.f, 500.f, "Testing new Widgets");
        std::shared_ptr<Frtk_Slider> sliderH = std::make_shared<Frtk_Slider>(window->getContext(), 250.0f, 175.0f, 200.0f, 56.0f, "SLIDER- H", FRTK_OSHADOW_DOWN_BOX);

        //  sliderH->stepSize(10.0f);
        sliderH->sliderType(H_SLIDER);
        window->addChild(sliderH);

        std::shared_ptr<Frtk_Slider> sliderV = std::make_shared<Frtk_Slider>(window->getContext(), 200.0f, 250.0f, 56.0f, 200.0f, "SLIDER - V", FRTK_UP_BOX);
        sliderV->sliderType(V_SLIDER);
        // sliderV->stepSize(5.0f);
        window->addChild(sliderV);

        std::shared_ptr<Frtk_Color_Picker> col = std::make_shared<Frtk_Color_Picker>(window->getContext(), 40.0f, 40.0f, 200.0f, 200.0f, "colorPicker", FRTK_UP_BOX);
        col->set_callback([window](Frtk_Widget& w) { pickcolor(w, *window);});
        
        window->addChild(col);
        return window;
            }
    }