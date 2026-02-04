#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_draw.h>

// class constructor
namespace FR {
    Frtk_Box::Frtk_Box(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Widget(x, y, w, h, l,b)
    {
        m_vg = vg;
        assert(vg != NULL);
        m_font.size.w = w;
        m_font.size.h = h;
        m_font.hAlign = NVG_ALIGN_CENTER;
        m_font.vAlign = NVG_ALIGN_MIDDLE;
        m_borderColor = glm::vec4(FR_BLACK);
    }
    Frtk_Box::~Frtk_Box() {
    }

    

    void Frtk_Box::draw()
    {
        //alwas check for all widgets
        if (!m_visible)
            return;
            draw_box(m_vg, m_boxType, m_dim,0.0f,NORMAL_BORDER,  nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a),nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
            drawLabel();
            if(m_IconTexture!=0)
                drawImage(m_x, m_y, m_w, m_h);
    }
    int Frtk_Box::handle(int e)
    {
        //Dose not do any events .. at least at the moment.
        return 0;
    }

    
    
}