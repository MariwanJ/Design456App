
#include <fr_toolbar.h>





void ToolbarUI()
{
    static bool use_work_area = false;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + 30));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 36));
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0
        | ImGuiWindowFlags_NoDocking
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoSavedSettings
        ;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("TOOLBAR", NULL, window_flags);
    ImGui::PopStyleVar();



    //All TOOLBARS ARE HERE !!
    //ImGui::BeginGroup(); // Lock X position
    //ImGui::Dummy(ImVec2(0.0f, 20.0f)); space -- Vertically 
    //ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILE, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr, nullptr);                                  //FILE NEW
    ImGui::Dummy(ImVec2(36.0f, 0.0f));
                                                                                                                            //ImGui::SameLine();
    if (ImGui::Button(ICON_MD_FILE_OPEN, ImVec2(ICON_SIZE)))   mnuFileOpen_cb(nullptr, nullptr);                            //FILE OPEN
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FLOPPY_DISK, ImVec2(ICON_SIZE)))   mnuFileSave_cb(nullptr, nullptr);                          //FILE SAVE
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROWS_DOWN_TO_LINE, ImVec2(ICON_SIZE)))   mnuFileSaveAs_cb(nullptr, nullptr);                //FILE SAVE AS
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_CIRCLE_XMARK, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr, nullptr);                          //FILE CLOSE                                  
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROW_LEFT, ImVec2(ICON_SIZE)))   mnuFileImport_cb(nullptr, nullptr);                         //FILE IMPORT
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_ARROW_RIGHT, ImVec2(ICON_SIZE)))   mnuFileExport_cb(nullptr, nullptr);                        //FILE EXPORT
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_FILE, ImVec2(ICON_SIZE)))   mnuFileNew_cb(nullptr, nullptr);
    ImGui::End();
}