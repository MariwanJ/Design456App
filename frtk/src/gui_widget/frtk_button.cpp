#include "frtk_button.h"

// class constructor
namespace FR {
    Frtk_Button::Frtk_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Box(vg, x, y, w, h, l, b), m_cellStyle(FR_PIC_LEFTTO_TEXT_CENTER), m_value(-1)
    {
        assert(vg != NULL);
        m_value = 0;
        m_wdgType = FRTK_TOOLBAR_BUTTON;
        m_color = glm::vec4(FR_LIGHTGRAY);
    }

    void Frtk_Button::cellStyle(FRTK_PICTXT_STYLE StyleType)
    {
        m_cellStyle = StyleType;
        redraw();
    }
    int Frtk_Button::cellStyle() const
    {
        return m_cellStyle;
    }

    void Frtk_Button::draw()
    {
        Dim_float_t t = { (m_x,m_y),(m_w,m_h) };
        if (m_value == 0) {
            //UP
            draw_box(m_vg, m_boxType, m_dim, 0.0f, THICK_BORDER, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a), nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), true);
        }
        else if (m_value == 1)
        {
            //DOWN
            draw_box(m_vg, (BOX_TYPE)((int)(m_boxType)+1), m_dim, 0.0f, THICK_BORDER, nvgRGBAf(m_color.r, m_color.g, m_color.b, m_color.a), nvgRGBAf(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_borderColor.a), false);
        }
        else
        {
            //Inactive
        }
        if (m_IconTexture != 0)
            drawImage(m_x, m_y, m_w, m_h);
        drawLabel();
        switch (m_cellStyle) {
        case FR_PIC_OVER_TEXT_CENTER: {
        } break;
        case FR_PIC_OVER_TEXT_LEFT: {
        } break;
        case FR_PIC_OVER_TEXT_RIGHT: {
        } break;
        case FR_PIC_UNDER_TEXT_CENTER: {
        } break;
        case FR_PIC_UNDER_TEXT_LEFT: {
        } break;
        case FR_PIC_UNDER_TEXT_RIGHT: {
        } break;
        case FR_PIC_LEFTTO_TEXT_CENTER: {
        } break;
        case FR_PIC_LEFTTO_TEXT_LEFT: {
        } break;
        case FR_PIC_LEFTTO_TEXT_RIGHT: {
        } break;
        case FR_PIC_RIGHTTO_TEXT_CENTER: {
        } break;
        case FR_PIC_RIGHTTO_TEXT_LEFT: {
        } break;
        case FR_PIC_RIGHTTO_TEXT_RIGHT: {
        } break;
        }
    }
    int Frtk_Button::handle(int e) {
        if (should_getEvent(false)) {
            if (e == FR_LEFT_PUSH) {
                m_value = 1;
                callback();
                return 1;
            }
            else if (e == FR_LEFT_RELEASE) {
                m_value = 0;
                //callback(); Optional if you want to execute the callback even when mouse is released.
                return 1;
            }
        }
        return 0;
    }
}