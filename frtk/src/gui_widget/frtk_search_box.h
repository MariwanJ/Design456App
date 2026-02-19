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

#ifndef  FRTK_SEARCH_BOX_H
#define  FRTK_SEARCH_BOX_H

#include <frtk.h>
#include <gui_widget/frtk_input_base.h>
#include <gui_widget/frtk_draw.h>



    namespace FR {
        class Frtk_Search_Box : public Frtk_Input_Base {
        public:
            Frtk_Search_Box(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b = FRTK_FLAT_BOX);
            int value(const std::string& str);

        protected:
            virtual int handle(int ev) override;
            virtual void draw();


            virtual void draw_focus() override;
            virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
            virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) override;
            


            std::string m_searchWords;

            dimPos_float_t m_SearchIconPos;
            dimPos_float_t m_CloseIconPos;

            int m_cursorPos;
            int m_mark;
            int m_tab_nav;
            float m_cornerRadius;

        };
}
#endif // ! FRTK_SEARCH_BOX_H
