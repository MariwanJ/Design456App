#ifndef FRTK_WINDOW_H
#define FRTK_WINDOW_H

#include<gui_widget/frtk_grpwidget.h>

namespace FR{
    //TODO: Temporary code -- FIXME
    typedef struct FontData_t {
        int fontNormal, fontBold, fontIcons, fontEmoji;
        int images[12];
    };    
    
    typedef struct {
        float height;
        float bevelHeight;
        float cornerRadius;

        NVGcolor topColor;
        NVGcolor bottomColor;
        NVGcolor strokeColor;
        float strokeAlpha;
        float m_cornerRadius;
    } Frtk_HeaderStyle_t;
    

    typedef struct {
        float contentX;
        float contentY;
    }frtk_Win_Mouse_t;

    class Frtk_Window : public Frtk_GrpWidget {
        friend Fr_Window;
    public:
        Frtk_Window(float X, float Y, float W, float H, std::string lbl = "Frtk_Window", BOX_TYPE b=FRTK_UP_BOX);
        ~Frtk_Window();
        void draw_header();
        void init(void);
        void drawLabel()  override;
        void drawLabel(float X, float Y, float W, float H)   override;
        NVGcontext* getContext(void);

        virtual void drawBox() override;
        virtual void drawBox(BOX_TYPE t, glm::vec4 c) override;
        virtual void drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) override;

        void draw_focus()   override;
        void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        int loadFonts();
        Frtk_HeaderStyle_t style();
        void style(Frtk_HeaderStyle_t & STYLE);
        bool Header_clicked(void);
        void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)  override;
        inline NVGcolor setAlpha(FR_COLOR& c, float alpha) { return NVGcolor{ c.R,c.G,c.B,alpha }; }
        Frtk_HeaderStyle_t m_WindowsStyle;
        static frtk_Win_Mouse_t m_mouseDim;

    protected:
        virtual int handle(int event) override;
        virtual void draw(void) override;

        FontData_t m_data;
        std::string default_font_path;
        
        

    private:
        NVGcontext*  m_nvgContext;
   
    };
    
}
#endif //!FRTK_WINDOW_H
