#ifndef FRTK_BUTTON_H
#define FRTK_BUTTON_H

#include <frtk.h>
#include <gui_widget/frtk_Box.h>

namespace FR {

    typedef enum FRTK_PICTXT_STYLE
    {	// align() values
        // picture Over Text and (Center, Left & Right)
        FR_PIC_OVER_TEXT_CENTER = 0,
        FR_PIC_OVER_TEXT_LEFT = 3,
        FR_PIC_OVER_TEXT_RIGHT = 4,

        // picture Under Text and (Center,  Left & Right)
        FR_PIC_UNDER_TEXT_CENTER = 5,
        FR_PIC_UNDER_TEXT_LEFT = 8,
        FR_PIC_UNDER_TEXT_RIGHT = 9,

        // picture Left To Text and (Center,Left & Right)
        FR_PIC_LEFTTO_TEXT_CENTER = 10,
        FR_PIC_LEFTTO_TEXT_LEFT = 13,
        FR_PIC_LEFTTO_TEXT_RIGHT = 14,

        // picture Right To Text and (Center, Left & Right)
        FR_PIC_RIGHTTO_TEXT_CENTER = 15,
        FR_PIC_RIGHTTO_TEXT_LEFT = 18,
        FR_PIC_RIGHTTO_TEXT_RIGHT = 19,
    };
    class Frtk_Button : public Frtk_Box
    {
    public:
        Frtk_Button(NVGcontext*vg, float x, float y, float w, float h, std::string l, BOX_TYPE b= FRTK_UP_BOX);

        int cellStyle() const;
        void cellStyle(FRTK_PICTXT_STYLE style);
        
    protected:
        virtual void draw() override;
        virtual int  handle(int e) override;

        int m_value;   
        FRTK_PICTXT_STYLE  m_cellStyle;
    };
}
#endif // FL_BUTTON_H