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

#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_button.h>
#include <gui_widget/frtk_toolbar.h>
#include <gui_widget/frtk_toolbar_button.h>
#include <gui_widget/frtk_check_button.h>
namespace FR {
    std::shared_ptr<Frtk_Window> runFRTKdemo2() {
        /*
          boxtypes:
          =========
                FRTK_NO_BOX = 0,
                FRTK_FLAT_BOX,
                FRTK_DOWN_BOX,
                FRTK_UP_BOX,
                FRTK_UP_FRAME,
                FRTK_DOWN_FRAME,
                FRTK_THIN_UP_BOX,
                FRTK_THIN_DOWN_BOX,
                FRTK_THIN_UP_FRAME,
                FRTK_THIN_DOWN_FRAME,

                FRTK_ROUNDED_BOX,
                FRTK_RSHADOW_BOX,
                FRTK_ROUNDED_FRAME,
                FRTK_RFLAT_BOX,
                FRTK_ROUND_UP_BOX,
                FRTK_ROUND_DOWN_BOX,
                FRTK_DIAMOND_UP_BOX,
                FRTK_DIAMOND_DOWN_BOX,
                FRTK_OVAL_BOX,
                FRTK_OSHADOW_BOX,
                FRTK_OVAL_FRAME,
                FRTK_OVALFLAT_BOX,

        */
        auto window = std::make_shared<Frtk_Window>(500.f, 200.f, 500.f, 500.f, "Testing Buttons");
        std::shared_ptr<Frtk_Box> box;
        std::string imagePath = EXE_CURRENT_DIR + "/resources/icons/32x32/House-32x32.png";

        float FF, NN;
        FF = NN = 40;
        //float next = FF + 5;
        std::shared_ptr<Frtk_Check_Button> button2 = std::make_shared<Frtk_Check_Button>(window->getContext(), 10.0f, 50.0f, 200.0f, 56.0f, "button244", FRTK_UP_BOX);
        std::shared_ptr<Frtk_Button> button3       = std::make_shared<Frtk_Button>(window->getContext(), 10.0f, 150.0f, 200.0f, 56.0f, "button3", FRTK_UP_BOX);
        std::shared_ptr<Frtk_Button> button1       = std::make_shared<Frtk_Button>(window->getContext(), 10.0f, 250.0f, 200.0f, 56.0f, "demo2 button1", FRTK_UP_BOX);


        std::shared_ptr<Frtk_Button> button11 = std::make_shared<Frtk_Button>(window->getContext(), 250.0f, 250.0f, 200.0f, 56.0f, "button4", FRTK_UP_BOX);
        std::shared_ptr<Frtk_Button> button22 = std::make_shared<Frtk_Button>(window->getContext(), 250.0f, 50.0f, 200.0f, 56.0f,  "button5", FRTK_UP_BOX);
        std::shared_ptr<Frtk_Button> button33 = std::make_shared<Frtk_Button>(window->getContext(), 250.0f, 150.0f, 200.0f, 56.0f, "button6", FRTK_UP_BOX);

        button1->wdgImage(imagePath);
         button2->wdgImage(imagePath);
        button3->wdgImage(imagePath);
        button11->wdgImage(imagePath);
        button22->wdgImage(imagePath);
        button33->wdgImage(imagePath);

        button1->cellStyle(FR_IMG_OVER_TEXT_RIGHT);
        button2->cellStyle(FR_IMG_OVER_TEXT_CENTER);
        button3->cellStyle(FR_IMG_OVER_TEXT_LEFT);

        button11->cellStyle(FR_IMG_UNDER_TEXT_RIGHT);
        button22->cellStyle(FR_IMG_UNDER_TEXT_CENTER);
        button33->cellStyle(FR_IMG_UNDER_TEXT_LEFT);


        window->addChild(button1);
        window->addChild(button2);
        window->addChild(button3);

        window->addChild(button11);
        window->addChild(button22);
        window->addChild(button33);

       //static int counter = 1;
       //for (int i = 1; i < 4; i++){
       // 
       //     for (int j=0;j<9;j++)
       //     {
       //         std::string str= std::to_string(counter);
       //         box = std::make_shared<Frtk_Box>(window->getContext(), next*j, i * next, FF, NN, str, (BOX_TYPE)counter);
       //         window->addChild(box);
       //         counter++;
       //     }
       // } 
       //
         return window;
    }
}