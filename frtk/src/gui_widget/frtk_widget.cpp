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
#include <frtk.h>
#include <gui_widget/frtk_widget.h>
#include <fr_window.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace FR {
    //Default callback function.Replace with your custom callback.Arguments are possible.
    void default_callback(Frtk_Widget* w) {
        FRTK_CORE_INFO("Default callback: replace this with your custom callback");
    }

    //Keep track of last object got focus. This can be the same as group focus or different as each group can have 1 focused widget
    global_focus_tracker_t g_focusedWdgt = { 0 };

    Fr_Window* Frtk_Widget::m_mainWindow = nullptr;
    Frtk_Widget::Frtk_Widget(float X, float Y, float W, float H, std::string label, BOX_TYPE b) :m_x(X), m_y(Y), m_w(W), m_h(H),
        m_label(label), m_wdgType(FRTK_WIDGET), m_boxType(b), m_has_focus(false),
        m_Image({ nullptr, {{0.f, 0.f}, {0.f, 0.f}} }), m_cellStyle(FR_IMG_LEFT_TO_TEXT),
        m_visible(true), m_dragging(false), m_active(true),
        m_cantake_focus(false), m_IconTexture(0), m_vg(NULL),
        m_borderColor(glm::vec4(FR_DARKSLATEGREY)), m_borderWidth(NORMAL_BORDER),
        m_callback(default_callback),
        m_color(glm::vec4(FR_GAINSBORO)), m_bkg_color(FR_SILVER) {
        if (!m_mainWindow) {
            m_mainWindow = FR::Fr_Window::getFr_Window().get();
        }
        m_font.blur = 2.0;
        m_font.fName = "sans";
        m_font.fontSize = FRTK_TOOLBAR_BUTTON_FONT_SIZE;
        m_font.forgColor = nvgRGBAf(FR_BLACK);
        m_font.hAlign = NVG_ALIGN_LEFT;
        m_font.vAlign = NVG_ALIGN_MIDDLE;
        m_font.pos = { 0.0, 0.0 };
        m_font.size = { 0.0, 0.0 };
        m_font.Rotate = 0.0f;
        m_font.shadowCol = nvgRGBAf(0.0f, 0.0f, 0.0f, 0.38f);
        m_font.shadowOffs = { 0.5f,0.5f };
        m_Image.opacity = 1.0;
        m_color_diabled = disabled_color();
    }
    Frtk_Widget* Frtk_Widget::parent() {
        return m_parent;
    }

    float Frtk_Widget::absX() const {
        return m_parent ? m_parent->absX() + m_x : m_x;
    }

    float Frtk_Widget::absY() const {
        if (!m_parent) return m_y;           // just own position
        return m_parent->absY() + m_y;       // sum with parent
    }

    void Frtk_Widget::parent(Frtk_Widget* parent) {
        m_parent = parent;
    }
    void Frtk_Widget::draw() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::redraw() {
        draw();
        if (m_IconTexture != 0)
            drawImage();//Dimensions are already calculated using style
        drawLabel();
    }
    int Frtk_Widget::handle(int ev) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }

    //The bool value is to skip using the header part of the windows if it is true (i.e. windows)
    bool Frtk_Widget::isMouse_inside() const
    {
        const auto& mouse = m_mainWindow->m_sysEvents.mouse; // content-space mouse

        float ax = absX();
        float ay = 0.0f;
        ay = absY();
        bool result;
        result = mouse.activeX >= ax && mouse.activeX <= ax + m_w &&
            mouse.activeY >= ay && mouse.activeY <= ay + m_h;
        return result;
    }

    void Frtk_Widget::label(const std::string& lbl) {
        m_label = lbl;
    }
    const std::string& Frtk_Widget::label() const {
        return m_label;
    }
    void Frtk_Widget::drawBox() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::drawBox(BOX_TYPE t, glm::vec4 c) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }

    void Frtk_Widget::draw_focus() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::draw_focus(BOX_TYPE t, float X, float Y, float W, float H) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::drawLabel() {
        drawTextInBox(m_vg, m_label, m_font);
    }
    void Frtk_Widget::drawLabel(float X, float Y, float W, float H, float rotateAngle ) {
        m_font.pos.x = X;
        m_font.pos.y = Y;
        m_font.size.w = W;
        m_font.size.h = H;
        m_font.Rotate = rotateAngle;
        drawTextInBox(m_vg, m_label, m_font);
    }

    void Frtk_Widget::rotateLabel(float angle)
    {
        m_font.Rotate = angle;
    }
    float Frtk_Widget::lblRotateAngle()  const{
        return m_font.Rotate;
    }

    void Frtk_Widget::boxType(BOX_TYPE nType)
    {
        m_boxType = nType;
        redraw();
    }

    int Frtk_Widget::cellStyle() const
    {
        return m_cellStyle;
    }

    void Frtk_Widget::cellStyle(FRTK_PICTXT_STYLE value)
    {
        m_cellStyle = value;
        applyStyle();
        redraw();
    }

    void Frtk_Widget::applyStyle() {
        throw NotImplementedException();
    }

    BOX_TYPE Frtk_Widget::boxtype() const {
        return m_boxType;
    }

    void Frtk_Widget::hide() {
        m_visible = false;
    }
    bool Frtk_Widget::visible() const {
        return m_visible;
    }

    void Frtk_Widget::color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
        m_color = glm::vec4(float(R) / 255.0f, float(G) / 255.0f, float(B) / 255.0f, float(A) / 255.0f);
        m_color_diabled = disabled_color();
    }
    void Frtk_Widget::color(float R, float G, float B, float A) {
        m_color = glm::vec4(R, G, B, A);
        m_color_diabled = disabled_color();
    }
    void Frtk_Widget::color(glm::vec4 col) {
        m_color = col;
        m_color_diabled = disabled_color();
    }

    glm::vec4 Frtk_Widget::color(void) const
    {
        return m_color;
    }

    void Frtk_Widget::opacity(float A) {
        m_color.z = A;
    }
    void Frtk_Widget::opacity(uint8_t A) {
        m_color.z = float(A) / 255.0f;
    }

    float Frtk_Widget::opacity() const
    {
        return m_color.z;
    }

    void Frtk_Widget::bkg_color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
        m_bkg_color = glm::vec4(float(R) / 255.0f, float(G) / 255.0f, float(B) / 255.0f, float(A) / 255.0f);
        m_color_diabled = disabled_color();
    }
    void Frtk_Widget::bkg_color(float R, float G, float B, float A) {
        m_bkg_color = glm::vec4(R, G, B, A);
        m_color_diabled = disabled_color();
    }
    void Frtk_Widget::bkg_color(glm::vec4 col) {
        m_color = col;
        m_color_diabled = disabled_color();
    }

    void Frtk_Widget::bkg_opacity(float A) {
        m_bkg_color.w = A;
    }
    void Frtk_Widget::bkg_opacity(uint8_t A) {
        m_bkg_color.w = float(A) / 255.0f;
    }

    float Frtk_Widget::bkg_opacity(void) const
    {
        return m_bkg_color.w;
    }

    void Frtk_Widget::x(float X) {
        m_x = X;
    }
    void Frtk_Widget::y(float Y) {
        m_y = Y;
    }
    void Frtk_Widget::w(float W) {
        m_w = W;
    }
    void Frtk_Widget::h(float H) {
        m_h = H;
    }
    float Frtk_Widget::x() const {
        return m_x;
    }
    float Frtk_Widget::y() const {
        return m_y;
    }
    float Frtk_Widget::w() const {
        return m_w;
    }
    float Frtk_Widget::h() const {
        return m_h;
    }
    void Frtk_Widget::resize(float X, float Y, float W, float H) {
        m_x = X;
        m_y = Y;
        m_w = W;
        m_h = H;
        
        m_Image.dim.pos.x = X;
        m_Image.dim.pos.y = Y;
        m_Image.dim.size.w = W;
        m_Image.dim.size.h = H;

        m_font.pos.x = X ;
        m_font.pos.y = Y;
        m_font.size.w = W;
        m_font.size.h = H;

    }
    void Frtk_Widget::position(float X, float Y) {
        resize(X, Y, m_w, m_h);
    }
    void Frtk_Widget::size(float W, float H) {
        resize(m_x, m_y, W, H);
    }
    void Frtk_Widget::align(LBL_ALIGN ALIGN) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    bool Frtk_Widget::active(void) const {
        return m_active;
    }

    void Frtk_Widget::disable(void) {
        m_active = false;
    }

    void Frtk_Widget::activate(void) {
        m_active = true;
    }

    int Frtk_Widget::wdgImage(const std::string path, std::optional<glm::vec4> tint)
    {
        if (path.empty())
            return -1;

        int w = 0, h = 0, channels = 0;

        unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 4);

        if (!data)
            return -1;

        if (tint)
        {
            const int pixels = w * h;
            for (int i = 0; i < pixels; ++i)
            {
                uint8_t& a = data[i * 4 + 3];
                if (a == 0) continue;
                data[i * 4 + 0] = tint->r;
                data[i * 4 + 1] = tint->g;
                data[i * 4 + 2] = tint->b;
            }
        }

        m_Image.dim.size.w = float(w);
        m_Image.dim.size.h = float(h);

        m_Image.image.reset(data, stbi_image_free);
        m_IconTexture = nvgCreateImageRGBA(m_vg, w, h, 0, data);
        if (m_IconTexture == 0)
            return -1;

        return 0;
    }

    int Frtk_Widget::wdgImage(const std::vector<uint8_t>& pngData, std::optional<glm::vec4> tint)
    {
        if (pngData.empty())
            return -1;

        int w = 0, h = 0, channels = 0;

        unsigned char* decoded =
            stbi_load_from_memory(pngData.data(),
                static_cast<int>(pngData.size()),
                &w, &h, &channels, 4);

        if (!decoded)
            return -1;

        if (tint)
        {
            uint8_t r = static_cast<uint8_t>(tint->r * 255.0f);
            uint8_t g = static_cast<uint8_t>(tint->g * 255.0f);
            uint8_t b = static_cast<uint8_t>(tint->b * 255.0f);

            for (int i = 0; i < w * h; ++i)
            {
                uint8_t& a = decoded[i * 4 + 3];
                if (a == 0) continue; // transparent

                decoded[i * 4 + 0] = r;
                decoded[i * 4 + 1] = g;
                decoded[i * 4 + 2] = b;
            }
        }

        m_Image.dim.size.w = static_cast<float>(w);
        m_Image.dim.size.h = static_cast<float>(h);
        m_Image.image.reset(decoded, stbi_image_free);
        m_IconTexture = nvgCreateImageRGBA(m_vg, w, h, 0, decoded);
        if (m_IconTexture == 0)
            return -1;

        return 0;
    }

    void Frtk_Widget::drawImage(Dim_float_t dim) {
        m_Image.dim = dim;
        drawImage();
    }
    void Frtk_Widget::drawImage(void)
    {
        if (!m_IconTexture) return;
        nvgSave(m_vg);
        nvgGlobalAlpha(m_vg, m_Image.opacity);
        nvgBeginPath(m_vg);
        nvgRect(m_vg, m_Image.dim.pos.x, m_Image.dim.pos.y, m_Image.dim.size.w, m_Image.dim.size.h);
        nvgFillPaint(m_vg, nvgImagePattern(m_vg, m_Image.dim.pos.x, m_Image.dim.pos.y,
            m_Image.dim.size.w, m_Image.dim.size.h, 0.0f, m_IconTexture, 1.0f));
        nvgFill(m_vg);
        nvgRestore(m_vg);
    }

    void Frtk_Widget::drawImage(float x, float y, float w, float h) {
        m_Image.dim.pos.x = x;
        m_Image.dim.pos.y = y;
        m_Image.dim.size.w = w;
        m_Image.dim.size.h = h;
        drawImage();
    }

    bool Frtk_Widget::can_focus() const {
        return (m_visible && m_active && m_cantake_focus);
    }
    bool Frtk_Widget::has_focus(void) {
        return m_has_focus;
    }
    void Frtk_Widget::focus(bool val) {
        m_has_focus = val;
    }

    bool set_child_focus(Frtk_Widget* w) {
        // default: do nothing
        return false;
    }
    bool Frtk_Widget::take_focus() {
        if (!can_focus()) return false; // widget may be non-focusable

        // Update global tracker
        g_focusedWdgt.prev = g_focusedWdgt.current;
        g_focusedWdgt.current = this;

        // Update group saved focus
        if (m_parent->m_wdgType == FRTK_GROUP) {
            set_child_focus(this);
        }
        return true;
    }

    bool Frtk_Widget::hasBelowMouse() const {
        return g_focusedWdgt.g_underMouse == this;
    }

    
    void Frtk_Widget::set_BelowMouse() {
        g_focusedWdgt.g_underMouse = this;
    }
    
    void Frtk_Widget::clear_BelowMouse() {
        g_focusedWdgt.g_underMouse = nullptr;
    }

    void Frtk_Widget::set_callback(Callback cb)
    {
        m_callback = std::move(cb);
    }

    //callback processing
    void Frtk_Widget::do_callback() {
        if (m_callback) m_callback(this);
    }
    dimPos_float_t Frtk_Widget::mainGui() const {
        throw NotImplementedException();
    }
}