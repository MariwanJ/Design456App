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

#include <gui_widget/examples/toolbarExample.h>

namespace FR {
    void doAnotherCallback(size_t index) {
        FRTK_CORE_INFO("BUTTON WITH INDEX {} pressed", index);
    }

    std::shared_ptr<Frtk_ToolBarWin> runFRTKToolbarDemo() {



        std::string iconPath = EXE_CURRENT_DIR + "/resources/icons/32x32/";
        std::string imagePath = EXE_CURRENT_DIR + "/resources/icons/32x32/House-32x32.png";
        

        std::vector<toolbBTN_t> tools = {
            // std::string lbl; std::string name; dimSize_float_t size; std::string icon; Frtk_Widget::Callback callback_; std::string tooltips !!
            {"New","New"   ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Create-32x32.png",[](Frtk_Widget* w) { doAnotherCallback(0); },   FRTK_UP_BOX, ""},
            {"Open","Open"  ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Import-32x32.png", [](Frtk_Widget* w) { doAnotherCallback(1); }, FRTK_UP_BOX, ""},
            {"Close","Close" ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Close-32x32.png" , [](Frtk_Widget* w) { doAnotherCallback(2); },FRTK_UP_BOX, ""},
        };
        
        
        std::shared_ptr<Frtk_ToolBarWin> tb1=std::make_shared<Frtk_ToolBarWin>( 450.f, 300.0f,350, FRTK_TOOLBAR_HEIGHT, "", tools,true);
        
        return tb1;
    }
}