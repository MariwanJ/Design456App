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

#include <gui_widget/frtk_toolbar.h>

namespace FR {
    Frtk_ToolBar::Frtk_ToolBar(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl,
        const std::vector<toolbBTN_t>& tools, bool horizontal, BOX_TYPE b) :
                     Frtk_GrpWidget(vg, X, Y, W, H, lbl, b) , 
                      m_padding(1.0f),m_horizontal(horizontal) {
        m_wdgType = FRTK_TOOLBAR;
        btnDim = { 0.0f,Y + 1.f }; //offset 1.0 pixel
        addButton(tools);
        if (!horizontal) {
            m_font.Rotate = 90.0;  //Will be converted internally for NanoVG
        }
    }
    Frtk_ToolBar::~Frtk_ToolBar()
    {
    }
    void Frtk_ToolBar::horizontal(bool val)
    {
        m_horizontal = val;
    }

    void Frtk_ToolBar::addButton(const std::vector<toolbBTN_t>& btns)
    {
        if (m_horizontal)
            btnDim = { 0.0f, 1.0f };
        else
            btnDim = { 1.0f, 0.0f };

            //Make sure that the toolbar has a correct dimension, user MUST make sure the dimension is correct 
            if(m_horizontal)
                FRTK_CORE_APP_ASSERT( (m_w) >= ((float)btns.size() * FRTK_TOOLBAR_HEIGHT ));
            else
                FRTK_CORE_APP_ASSERT( (m_h) >=((float) btns.size() * FRTK_TOOLBAR_HEIGHT ));

        for (const auto& item : btns) {
            auto btn = std::make_shared<Frtk_ToolBar_Button>(m_vg,btnDim.x, btnDim.y, item.size.w, item.size.h, item.lbl);
            btn->name(item.name);
            btn->tooltips(item.tooltips);

            
            if(m_horizontal){
                btnDim.x += item.size.w+m_padding;
            }
            else
            {
                //Vertical Toolbar
                btnDim.y += item.size.h + m_padding;
            }
            btn->wdgImage(item.icon);
            btn->cellStyle(FR_IMG_OVER_TEXT_CENTER);
            btn->set_callback(item.callback_);
            addChild(btn);
        }
    }

    int Frtk_ToolBar::removeButton(size_t index)
    {
        return remove_child_at(index);
    }
    //We need to have names for the buttons as it is not sure we have label.
    int Frtk_ToolBar::removeButton(std::string& name)
    {
        for (auto& wdg : m_children){
            if (auto* btn = dynamic_cast<Frtk_ToolBar_Button*>(wdg.get()))
                if (btn->name() == name) {
                    remove_child(wdg);
                    return 0;
            }
        }
        return -1; //failed     
    }
   
}