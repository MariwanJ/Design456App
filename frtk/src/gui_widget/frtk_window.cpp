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

#include<gui_widget/frtk_window.h>

namespace FR {
    frtk_Win_Mouse_t Frtk_Window::m_mouseDim = { 0 };   //TODO : THIS IS BAD ... TEMPEORARY SOLUTION .. FIXME PLEASE!!

    Frtk_Window::Frtk_Window(float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :Frtk_GrpWidget(NULL, X, Y, W, H, lbl,b), m_nvgContext(NULL) {
        init();
        m_data.fontBold = 0;
        m_data.fontEmoji = 0;
        m_data.fontIcons = 0;
        m_data.fontNormal = 0;
        memset(m_data.images, 0, 12);
        m_color.w = 0.5f;  //Default Opacity
        ///Default style
        m_WindowsStyle.height = 30.0f;
        m_WindowsStyle.bevelHeight = 10.0f;
        m_WindowsStyle.cornerRadius = 3.0f;

        m_WindowsStyle.topColor = nvgRGBAf(FR_DARKBLUE);
        m_WindowsStyle.bottomColor = nvgRGBAf(FR_DARKCYAN);
        m_WindowsStyle.strokeColor = nvgRGBA(0, 0, 0, 32);
        m_WindowsStyle.strokeAlpha = 32.0f / 255.0f;
        m_WindowsStyle.m_cornerRadius = 3.0f;

        m_font.fontSize = 18.0;
        m_font.fName = "sans-bold";
        m_font.hAlign = NVG_ALIGN_CENTER;
        m_font.vAlign = NVG_ALIGN_MIDDLE;

        /*When windows start to be visible, it will be the focused widget.
        this can change later as children get focus. currnt and prev will be the same here
        */
        //global variables
        g_focusedWdgt.current = this;
        g_focusedWdgt.prev = this;

        // widgets specific variables
        m_has_focus = true;
        m_cantake_focus = true;
        m_wdgType = FRTK_WINDOW;
    }

    Frtk_Window::~Frtk_Window() {
    }
    void Frtk_Window::draw() {
        if (!m_visible)
            return;

        Fr_Camera& camera = m_mainWindow->activeScene->getActiveCamera();
        float ratio = camera.getRatio();
        assert(m_nvgContext != nullptr);
        float cornerRadius = 3.0f;

        nvgBeginFrame(m_nvgContext, (float)m_mainWindow->w(), (float)m_mainWindow->h(), ratio);

        nvgSave(m_nvgContext);

        nvgBeginPath(m_nvgContext);
        nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_h, cornerRadius);
        nvgFillColor(m_nvgContext, nvgRGBAf(m_color.x, m_color.y, m_color.z, m_color.w));
        nvgFill(m_nvgContext);

        NVGpaint shadowPaint = nvgBoxGradient(
            m_nvgContext, m_x, m_y + 2, m_w, m_h, cornerRadius * 2, 10,
            nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0)

        );

        nvgSave(m_nvgContext);
        nvgResetScissor(m_nvgContext);

        nvgBeginPath(m_nvgContext);
        nvgRect(m_nvgContext, m_x - 10, m_y - 10, m_w + 20, m_h + 20);
        nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_h, cornerRadius);
        nvgPathWinding(m_nvgContext, NVG_HOLE);
        nvgFillPaint(m_nvgContext, shadowPaint);
        nvgFill(m_nvgContext);

        //nvgRestore(m_nvgContext);

        draw_header();
        if (!m_label.empty())
            drawLabel();

        //nvgSave(m_nvgContext);
        nvgRestore(m_nvgContext);
        nvgTranslate(m_nvgContext, m_x, m_y + m_WindowsStyle.height);
        //Frtk_GrpWidget::draw(); We don't need to draw the group as it is the windows now.
        Frtk_GrpWidget::draw_children();
        nvgRestore(m_nvgContext);
        nvgEndFrame(m_nvgContext);
    }

    void Frtk_Window::draw_header() {
        // Header
        NVGpaint headerPaint;
        headerPaint = nvgLinearGradient(m_nvgContext, m_x, m_y, m_x, m_y + 15, m_WindowsStyle.topColor, m_WindowsStyle.bottomColor);
        nvgBeginPath(m_nvgContext);
        nvgRoundedRect(m_nvgContext, m_x, m_y, m_w - 2, m_WindowsStyle.height, m_WindowsStyle.cornerRadius - 1);
        nvgFillPaint(m_nvgContext, headerPaint);
        nvgFill(m_nvgContext);
        nvgBeginPath(m_nvgContext);
        nvgRoundedRect(m_nvgContext, m_x, m_y, m_w, m_WindowsStyle.bevelHeight, m_WindowsStyle.cornerRadius);
        nvgStrokeColor(m_nvgContext, m_WindowsStyle.strokeColor);
        nvgSave(m_nvgContext);
        nvgIntersectScissor(m_nvgContext, m_x, m_y, m_w, 0.5f);
        nvgStroke(m_nvgContext);
        nvgRestore(m_nvgContext);

        nvgBeginPath(m_nvgContext);
        nvgMoveTo(m_nvgContext, m_x + 0.5f, m_y + m_WindowsStyle.bevelHeight - 1.5f);
        nvgLineTo(m_nvgContext, m_x + m_w - 0.5f, m_y + m_WindowsStyle.bevelHeight - 1.5);
        nvgStrokeColor(m_nvgContext, m_WindowsStyle.strokeColor);
        nvgStroke(m_nvgContext);
    }
    void Frtk_Window::init(void)
    {
        assert(m_mainWindow);
        m_nvgContext = m_mainWindow->getnvgContext();
        assert(m_nvgContext != nullptr);

        if (!m_nvgContext) {
            throw std::runtime_error("NanoVG context not initialized");
        }

        default_font_path = EXE_CURRENT_DIR + "/frtk/vendor/nanovg/example/";
        loadFonts();
    }
    void Frtk_Window::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)
    {
    }
    void Frtk_Window::drawLabel() {
        m_font.pos = { m_x, m_y };
        m_font.size = { m_w, m_WindowsStyle.height };
        drawTextInBox(m_nvgContext, m_label, m_font);
    }

    void Frtk_Window::drawLabel(float X, float Y, float W, float H) {
        m_font.size.w = W;
        m_font.size.h = H;
        drawLabel();
    }

    NVGcontext* Frtk_Window::getContext(void) {
        //this is to allow widgets to get the context as it is required for each drawing
        return m_mainWindow->getnvgContext();
    }

    void Frtk_Window::drawBox()
    {
    }

    void Frtk_Window::drawBox(BOX_TYPE t, glm::vec4 c)
    {
    }

    void Frtk_Window::drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c)
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
    Frtk_HeaderStyle_t Frtk_Window::style() {
        return m_WindowsStyle;
    }
    void Frtk_Window::style(Frtk_HeaderStyle_t& STYLE) {
        m_WindowsStyle = STYLE;
    }
    bool Frtk_Window::Header_clicked(void) {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse; // content-space mouse
        bool result = mouse.activeX >= m_x && mouse.activeX <= m_x + m_w &&
            mouse.activeY >= m_y && mouse.activeY <= m_y + m_WindowsStyle.height;
        //FRTK_CORE_INFO("{} {} , {} {} - {} {} {} ",m_x,m_y, m_x+m_w, m_y+ m_WindowsStyle.height, mouse.activeX,mouse.activeY , result);
        return result;
    }
    int Frtk_Window::handle(int events)
    {
        m_mouseDim.contentX = (float)m_mainWindow->m_sysEvents.mouse.activeX;
        m_mouseDim.contentY = (float)m_mainWindow->m_sysEvents.mouse.activeY - m_WindowsStyle.height;
        auto& mouse = m_mainWindow->m_sysEvents.mouse;
        int result = 0;
        if (should_getEvent(true)) {
            result = 1;
            if (Header_clicked() || m_dragging) {
                if (events == FR_LEFT_DRAG_PUSH) {
                    m_dragging = true;
                    float dx, dy;
                    dx = (float)( mouse.prevX - mouse.activeX);
                    dy = (float)(mouse.prevY - mouse.activeY);
                    position(m_x - dx, m_y - dy);
                    return 1;
                }
                else if (m_dragging && events == FR_LEFT_RELEASE) {
                    m_dragging = false;
                    return 1;
                }
            }
        
        // WE MUST RETURN ALWAYS 1 .. events over the window should be consumed
        // we dont care if the group dosen't consume the events
        // Scene should not get events if the mouse was over a frtk-window!!!! IMPORTANT TO REMEMBER!!!
        Frtk_GrpWidget::handle(events);
        return result;
        }
    }
}