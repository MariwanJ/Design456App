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
        dimPos_float_t pos = { 0.0f,0.0f };
        dimSize_float_t size = { 30.0f, 14.f*1.3f};
        NVGcolor forgColor = nvgRGBA(0, 0, 0, 255);
        NVGcolor shadowCol = nvgRGBA(255, 255, 255, 255);
        float fontSize = 14.0f;
        std::string fName = "sans";
        dimPos_float_t  shadowOffs = { 0.0f,0.0f };
        float blur = 2.0f;
        int vAlign = NVG_ALIGN_MIDDLE;
        int hAlign = NVG_ALIGN_LEFT ;
    }font_t;


    void drawBoxUpDown(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth = NORMAL_BORDER,
        NVGcolor baseCol = nvgRGBAf(FR_LIGHTGRAY),
        NVGcolor shadowColor = nvgRGBAf(FR_DARK_SHADOW), bool up = true);

     

    

    float getTextWidth(NVGcontext* vg, const std::string& str, float fontSize = 14.0f, const char* fontFace = "sans", int align = NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
    void draw_box(NVGcontext* vg, BOX_TYPE b, Dim_float_t dim, float cornerRadius=0.0f, float strokeWidth=1.0f, 
                    NVGcolor c = nvgRGBAf(FR_BLANCHEDALMOND), NVGcolor shadowCol= nvgRGBAf(FR_DARK_SHADOW), bool up=true);

    
    //TEXT Drawing :: 
   // void draw_label(NVGcontext* vg, const std::string& text,  font_t& fnt);
    void drawTextInBox(NVGcontext* vg, const std::string& text, font_t& fnt);



}

#endif // !FRTK_DDRAW_H
