#include <gui_widget/frtk_grpwidget.h>

namespace FR {
    Frtk_GrpWidget::Frtk_GrpWidget(float X, float Y, float W, float H, std::string label) :Frtk_Widget(X, Y, W, H, label) {
    }
    Frtk_GrpWidget::~Frtk_GrpWidget() {
    }

    void Frtk_GrpWidget::draw() {
        if (visible()){
            draw_box();
            draw_focus();
            draw_label();
            //Then draw all widgets
            for (auto wdg : m_children) {
                if(wdg->visible()){
                    wdg->draw();
                }
            }
        }
    }

    void Frtk_GrpWidget::redraw()  {
        if(visible()){
            draw();
        }
    }
    //Return = 1 Event consumed 
    //Return = 0 or -1 Event should continue to be delivered to other widgets
    int Frtk_GrpWidget::handle(int ev) {
        
        //NOTE:: Sub-class it to use it

        if (should_getEvent()) {
            for (auto wdg : m_children) {
                int result = wdg->handle(ev);
                if (result == 1) { 
                    //Event is consumed.
                    return 1;
                }
            }
        }
        return 0;
    }

    void Frtk_GrpWidget::draw_box() {
        if (visible()) {
            draw_box(BOX_TYPE::FRTK_UP_FRAME,m_x, m_y, m_w, m_h, m_color);
            for (auto wdg : m_children) {
                draw_box(wdg->boxtype(), wdg->x(), wdg->y(), wdg->w(), wdg->h(), wdg->color());
                }
            }
    }
    
    void Frtk_GrpWidget::draw_box(BOX_TYPE t, glm::vec4 c) {
        if (visible()) {
            color(c);
            draw_box(t, m_x, m_y, m_w, m_h, c);

            for (auto wdg : m_children) {
                draw_box(wdg->boxtype(), wdg->x(), wdg->y(), wdg->w(), wdg->h(), wdg->color());
            }
        }
    }
    void Frtk_GrpWidget::draw_box(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c){
        if (visible()) {
            //we should draw the box here : 
            for (auto wdg : m_children) {
                draw_box(wdg->boxtype(), wdg->x(), wdg->y(), wdg->w(), wdg->h(), wdg->color());
            }
        }
    }
    void Frtk_GrpWidget::draw_focus()  {

    }
    void Frtk_GrpWidget::draw_focus(BOX_TYPE t, float X, float Y, float W, float H)  {
    }
    void Frtk_GrpWidget::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) {
    }
    void Frtk_GrpWidget::draw_label() {
    }
    void Frtk_GrpWidget::draw_label(float X, float Y, float W, float H)  {
    }

    void Frtk_GrpWidget::send_event(Frtk_Widget& w, int ev) {
        if (w.should_getEvent()) {
            w.handle(ev);
        }
    }
    int Frtk_GrpWidget::findIndex(const std::shared_ptr<Frtk_Widget>& w) const{
        auto it = std::find(m_children.begin(), m_children.end(), w);
        if (it != m_children.end())
            return std::distance(m_children.begin(), it);
        return -1;
    }
    
    void Frtk_GrpWidget::remove_children(size_t index) {
        m_children.erase(m_children.begin() + index);
    }
    void Frtk_GrpWidget::remove_all(){
        m_children.clear();
    }
    void Frtk_GrpWidget::addChild(std::shared_ptr<Frtk_Widget> w)
    {
        m_children.push_back(std::move(w));
    }
}