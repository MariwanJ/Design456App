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

#define FRTK_NO_BORDER      0.0f
#define FRTK_THIN_BORDER    0.3f
#define FRTK_NORMAL_BORDER  2.0f
#define FRTK_THICK_BORDER   3.0f

   //TODO: Temporary code -- FIXME
    typedef struct {
        int fontNormal, fontBold, fontIcons, fontEmoji;
    }FontData_t;


    typedef enum {
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
                                      
    }BOX_TYPE;

    typedef struct {
        dimPos_float_t pos  ;
        dimSize_float_t size ;
        dimPos_float_t realPos;
        NVGcolor forgColor  ;
        NVGcolor shadowCol  ;
        float fontSize  ;
        std::string fName;
        dimPos_float_t  shadowOffs  ;
        float blur  ;
        int lblAlign  ; //for labels of widgets
        int txtAlign  ; //for text (special for input widgets
        float Rotate;
    }font_t;

    //frtk_no_box
    void drawFilledRect(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth= FRTK_NORMAL_BORDER, 
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW), 
        bool up = false);
    //Frtk_box_up/down - Square or rounded edges based on r
    void drawBoxUpDown(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW), bool up = true);

     

    //Frtk_up_frame:      frtk_down_frame:     frtk_thin_up_frame:     frtk_thin_down_frame:
    void drawFrameRect(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor c, NVGcolor shadowCol, bool up);

    //Frtk_diamond_up_box:  frtk_diamond_down_box:
    void drawDiamondWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);

    void drawSolidCircleWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawOvalFrameWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawSolidOvalWithState(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawShadowBox(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    void drawOvalFLAT(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);
    
    void drawOval(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = FRTK_NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHT_GRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW),
        bool up = false);

    void draw_nice_round_box(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor col, NVGcolor shadowCol, bool up);
    void draw_nice_squre(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool pressed);

    void draw_box(NVGcontext* vg, BOX_TYPE b, Dim_float_t dim, float cornerRadius, float strokeWidth, NVGcolor c, NVGcolor shadowCol, bool up);

    float getTextLeftBearing(NVGcontext* vg, const std::string& text, const font_t& fnt);

    //Horizontal = NVG_ALIGN_CENTER,    NVG_ALIGN_LEFT / NVG_ALIGN_CENTER / NVG_ALIGN_RIGHT
    //Vertical =  NVG_ALIGN_MIDDLE    NVG_ALIGN_TOP / NVG_ALIGN_MIDDLE / NVG_ALIGN_BOTTOM
    //Rotation =0.0 by default
    void drawTextInBox(NVGcontext* vg, const std::string& text, font_t& fnt, bool isLabel, FontData_t &fnttData, const char *secrete = 0);

    // Function to draw a check mark with default color = BLACK
    void drawCheckMark(NVGcontext* vg, float x, float y, float size, NVGcolor col = nvgRGBAf(FR_BLACK));

}




#endif // !FRTK_DDRAW_H
