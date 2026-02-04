#ifndef FRTK_GRPWIDGET_H
#define FRTK_GRPWIDGET_H

#include <fr_core.h>
#include <gui_widget/frtk_widget.h>

namespace FR {
    
    class Frtk_GrpWidget : public Frtk_Widget {
    public:
        Frtk_GrpWidget(NVGcontext* vg, float X, float Y, float W, float H, std::string label, BOX_TYPE b= FRTK_NO_BOX);
        ~Frtk_GrpWidget();

        virtual void draw()  override;
        
        virtual void draw_children();
        virtual void redraw_children();

        virtual void redraw() override;
        bool restore_focus();
        virtual int handle(int ev) override;

        virtual void drawBox() override;
        virtual void drawBox(BOX_TYPE t, glm::vec4 c) override;
        virtual void drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) override;

        virtual void draw_focus() override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)  override;

        virtual void draw_childrenLabel();
        virtual void draw_childrenLabel(float X, float Y, float W, float H);


        int send_event(Frtk_Widget& w, int ev);

        int Frtk_GrpWidget::findIndex(const std::shared_ptr<Frtk_Widget>& w) const;
        void remove_children(size_t index);
        void remove_all();

        void Frtk_GrpWidget::addChild(std::shared_ptr<Frtk_Widget> w);

        bool navigate_focus(int key);
        
    protected:
        std::vector<std::shared_ptr<Frtk_Widget>> m_children;
        bool set_child_focus(Frtk_Widget* w) override;
        Frtk_Widget* m_childFocus;  //keep track of focused widget
    private:

    };
}
#endif // !FRTK_GRPWIDGET_H
