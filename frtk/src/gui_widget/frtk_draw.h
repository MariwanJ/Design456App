#ifndef FRTK_DDRAW_H
#define FRTK_DDRAW_H
/*
            Every Basic Drawing should be implemented here. 

*/
#include <fr_core.h>

namespace FR{

    enum class LBL_ALIGN {
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
    enum class BOX_TYPE {
        FRTK_NO_BOX = 0        ,        
        FRTK_DOWN_BOX          ,         
        FRTK_UP_BOX            ,     
        FRTK_UP_FRAME          ,         
        FRTK_DOWN_FRAME        ,         
        FRTK_THIN_UP_BOX       ,             
        FRTK_THIN_DOWN_BOX     ,             
        FRTK_THIN_UP_FRAME     ,             
        FRTK_THIN_DOWN_FRAME   ,                 
                               
        FRTK_ROUNDED_BOX       ,
        FRTK_RSHADOW_BOX       ,
        FRTK_ROUNDED_FRAME     ,
        FRTK_RFLAT_BOX         ,
        FRTK_ROUND_UP_BOX      ,
        FRTK_ROUND_DOWN_BOX    ,
        FRTK_DIAMOND_UP_BOX    ,
        FRTK_DIAMOND_DOWN_BOX  ,
        FRTK_OVAL_BOX          ,
        FRTK_OSHADOW_BOX       ,
        FRTK_OVAL_FRAME        ,
        FRTK_OVALFLAT_BOX      ,
    };


    void draw_box(NVGcontext vg, BOX_TYPE b, float x, float y, float w, float  h , FR_COLOR c);
    void draw_box(NVGcontext vg, BOX_TYPE b, float x, float y, float w, float  h, FR_COLOR c);

}

#endif // !FRTK_DDRAW_H
