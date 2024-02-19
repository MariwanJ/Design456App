#include "fr_ImGuiLayer.h"
#include<Fr_Core.h>
#include <frtk.h>
#include<fr_constants.h>
#include <Fr_GL3Window.h>
namespace FR {
    Fr_ImGuiLayer::Fr_ImGuiLayer() : m_visible(true)
    {
    }

    Fr_ImGuiLayer::~Fr_ImGuiLayer()
    {
    }

    void Fr_ImGuiLayer::createLayer()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        float fontSize = 18.0f;
        std::string path = "../frtk/vendor/imGui/src/imguiFont/OpenSans-Bold.ttf";
        io.Fonts->AddFontFromFileTTF(path.c_str(), fontSize);
        path = "../frtk/vendor/imGui/src/imguiFont/Open Sans Regular.ttf";
        io.FontDefault = io.Fonts->AddFontFromFileTTF(path.c_str(), fontSize);

        std::string PathICON = fontPath + std::string(FONT_ICON_FILE_NAME_FAS);
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };

        io.Fonts->AddFontFromFileTTF(PathICON.c_str(), ICON_FONT_SIZE, &icons_config, icons_ranges);

        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        ImGui::StyleColorsLight();
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        //put theme here if you want !!

        GLFWwindow* window = (GLFWwindow*)(Fr_GL3Window::getfr_Gl3Window()->pWindow);
        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void Fr_ImGuiLayer::destroyLayer()
    {
        //Destroy Dear the layer
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Fr_ImGuiLayer::StartLayer()
    {
        //We create frame ONLY if it is visible
        if (m_visible) {
            // Start the Dear ImGui layer
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGuizmo::BeginFrame();
        }
    }

    void Fr_ImGuiLayer::EndLayer()
    {
        if (m_visible) {//We do this ONLY if visible otherwise we do nothing
            ImGuiIO io = ImGui::GetIO();
            if (Fr_GL3Window::getfr_Gl3Window() != nullptr) {
                io.DisplaySize = ImVec2(float(Fr_GL3Window::getfr_Gl3Window()->w()), float(Fr_GL3Window::getfr_Gl3Window()->h()));

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                    GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backupCurrentContext);
                }
            }
            else {
                std::cout << "pWindow not defined\n";
            }
        }
    }

    bool Fr_ImGuiLayer::Visible()
    {
        return m_visible;
    }

    void Fr_ImGuiLayer::Visible(bool v)
    {
        m_visible = v;
    }
}