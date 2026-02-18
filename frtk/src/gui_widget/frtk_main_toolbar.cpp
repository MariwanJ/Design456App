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
#include <gui_widget/Frtk_ToolBarWin.h>
#include <fr_file_dialog.h>
#include <fr_window.h>

namespace FR {
/*
                        TOOLBARS CALLBACKS

*/
    void Fr_Window::mainToolbar_callback(size_t index, void* data) {
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

    void Fr_Window::selectionToolbar_callback(size_t index, void* data) {
        std::shared_ptr<Fr_Window> win = Fr_Window::getFr_Window();
        FRTK_CORE_APP_ASSERT(win);
        switch (index) {
        case FR_SELECTION_MESH: {
            m_currentSelMode = SelectionMode::MESH;
            win->mnuSelMesh_cb(nullptr);
        } break;
        case FR_SELECTION_FACE: {
            m_currentSelMode = SelectionMode::FACE;
            win->mnuSelFace_cb(nullptr);
        } break;
        case FR_SELECTION_EDGE: {
            m_currentSelMode = SelectionMode::EDGE;
            win->mnuSelEdges_cb(nullptr);
        } break;
        case FR_SELECTION_VERTEX: {
            m_currentSelMode = SelectionMode::VERTEX;
            win->mnuSelVertex_cb(nullptr);
        } break;
        default: {
            m_currentSelMode = SelectionMode::MESH;
            win->mnuSelMesh_cb(nullptr);
        }
        }
    }
    //********************************************************************************************************************************************

    /*
                        TOOLBARS DEFINITIONS

*/

    std::shared_ptr<Frtk_ToolBarWin> Fr_Window::createMainToolbar() {
        std::vector<toolbBTN_t> tools1 = {
        {"New",                                                                         // std::string lbl
        "New",                                                                          //std::string name
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},                          //dimSize_float_t size
        iconPath + "Folder-Create-32x32.png",                                           //std::string icon
        [this](Frtk_Widget* w) { this->mainToolbar_callback(FR_FILE_NEW); },            //Frtk_Widget::Callback callback_
        FRTK_UP_BOX,                                                                    //WIDGTYPE boxType
        "",                                                                             //std::string tooltips;  //not implemented y
        },
        { "Open",
         "Open",
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},
        iconPath + "Folder-Open-32x32.png",
        [this](Frtk_Widget* w) { this->mainToolbar_callback(FR_FILE_OPEN); },
        FRTK_UP_BOX,
        "" },
        { "Close",
         "Close",
         {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},
         iconPath + "Folder-Close-32x32.png",
         [this](Frtk_Widget* w) { this->mainToolbar_callback(FR_FILE_CLOSE); },
         FRTK_UP_BOX,
         "" },
        { "Save",
        "Save",
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},
        iconPath + "Save-32x32.png",
        [this](Frtk_Widget* w) { this->mainToolbar_callback(FR_FILE_CLOSE); },
        FRTK_UP_BOX,
        "" },
    };
        std::shared_ptr<Frtk_ToolBarWin>tb1=std::make_shared<Frtk_ToolBarWin>(0.0f, y() + menuHeight(), 350, FRTK_TOOLBAR_HEIGHT, "", tools1, true);
        tb1->widgetType(FRTK_TOOLBARWIN);
        return tb1;
}

std::shared_ptr<Frtk_ToolBarWin> Fr_Window::createSelectionToolbar() {
    std::vector<toolbBTN_t> tools2 = {
        {"",                                                                                                // std::string lbl
        "Mesh",                                                                                             //std::string name
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},                                              //dimSize_float_t size
        iconPath + "SelectionModeBody.png",                                                                 //std::string icon
        [this](Frtk_Widget* w) { this->selectionToolbar_callback(FR_SELECTION_MESH); },                     //Frtk_Widget::Callback callback_
        FRTK_FLAT_BOX,                                                                                      //BOX_TYPE boxType
        ""},                                                                                                //std::string tooltips;  //not implemented y
        {"",
        "Face",
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},
        iconPath + "SelectionModeFace.png",
        [this](Frtk_Widget* w) { this->selectionToolbar_callback(FR_SELECTION_FACE); }, 
        FRTK_FLAT_BOX, 
        ""},
        {"",
        "Edge",
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},
        iconPath + "SelectionModeEdges.png", 
        [this](Frtk_Widget* w) { this->selectionToolbar_callback(FR_SELECTION_EDGE);},
        FRTK_FLAT_BOX, 
        ""},
        {"",
        "Vertex",
        {FRTK_TOOLBAR_BUTTON_HEGHT,FRTK_TOOLBAR_BUTTON_HEGHT},
        iconPath + "SelectionModeVertex.png",
        [this](Frtk_Widget* w) { this->selectionToolbar_callback(FR_SELECTION_VERTEX);},
        FRTK_FLAT_BOX,
        ""},
    };
    //Frtk_ToolBarWin(float, float Y, float W, float H, std::string lbl, const std::vector<toolbBTN_t>&tools = {}, bool horizontal = true, BOX_TYPE b = FRTK_UP_BOX, WIDGTYPE btnType = FRTK_TOOLBAR_BUTTON);
    std::shared_ptr<Frtk_ToolBarWin> tb2 = std::make_shared<Frtk_ToolBarWin>(w() / 2 - FRTK_TOOLBAR_HEIGHT * 2,
        y() + menuHeight(),
        FRTK_TOOLBAR_HEIGHT * 4 + FRTK_TOOLBAR_HEIGHT / 2,
        FRTK_TOOLBAR_HEIGHT, "",
        tools2, true,
        FRTK_FLAT_BOX, FRTK_TOGGLE_BUTTON);
    size_t childrens = tb2->m_guiWindow->getChildrenNo();
    for (size_t i = 0; i < childrens; ++i) {
        tb2->m_guiWindow->getChildAt(i)->cellStyle(FR_IMG_LEFT_TO_TEXT); //Make both be in the center;
    }
    tb2->widgetType(FRTK_TOOLBARWIN_TOOGLE);
    //tb2->dockable(false); //don't allow docking - this should be a static toolbar in the middle of the screen.
    return tb2;
}
}