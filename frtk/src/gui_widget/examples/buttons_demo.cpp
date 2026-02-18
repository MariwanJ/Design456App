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

#include<gui_widget/examples/buttons_demo.h>

#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_button.h>

#include <gui_widget/frtk_check_button.h>
#include <gui_widget/frtk_light_button.h>
#include <gui_widget/frtk_switch_button.h>

#include <gui_widget/frtk_repeat_button.h>
#include <gui_widget/frtk_return_button.h>
#include <gui_widget/frtk_round_button.h>
#include <gui_widget/frtk_toggle_light_button.h>
#include <gui_widget/frtk_toggle_round_button.h>
#include <gui_widget/frtk_toolbar_button.h>

#include <gui_widget/frtk_toolbar.h>
#include <gui_widget/frtk_widget.h>


namespace FR {
    void doCallback(size_t index) {
        FRTK_CORE_INFO("BUTTON WITH INDEX {} pressed", index);
    }

    std::shared_ptr<Frtk_Window> runFRTKdemo() {
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







        float counter = 0.f;
        //int i = 0;
        auto window = std::make_shared<Frtk_Window>(500.f, 200.f, 500.f, 500.f, "Testing buttons, toolbars",FRTK_UP_BOX);
        //frtk_check_button
        //frtk_light_button
        //frtk_repeat_button
        //frtk_return_button
        //frtk_round_button
        //frtk_toggle_light_button
        //frtk_toggle_round_button
        //frtk_toolbar_button
        
        std::string iconPath1 =EXE_CURRENT_DIR + "/resources/icons/32x32/";
        std::string imagePath1 = EXE_CURRENT_DIR + "/resources/icons/32x32/House-32x32.png";
        
        std::vector<toolbBTN_t> tools = {
            // std::string lbl; std::string name; dimSize_float_t size; std::string icon; Frtk_Widget::Callback callback_; std::string tooltips !!
            {"New","New"   ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath1 + "Folder-Create-32x32.png",[](Frtk_Widget* w)    { (void)w; doCallback(0); }, ""},
            {"Open","Open"  ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath1 + "Folder-Import-32x32.png", [](Frtk_Widget* w)  { (void)w; doCallback(1); }, ""},
            {"Close","Close" ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath1 + "Folder-Close-32x32.png" , [](Frtk_Widget* w) { (void)w; doCallback(2); }, ""},
        };

        std::shared_ptr<Frtk_ToolBar> tb1=std::make_shared<Frtk_ToolBar>(window->getContext(), 0.f, 350.0f, window->w(), FRTK_TOOLBAR_HEIGHT, "Toolbar1", tools);
        std::shared_ptr<Frtk_ToolBar> tb2 = std::make_shared<Frtk_ToolBar>(window->getContext(),350.f, 0.0f, FRTK_TOOLBAR_HEIGHT, window->h(), "Toolbar2", tools,false);
        tb1->parent(window.get());
        window->addChild(tb1);

        tb2->parent(window.get());
        window->addChild(tb2);

        float xx, yy, ww, hh;
        xx = 10.0f;
        yy = 0.f;
        ww = 80.f;
        hh = FRTK_ICON_SIZE.y;

        std::shared_ptr<Frtk_Check_Button>b1 = std::make_shared<Frtk_Check_Button>(window->getContext(), xx + ww * counter + 10.0f, yy, ww, hh, "CHECK");
        counter++;
        b1->wdgImage(imagePath1);
        window->addChild(b1);

        std::shared_ptr<Frtk_Light_Button>b2 = std::make_shared<Frtk_Light_Button>(window->getContext(), xx + ww * counter + 10.0f, yy, ww, hh, std::to_string(counter));
        b2->wdgImage(imagePath1);
        counter++;
        window->addChild(b2);
        std::shared_ptr<Frtk_Repeat_Button>b3 = std::make_shared<Frtk_Repeat_Button>(window->getContext(), xx + ww * counter + 10.0f, yy, ww, hh, std::to_string(counter), FRTK_DIAMOND_UP_BOX);
        counter++;
        window->addChild(b3);
        b3->wdgImage(imagePath1);
        std::shared_ptr<Frtk_Return_Button>b4 = std::make_shared<Frtk_Return_Button>(window->getContext(), xx + ww * counter + 10.0f, yy, ww, hh, std::to_string(counter));
        counter++;
        window->addChild(b4);

        counter = 0;
        std::shared_ptr<Frtk_Round_Button>b5 = std::make_shared<Frtk_Round_Button>(window->getContext(), xx + counter , yy + 60.f, ww, hh, std::to_string(counter));      
        b5->wdgImage(imagePath1);
        window->addChild(b5);
        counter+=ww+10.0f;
        std::shared_ptr<Frtk_Toggle_Light_Button>b6 = std::make_shared<Frtk_Toggle_Light_Button>(window->getContext(), xx + counter , yy + 60.f, ww, hh, std::to_string(counter));

        b6->wdgImage(imagePath1);
        window->addChild(b6);
        counter += ww + 10.0f;
        std::shared_ptr<Frtk_Toggle_Round_Button>b7 = std::make_shared<Frtk_Toggle_Round_Button>(window->getContext(), xx + counter , yy + 60.f, ww, hh, std::to_string(counter));
        
        b7->wdgImage(imagePath1);
        window->addChild(b7);
        counter += ww + 10.0f;
        std::shared_ptr<Frtk_ToolBar_Button>b8 = std::make_shared<Frtk_ToolBar_Button>(window->getContext(), xx + counter , yy + 60.f, FRTK_TOOLBAR_BUTTON_HEGHT, FRTK_TOOLBAR_BUTTON_HEGHT, "");
        b8->wdgImage(imagePath1);
        window->addChild(b8);

        counter = 0;
        std::shared_ptr<Frtk_Switch_Button>b9 = std::make_shared<Frtk_Switch_Button>(window->getContext(), xx + ww * counter + 10.0f, yy + 120.f, ww, hh, std::to_string(counter));
        b9->wdgImage(imagePath1);
        window->addChild(b9);
        counter++;

        return window;
    }
}