//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FRTK_GRPWIDGET_H
#define FRTK_GRPWIDGET_H

#include <fr_core.h>
#include <gui_widget/frtk_widget.h>

class Frtk_Window;

namespace FR {
    class Frtk_GrpWidget : public Frtk_Widget {
        friend Frtk_Window;
    public:
        Frtk_GrpWidget(NVGcontext* vg, float X , float Y , float W , float H , std::string label = "", BOX_TYPE b = FRTK_NO_BOX);
        virtual ~Frtk_GrpWidget();

        virtual void draw_children();

        virtual void redraw() override;
        bool restore_focus();

        virtual void drawBox() override;
        virtual void drawBox(BOX_TYPE t, glm::vec4 c) override;
        virtual void drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) override;

        int send_event(Frtk_Widget& w, int ev);

        virtual int findIndex(const std::shared_ptr<Frtk_Widget>& w) const;
        virtual std::shared_ptr<Frtk_Widget>  getChildAt(size_t index);
        virtual int getChildrenNo();
        virtual int remove_child_at(size_t index);
        virtual int remove_child(std::shared_ptr<Frtk_Widget> &wdg);
        virtual void remove_all();

        virtual void addChild(std::shared_ptr<Frtk_Widget> w);
        virtual bool navigate_focus(int key);
        Frtk_Widget* first_focusable_widget();
        //Return a const reference to prevent modification
        const std::vector<std::shared_ptr<Frtk_Widget>>& getChildren() const;
        virtual void lose_focus() override;
        Frtk_Widget* focusedChild();
        virtual bool set_child_focus(Frtk_Widget* w=nullptr) override;
        virtual bool take_focus() override;
    protected:
        Frtk_Window* Frtk_GrpWidget::getParentWindow();
        virtual void draw()  override;
        virtual int handle(int ev) override;
        dimPos_float_t mainGui() const override;
        std::vector<std::shared_ptr<Frtk_Widget>> m_children;
        Frtk_Widget* m_childFocus;  //keep track of focused widget
        Frtk_Widget* m_grabbedChild;
    private:
    };
}
#endif // !FRTK_GRPWIDGET_H
