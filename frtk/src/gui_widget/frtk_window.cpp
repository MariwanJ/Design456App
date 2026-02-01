#include<gui_widget/frtk_window.h>


namespace FR {
    Fr_Window* Frtk_Window::pMainGlfwWindow=NULL;
    Frtk_Window::Frtk_Window(float X, float Y, float W, float H, std::string lbl) :Frtk_GrpWidget(X, Y, W, H, lbl), m_nvgContext(NULL) {
        init();
        m_data.fontBold = 0;
        m_data.fontEmoji = 0;
        m_data.fontIcons = 0;
        m_data.fontNormal = 0;
        memset(m_data.images, 0, 12);
        m_color.w = 0.5f;  //Default Opacity
    }
    
    Frtk_Window::~Frtk_Window() {
     }
    void Frtk_Window::draw()  {
        if (m_visible) {
            Fr_Camera& camera = pMainGlfwWindow->activeScene->getActiveCamera();
            float ratio = camera.getRatio();
            assert(m_nvgContext!=NULL);
            //Be aware that the width and height is not this windows w/h .. it is Glfw dimentions, the same for the ratio
            nvgBeginFrame(m_nvgContext, (float)pMainGlfwWindow->w() , (float)pMainGlfwWindow->h(), ratio);

            float cornerRadius = 3.0f;
            NVGpaint shadowPaint;

            nvgSave(m_nvgContext);
            // Window
            nvgBeginPath(m_nvgContext);
            nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_h, cornerRadius);
            nvgFillColor(m_nvgContext, nvgRGBAf(m_color.x,m_color.y,m_color.z,m_color.w));
            nvgFill(m_nvgContext);

            // Drop shadow
            shadowPaint = nvgBoxGradient(m_nvgContext, m_x, m_y + 2, m_w, m_h, cornerRadius * 2, 10, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
            nvgSave(m_nvgContext);
            nvgResetScissor(m_nvgContext);
            
            nvgBeginPath(m_nvgContext);
            nvgRect(m_nvgContext, m_x - 10, m_y - 10, m_w + 20, m_h + 20);
            nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_h, cornerRadius);
            nvgPathWinding(m_nvgContext, NVG_HOLE);
            nvgFillPaint(m_nvgContext, shadowPaint);
            nvgFill(m_nvgContext);
            nvgRestore(m_nvgContext);

            draw_header();

            if(!m_label.empty()){
            draw_label();
            }
            Frtk_GrpWidget::draw(); //we should draw also all children
            nvgRestore(m_nvgContext);
            nvgEndFrame(m_nvgContext);
        }

#if 0 //origional 
        if (m_visible) {
            Fr_Camera& camera = pMainGlfwWindow->activeScene->getActiveCamera();
            float ratio = camera.getRatio();
            assert(m_nvgContext != NULL);
            //Be aware that the width and height is not this windows w/h .. it is Glfw dimentions, the same for the ratio
            nvgBeginFrame(m_nvgContext, pMainGlfwWindow->w(), pMainGlfwWindow->h(), ratio);

            float cornerRadius = 3.0f;
            NVGpaint shadowPaint;


            nvgSave(m_nvgContext);
            // Window
            nvgBeginPath(m_nvgContext);
            nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_h, cornerRadius);
            nvgFillColor(m_nvgContext, nvgRGBA(28, 30, 34, 192));
            nvgFill(m_nvgContext);

            // Drop shadow
            shadowPaint = nvgBoxGradient(m_nvgContext, m_x, m_y + 2, m_w, m_h, cornerRadius * 2, 10, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
            nvgSave(m_nvgContext);
            nvgResetScissor(m_nvgContext);

            nvgBeginPath(m_nvgContext);
            nvgRect(m_nvgContext, m_x - 10, m_y - 10, m_w + 20, m_h + 20);
            nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_h, cornerRadius);
            nvgPathWinding(m_nvgContext, NVG_HOLE);
            nvgFillPaint(m_nvgContext, shadowPaint);
            nvgFill(m_nvgContext);
            nvgRestore(m_nvgContext);

            draw_header();

            if (!m_label.empty()) {
                draw_label();
            }
            nvgRect(m_nvgContext, m_x, m_y, m_x + m_w, m_y + m_h);
            nvgFillColor(m_nvgContext, nvgRGB(255, 0, 0));
            Frtk_GrpWidget::draw(); //we should draw also all children
            nvgRestore(m_nvgContext);
            nvgEndFrame(m_nvgContext);
        }
#endif 
    }
    void Frtk_Window::draw_header() {
        // Header
        NVGpaint headerPaint;
        headerPaint = nvgLinearGradient(m_nvgContext, m_x, m_y, m_x, m_y + 15, nvgRGBAf(FR_YELLOW), nvgRGBAf(FR_BLACK)); // nvgRGBA(255, 255, 255, 8), nvgRGBA(0, 0, 0, 16));
        nvgBeginPath(m_nvgContext);
        nvgRoundedRect(m_nvgContext, m_x, m_y, m_w - 2, 30, m_cornerRadius - 1);
        nvgFillPaint(m_nvgContext, headerPaint);
        nvgFill(m_nvgContext);
        nvgBeginPath(m_nvgContext);
        nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, 10, m_cornerRadius);
        nvgStrokeColor(m_nvgContext, nvgRGBA(0, 0, 0, 32));
        nvgSave(m_nvgContext);
        nvgIntersectScissor(m_nvgContext, m_x, m_y, m_w, 0.5f);
        nvgStroke(m_nvgContext);
        nvgRestore(m_nvgContext);

        nvgBeginPath(m_nvgContext);
        nvgMoveTo(m_nvgContext, m_x + 0.5f, m_y + 10.f - 1.5f);
        nvgLineTo(m_nvgContext, m_x + m_w - 0.5f, m_y + 10.f - 1.5);
        nvgStrokeColor(m_nvgContext, nvgRGBA(0, 0, 0, 32));
        nvgStroke(m_nvgContext);
    }
    void Frtk_Window::init(void)
    {
        pMainGlfwWindow = Fr_Window::getFr_Window();
        assert(pMainGlfwWindow);
        m_nvgContext = pMainGlfwWindow->getnvgContext().get();
        default_font_path = EXE_CURRENT_DIR + "/frtk/vendor/nanovg/example/";
        loadFonts();
    }
    void Frtk_Window::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)
    {
    }
    void Frtk_Window::draw_label()   {
        nvgFontSize(m_nvgContext, 18.0f);
        nvgFontFace(m_nvgContext, "sans-bold");
        nvgTextAlign(m_nvgContext, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

        nvgFontBlur(m_nvgContext, 2);
        nvgFillColor(m_nvgContext, nvgRGBA(0, 0, 0, 128));
        nvgText(m_nvgContext, m_x + m_w / 2, m_y + 16 + 1, m_label.c_str(), NULL);

        nvgFontBlur(m_nvgContext, 0);
        nvgFillColor(m_nvgContext, nvgRGBA(220, 220, 220, 160));
        nvgText(m_nvgContext, m_x + m_w / 2, m_y + 16, m_label.c_str(), NULL);

    }
    void Frtk_Window::draw_label(float X, float Y, float W, float H)   {
        
        nvgFontSize(m_nvgContext, 18.0f);
        nvgFontFace(m_nvgContext, "sans-bold");
        nvgTextAlign(m_nvgContext, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

        nvgFontBlur(m_nvgContext, 2);
        nvgFillColor(m_nvgContext, nvgRGBA(0, 0, 0, 128));
        nvgText(m_nvgContext, X + W/ 2, Y+ 16 + 1, m_label.c_str(), NULL);

        nvgFontBlur(m_nvgContext, 0);
        nvgFillColor(m_nvgContext, nvgRGBA(220, 220, 220, 160));
        nvgText(m_nvgContext, X+ W/ 2, Y + 16, m_label.c_str(), NULL);
    }
    std::shared_ptr<NVGcontext> Frtk_Window::getContext(void) {
        //this is to allow widgets to get the context as it is required for each drawing
        return pMainGlfwWindow->getnvgContext();
    }

    void Frtk_Window::draw_box()
    {
    }

    void Frtk_Window::draw_box(BOX_TYPE t, glm::vec4 c)
    {
    }

    void Frtk_Window::draw_box(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c)
    {
    }

    void Frtk_Window::draw_focus()  
    {
    }

    void Frtk_Window::draw_focus(BOX_TYPE t, float X, float Y, float W, float H)
    {
    }

    int Frtk_Window::loadFonts()
    {
        int i;

        if (m_nvgContext == NULL)
            return -1;

        for (i = 0; i < 12; i++) {
            char file[128];
            std::string f; 
            f = default_font_path + "images/";
            snprintf(file, 128, "%simage%d.jpg", f.c_str(), i + 1);
            m_data.images[i] = nvgCreateImage(m_nvgContext, file, 0);
            if (m_data.images[i] == 0) {
                printf("Could not load %s.\n", file);
                return -1;
            }
        }
        std::string f = default_font_path + "entypo.ttf";
        m_data.fontIcons = nvgCreateFont(m_nvgContext, "icons", f.c_str());
        if (m_data.fontIcons == -1) {
            printf("Could not add font icons.\n");
            return -1;
        }
        f = default_font_path + "Roboto-Regular.ttf";
        m_data.fontNormal = nvgCreateFont(m_nvgContext, "sans", f.c_str());
        if (m_data.fontNormal == -1) {
            printf("Could not add font italic.\n");
            return -1;
        }
        f = default_font_path + "Roboto-Bold.ttf";
        m_data.fontBold = nvgCreateFont(m_nvgContext, "sans-bold", f.c_str());
        if (m_data.fontBold == -1) {
            printf("Could not add font bold.\n");
            return -1;
        }
        f = default_font_path + "NotoEmoji-Regular.ttf";
        m_data.fontEmoji = nvgCreateFont(m_nvgContext, "emoji", f.c_str());
        if (m_data.fontEmoji == -1) {
            printf("Could not add font emoji.\n");
            return -1;
        }
        nvgAddFallbackFontId(m_nvgContext, m_data.fontNormal, m_data.fontEmoji);
        nvgAddFallbackFontId(m_nvgContext, m_data.fontBold, m_data.fontEmoji);

        return 0;
    }
    float Frtk_Window::cornorRadious() const {
        return m_cornerRadius;
    }
    int Frtk_Window::handle(int events)
    {
        auto& mouse = pMainGlfwWindow->m_systemEvents.mouse;
       
        if (should_getEvent() || m_dragging){
        if (events == FR_LEFT_DRAG_PUSH) {
            m_dragging = true;
            float dx, dy;
            dx = mouse.prevX - mouse.activeX;
            dy = mouse.prevY - mouse.activeY;
            position(m_x - dx, m_y -dy);
            return 1;
        }
        if (m_dragging && events == FR_LEFT_RELEASE)
            m_dragging = false;
        return 1;
        }

        if (should_getEvent()) {
            switch (events) {
            default: {} break;
            }
        }
        return 0;
    }
    void Frtk_Window::cornorRadious(float& f)
    {
        m_cornerRadius = f;
    }

}