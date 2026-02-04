#include <gui_widget/frtk_toolbar.h>

namespace FR {
    // class constructor
    Frtk_ToolBar::Frtk_ToolBar(NVGcontext* vg, int x, int y, int w, int h, const char* l, BOX_TYPE b) :Frtk_GrpWidget(vg,x, y, w, h, l,b)
    {
        m_wdgType = FRTK_TOOLBAR;
      
    }
    int Frtk_ToolBar::GetDockable()
    {
        return dockable;
    }
    void Frtk_ToolBar::SetDockable(int gData)
    {
        dockable = gData;
    }
    int Frtk_ToolBar::handle(int e)
    {

        return Frtk_GrpWidget::handle(e);
    }



    void Frtk_ToolBar::draw()
    {

    }

    Frtk_ToolBar* Frtk_ToolBar::addButton(const char* l, std::shared_ptr<uint8_t> img)
    {

        return 0;
    }


    // class destructor
    Frtk_ToolBar::~Frtk_ToolBar()
    {
        // insert your code here
    }
}