#include <fr_toolbar.h>
#include <fr_window.h>
namespace FR {
    int Fr_Window::imgui_ToolbarPannel()
    {
        //Here we have the top toolbar
        const uint8_t TOOLBAR_HEIGHT = 36;

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
        ImGui::SetNextWindowPos(ImVec2( x(), y()+ menuBarHeight+3 ));
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, TOOLBAR_HEIGHT));

        ImGui::Begin("TOOLBAR", NULL, window_flags);

        ImVec4 dummy_col = ImVec4(FR_LIGHTGRAY);
        //All TOOLBARS ARE HERE !!
        ImVec4 pressedCol = ImVec4(FR_BEIGE);
        ImVec4 normalCol = ImVec4(FR_LIGHTGRAY);

        // ImGui::Dummy(ImVec2(0.0f, 20.0f));           //space -- Vertically
        ImGui::SameLine(0,2);
        if (ImGui::Button(ICON_FA_FILE, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr);                                  //FILE NEW
        // ImGui::Dummy(ImVec2(36.0f, 0.0f));
        ImGui::SameLine(0, 2);

        if (ImGui::Button(ICON_FA_FILE_ARROW_UP, ImVec2(ICON_SIZE)))     mnuFileOpen_cb(nullptr);                     //FILE OPEN
        ImGui::SameLine(0, 2);
        if (ImGui::Button(ICON_FA_FLOPPY_DISK, ImVec2(ICON_SIZE)))   mnuFileSave_cb(nullptr);                          //FILE SAVE
        ImGui::SameLine(0, 2);
        if (ImGui::Button(ICON_FA_ARROWS_DOWN_TO_LINE, ImVec2(ICON_SIZE)))   mnuFileSaveAs_cb(nullptr);                //FILE SAVE AS
        ImGui::SameLine(0, 2);
        if (ImGui::Button(ICON_FA_CIRCLE_XMARK, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr);                          //FILE CLOSE
        ImGui::SameLine(0, 2);
        if (ImGui::Button(ICON_FA_ARROW_DOWN, ImVec2(ICON_SIZE)))   mnuFileImport_cb(nullptr);                         //FILE IMPORT
        ImGui::SameLine(0, 2);
        if (ImGui::Button(ICON_FA_ARROW_UP, ImVec2(ICON_SIZE)))   mnuFileExport_cb(nullptr);                            //FILE EXPORT

        ImGui::End();

        return 0;
    }
}