#ifndef FRTK_TOOLBAR_H
#define FRTK_TOOLBAR_H
#include <gui_widget/frtk_grpwidget.h>
#include <gui_widget/frtk_toolbar_button.h>

namespace FR {
    class Frtk_ToolBar : public Frtk_GrpWidget
    {
    public:
        // class constructor
        Frtk_ToolBar(NVGcontext* vg, int x, int y, int h, int w, const char* l, BOX_TYPE b=FRTK_UP_BOX);
        void    SetDockable(int gData);
        int     GetDockable();
        Frtk_ToolBar* addButton(const char* l, std::shared_ptr<uint8_t> img);

        ~Frtk_ToolBar();
    protected:
        virtual  int handle(int e);
        virtual  void draw();
    private:
        static int offset[2];
        int dockable; //  1 docable , 0 not 
        int xCell;
        int yCell;
        int wCell;
        int hCell;
    };
}
#endif // FL_TOOLBAR_H
