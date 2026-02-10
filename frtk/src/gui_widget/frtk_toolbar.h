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

#ifndef FRTK_TOOLBAR_H
#define FRTK_TOOLBAR_H

#include <fr_core.h>
#include <gui_widget/frtk_grpwidget.h>
#include <gui_widget/frtk_draw.h>
#include<gui_widget/frtk_toolbar_button.h>

namespace FR {

    typedef struct {
        std::string lbl;
        std::string name;
        dimSize_float_t size;
        std::string icon;
        Frtk_Widget::Callback callback_;
        std::string tooltips; //not implemented yet!!
    }toolbBTN_t;

    class Frtk_ToolBar : public Frtk_GrpWidget
    {
    public:
        Frtk_ToolBar(NVGcontext* vg, float , float Y , float W , float H, std::string lbl, const std::vector<toolbBTN_t>& tools = {}, BOX_TYPE b = FRTK_UP_BOX);
        virtual ~Frtk_ToolBar();

        void    dockable(bool val);
        bool    dockable();
        void horizontal(bool val);
        void addButton(const std::vector<toolbBTN_t>& btns);

        int removeButton(size_t index);
        int removeButton(std::string & name);
    protected:
        bool m_horizontal; //is the toolbar horizontal or vertical??
        std::shared_ptr<Frtk_ToolBar_Button> dockingBTN; //Used to interact with the toolbar itself.
        bool m_dockable; 
        dimPos_float_t btnDim;
        float m_padding;
    };
}
#endif // FL_TOOLBAR_H
