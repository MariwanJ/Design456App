#ifndef FRTK_GRPWIDGET_H
#define FTK_GRPWIDGET_H
#include <gui_widget/frtk_widget.h>
#include <fr_core.h>

namespace FR {

    class Frtk_GrpWidget : public Frtk_Widget {
    public:
        Frtk_GrpWidget(float X, float Y, float W, float H, std::string label);
        ~Frtk_GrpWidget();

        virtual void draw()  override;
        virtual void redraw() override;
        virtual int handle(int ev) override;

        virtual void draw_box() override;
        virtual void draw_box(BOX_TYPE t, glm::vec4 c) override;
        virtual void draw_box(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) override;

        virtual void draw_focus() override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg)  override;
        virtual void draw_label() override;
        virtual void draw_label(float X, float Y, float W, float H) override;
        

        void send_event(Frtk_Widget& w, int ev);

        int Frtk_GrpWidget::findIndex(const std::shared_ptr<Frtk_Widget>& w) const;
        void remove_children(size_t index);
        void remove_all();

        void Frtk_GrpWidget::addChild(std::shared_ptr<Frtk_Widget> w);

    protected:
        std::vector<std::shared_ptr<Frtk_Widget>> m_children;

    private:

    };
}
#endif // !FRTK_GRPWIDGET_H
