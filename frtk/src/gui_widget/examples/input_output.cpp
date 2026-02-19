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
        
        auto window = std::make_shared<Frtk_Window>(500.f, 200.f, 500.f, 500.f, "Testing buttons, toolbars", FRTK_UP_BOX);

        std::shared_ptr<Frtk_Search_Box> input1 = std::make_shared<Frtk_Search_Box>(window->getContext(), 10.0f, 10.0f, 200.0f, 100.0f, "Search1", FRTK_UP_BOX);
        std::shared_ptr<Frtk_Input_Base> input2 = std::make_shared<Frtk_Input_Base>(window->getContext(), 10.0f, 120.0f, 300.0f, 50.0f, "Search2", FRTK_UP_BOX);
       // std::shared_ptr<Frtk_Input_Base> input3 = std::make_shared<Frtk_Input_Base>(window->getContext(), 210.0f, 10.0f, 200.0f, 25.0f, "Search3", FRTK_UP_BOX);
        input1->value("Please search1 for something");
        input2->value("Please search2 for something");
      //  input3->value("Please search3 ");
        window->addChild(input1);
        window->addChild(input2);
    //    window->addChild(input3);
         return window;
    }
}