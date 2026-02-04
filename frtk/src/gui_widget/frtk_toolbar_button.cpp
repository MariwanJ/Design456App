#include <gui_widget/frtk_toolbar_button.h> 


namespace FR {
    Fl_ToolBar_Button::Fl_ToolBar_Button(NVGcontext* vg, int x, int y, int w, int h, const char* l, BOX_TYPE b) :Frtk_Button(vg,x, y, w, h, l,b)
    {
        // USE OR SYMBOLE FOR DIVIDER BUTTON
        pItemNext = 0;
        pItemPrev = 0;
        if (l != 0)
            if (!(strcmp(l, "|")))
                disable(); // It's a divider
        m_wdgType = FRTK_BUTTON;
    }
    Fl_ToolBar_Button::~Fl_ToolBar_Button()
    {
    }
}