#include <gui_widget/frtk_widget.h>
#include <fr_window.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace FR {

    
    
    
    
    //Default callback function.Replace with your custom callback.Arguments are possible.
    void default_callback(Frtk_Widget* w) {
        FRTK_CORE_INFO("Default callback: replace this with your custom callback") ;
    }


    
    
    //Keep track of last object got focus. This can be the same as group focus or different as each group can have 1 focused widget
    global_focus_tracker_t g_focusedWdgt = { 0 };
    
    Fr_Window *Frtk_Widget::m_mainWindow = nullptr;
    Frtk_Widget::Frtk_Widget(float X, float Y, float W, float H, std::string label = "Widget", BOX_TYPE b) :m_x(X), m_y(Y), m_w(W), m_h(H),
        m_label(label), m_wdgType(FRTK_WIDGET), m_boxType(b),m_has_focus(false),
        m_visible(true), m_dragging(false), m_active(true), m_cantake_focus(false),
        m_borderColor(glm::vec4(FR_DARKSLATEGREY)),m_borderWidth(NORMAL_BORDER), m_dim{ X,Y,W,H}, m_img_dim{ X,Y,W,H},m_callback(default_callback),
        m_color(glm::vec4(FR_GRAY)), m_bkg_color(FR_LIGHTGRAY) {
        if (!m_mainWindow) {
            m_mainWindow = FR::Fr_Window::getFr_Window().get();
        }
    }
    Frtk_Widget::~Frtk_Widget() {
    }
    Frtk_Widget* Frtk_Widget::parent() {
        return m_parent;
    }

    float Frtk_Widget::absX() const {
        return m_parent ? m_parent->absX() + m_x : m_x;
    }

    float Frtk_Widget::absY() const {
        return m_parent ? m_parent->absY() + m_y : m_y;
    }

    void Frtk_Widget::parent(Frtk_Widget* parent) {
        m_parent = parent;
    }
    void Frtk_Widget::draw() {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }
    void Frtk_Widget::redraw() {
        draw();
        drawLabel();
    }
    int Frtk_Widget::handle(int ev) {
        throw NotImplementedException();  // this method should be implemented by subclassing the widget
    }


    bool Frtk_Widget::should_getEvent(bool win) const
    {
         
        const auto& mouse = m_mainWindow->m_systemEvents.mouse; // content-space mouse

        float ax = absX();
        float ay;
        if (!win) {
            ay = absY() + FRTK_WINDOWS_TITLE_HEIGHT;
        }
        else {
            ay = absY();
        }

        bool result;
        result= mouse.activeX >= ax &&   mouse.activeX <= ax + m_w &&
                 mouse.activeY >= ay &&      mouse.activeY <= ay + m_h;
        //FRTK_CORE_INFO("---{} {} , {} {} - {} {} {} ", ax, ay, ax+ m_w, ay, mouse.activeX, mouse.activeY, result);
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
        
        m_font.pos = { m_x, m_y };
        drawTextInBox(m_vg, m_label, m_font);
    }
    void Frtk_Widget::drawLabel(float X, float Y, float W, float H) {
        m_font.pos.x  = X;
        m_font.pos.y  = Y;
        m_font.size.w = W;
        m_font.size.h = H;
        drawTextInBox(m_vg, m_label, m_font);
    }
    
    void Frtk_Widget::boxType(BOX_TYPE nType)
    {
        m_boxType = nType;
        redraw();
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
    bool Frtk_Widget::active(void) const {
        return m_active;
    }
    
    void Frtk_Widget::disable(void) {
        m_active = false;
    }

    void Frtk_Widget::activate(void) {
        m_active = true;
    }

    void Frtk_Widget::wdgImage(std::string path) {
        if (path.empty())
            return;
        int w, h, channels;
        auto data = stbi_load(path.c_str(), &w, &h, &channels, 0);

        if (!data) {
            FRTK_CORE_ERROR("Failed to load image {}: {}", path, stbi_failure_reason());
            m_Image.reset();
            return;
        }

        m_Image = std::shared_ptr<uint8_t>(data, stbi_image_free);
        if (!m_Image) {
            FRTK_CORE_ERROR("Image not found {}", path);
        }
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
        if (m_parent->m_wdgType==FRTK_GROUP) {
            set_child_focus(this);
        }
        return true;
    }

    bool Frtk_Widget::hasBelowMouse() const {
        return g_focusedWdgt.g_underMouse == this;
    }

    // Set this widget as the one under the mouse
    void Frtk_Widget::set_BeloMouse() {
        g_focusedWdgt.g_underMouse = this;
    }

    void Frtk_Widget::set_callback(Callback cb)
    {
         m_callback = std::move(cb); 
    }

    //callback processing 
    void Frtk_Widget::callback() {
        if (m_callback) m_callback(this);
    }

}