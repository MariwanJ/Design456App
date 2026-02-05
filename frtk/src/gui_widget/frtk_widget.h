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

#ifndef FRTK_WIDGET_H
#define FRTK_WIDGET_H

#include <fr_constants.h>
#include <fr_core.h>
#include <fr_window.h>

#include <GLFW/glfw3.h>
#include<gui_widget/frtk_draw.h>





namespace FR {
    
#define FRTK_WINDOWS_TITLE_HEIGHT 30.0

    class FRTK_API Frtk_Widget {
        friend class Frtk_GrpWidget;
    
    protected:
        Frtk_Widget(float X, float Y, float W, float H, std::string label, BOX_TYPE b =FRTK_NO_BOX);
        virtual ~Frtk_Widget();// = default;
    
        Frtk_Widget(const Frtk_Widget&)=delete;
        /** unimplemented assignment operator */
        Frtk_Widget& operator=(const Frtk_Widget&)=delete;
    
    public:
        virtual void redraw(void) ;
        /*Use always this check inside handle before treating any widget.
          Main this toolkit window, SHOULD consume the event 
          so we prevent Scene get the event*/

        bool Frtk_Widget::should_getEvent(bool win) const;

        void label(const std::string& lbl);
        const std::string& label() const;

        virtual void drawBox();
        virtual void drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) ;
        virtual void drawBox(BOX_TYPE t, glm::vec4 c) ;

        virtual void draw_focus() ;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) ;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) ;
        
        virtual void drawLabel() ;
        virtual void drawLabel(float X, float Y, float W, float H = 18.0* 1.3f) ;

        //Widget Icon/image
        virtual int wdgImage(std::string  path );
        void drawImage(Dim_float_t dim);
        void drawImage();
        void drawImage(float x, float y, float w, float h);

        bool can_focus() const;
       
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
        float x(void) const;
        float y(void) const;
        float w(void) const;
        float h(void) const;
        virtual void resize(float X, float Y, float W, float H);
        void position(float X, float Y);
        void size(float W, float H);
        void align(LBL_ALIGN ALIGN);
        void hide();
        bool visible() const;
        std::shared_ptr<uint8_t> img; //stb image
        
        bool active(void) const;
        void activate(void);
        void disable(void);
        
        virtual void boxType(BOX_TYPE nType);

        virtual BOX_TYPE boxtype() const;
        Frtk_Widget* parent();
        float absX() const;
        float absY() const;
        void parent(Frtk_Widget* parent);
        bool has_focus(void);
        void focus(bool val);
        void lose_focus();
        bool take_focus(void);
        bool hasBelowMouse() const;
        void set_BeloMouse();

        //Callback function definition
        using Callback = std::function<void(Frtk_Widget*)>; 
        void set_callback(Callback cb);

    protected:
        virtual void draw(void);
        virtual int handle(int ev);
        virtual bool set_child_focus(Frtk_Widget* w) { return false; } // default: do nothing
        void callback();

        Frtk_Widget* m_parent = nullptr;

        NVGcontext* m_vg;
        float m_x, m_y, m_w, m_h;
        std::string m_label;
        glm::vec4 m_color;
        glm::vec4 m_borderColor;
        glm::vec4 m_bkg_color;
        bool m_visible;
        bool m_dragging;
        WIDGTYPE m_wdgType;
        static Fr_Window* m_mainWindow;
        bool m_active;
        float m_borderWidth;
        font_t m_font;
        Dim_float_t m_dim;
        Dim_float_t m_img_dim;
        //dimPos_float_t m_lbl_pos;
        BOX_TYPE m_boxType;
        bool m_has_focus;
        bool m_cantake_focus;
        iconImageSize_t m_Image;
        
        Callback m_callback;
        GLuint m_IconTexture;

    private:
};

    typedef struct {
        Frtk_Widget* current;
        Frtk_Widget* prev;
        Frtk_Widget* g_underMouse;
    }global_focus_tracker_t;

    extern global_focus_tracker_t g_focusedWdgt; 

}

#endif // !FRTK_WIDGET_H
