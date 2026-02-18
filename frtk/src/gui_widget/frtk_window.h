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

#ifndef FRTK_WINDOW_H
#define FRTK_WINDOW_H

#include<gui_widget/frtk_grpwidget.h>

namespace FR{


    //TODO: Temporary code -- FIXME
    typedef struct {
        int fontNormal, fontBold, fontIcons, fontEmoji;
    }FontData_t;
    
    typedef struct {
        float height;
        float bevelHeight;
        float cornerRadius;

        NVGcolor topColor;
        NVGcolor bottomColor;
        NVGcolor strokeColor;
        float strokeAlpha;
        float m_cornerRadius;
    } Frtk_HeaderStyle_t;
    
    class Frtk_Window : public Frtk_Widget {
        friend Fr_Window;
    public:
        Frtk_Window(float X, float Y, float W, float H, std::string lbl = "Frtk_Window", BOX_TYPE b=FRTK_UP_BOX, bool hasHeader = true);

        std::shared_ptr<Frtk_GrpWidget> m_guiWindow;
        void init(void);
        void drawLabel()  override;
        void drawLabel(float X, float Y, float W, float H, float rotateAngle=0.0f)   override;
        NVGcontext* getContext(void);

        virtual void remove_child_at(size_t &index);
        virtual void remove_child(std::shared_ptr<Frtk_Widget>& wdg);
        virtual void remove_all();

        virtual void addChild(std::shared_ptr<Frtk_Widget> w);

        int loadFonts();
        Frtk_HeaderStyle_t style();
        void style(Frtk_HeaderStyle_t & STYLE);
        bool Header_clicked(void);
        inline NVGcolor setAlpha(FR_COLOR& c, float alpha) { return NVGcolor{ c.R,c.G,c.B,alpha }; }
        Frtk_HeaderStyle_t m_WindowsStyle;
        
        bool hasHeader()const;
        void hasHeader(bool val);

    protected:
        virtual int handle(int event) override;
        dimPos_float_t mainGui() const override;
        bool isMouse_inside() const override;
        virtual void draw(void) override;
        virtual void draw_header();
        FontData_t m_data;
        std::string default_font_path;
        bool m_hasHeader;
    };
    
}
#endif //!FRTK_WINDOW_H
