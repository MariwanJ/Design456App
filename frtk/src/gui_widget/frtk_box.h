#ifndef FRTK_BOX_H
#define FRTK_BOX_H

#include <frtk.h>
#include <gui_widget/frtk_widget.h>

namespace FR {

   class Frtk_Box : public Frtk_Widget
    {
    public:
         Frtk_Box(NVGcontext* vg, float x, float y, float w, float h, std::string l="", BOX_TYPE=FRTK_UP_BOX);
        ~Frtk_Box();
        virtual void draw() override;
        virtual int  handle(int e) override;
   };
}
#endif // FL_CELL_H