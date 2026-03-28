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

#include <gui_widget/frtk_color_picker.h>

namespace FR {
    Frtk_Color_Picker::Frtk_Color_Picker(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_Box(vg, X, Y, W, H, lbl, b), m_pickerDeg(0.0f), m_picked{ 1.0f },
        m_baseDim{ 0.f }, m_pickerDim{ 0.f }, m_padWidt{ 20.0f }, m_Tdraggin(false), m_Cdraggin(false)
    {
        r = (m_w < m_h ? m_w : m_h) * 0.5f - 31.0f;
        m_Tripicker.pos.x = cosf(120.0f / 180.0f * NVG_PI) * r * 0.3f;
        m_Tripicker.pos.y = sinf(120.0f / 180.0f * NVG_PI) * r * 0.4f;

        triangelDim.ax = cosf(120.0f / 180.0f * NVG_PI) * r;
        triangelDim.ay = sinf(120.0f / 180.0f * NVG_PI) * r;
        triangelDim.bx = cosf(-120.0f / 180.0f * NVG_PI) * r;
        triangelDim.by = sinf(-120.0f / 180.0f * NVG_PI) * r;
    }

    glm::vec4 Frtk_Color_Picker::pickedColorRGBA()
    {
        return m_picked;
    }

    HSV_t Frtk_Color_Picker::pickedColorHSV()
    {
        float r = m_picked.r;
        float g = m_picked.g;
        float b = m_picked.b;

        float cmax = glm::max(r, glm::max(g, b));
        float cmin = glm::min(r, glm::min(g, b));
        float delta = cmax - cmin;

        HSV_t result;
        result.v = cmax;
        result.s = (cmax == 0.0f) ? 0.0f : delta / cmax;
        if (delta == 0.0f) {
            result.h = 0.0f;
        }
        else if (cmax == r) {
            result.h = 60.0f * fmod((g - b) / delta, 6.0f);
        }
        else if (cmax == g) {
            result.h = 60.0f * ((b - r) / delta + 2.0f);
        }
        else {
            result.h = 60.0f * ((r - g) / delta + 4.0f);
        }

        if (result.h < 0.0f)
            result.h += 360.0f;

        return result;
    }
    
    NVGcolor Frtk_Color_Picker::pickedColorNVG()
    {
        return nvgRGBAf(m_picked.r, m_picked.g, m_picked.b, m_picked.a);
    }

    CMYK_t Frtk_Color_Picker::pickedColorCMYK()
    {
        float r = m_picked.r;
        float g = m_picked.g;
        float b = m_picked.b;

        // find k first
        float k = 1.0f - glm::max(r, glm::max(g, b));

        // avoid division by zero (pure black)
        if (k == 1.0f)
            return { 0.0f, 0.0f, 0.0f, 1.0f };

        CMYK_t result;
        result.c = (1.0f - r - k) / (1.0f - k);
        result.m = (1.0f - g - k) / (1.0f - k);
        result.y = (1.0f - b - k) / (1.0f - k);
        result.k = k;

        return result;
    }

    bool Frtk_Color_Picker::insideColorPad() {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        float cx = absX() + m_w / 2;
        float cy = absY() + m_h / 2;

        float dx = mouse.activeX - cx;
        float dy = mouse.activeY - cy;
        float dist = sqrt(dx * dx + dy * dy);

        float r_inner = r;
        float r_outer = r + 20;
        bool result = (dist >= r_inner && dist <= r_outer);
        FRTK_CORE_INFO("{}", result);
        return result;
    }

    bool Frtk_Color_Picker::insideTriangle() {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        float cx = absX() + m_w / 2;
        float cy = absY() + m_h / 2;
        float mx = mouse.activeX - cx;
        float my = mouse.activeY - cy;

        float v0x = r * cos(glm::radians(m_pickerDeg));
        float v0y = r * sin(glm::radians(m_pickerDeg));
        float v1x = r * cos(glm::radians(m_pickerDeg) + 2 * M_PI / 3);
        float v1y = r * sin(glm::radians(m_pickerDeg) + 2 * M_PI / 3);
        float v2x = r * cos(glm::radians(m_pickerDeg) + 4 * M_PI / 3);
        float v2y = r * sin(glm::radians(m_pickerDeg) + 4 * M_PI / 3);

        auto cross = [](float ax, float ay, float bx, float by, float px, float py) {
            return (bx - ax) * (py - ay) - (by - ay) * (px - ax);
            };

        float d0 = cross(v0x, v0y, v1x, v1y, mx, my);
        float d1 = cross(v1x, v1y, v2x, v2y, mx, my);
        float d2 = cross(v2x, v2y, v0x, v0y, mx, my);
        bool result = (d0 >= 0 && d1 >= 0 && d2 >= 0) || (d0 <= 0 && d1 <= 0 && d2 <= 0);
        FRTK_CORE_INFO("{}", result);
        return result;
    }

    float Frtk_Color_Picker::pickerDeg()
    {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        float cx = absX() + m_w / 2;
        float cy = absY() + m_h / 2;
        float dx = mouse.activeX - cx;
        float dy = mouse.activeY - cy;

        float hue = atan2(dy, dx);
        if (hue < 0)
            hue += 2 * M_PI;

        m_pickerDeg = glm::degrees(hue);  // shift so 12 o'clock = 0°
        if (m_pickerDeg >= 360.0f)
            m_pickerDeg -= 360.0f;

        return m_pickerDeg;
    }

    glm::vec4 Frtk_Color_Picker::colorFromTriangle() {
        float mx = m_Tripicker.pos.x;
        float my = m_Tripicker.pos.y;

        // triangle vertices
        float x0 = r, y0 = 0;
        float x1 = triangelDim.ax, y1 = triangelDim.ay;
        float x2 = triangelDim.bx, y2 = triangelDim.by;

        float denom = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2);
        float l0 = ((y1 - y2) * (mx - x2) + (x2 - x1) * (my - y2)) / denom;
        float l1 = ((y2 - y0) * (mx - x2) + (x0 - x2) * (my - y2)) / denom;
        float l2 = 1.0f - l0 - l1;

        l0 = glm::clamp(l0, 0.0f, 1.0f);
        l1 = glm::clamp(l1, 0.0f, 1.0f);
        l2 = glm::clamp(l2, 0.0f, 1.0f);

        NVGcolor hueColor = nvgHSLA(m_pickerDeg / 360.0f, 1.0f, 0.5f, 255);

        glm::vec4 result;
        result.r = hueColor.r * l0 + 1.0f * l1 + 0.0f * l2;
        result.g = hueColor.g * l0 + 1.0f * l1 + 0.0f * l2;
        result.b = hueColor.b * l0 + 1.0f * l1 + 0.0f * l2;
        result.a = 1.0f;
        return result;
    }


    void Frtk_Color_Picker::draw_pad_cursor() {
        float r1 = (m_w < m_h ? m_w : m_h) * 0.5f - 5.0f;
        float r0 = r1 - m_padWidt;

        nvgStrokeWidth(m_vg, 2.0f);
        nvgBeginPath(m_vg);
        nvgRect(m_vg, r0 - 1, -3, r1 - r0 + 2, 6);
        nvgStrokeColor(m_vg, nvgRGBAf(1.f, 1.f, 1.f, 0.75f));
        nvgStroke(m_vg);

        NVGpaint paint = nvgBoxGradient(m_vg, r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.5f), nvgRGBAf(0.0f, 0.0f, 0.0f, 0.0f));
        nvgBeginPath(m_vg);
        nvgRect(m_vg, r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
        nvgRect(m_vg, r0 - 2, -4, r1 - r0 + 4, 8);
        nvgPathWinding(m_vg, NVG_HOLE);
        nvgFillPaint(m_vg, paint);
        nvgFill(m_vg);
    }
    void Frtk_Color_Picker::drawOuterCircleColorPad() {
        float r1 = (m_w < m_h ? m_w : m_h) * 0.5f - 5.0f;
        float r0 = r1 - m_padWidt;
        float cx = m_x + m_w * 0.5f;
        float cy = m_y + m_h * 0.5f;
        nvgBeginPath(m_vg);
        nvgCircle(m_vg, cx, cy, r0 - 0.5f);
        nvgCircle(m_vg, cx, cy, r1 + 0.5f);
        nvgStrokeColor(m_vg, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.15f));
        nvgStrokeWidth(m_vg, 1.0f);
        nvgStroke(m_vg);
    }


    void Frtk_Color_Picker::draw_colPad() {
        float ax, ay, bx, by, aeps;
        int i;
        triangelDim.center.pos.x = m_x + m_w * 0.5f;
        triangelDim.center.pos.y = m_y + m_h * 0.5f;

        float r1 = (m_w < m_h ? m_w : m_h) * 0.5f - 5.0f;
        float r0 = r1 - m_padWidt;
        aeps = 0.5f / r1;
        for (i = 0; i < 6; i++) {
            float a0 = (float)i / 6.0f * NVG_PI * 2.0f - aeps;
            float a1 = (float)(i + 1.0f) / 6.0f * NVG_PI * 2.0f + aeps;
            nvgBeginPath(m_vg);
            nvgArc(m_vg, triangelDim.center.pos.x, triangelDim.center.pos.y, r0, a0, a1, NVG_CW);
            nvgArc(m_vg, triangelDim.center.pos.x, triangelDim.center.pos.y, r1, a1, a0, NVG_CCW);
            nvgClosePath(m_vg);
            ax = triangelDim.center.pos.x + cosf(a0) * (r0 + r1) * 0.5f;
            ay = triangelDim.center.pos.y + sinf(a0) * (r0 + r1) * 0.5f;
            bx = triangelDim.center.pos.x + cosf(a1) * (r0 + r1) * 0.5f;
            by = triangelDim.center.pos.x + sinf(a1) * (r0 + r1) * 0.5f;
            NVGpaint paint = nvgLinearGradient(m_vg, ax, ay, bx, by, nvgHSLA(a0 / (NVG_PI * 2), 1.0f, 0.55f, 255), nvgHSLA(a1 / (NVG_PI * 2), 1.0f, 0.55f, 255));
            nvgFillPaint(m_vg, paint);
            nvgFill(m_vg);
        }
        drawOuterCircleColorPad();
    }

    void Frtk_Color_Picker::baseTriangle() {
        nvgSave(m_vg);
        nvgTranslate(m_vg, m_x + m_w * 0.5f, m_y + m_h * 0.5f);
        nvgRotate(m_vg, glm::radians(m_pickerDeg));

        NVGpaint paint;
        float hue = m_pickerDeg / 360.0f;

        nvgBeginPath(m_vg);
        nvgMoveTo(m_vg, r, 0);
        nvgLineTo(m_vg, triangelDim.ax, triangelDim.ay);
        nvgLineTo(m_vg, triangelDim.bx, triangelDim.by);
        nvgClosePath(m_vg);

        paint = nvgLinearGradient(m_vg, r, 0, triangelDim.ax, triangelDim.ay,
            nvgHSLA(hue, 1.0f, 0.5f, 255), nvgRGBAf(1.f, 1.f, 1.f, 1.f));
        nvgFillPaint(m_vg, paint);
        nvgFill(m_vg);

        paint = nvgLinearGradient(m_vg, (r + triangelDim.ax) * 0.5f, (0 + triangelDim.ay) * 0.5f,
            triangelDim.bx, triangelDim.by,
            nvgRGBAf(0.0f, 0.0f, 0.0f, 0.0f), nvgRGBAf(0.0f, 0.0f, 0.0f, 1.0f));
        nvgFillPaint(m_vg, paint);
        nvgFill(m_vg);

        nvgStrokeColor(m_vg, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f));
        nvgStroke(m_vg);
        draw_pad_cursor();
        pickerInsideTriangle();
        nvgRestore(m_vg);
    }

    void Frtk_Color_Picker::pickerInsideTriangle() {
        float const whiteCirclR = 5.0f; //if we need to change it
        nvgStrokeWidth(m_vg, 2.0f);
        nvgBeginPath(m_vg);
        nvgCircle(m_vg, m_Tripicker.pos.x, m_Tripicker.pos.y, whiteCirclR);
        nvgStrokeColor(m_vg, nvgRGBAf(1.f, 1.f, 1.f, 0.75f));
        nvgStroke(m_vg);

        NVGpaint paint = nvgRadialGradient(m_vg, m_Tripicker.pos.x, m_Tripicker.pos.y, 7, 9, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.25f), nvgRGBAf(0.0f, 0.0f, 0.0f, 0.0f));
        nvgBeginPath(m_vg);
        nvgRect(m_vg, m_Tripicker.pos.x - 20, m_Tripicker.pos.y - 20, 40, 40);
        nvgCircle(m_vg, m_Tripicker.pos.x, m_Tripicker.pos.y, 7);
        nvgPathWinding(m_vg, NVG_HOLE);
        nvgFillPaint(m_vg, paint);
        nvgFill(m_vg);
    }
    void Frtk_Color_Picker::draw() {
        draw_box(m_vg, m_boxType, { {m_x,m_y}, {m_w,m_h} }, m_cornerRadius, FRTK_NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        draw_colPad();
        baseTriangle();
    }
    void Frtk_Color_Picker::updateMousePos() {

        auto mouse = m_mainWindow->m_sysEvents.mouse;

        float dx = mouse.activeX - mouse.prevX;
        float dy = mouse.activeY - mouse.prevY;

        float angle = -glm::radians(m_pickerDeg);
        float cosA = cos(angle);
        float sinA = sin(angle);

        float localDX = dx * cosA - dy * sinA;
        float localDY = dx * sinA + dy * cosA;

        m_Tripicker.pos.x += localDX;
        m_Tripicker.pos.y += localDY;

        float x0 = r;
        float y0 = 0;
        float x1 = triangelDim.ax;
        float y1 = triangelDim.ay;
        float x2 = triangelDim.bx;
        float y2 = triangelDim.by;

        float mx = m_Tripicker.pos.x;
        float my = m_Tripicker.pos.y;

        float denom = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2);

        float l0 = ((y1 - y2) * (mx - x2) + (x2 - x1) * (my - y2)) / denom;
        float l1 = ((y2 - y0) * (mx - x2) + (x0 - x2) * (my - y2)) / denom;
        float l2 = 1.0f - l0 - l1;

        l0 = glm::clamp(l0, 0.0f, 1.0f);
        l1 = glm::clamp(l1, 0.0f, 1.0f);
        l2 = glm::clamp(l2, 0.0f, 1.0f);

        float sum = l0 + l1 + l2;
        l0 /= sum;
        l1 /= sum;
        l2 /= sum;

        m_Tripicker.pos.x = l0 * x0 + l1 * x1 + l2 * x2;
        m_Tripicker.pos.y = l0 * y0 + l1 * y1 + l2 * y2;
    }

    int Frtk_Color_Picker::handle(int ev)
    {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        if (ev == FR_LEFT_DRAG_PUSH || ev == FR_LEFT_PUSH || ev == FR_LEFT_DRAG_MOVE) {
            if (insideColorPad()) {
                if(!m_Cdraggin)
                    m_Tdraggin = true;
                pickerDeg();
                
            }else
                if (insideTriangle()) {
                    if(!m_Tdraggin)
                    m_Cdraggin = true;
                    updateMousePos();
                    do_callback();
                }
        }
        else if (ev == FR_LEFT_DRAG_RELEASE || ev == FR_LEFT_RELEASE) {
            m_Tdraggin = true;
            m_Cdraggin = true;
            m_picked = colorFromTriangle();
            do_callback();
        }
        return 0;
    }
}