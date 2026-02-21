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

#include<gui_widget/examples/demo2.h>

#include <gui_widget/frtk_search_box.h>
#include <gui_widget/frtk_input_base.h>
namespace FR {

    std::shared_ptr<Frtk_Window> runInputOutput() {
        
        auto window = std::make_shared<Frtk_Window>(500.f, 200.f, 700.f, 700.f, "Testing buttons, toolbars", FRTK_UP_BOX);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                auto input = std::make_shared<Frtk_Input_Base>(window->getContext(), 50.0f + j * 160.0f, 30.0f + i * 70.0f, 150.0f, 50.0f,"TESTIT", FRTK_UP_BOX);

                switch (i * 3 + j)
                {
                case 0: input->lblAlign(NVG_ALIGN_TOP_LEFT);      input->value("top - left"); break;
                case 1: input->lblAlign(NVG_ALIGN_TOP_CENTER);    input->value("top - center"); break;
                case 2: input->lblAlign(NVG_ALIGN_TOP_RIGHT);     input->value("top - right"); break;

                case 3: input->lblAlign(NVG_ALIGN_MIDDLE_LEFT);   input->value("MIDDLE - left"); break;
                case 4: input->lblAlign(NVG_ALIGN_MIDDLE_CENTER); input->value("MIDDLE - center"); break;
                case 5: input->lblAlign(NVG_ALIGN_MIDDLE_RIGHT);  input->value("MIDDLE - right"); break;

                case 6: input->lblAlign(NVG_ALIGN_BOTTOM_LEFT);   input->value("BOTTOM - left"); break;
                case 7: input->lblAlign(NVG_ALIGN_BOTTOM_CENTER); input->value("BOTTOM - center"); break;
                case 8: input->lblAlign(NVG_ALIGN_BOTTOM_RIGHT);  input->value("BOTTOM - right"); break;
                }

                input->txtAlign(NVG_ALIGN_MIDDLE_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);
                window->addChild(input);
            }

        
    //    window->addChild(input3);
         return window;
    }
}