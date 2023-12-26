#ifndef FR_LINE_WIDGET_H
#define FR_LINE_WIDGET_H

 #include<ThreeDWidgets/fr_widget.h>
//#include<ThreeDWidgets/fr_draw.h>
class Fr_TwoD_Drawing;
namespace FR {
    class FRTK_API Fr_Line_Widget : public Fr_Widget {
    public:
        Fr_Line_Widget(glm::vec3 position,                                          //Translation 
                        std::shared_ptr<std::vector <float>>verticies,
                        std::shared_ptr<std::vector <unsigned int>> indicies,
                        std::string label);
        ~Fr_Line_Widget();
        //Default constructor is disallowed
        Fr_Line_Widget() = delete;
        virtual void draw();
        virtual void lbl_draw();
        virtual void lbl_redraw();
    protected:
        std::shared_ptr <Fr_TwoD_Drawing> lineObj;
        int handle(int e);
        void Render(RenderInfo& info, const glm::mat4& modelview) override;
    };
}

#endif // !FR_LINE_WIDGET
