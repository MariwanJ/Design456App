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

#include<gui_widget/frtk_basewin.h>

namespace FR {
    
    Frtk_BaseWin::Frtk_BaseWin(float X, float Y, float W, float H, std::string lbl, BOX_TYPE b, bool hasHeader) :
        Frtk_Widget(X, Y, W, H, lbl, b), m_hasHeader(hasHeader) {
        init();
        m_data.fontBold = 0;
        m_data.fontEmoji = 0;
        m_data.fontIcons = 0;
        m_data.fontNormal = 0;
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
        m_wdgType = FRTK_BASEWIN;
        m_linkTofrtkWindow = this;
    }
    void Frtk_BaseWin::x(float v) {
        m_x = v;
        m_guiWindow->x(v);
    }
    void Frtk_BaseWin::y(float v) {
        m_y = v;
        m_guiWindow->y(v);

    }
    void Frtk_BaseWin::w(float v) {
        m_w = v;
        m_guiWindow->w(v);

    }
    void Frtk_BaseWin::h(float v) {
        m_h = v;
        m_guiWindow->h(v);
    }

    float Frtk_BaseWin::x() const
    {
        return m_x;
    }

    float Frtk_BaseWin::y() const
    {
        return m_y;
    }

    float Frtk_BaseWin::w() const
    {
        return m_w;
    }

    float Frtk_BaseWin::h() const
    {
        return m_h;
    }

    float Frtk_BaseWin::absX() const{
        return 0.0f;
    }
    float Frtk_BaseWin::absY() const {
        return 0.0f;
    }

    void Frtk_BaseWin::draw() {
    }

    void Frtk_BaseWin::init(void)
    {
       //should be subclassed
    }
    void Frtk_BaseWin::drawLabel() {
     }

    void Frtk_BaseWin::drawLabel(float X, float Y, float W, float H, float rotateAngle) {
    }

    NVGcontext* Frtk_BaseWin::getContext(void) {
        return nullptr;//should be subclassed
    }

    int Frtk_BaseWin::loadFonts()
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
    int Frtk_BaseWin::handle(int events)
    {
        return 0; //should be subclassed
    }

    dimPos_float_t Frtk_BaseWin::mainGui() const
    {
        return { x(), y() };
    }

    bool Frtk_BaseWin::isMouse_inside() const
    {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse; // content-space mouse
        bool result;
        result = mouse.activeX >= m_x && mouse.activeX <= m_x + m_w &&
            mouse.activeY >= m_y && mouse.activeY <= m_y + m_h;
        return result;
    }

    void Frtk_BaseWin::remove_child_at(size_t& index) {
        m_guiWindow->remove_child_at(index);
    }
    void Frtk_BaseWin::remove_child(std::shared_ptr<Frtk_Widget>& wdg) {
        m_guiWindow->remove_child(wdg);
    }
    void Frtk_BaseWin::remove_all() {
        m_guiWindow->remove_all();
    }
    void Frtk_BaseWin::addChild(std::shared_ptr<Frtk_Widget> w) {
        w->m_linkTofrtkWindow = this;
        m_guiWindow->addChild(w);
    }
    void Frtk_BaseWin::lose_focus()
    {
      //should be subclassed
    }
    
    const FontData_t &Frtk_BaseWin::getFontData() 
    {
        return m_data;
    }

    bool Frtk_BaseWin::set_child_focus(Frtk_Widget* w) {
        if(w){
            m_guiWindow->set_child_focus(w);
        }
        return false;
    }

    bool Frtk_BaseWin::take_focus()
    {
        if (can_focus()){
            Frtk_Widget::take_focus();
            m_guiWindow->take_focus();
            return true;
        }
        return false;
    }

}