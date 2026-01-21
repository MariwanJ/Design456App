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
#include <fr_toolbar.h>
#include <fr_window.h>
namespace FR {
   
    bool IconButtonPressed(const char* icon, bool active, const ImVec2& size)
    {
        if (active)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
        }

        bool pressed = ImGui::Button(icon, size);

        if (active)
            ImGui::PopStyleColor(2);

        return pressed;
    }


    int Fr_Window::imgui_SelectionToolbar() {
        /*
        
                    KEEP THIS FOR FUTURE USE -- WITH OTHER FUNCTIONALITIES
        
        */
        //static bool use_work_area = false;
        //ImGuiViewport* viewport = ImGui::GetMainViewport();

        ////TODO: THIS IS NOT CORRECT 
        //ImGuiWindowFlags window_flags =
        //    ImGuiWindowFlags_NoTitleBar |
        //    ImGuiWindowFlags_NoResize |
        //    ImGuiWindowFlags_NoMove |
        //    ImGuiWindowFlags_NoScrollbar |
        //    ImGuiWindowFlags_NoCollapse |
        //    ImGuiWindowFlags_NoBringToFrontOnFocus |
        //    ImGuiWindowFlags_NoNavFocus |
        //    ImGuiWindowFlags_NoDecoration;   // <- equivalent to disabling all decorations

        //uint8_t selectionButtNo = 5;
        //float menuBarHeight = ImGui::GetFrameHeight();
        //ImGui::SetNextWindowPos(ImVec2(x()+w()- ((int)menuBarHeight *2 ), y()+h()-(ICON_SIZE.x*selectionButtNo*2) + (int)menuBarHeight + 3));
        //ImGui::SetNextWindowSize(ImVec2(TOOLBAR_HEIGHT, ICON_SIZE.x * selectionButtNo));

        //ImGui::Begin("SelectionToolbar", NULL, window_flags);

        //ImVec4 dummy_col = ImVec4(FR_LIGHTGRAY);
        ////All TOOLBARS ARE HERE !!
        //ImVec4 pressedCol = ImVec4(FR_BEIGE);
        //ImVec4 normalCol = ImVec4(FR_LIGHTGRAY);

        //if (IconButtonPressed(GLYPH_CUBES, m_currentSelMode == SelectionMode::Mesh, ICON_SIZE))
        //{
        //    m_currentSelMode = SelectionMode::Mesh;
        //    mnuSelMesh_cb(nullptr);
        //}

        //if (IconButtonPressed(GLYPH_BOX_1_FILL, m_currentSelMode == SelectionMode::Face, ICON_SIZE))
        //{
        //    m_currentSelMode = SelectionMode::Face;
        //    mnuSelFace_cb(nullptr);
        //}

        //if (IconButtonPressed(GLYPH_SHAPE_2_FILL, m_currentSelMode == SelectionMode::Edge, ICON_SIZE))
        //{
        //    m_currentSelMode = SelectionMode::Edge;
        //    mnuSelEdges_cb(nullptr);
        //}

        //if (IconButtonPressed(GLYPH_BORDER_TOP_LEFT, m_currentSelMode == SelectionMode::Vertex, ICON_SIZE))
        //{
        //    m_currentSelMode = SelectionMode::Vertex;
        //    mnuSelVertex_cb(nullptr);
        //}


        //ImGui::End();

        return 0;

    }

    int Fr_Window::imgui_ToolbarPannel()
    {
        static bool use_work_area = false;
        ImGuiViewport* viewport = ImGui::GetMainViewport();

        //TODO: THIS IS NOT CORRECT 
         ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoDecoration;   // <- equivalent to disabling all decorations

        
        float menuBarHeight = ImGui::GetFrameHeight();
        ImGui::SetNextWindowPos(ImVec2( x(), y()+ (int)menuBarHeight+3 ));
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, TOOLBAR_HEIGHT));

        ImGui::Begin("TOOLBAR", NULL, window_flags);

        ImVec4 dummy_col = ImVec4(FR_LIGHTGRAY);
        //All TOOLBARS ARE HERE !!
        ImVec4 pressedCol = ImVec4(FR_BEIGE);
        ImVec4 normalCol = ImVec4(FR_LIGHTGRAY);

        // ImGui::Dummy(ImVec2(0.0f, 20.0f));           //space -- Vertically
        ImGui::SameLine(0,2);
        if (ImGui::Button(GLYPH_FILE_CIRCLE_PLUS, ICON_SIZE))   mnuFileNew_cb(nullptr);               //FILE NEW
        // ImGui::Dummy(ImVec2(36.0f, 0.0f));
        ImGui::SameLine(0, 2);

  

        if (ImGui::Button(GLYPH_FOLDER_OPEN_LINE, ICON_SIZE))     mnuFileOpen_cb(nullptr);            //FILE OPEN
        ImGui::SameLine(0, 2);
        if (ImGui::Button(GLYPH_SAVE_LINE, ICON_SIZE))   mnuFileSave_cb(nullptr);                     //FILE SAVE
        ImGui::SameLine(0, 2);
        if (ImGui::Button(GLYPH_SAVE_2_LINE, ICON_SIZE))   mnuFileSaveAs_cb(nullptr);                 //FILE SAVE AS
        ImGui::SameLine(0, 2);
        if (ImGui::Button(GLYPH_CLOSE_CIRCLE_LINE, ICON_SIZE))   mnuFileClose_cb(nullptr);            //FILE CLOSE
        ImGui::SameLine(0, 2);
        if (ImGui::Button(GLYPH_IMPORT_FILL, ICON_SIZE))   mnuFileImport_cb(nullptr);                 //FILE IMPORT
        ImGui::SameLine(0, 2);
        if (ImGui::Button(GLYPH_EXPORT_LINE, ICON_SIZE))   mnuFileExport_cb(nullptr);                 //FILE EXPORT
        
        ImGui::SameLine(0, 2);
        
        // SELECTION TOOLBAR !!
        float toolbarWidth = ImGui::GetWindowWidth()/2;
        const float BTN_SPACING = 2.0f;
        float rightWidth = 4 * ICON_SIZE.x + 2 * BTN_SPACING ;
        
        ImGui::SetCursorPosX(toolbarWidth - rightWidth/2);

        uint8_t selectionButtNo = 5;
        if (IconButtonPressed(GLYPH_CUBES, m_currentSelMode == SelectionMode::Mesh, ICON_SIZE))
        {
            m_currentSelMode = SelectionMode::Mesh;
            mnuSelMesh_cb(nullptr);
        }
        ImGui::SameLine(0, 2);
        if (IconButtonPressed(GLYPH_BOX_1_FILL, m_currentSelMode == SelectionMode::Face, ICON_SIZE))
        {
            m_currentSelMode = SelectionMode::Face;
            mnuSelFace_cb(nullptr);
        }
        ImGui::SameLine(0, 2);
        if (IconButtonPressed(GLYPH_SHAPE_2_FILL, m_currentSelMode == SelectionMode::Edge, ICON_SIZE))
        {
            m_currentSelMode = SelectionMode::Edge;
            mnuSelEdges_cb(nullptr);
        }
        ImGui::SameLine(0, 2);
        if (IconButtonPressed(GLYPH_BORDER_TOP_LEFT, m_currentSelMode == SelectionMode::Vertex, ICON_SIZE))
        {
            m_currentSelMode = SelectionMode::Vertex;
            mnuSelVertex_cb(nullptr);
        }
        ImGui::SameLine(0, 2);


        ImGui::End();

        return 0;
    }
}