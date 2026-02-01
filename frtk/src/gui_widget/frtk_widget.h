#ifndef FRTK_WIDGET_H
#define FRTK_WIDGET_H

#include <fr_constants.h>
#include <fr_core.h>
#include <fr_window.h>

#include <GLFW/glfw3.h>
#include<gui_widget/frtk_draw.h>





namespace FR {
    
    enum class WIDG_TYPE {
        FRTK_NONE,
        FRTK_WIDGET,
        FRTK_BOX,
        FRTK_BUTTON,
        FRTK_TOGGLE_BUTTON,
    };

    class FRTK_API Frtk_Widget {
        friend class Frtk_Group;
    
    protected:
        Frtk_Widget(float X, float Y, float W, float H, std::string label);
        ~Frtk_Widget();
    
        Frtk_Widget(const Frtk_Widget&)=delete;
        /** unimplemented assignment operator */
        Frtk_Widget& operator=(const Frtk_Widget&)=delete;
    
    public:
        virtual void draw(void) ;
        virtual void redraw(void) ;
        virtual int handle(int ev);
        /*Use always this check inside handel before treating any widget.
          Main this toolkit window, SHOULD consume the event 
          so we prevent Scene get the event*/
        inline bool should_getEvent() const {
                         auto &mouse = Fr_Window::m_systemEvents.mouse;
                        return (mouse.activeX >= m_x && mouse.activeX <= (m_x + m_w) &&
                                mouse.activeY >= m_y && mouse.activeY <= (m_y + m_h));}
        void label(const std::string& lbl);
        const std::string& label() const;

        virtual void draw_box();
        virtual void draw_box(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) ;
        virtual void draw_box(BOX_TYPE t, glm::vec4 c) ;

        virtual void draw_focus() ;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) ;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) ;
        
        virtual void draw_label() ;
        virtual void draw_label(float X, float Y, float W, float H) ;
        void boxtype(BOX_TYPE bt);
        BOX_TYPE boxtype() const;

        
        void color(uint8_t R, uint8_t G, uint8_t B, uint8_t A=255);
        void color(float R, float G, float B, float A=1.0f);
        void color(glm::vec4 col);
        glm::vec4 color(void) const;

        void  opacity(float A = 1.0f);
        void  opacity(uint8_t A = 255);
        float opacity() const;

        void bkg_color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255); 
        void bkg_color(float R, float G, float B, float A = 1.0f);
        void bkg_color(glm::vec4 col);

        void  bkg_opacity(float A = 1.0f);
        void  bkg_opacity(uint8_t A = 255);
        float bkg_opacity(void) const ;

        void x(float v);
        void y(float v);
        void w(float v);
        void h(float v);
        float x() const;
        float y() const;
        float w() const;
        float h() const;
        virtual void resize(float X, float Y, float W, float H);
        void position(float X, float Y);
        void size(float W, float H);
        void align(LBL_ALIGN ALIGN);
        void hide();
        bool visible() const;

    protected:
        float m_x, m_y, m_w, m_h;
        std::string m_label;
        glm::vec4 m_color;
        glm::vec4 m_bkg_color;
        bool m_visible;
        bool m_dragging;

    private:
        BOX_TYPE m_boxtype;
        WIDG_TYPE m_widgType;
        LBL_ALIGN m_align;
        std::shared_ptr<Fr_Window> m_mainWindow;

    };

}

#endif // !FRTK_WIDGET_H
