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
    
    Frtk_Window* Frtk_Window::m_MainFrtkInstance = nullptr;

    Frtk_Window::Frtk_Window(float X, float Y, float W, float H, std::string lbl, BOX_TYPE b, bool hasHeader) :
        Frtk_Widget(X, Y, W, H, lbl, b), m_hasHeader(hasHeader) {
        init();
        m_data.fontBold = 0;
        m_data.fontEmoji = 0;
        m_data.fontIcons = 0;
        m_data.fontNormal = 0;
        //m_color.w = 0.5f;  //Default Opacity
        ///Default style
        m_WindowsStyle.height = FRTK_WINDOWS_TITLE_HEIGHT;
        m_WindowsStyle.bevelHeight = 10.0f;
        m_WindowsStyle.cornerRadius = 3.0f;

        m_WindowsStyle.topColor = nvgRGBAf(FR_AQUAMARINE);
        m_WindowsStyle.bottomColor = nvgRGBAf(FR_DARKBLUE);
        m_WindowsStyle.strokeColor = nvgRGBAf(0.0f, 0.0f, 0.0f, 0.1254f);
        m_WindowsStyle.strokeAlpha = 0.1254f;
        m_WindowsStyle.m_cornerRadius = 3.0f;

        m_font.fontSize = 18.0;
        m_font.fName = "sans-bold";
        m_font.lblAlign = NVG_ALIGN_MIDDLE_CENTER | NVG_ALIGN_INSIDE;
        m_font.txtAlign = NVG_ALIGN_MIDDLE_CENTER;
        m_font.pos.x = m_x + m_font.fontSize * 0.4f;
        m_font.pos.y = m_y + m_font.fontSize * 0.4f;
        m_font.size.w = m_w;
        m_font.size.h = m_h;

        /*When windows start to be visible, it will be the focused widget.
        this can change later as children get focus. current and prev will be the same here
        */
        //global variables
        g_focusedWdgt.current = this;
        g_focusedWdgt.prev = this;

        // widgets specific variables
        m_wdgType = FRTK_WINDOW;
        m_linkTofrtkWindow = this;
        m_MainFrtkInstance = this;
        if (m_hasHeader) {
            m_guiWindow = std::make_shared<Frtk_GrpWidget>(m_vg, X, Y + m_WindowsStyle.height, W, H - m_WindowsStyle.height);
        }
        else {
            m_guiWindow = std::make_shared<Frtk_GrpWidget>(m_vg, X, Y, W, H);
        }
        m_guiWindow->m_linkTofrtkWindow = this;
        m_guiWindow->parent(this);
        m_guiWindow->boxType(b);

        FRTK_CORE_APP_ASSERT(m_guiWindow);
    }
    void Frtk_Window::x(float v) {
        m_x = v;
        m_guiWindow->x(v);
    }
    void Frtk_Window::y(float v) {
        m_y = v;
        m_guiWindow->y(v);

    }
    void Frtk_Window::w(float v) {
        m_w = v;
        m_guiWindow->w(v);

    }
    void Frtk_Window::h(float v) {
        m_h = v;
        m_guiWindow->h(v);
    }

    float Frtk_Window::x() const
    {
        return m_x;
    }

    float Frtk_Window::y() const
    {
        return m_y;
    }

    float Frtk_Window::w() const
    {
        return m_w;
    }

    float Frtk_Window::h() const
    {
        return m_h;
    }

    float Frtk_Window::absX() const{
        return 0.0f;
    }
    float Frtk_Window::absY() const {
        return 0.0f;
    }

    void Frtk_Window::draw() {
        if (!m_visible)
            return;
        FRTK_CORE_APP_ASSERT(m_vg != nullptr);
        m_guiWindow->draw();
        if (m_hasHeader) {
            draw_header();
        }
        if (!m_label.empty())
            drawLabel();
        draw_focus();
    }

    void Frtk_Window::draw_header()
    {
        float headerHeight = m_WindowsStyle.height;

        // Gradient background
        NVGpaint headerPaint = nvgLinearGradient(m_vg, m_x, m_y, m_x, m_y + headerHeight,
            m_WindowsStyle.topColor, m_WindowsStyle.bottomColor);

        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_x, m_y, m_w, headerHeight, m_WindowsStyle.cornerRadius);
        nvgFillPaint(m_vg, headerPaint);
        nvgFill(m_vg);

        // Top bevel stroke
        nvgBeginPath(m_vg);
        nvgRoundedRect(m_vg, m_x, m_y, m_w, m_WindowsStyle.bevelHeight, m_WindowsStyle.cornerRadius);
        nvgStrokeWidth(m_vg, 1.0f);
        nvgStrokeColor(m_vg, m_WindowsStyle.strokeColor);

        nvgSave(m_vg);
        nvgIntersectScissor(m_vg, m_x, m_y, m_w, 1.0f);
        nvgStroke(m_vg);
        nvgRestore(m_vg);

        // Bottom separator line
        nvgBeginPath(m_vg);
        nvgMoveTo(m_vg, floorf(m_x) + 0.5f, floorf(m_y + m_WindowsStyle.bevelHeight - 1.0f) + 0.5f);
        nvgLineTo(m_vg, floorf(m_x + m_w) - 0.5f, floorf(m_y + m_WindowsStyle.bevelHeight - 1.0f) + 0.5f);
        nvgStroke(m_vg);
    }

    void Frtk_Window::init(void)
    {
        FRTK_CORE_APP_ASSERT(m_mainWindow);
        m_vg = m_mainWindow->getnvgContext();
        FRTK_CORE_APP_ASSERT(m_vg != nullptr);

        if (!m_vg) {
            throw std::runtime_error("NanoVG context not initialized");
        }

        default_font_path = EXE_CURRENT_DIR + "/frtk/vendor/nanovg/example/";
        loadFonts();
    }
    void Frtk_Window::drawLabel() {
        m_font.pos = { m_x, m_y };
        m_font.size = { m_w, m_WindowsStyle.height };
        if(m_linkTofrtkWindow)
            drawTextInBox(m_vg, m_label, m_font,true, m_linkTofrtkWindow->getFontData());
     }

    void Frtk_Window::drawLabel(float X, float Y, float W, float H, float rotateAngle) {
        m_font.size.w = W;
        m_font.size.h = H;
        m_font.Rotate = rotateAngle;
        drawLabel();
    }

    NVGcontext* Frtk_Window::getContext(void) {
        //this is to allow widgets to get the context as it is required for each drawing
        return m_mainWindow->getnvgContext();
    }

    int Frtk_Window::loadFonts()
    {
        //TODO FIXME: Do we need emoji fonts?? don't think so.
        if (m_vg == NULL)
            return -1;

        std::string f = default_font_path + "entypo.ttf";
        m_data.fontIcons = nvgCreateFont(m_vg, "icons", f.c_str());
        if (m_data.fontIcons == -1) {
            printf("Could not add font icons.\n");
            return -1;
        }
        f = default_font_path + "Roboto-Regular.ttf";
        m_data.fontNormal = nvgCreateFont(m_vg, "sans", f.c_str());
        if (m_data.fontNormal == -1) {
            printf("Could not add font italic.\n");
            return -1;
        }
        f = default_font_path + "Roboto-Bold.ttf";
        m_data.fontBold = nvgCreateFont(m_vg, "sans-bold", f.c_str());
        if (m_data.fontBold == -1) {
            printf("Could not add font bold.\n");
            return -1;
        }
        f = default_font_path + "NotoEmoji-Regular.ttf";
        m_data.fontEmoji = nvgCreateFont(m_vg, "emoji", f.c_str());
        if (m_data.fontEmoji == -1) {
            printf("Could not add font emoji.\n");
            return -1;
        }
        nvgAddFallbackFontId(m_vg, m_data.fontNormal, m_data.fontEmoji);
        nvgAddFallbackFontId(m_vg, m_data.fontBold, m_data.fontEmoji);

        return 0;
    }
    Frtk_HeaderStyle_t Frtk_Window::style() {
        return m_WindowsStyle;
    }
    void Frtk_Window::style(Frtk_HeaderStyle_t& STYLE) {
        m_WindowsStyle = STYLE;
    }
    bool Frtk_Window::Header_clicked(void) {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse;
        bool result = mouse.activeX >= m_x && mouse.activeX <= m_x + m_w &&
            mouse.activeY >= m_y && mouse.activeY <= m_y + m_WindowsStyle.height;
        return result;
    }
    int Frtk_Window::handle(int events)
    {
        bool mouseIsInside = isMouse_inside();
        if (events == FR_LEFT_PUSH)
        {
            if (mouseIsInside && g_focusedWdgt.keyboardOwner != this)
            {
                // Window gains keyboard
                if (g_focusedWdgt.keyboardOwner)
                    g_focusedWdgt.keyboardOwner->m_guiWindow->handle(FR_UNFOCUS);

                g_focusedWdgt.keyboardOwner = this;
                m_has_focus = true;
            }
            else if (!mouseIsInside && g_focusedWdgt.keyboardOwner == this)
            {
                // Click outside this window -> lose keyboard
                g_focusedWdgt.keyboardOwner = nullptr;
                m_has_focus = false;
            }
        }

        int result = 0;
        if (mouseIsInside || m_dragging) {
            m_mainWindow->deactivateNavi();
            result = 1;

            if (m_hasHeader) {
                if (Header_clicked() || m_dragging) {
                    if (events == FR_LEFT_DRAG_MOVE) {
                        m_dragging = true;
                        float dx, dy;
                        const auto& mouse = m_mainWindow->m_sysEvents.mouse;
                        dx = (float)(mouse.prevX - mouse.activeX);
                        dy = (float)(mouse.prevY - mouse.activeY);
                        position(m_x - dx, m_y - dy);
                        m_guiWindow->position(m_guiWindow->x() - dx, m_guiWindow->y() - dy);
                        return 1;
                    }
                    else if (m_dragging && events == FR_LEFT_DRAG_RELEASE) {
                        m_dragging = false;
                        m_mainWindow->activateNavi();
                        return 1;
                    }
                }
            }
            // WE MUST RETURN ALWAYS 1 .. events over the window should be consumed
            // we don't care if the group doesn't consume the events
            // Scene should not get events if the mouse was over a frtk-window!!!! IMPORTANT TO REMEMBER!!!
            if (!m_dragging)
                m_mainWindow->activateNavi();
            m_guiWindow->handle(events); /* we don't care about the results, 
                                            forward all events to container widget */
        }
        return result;
    }

    dimPos_float_t Frtk_Window::mainGui() const
    {
        return { x(), y() };
    }

    bool Frtk_Window::isMouse_inside() const
    {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse; // content-space mouse
        bool result;
        result = mouse.activeX >= m_x && mouse.activeX <= m_x + m_w &&
            mouse.activeY >= m_y && mouse.activeY <= m_y + m_h;
        return result;
    }

    void Frtk_Window::remove_child_at(size_t& index) {
        m_guiWindow->remove_child_at(index);
    }
    void Frtk_Window::remove_child(std::shared_ptr<Frtk_Widget>& wdg) {
        m_guiWindow->remove_child(wdg);
    }
    void Frtk_Window::remove_all() {
        m_guiWindow->remove_all();
    }
    void Frtk_Window::addChild(std::shared_ptr<Frtk_Widget> w) {
        w->m_linkTofrtkWindow = this;
        m_guiWindow->addChild(w);
    }
    bool Frtk_Window::hasHeader() const {
        return m_hasHeader;
    }
    void Frtk_Window::hasHeader(bool val) {
        m_hasHeader = val;
    }
    void Frtk_Window::lose_focus()
    {
        m_has_focus = false;
        Frtk_Widget::lose_focus();
        m_guiWindow->lose_focus();
        
        if (g_focusedWdgt.keyboardOwner == this) {
            g_focusedWdgt.keyboardOwner = nullptr;
            g_focusedWdgt.prev = g_focusedWdgt.current;
            g_focusedWdgt.current = nullptr;
        }
    }
    
    const FontData_t &Frtk_Window::getFontData() 
    {
        return m_data;
    }

    bool Frtk_Window::set_child_focus(Frtk_Widget* w) {
        if(w){
            m_guiWindow->set_child_focus(w);
        }
        return false;
    }

    bool Frtk_Window::take_focus()
    {
        if (can_focus()){
            Frtk_Widget::take_focus();
            m_guiWindow->take_focus();
            return true;
        }
        return false;
    }

}