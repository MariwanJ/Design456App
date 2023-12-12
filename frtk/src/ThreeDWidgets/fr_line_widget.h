#ifndef FR_LINE_WIDGET
#define FR_LINE_WIDGET

#include<ThreeDWidgets/fr_widget.h>

namespace FR {
    class Fr_Line_Widget : public Fr_Widget {
    public:
        Fr_Line_Widget(glm::vec3 position, std::shared_ptr<std::vector <float>>verticies, std::shared_ptr<std::vector <float>> indicies, std::string label);
        ~Fr_Line_Widget();
        virtual void draw();
        virtual void lbl_draw();
        virtual void lbl_redraw();
    protected:
        int handle(int e);
    };
}

#endif // !FR_LINE_WIDGET
