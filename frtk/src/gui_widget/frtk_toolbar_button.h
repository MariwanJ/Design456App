#ifndef FRTK_TOOLBAR_BUTTON_H
#define FRTK_TOOLBAR_BUTTON_H

#include <gui_widget/frtk_button.h> 

namespace FR {
	class Fl_ToolBar_Button : public Frtk_Button
	{
	public:
		Fl_ToolBar_Button(NVGcontext* vg, int x, int y, int w, int h, const char* l, BOX_TYPE b=FRTK_UP_BOX);
		Fl_ToolBar_Button* pItemNext;
		Fl_ToolBar_Button* pItemPrev;
		~Fl_ToolBar_Button();


	};
}
#endif // FRTK_TOOLBAR_BUTTON_H
