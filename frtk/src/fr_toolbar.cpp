
#include <fr_toolbar.h>
#include <Fr_GL3Window.h>



int Fr_GL3Window::imgui_TopPannel()
{
    static bool use_work_area = false;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
  //   ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y+25));
    // ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 100));
   //ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0
        //   | ImGuiWindowFlags_NoDocking
         //   | ImGuiWindowFlags_NoTitleBar
            //| ImGuiWindowFlags_NoResize
        //   | ImGuiWindowFlags_NoMove
           //| ImGuiWindowFlags_NoScrollbar
           //| ImGuiWindowFlags_NoSavedSettings
        ;
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("TOOLBAR", NULL, window_flags);

    // ImGui::PopStyleVar();


    ImVec4 dummy_col = ImVec4(FR_LIGHTGRAY);
    //All TOOLBARS ARE HERE !!
   // ImGui::BeginGroup();                        // Lock X position
    ImVec4 pressedCol = ImVec4(FR_BEIGE);
    ImVec4 normalCol = ImVec4(FR_LIGHTGRAY);

   // ImGui::Dummy(ImVec2(0.0f, 20.0f));           //space -- Vertically 
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILE, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr);                                  //FILE NEW
   // ImGui::Dummy(ImVec2(36.0f, 0.0f));
    ImGui::SameLine();

    if (ImGui::Button(ICON_FA_FILE_ARROW_UP, ImVec2(ICON_SIZE)))     mnuFileOpen_cb(nullptr);                     //FILE OPEN

    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FLOPPY_DISK, ImVec2(ICON_SIZE)))   mnuFileSave_cb(nullptr);                          //FILE SAVE
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROWS_DOWN_TO_LINE, ImVec2(ICON_SIZE)))   mnuFileSaveAs_cb(nullptr);                //FILE SAVE AS
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_CIRCLE_XMARK, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr);                          //FILE CLOSE                                  
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROW_DOWN, ImVec2(ICON_SIZE)))   mnuFileImport_cb(nullptr);                         //FILE IMPORT
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROW_UP, ImVec2(ICON_SIZE)))   mnuFileExport_cb(nullptr);                        //FILE EXPORT
    //ImGui::EndGroup();
    ImGui::End();

    return 0;
}