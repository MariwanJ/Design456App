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

#ifndef FRTK_TAB_H
#define FRTK_TAB_H
#include <gui_widget/frtk_button.h>
#include <gui_widget/frtk_grpwidget.h>
namespace FR {
#define TAB_BUTTON_SIZE 20.0f
#define padding         5.f
    FRTK_API class Frtk_Tabwdg : public Frtk_GrpWidget {
    public:
        Frtk_Tabwdg(NVGcontext* vg, float w, float h, std::string l = "Tabwdg", BOX_TYPE b = FRTK_FLAT_BOX);
        void setHeaderDim(float X, float Y, float W, float H);
        void setBodyDim (float X, float Y, float W, float H);
        Dim_float_t getHeadDim();
        Dim_float_t getBodyDim();

    protected:
        virtual int handle(int ev) override;
        virtual void draw() override;
        virtual void drawLabel() override;
        virtual void draw_tabHeader();
        virtual void draw_focus() override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) override;
        std::vector<std::shared_ptr<Frtk_GrpWidget>> m_tab;
        void init_headwidth();

    private:
        void draWBody();
        float m_headSapce;
        float m_headWidth;
        Dim_float_t m_headDim;
        Dim_float_t m_bodyDim;
    };

    FRTK_API class Frtk_Tab : public Frtk_GrpWidget {
    public:
        Frtk_Tab(NVGcontext* vg, float x, float y, float w, float h, std::string l = "Tab", BOX_TYPE b = FRTK_UP_BOX);
        virtual std::shared_ptr < Frtk_Tabwdg> addTab();
        void layoutTabs();

    protected:
        virtual int handle(int ev) override;

        virtual void draw() override;
        std::vector<std::shared_ptr<Frtk_Tabwdg>> m_tabChildren;
        std::vector<Frtk_Button> m_navButton;

    private:
        
    };
}
#endif //FRTK_TAB_H