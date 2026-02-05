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
#include <gui_widget/frtk_grpwidget.h>
#include <gui_widget/frtk_toolbar_button.h>

namespace FR {
    class Frtk_ToolBar : public Frtk_GrpWidget
    {
    public:
        // class constructor
        Frtk_ToolBar(NVGcontext* vg, float x, float y, float w, float h, const char* l, BOX_TYPE b = FRTK_UP_BOX);
        void    dockable(bool val);
        bool    dockable();
    protected:
        virtual  int handle(int e);
        virtual  void draw();
    private:
        bool m_dockable; 
    };
}
#endif // FL_TOOLBAR_H
