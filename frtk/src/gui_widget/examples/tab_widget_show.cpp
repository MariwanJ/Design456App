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

#include<gui_widget/examples/tab_widget_show.h>

#include <gui_widget/frtk_tab.h>
#include <gui_widget/frtk_window.h>
#include <gui_widget/frtk_scroll.h>
namespace FR {
    std::shared_ptr<Frtk_Window> runTabWidget() {
        auto window = std::make_shared<Frtk_Window>(500.f, 200.f, 700.f, 700.f, "جونى باشى", FRTK_UP_BOX);
        auto tab = std::make_shared<Frtk_Tabs>(window->getContext(), 10.0f, 10.0f, 300.0f, 300.0f, "tab", FRTK_UP_BOX);
        auto btn = std::make_shared<Frtk_Button>(window->getContext(), 30.0f, 30.0f, 40.0f, 40.0f, "OK!", FRTK_UP_BOX);

        tab->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);
        for (int i = 0; i < 2; ++i) {
            auto newTab = tab->addTab();
            std::string lbl = "Tab " + std::to_string(i);
            newTab->label(lbl);
            newTab->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);
            newTab->addChildToTab(btn);
        }
        auto sc = std::make_shared<Frtk_Scroll>(window->getContext(), 450.0f, 40.0f, 20.0f, 300.0f, "OK!", FRTK_UP_BOX);
        tab->layoutTabs();
        tab->parent(window.get());
        window->addChild(tab);
        sc->parent(window.get());
        window->addChild(sc);
        return window;
    }
}