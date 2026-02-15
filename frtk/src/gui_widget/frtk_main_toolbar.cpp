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

#include <gui_widget/frtk_main_toolbar.h>

namespace FR {
    void mainToolbar_callback(size_t index) {
        std::shared_ptr<Fr_Window> win = Fr_Window::getFr_Window();
        switch (index) {
        case FR_FILE_NEW: {
        } break;
        case FR_FILE_OPEN: {
            std::shared_ptr<fileDialog> dialog = std::make_shared<fileDialog>(EXE_CURRENT_DIR + "/resources/mesh/");
            std::string result = dialog->openFile();
            if (result.empty())
            {
                return;
            }
            else {
                win->activeScene->add3DObject(result);
            }
        } break;
        case FR_FILE_CLOSE: {
        } break;
        case FR_FILE_SAVE: {
        } break;
        case FR_FILE_SAVEAS: {
        } break;
        case FR_FILE_IMPORT: {
        } break;
        case FR_FILE_EXPORT: {
        } break;
        case FR_EDIT_COPY: {
        } break;
        case FR_EDIT_CUT: {
        } break;
        case FR_EDIT_DUPLICATE: {
        } break;
        case FR_EDIT_PASTE: {
        } break;
        }
    }

    std::shared_ptr<Frtk_ToolBarWin> createMainToolbar() {
        std::vector<toolbBTN_t> tools = {
            // std::string lbl; std::string name; dimSize_float_t size; std::string icon; Frtk_Widget::Callback callback_; std::string tooltips !!
            {"New","New"   ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Create-32x32.png",[](Frtk_Widget* w) { mainToolbar_callback(FR_FILE_NEW); }, ""},
            {"Open","Open"  ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Import-32x32.png", [](Frtk_Widget* w) { mainToolbar_callback(FR_FILE_OPEN); }, ""},
            {"Close","Close" ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Close-32x32.png" , [](Frtk_Widget* w) { mainToolbar_callback(FR_FILE_CLOSE); }, ""},
            {"Save","Save" ,{FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},iconPath + "Folder-Close-32x32.png" , [](Frtk_Widget* w) { mainToolbar_callback(FR_FILE_CLOSE); }, ""},
        };
        
        
        std::shared_ptr<Frtk_ToolBarWin> tb1=std::make_shared<Frtk_ToolBarWin>( 450.f, 300.0f,350, FRTK_TOOLBAR_HEIGHT, "", tools,true);
        
        return tb1;
    }
}