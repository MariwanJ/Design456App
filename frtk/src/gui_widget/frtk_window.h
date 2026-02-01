#ifndef FRTK_WINDOW_H
#define FRTK_WINDOW_H

#include<gui_widget/frtk_grpwidget.h>

namespace FR{
    //TODO: Temporary code -- FIXME
    typedef struct FontData_t {
        int fontNormal, fontBold, fontIcons, fontEmoji;
        int images[12];
    };
    



    class Frtk_Window : public Frtk_GrpWidget {
    public:
        Frtk_Window(float X, float Y, float W, float H, std::string lbl = "Frtk_Window");
        ~Frtk_Window();
        virtual void draw(void) override;
        void draw_header();
        void init(void);
        void draw_label()  override;
        void draw_label(float X, float Y, float W, float H)   override;
        std::shared_ptr<NVGcontext> getContext(void);

        virtual void draw_box() override;
        virtual void draw_box(BOX_TYPE t, glm::vec4 c) override;
        virtual void draw_box(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) override;

        void draw_focus()   override;
        void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        int loadFonts();
        void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)  override;
        void cornorRadious(float& f);
        float cornorRadious() const;
        inline NVGcolor setAlpha(FR_COLOR& c, float alpha) { return NVGcolor{ c.R,c.G,c.B,alpha }; }
        
        virtual int handle(int event) override;

    protected:
        FontData_t m_data;
        std::string default_font_path;

    private:
        static Fr_Window *pMainGlfwWindow;
        NVGcontext* m_nvgContext;
        float m_cornerRadius = 3.0f;
    };
    
}
#endif //!FRTK_WINDOW_H
