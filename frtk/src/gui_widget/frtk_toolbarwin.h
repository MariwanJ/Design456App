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

#ifndef FRTK_TOOLBARWIN_H
#define FRTK_TOOLBARWIN_H

#include <gui_widget/frtk_window.h>
#include <gui_widget/frtk_draw.h>
#include<gui_widget/frtk_toolbar_button.h>

namespace FR {

    struct toolbBTN_t {
        std::string lbl;
        std::string name;
        dimSize_float_t size;
        std::string icon;
        Frtk_Widget::Callback callback_;
        BOX_TYPE boxType;
        std::string tooltips; //not implemented yet!!
    };

    class FRTK_API  Frtk_ToolBarWin : public Frtk_Window
    {
    public:
        Frtk_ToolBarWin(float , float Y , float W , float H, std::string lbl, const std::vector<toolbBTN_t>& tools = {}, bool horizontal=true, BOX_TYPE b = FRTK_UP_BOX, WIDGTYPE btnType= FRTK_TOOLBAR_BUTTON);
        void    dockable(bool val);
        bool    dockable();
        void horizontal(bool val);
        
        virtual void addButton(const std::vector<toolbBTN_t>& btns);
        virtual int removeButton(const std::string & name);
        virtual bool dockingBTN(void);
        virtual void addButtonAtPos(const std::shared_ptr<Frtk_ToolBar_Button>& w);

        Fr_Window* parent(void);
        void parent(Fr_Window* w);

    protected:
        void drawVerticalDivider();
        virtual void draw() override;
        virtual void setLayoutHorizontal();
        virtual void setLayoutVertical();
        virtual int handle(int ev)override;
        




       virtual void applyDocking(void);
        
        bool m_horizontal; //is the toolbar horizontal or vertical??
        bool m_dockable; 
        float m_padding;
        Dim_float_t m_dockingSize;
        FontData_t m_data;
        std::string default_font_path;
        Fr_Window* m_parent;
        WIDGTYPE m_buttonsType;
    };
}
#endif // FL_TOOLBAR_H
