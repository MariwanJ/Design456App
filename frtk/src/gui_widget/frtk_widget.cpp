#include <gui_widget/frtk_widget.h>
#include <fr_window.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace FR {
    Frtk_Widget::Frtk_Widget(float X, float Y, float W, float H, std::string label = "Widget") :m_x(X), m_y(Y), m_w(W), m_h(H),
        m_label(label), m_widgType(WIDG_TYPE::FRTK_WIDGET), m_boxtype(BOX_TYPE::FRTK_UP_BOX),
        m_align(LBL_ALIGN::FRTK_ALIGN_CENTER_LEFT), m_visible(true), m_dragging(false),
        m_color(glm::vec4(FR_GRAY)), m_bkg_color(FR_LIGHTGRAY) {
        Fr_Window* win = Fr_Window::getFr_Window();
        assert(win != 0);
        m_mainWindow = std::shared_ptr<Fr_Window>(win);
    }
    Frtk_Widget::~Frtk_Widget() {
    }

    void Frtk_Widget::draw() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::redraw() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    int Frtk_Widget::handle(int ev) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }

    void Frtk_Widget::label(const std::string& lbl) {
        m_label = lbl;
    }
    const std::string& Frtk_Widget::label() const {
        return m_label;
    }
    void Frtk_Widget::draw_box() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::draw_box(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::draw_box(BOX_TYPE t, glm::vec4 c) {
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
    void Frtk_Widget::draw_label() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::draw_label(float X, float Y, float W, float H) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }

    void Frtk_Widget::boxtype(BOX_TYPE bt) {
    }
    BOX_TYPE Frtk_Widget::boxtype() const {
        return m_boxtype;
    }

    void Frtk_Widget::hide() {
        m_visible = false;
    }
    bool Frtk_Widget::visible() const {
        return m_visible;
    }

    void Frtk_Widget::color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
        m_color = glm::vec4(float(R) / 255.0f, float(G) / 255.0f, float(B) / 255.0f, float(A) / 255.0f);
    }
    void Frtk_Widget::color(float R, float G, float B, float A) {
        m_color = glm::vec4(R, G, B, A);
    }
    void Frtk_Widget::color(glm::vec4 col) {
        m_color = col;
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
    }
    void Frtk_Widget::bkg_color(float R, float G, float B, float A) {
        m_bkg_color = glm::vec4(R, G, B, A);
    }
    void Frtk_Widget::bkg_color(glm::vec4 col) {
        m_color = col;
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
}