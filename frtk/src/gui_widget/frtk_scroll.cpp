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


#include <gui_widget/frtk_scroll.h>
#include <gui_widget/frtk_draw.h>
#include <nanovg.h>

namespace FR{

    Frtk_Scroll::Frtk_Scroll(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl , BOX_TYPE b):
        Frtk_GrpWidget(vg,X,Y,W,H,lbl,b), m_scrollWidHeit({8.0f,8.0f})
    {
        
    }
    void Frtk_Scroll::draw()
    {
        draw_scroll();
    }
    void Frtk_Scroll::draw_scroll()
    {
        float t = 1.03000002e-05;
        NVGpaint shadowPaint, imgPaint, fadePaint;
        float u = (1 + cosf(t * 0.5f)) * 0.5f;
        
        if (m_Vscroll_visible) {
            // shadow of the track
            shadowPaint = nvgBoxGradient(
                m_vg,
                m_x + m_w - 12 + 1,
                m_y + 4 + 1,
                8,
                m_h - 8,
                3, 4,
                nvgRGBAf(0, 0, 0, 0.1254f),
                nvgRGBAf(0, 0, 0, 0.3607f)
            );
            nvgBeginPath(m_vg);
            nvgRoundedRect(m_vg, m_x + m_w - 12, m_y + 4, 8, m_h - 8, 3);
            nvgFillPaint(m_vg, shadowPaint);
            nvgFill(m_vg);

            // movable bar
            float barY = m_y + 4 + m_scrolloffset.y; // <-- include scroll offset
            shadowPaint = nvgBoxGradient(
                m_vg,
                m_x + m_w - 12 - 1,
                barY - 1,
                8,
                m_scrollSize.h,
                3, 4,
                nvgRGBAf(FR_GAINSBORO),
                nvgRGBAf(FR_GRAY)
            );
            nvgBeginPath(m_vg);
            nvgRoundedRect(
                m_vg,
                m_x + m_w - 12 + 1,
                barY + 1,
                8 - 2,
                m_scrollSize.h - 2,
                2
            );
            nvgFillPaint(m_vg, shadowPaint);
            nvgFill(m_vg);
        }
    }
    dimSize_float_t Frtk_Scroll::getTotalViewPortDim() const {
        dimSize_float_t result;
        result.w = m_w;
        result.h = m_h;
        if (m_Vscroll_visible)
            result.w -= m_scrollWidHeit.w;
        if (m_Hscroll_visible)
            result.h -= m_scrollWidHeit.h;
        result.w = std::max(0.f, result.w);
        result.h = std::max(0.f, result.h);
        return result;
    }


    int Frtk_Scroll::handle(int ev) {
        return 0;
    }

}



//nvgSave(ctx);
//
//// Clip to the viewport
//nvgScissor(ctx, viewportX, viewportY, viewportWidth, viewportHeight);
//
//// Translate by scroll offsets
//nvgTranslate(ctx, -mScrollX, -mScrollY);
//
//// Draw all children (as if nothing changed)
//for (auto child : children())
//child->draw(ctx);
//
//nvgRestore(ctx);