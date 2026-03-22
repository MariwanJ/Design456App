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

#ifndef FRTK_TABS_H
#define FRTK_TABS_H
#include <gui_widget/frtk_button.h>
#include <gui_widget/frtk_grpwidget.h>
#include <gui_widget/frtk_box.h>

namespace FR {
    class Frtk_Tabwdg;
#define TAB_BUTTON_SIZE 15.0f
#define Hpadding         8.0f
#define Vpadding         3.0f
#define HEIGHT_FACTOR   1.3f
    typedef struct {
        bool body;
        bool head;
    }Visibile_t;
    typedef struct {
        std::shared_ptr<Frtk_Tabwdg> m_prev;
        std::shared_ptr<Frtk_Tabwdg> m_current;
        std::shared_ptr<Frtk_Tabwdg> m_first;
        std::shared_ptr<Frtk_Tabwdg> m_last;
    }history_t;

    class Frtk_Tabs;
    class FRTK_API  Frtk_Tabwdg : public Frtk_GrpWidget {
        friend Frtk_Tabs;
    public:
        Frtk_Tabwdg(NVGcontext* vg, float w, float h, std::string l = "Tabwdg", BOX_TYPE b = FRTK_UP_BOX);
        void setHeaderDim(float X, float Y, float W, float H);
        void setBodyDim(float X, float Y, float W, float H);
        Dim_float_t getHeadDim();
        Dim_float_t getBodyDim();
        void draw_head();
        virtual void addChildToTab(std::shared_ptr<Frtk_Widget> wdg);
        virtual void show() override;
        virtual void hide() override;
        virtual void hide_children();
        virtual void show_children();
        virtual bool isTabClicked();

    protected:
        void draw_body();
        virtual void draw() override;
        virtual void drawLabel() override;
        virtual void draw_focus() override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) override;
        std::shared_ptr<Frtk_GrpWidget> m_body;
        Visibile_t m_tabParts;
        float m_headSapce;
        float m_headWidth;
        Dim_float_t m_headDim;
        Dim_float_t m_bodyDim;

    };

    //----------------------------------------------------------------------------------------------------------------------------------------


    typedef struct {
        bool btnLeft;
        bool btnRight;
    } btnTabEvent;

    typedef struct {
        bool H;
    } overTabflow_t;

    typedef struct {
        Dim_float_t btnDec;
        Dim_float_t btnInc;
        glm::vec4 btnColor;
    } ScrollTabBarAxis_t;

    typedef struct {
        ScrollTabBarAxis_t Hor;
        btnTabEvent event;
    } TabScroll_t;

    typedef struct {
        bool left;
        bool right;
    }activeTabButton_t;


    /*                      Container widget                                          */
    class FRTK_API  Frtk_Tabs : public Frtk_GrpWidget {
        friend Frtk_Tabwdg;
    public:
        Frtk_Tabs(NVGcontext* vg, float x, float y, float w, float h, std::string l = "Tab", BOX_TYPE b = FRTK_DOWN_BOX);
        virtual std::shared_ptr < Frtk_Tabwdg> addTab();
        void layoutTabs();
        virtual void show() override;
        virtual void hide() override;
        void activeTab(size_t ind);
        int findIndex(Frtk_Tabwdg* w);
        inline const Dim_float_t getViewPort() { return m_viewPort; }
        inline const Dim_float_t getContent() { return m_content; }
        inline void setOffset(const float& ofs) { m_viewOffs = ofs; }
        bool shouldClip();
        int  getIndex(std::shared_ptr < Frtk_Tabwdg> wdg);

    protected:
        bool btnUpDownLeft;
        bool btnDownDownRight;
        TabScroll_t m_scrollwdg;

    private:
        activeTabButton_t m_activeBtns;
        float m_scrollbarThickness;
        float m_minThumbSize;
        float m_trackExtra;
        float m_squarePadding;
        overTabflow_t m_overflow;
        size_t getWidthFirstLastTabs();

    protected:
        Dim_float_t m_viewPort;             //(x,y,w,h)
        Dim_float_t m_content;             //(x,y,w,h)
        float m_viewOffs;
        history_t m_history;

        void draw_scrollH();
        void updteTabBTNpos();
        bool checkOverflow();
        void updateContentSize();
        int updateBtnPressed();

        virtual void draw() override;
        virtual int handle(int ev) override;
    };
}
#endif //FRTK_TABS_H