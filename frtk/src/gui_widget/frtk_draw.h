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

#ifndef FRTK_DRAW_H
#define FRTK_DRAW_H
/*
            Every Basic Drawing should be implemented here. 

*/
#include <fr_core.h>
#include <nanovg.h>

namespace FR {

#define NO_BORDER      0.0f
#define THIN_BORDER    0.3f
#define NORMAL_BORDER  2.0f
#define THICK_BORDER   3.0f

    typedef enum LBL_ALIGN {
        FRTK_ALIGN_CENTER = 0,
        FRTK_ALIGN_TOP = 1,
        FRTK_ALIGN_BOTTOM = 2,
        FRTK_ALIGN_LEFT = 4,
        FRTK_ALIGN_RIGHT = 8,
        FRTK_ALIGN_INSIDE = 16,
        FRTK_ALIGN_TOP_LEFT = FRTK_ALIGN_TOP | FRTK_ALIGN_LEFT,
        FRTK_ALIGN_TOP_RIGHT = FRTK_ALIGN_TOP | FRTK_ALIGN_RIGHT,
        FRTK_ALIGN_BOTTOM_LEFT = FRTK_ALIGN_BOTTOM | FRTK_ALIGN_LEFT,
        FRTK_ALIGN_BOTTOM_RIGHT = FRTK_ALIGN_BOTTOM | FRTK_ALIGN_RIGHT,

        FRTK_ALIGN_CENTER_LEFT = FRTK_ALIGN_CENTER | FRTK_ALIGN_LEFT,
        FRTK_ALIGN_CENTER_RIGHT = FRTK_ALIGN_CENTER | FRTK_ALIGN_RIGHT,
        FRTK_ALIGN_CENTER_CENTER = FRTK_ALIGN_CENTER | FRTK_ALIGN_CENTER,

    };
    typedef enum BOX_TYPE {
        FRTK_NO_BOX                =  0,
        FRTK_FLAT_BOX              =  1,
        FRTK_UP_BOX                =  2,
        FRTK_DOWN_BOX              =  3,
        FRTK_THIN_UP_BOX           =  4,
        FRTK_THIN_DOWN_BOX         =  5,

        FRTK_ROUNDED_BOX_UP        =  6,
        FRTK_ROUNDED_BOX_DOWN      =  7,
                                     
        FRTK_ROUND_UP_BOX          =  8,
        FRTK_ROUND_DOWN_BOX        =  9,
        FRTK_ROUND_FLAT_BOX        = 10,
                                     
                                      
        FRTK_UP_FRAME              = 11,
        FRTK_DOWN_FRAME            = 12,
        FRTK_ROUNDED_UP_FRAME      = 13,
        FRTK_ROUNDED_DOWN_FRAME    = 14,
                                      
        FRTK_THIN_UP_FRAME         = 15,
        FRTK_THIN_DOWN_FRAME       = 16,
                                      
        FRTK_ROUND_SHADOW_UP_BOX   = 17,
        FRTK_ROUND_SHADOW_DOWN_BOX = 18,
                                      
        FRTK_DIAMOND_UP_BOX        = 19,
        FRTK_DIAMOND_DOWN_BOX      = 20,
                                      
        FRTK_OVALFLAT_BOX          = 21,
        FRTK_OVAL_UP_BOX           = 22,
        FRTK_OVAL_DOWN_BOX         = 23,
        FRTK_OVAL_UP_FRAME         = 24,
        FRTK_OVAL_DOWN_FRAME       = 25,

        FRTK_OSHADOW_UP_BOX        = 26,
        FRTK_OSHADOW_DOWN_BOX      = 27,
                                      
    };

    typedef struct {
        dimPos_float_t pos  ;
        dimSize_float_t size ;
        NVGcolor forgColor  ;
        NVGcolor shadowCol  ;
        float fontSize  ;
        std::string fName;
        dimPos_float_t  shadowOffs  ;
        float blur  ;
        int vAlign  ;
        int hAlign  ;
        float Rotate;
    }font_t;

    //frtk_no_box
    void drawFilledRect(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth= NORMAL_BORDER, 
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW), 
        bool up = false);
    //Frtk_box_up/down - Square or rounded edges based on r
    void drawBoxUpDown(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW), bool up = true);

     

    //Frtk_up_frame:      frtk_down_frame:     frtk_thin_up_frame:     frtk_thin_down_frame:
    void drawFrameRect(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor c, NVGcolor shadowCol, bool up);

    //Frtk_diamond_up_box:  frtk_diamond_down_box:
    void drawDiamondWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);

    void drawSolidCircleWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawOvalFrameWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawSolidOvalWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawShadowBox(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    void drawOvalFLAT(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawOval(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);

    void draw_box(NVGcontext* vg, BOX_TYPE b, Dim_float_t dim, float cornerRadius, float strokeWidth, NVGcolor c, NVGcolor shadowCol, bool up);

    float getTextLeftBearing(NVGcontext* vg, const std::string& text, const font_t& fnt);

    //Horizontal = NVG_ALIGN_CENTER,    NVG_ALIGN_LEFT / NVG_ALIGN_CENTER / NVG_ALIGN_RIGHT
    //Vertical =  NVG_ALIGN_MIDDLE    NVG_ALIGN_TOP / NVG_ALIGN_MIDDLE / NVG_ALIGN_BOTTOM
    //Rotation =0.0 by default
    void drawTextInBox(NVGcontext* vg, const std::string& text, font_t& fnt);

    // Function to draw a check mark with default color = BLACK
    void drawCheckMark(NVGcontext* vg, float x, float y, float size, NVGcolor col = nvgRGBAf(FR_BLACK));

}




#endif // !FRTK_DDRAW_H
