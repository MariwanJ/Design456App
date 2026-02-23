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

#include<gui_widget/frtk_draw.h>
namespace FR {
    //FRTK_NO_BOX
    void drawFilledRect(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor c, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;
        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillColor(vg, c);
        nvgFill(vg);
    }
    //FRTK_BOX_UP/DOWN
    void drawBoxUpDown(NVGcontext* vg, Dim_float_t dim, float r, float strokeWidth, NVGcolor baseCol, NVGcolor shadowColor, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        NVGcolor top = nvgLerpRGBA(baseCol, nvgRGBAf(FR_WHITE), 0.1f);
        NVGcolor bot = nvgLerpRGBA(baseCol, nvgRGBAf(FR_BLACK), 0.1f);

        NVGpaint grad = nvgLinearGradient(vg, x, y, x, y + h - r, top, bot);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillPaint(vg, grad);
        nvgFill(vg);

        NVGcolor highlight = nvgLerpRGBA(baseCol, nvgRGBAf(1.0f, 1.0f, 1.0f, baseCol.a), 0.4f);
        float offcet1 = 1.0f;
        float offcet2 = 2.0f;
        if (r == 0.0) {
            offcet1 = 0.0f;
            offcet2 = 0.0f;
        }
        if (up)
        {
            nvgBeginPath(vg);
            nvgMoveTo(vg, x, y + h - r);
            nvgLineTo(vg, x, y + r - offcet2);
            nvgLineTo(vg, x + r - offcet1, y);
            nvgLineTo(vg, x + w - r, y);
            nvgStrokeColor(vg, highlight);
            nvgStrokeWidth(vg, strokeWidth);
            nvgStroke(vg);

            nvgBeginPath(vg);
            nvgMoveTo(vg, x + r - offcet1, y + h);
            nvgLineTo(vg, x + w - r + offcet2, y + h);
            nvgLineTo(vg, x + w + offcet1, y + h - r);
            nvgLineTo(vg, x + w + offcet1, y + r);
            nvgStrokeColor(vg, shadowColor);
            nvgStrokeWidth(vg, strokeWidth);
            nvgStroke(vg);
        }
        else {
            nvgBeginPath(vg);
            nvgMoveTo(vg, x, y + h - r);
            nvgLineTo(vg, x, y + r - offcet2);
            nvgLineTo(vg, x + r - offcet1, y);
            nvgLineTo(vg, x + w - r, y);
            nvgStrokeColor(vg, shadowColor);
            nvgStrokeWidth(vg, strokeWidth);
            nvgStroke(vg);

            nvgBeginPath(vg);
            nvgMoveTo(vg, x + r - offcet1, y + h);
            nvgLineTo(vg, x + w - r + offcet2, y + h);
            nvgLineTo(vg, x + w + offcet1, y + h - r);
            nvgLineTo(vg, x + w + offcet1, y + r);
            nvgStrokeColor(vg, highlight);
            nvgStrokeWidth(vg, strokeWidth);
            nvgStroke(vg);
        }
    }

    //FRTK_UP_FRAME:      FRTK_DOWN_FRAME:     FRTK_THIN_UP_FRAME:     FRTK_THIN_DOWN_FRAME:
    void drawFrameRect(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor c, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        // Edge highlight/shadow
        NVGcolor edgeColor;
        float offcet1 = 1.0f;
        float offcet2 = 2.0f;

        if (r == 0.0) {
            offcet1 = 0.0f;
            offcet2 = 0.0f;
        }
        if (!up) {
            edgeColor = c;
            c = shadowCol;
        }
        else {
            edgeColor = shadowCol;
        }

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x + t / 2, y + t / 2, w - t, h - t, r);
        nvgStrokeColor(vg, c);
        nvgStrokeWidth(vg, t);
        nvgStroke(vg);

        nvgBeginPath(vg);
        nvgMoveTo(vg, x + r - offcet2, y + h);
        nvgLineTo(vg, x + w - r + offcet2 + offcet1, y + h);
        nvgLineTo(vg, x + w + offcet1, y + h - r + offcet1);
        nvgLineTo(vg, x + w + offcet1, y + r);

        nvgStrokeColor(vg, edgeColor);
        nvgStrokeWidth(vg, t);
        nvgStroke(vg);
    }

    //FRTK_DIAMOND_UP_BOX:  FRTK_DIAMOND_DOWN_BOX:
    void drawDiamondWithState(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        NVGcolor top = up ? nvgRGBAf(1.f, 1.f, 1.f, 0.3921f) : nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f);
        NVGcolor bottom = up ? nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f) : nvgRGBAf(1.0f, 1.0f, 1.f, 0.3921f);
        NVGpaint grad = nvgLinearGradient(vg, x, y, x + w, y + h, top, bottom);

        nvgBeginPath(vg);
        nvgMoveTo(vg, x + w * 0.5f, y);
        nvgLineTo(vg, x + w, y + h * 0.5f);
        nvgLineTo(vg, x + w * 0.5f, y + h);

        nvgLineTo(vg, x, y + h * 0.5f);
        nvgClosePath(vg);

        nvgFillColor(vg, baseCol);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgMoveTo(vg, x + w * 0.5f, y);
        nvgLineTo(vg, x + w, y + h * 0.5f);
        nvgLineTo(vg, x + w * 0.5f, y + h);
        nvgLineTo(vg, x, y + h * 0.5f);
        nvgClosePath(vg);

        nvgFillPaint(vg, grad);
        nvgFill(vg);

        nvgStrokeWidth(vg, t);
        nvgStrokeColor(vg, up ? shadowCol : nvgRGBAf(0.3921f, 0.3921f, 0.3921f, 0.3921f));
        nvgStroke(vg);
    }

    void drawSolidCircleWithState(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        NVGcolor top = up ? nvgRGBAf(1.0f, 1.0f, 1.0f, 0.3921f) : nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f);
        NVGcolor bottom = up ? nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f) : nvgRGBAf(1.0f, 1.0f, 1.0f, 0.3921f);
        NVGpaint grad = nvgRadialGradient(vg, x + w * 0.5f, y + h * 0.5f, w * 0.1f, w * 0.5f, top, bottom);

        nvgBeginPath(vg);
        nvgEllipse(vg, x + w * 0.5f, y + h * 0.5f, w * 0.5f, h * 0.5f);
        nvgFillColor(vg, baseCol);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgEllipse(vg, x + w * 0.5f, y + h * 0.5f, w * 0.5f, h * 0.5f);
        nvgFillPaint(vg, grad);
        nvgFill(vg);

        nvgStrokeWidth(vg, t);
        nvgStrokeColor(vg, up ? shadowCol : nvgRGBAf(0.3921f, 0.3921f, 0.3921f, 0.3921f));
        nvgStroke(vg);
    }

    void drawOvalFrameWithState(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        float cx = x + w * 0.5f;
        float cy = y + h * 0.5f;

        float r1 = (w == h) ? w * 0.55f : w * 0.5f;
        float r2 = (w == h) ? w * 0.45f : h * 0.5f;

        float shadowOffset = 2.0f;
        float sx = up ? -shadowOffset : shadowOffset;
        float sy = up ? -shadowOffset : shadowOffset;

        nvgSave(vg);
        nvgTranslate(vg, sx, sy);
        nvgBeginPath(vg);
        nvgEllipse(vg, cx, cy, r1, r2);
        nvgStrokeColor(vg, shadowCol);
        nvgStrokeWidth(vg, t);
        nvgStroke(vg);
        nvgRestore(vg);

        nvgBeginPath(vg);
        nvgEllipse(vg, cx, cy, r1, r2);
        nvgStrokeColor(vg, baseCol);
        nvgStrokeWidth(vg, t);
        nvgStroke(vg);
    }

    void drawSolidOvalWithState(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor col, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        float cx = x + w * 0.5f;
        float cy = y + h * 0.5f;

        float r1;
        float r2;
        if (w == h) {
            r1 = w * 0.55f;
            r2 = w * 0.45f;
        }
        else
        {
            r1 = w * 0.5f;
            r2 = h * 0.5f;
        }
        nvgBeginPath(vg);
        nvgEllipse(vg, cx, cy + 2.0f, r1, r2);
        nvgFillColor(vg, shadowCol);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgEllipse(vg, cx, cy, r1, r2);

        NVGpaint grad = nvgLinearGradient(vg, x, y, x, y + h, nvgRGBAf(col.r, col.g, col.b, 1.0f),
            nvgRGBAf(col.r * 0.8f, col.g * 0.8f, col.b * 0.8f, 1.0f));
        nvgFillPaint(vg, grad);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgEllipse(vg, cx, cy, r1, r2);
        nvgStrokeColor(vg, nvgRGBAf(0, 0, 0, 0.3f));
        nvgStrokeWidth(vg, t);
        nvgStroke(vg);

        if (up) {
            NVGpaint highlight = nvgRadialGradient(vg, cx, cy - r2 * 0.35f, r2 * 0.05f, r2 * 0.9f, nvgRGBAf(1, 1, 1, 0.45f), nvgRGBAf(1, 1, 1, 0.0f));

            nvgBeginPath(vg);
            nvgEllipse(vg, cx, cy, r1 * 0.92f, r2 * 0.82f);
            nvgFillPaint(vg, highlight);
            nvgFill(vg);

            NVGpaint innerShadow = nvgLinearGradient(vg, cx, cy + r2 * 0.2f, cx, cy + r2, nvgRGBAf(0, 0, 0, 0.0f), nvgRGBAf(0, 0, 0, 0.25f));

            nvgBeginPath(vg);
            nvgEllipse(vg, cx, cy, r1 * 0.95f, r2 * 0.9f);
            nvgFillPaint(vg, innerShadow);
            nvgFill(vg);

            nvgBeginPath(vg);
            nvgEllipse(vg, cx, cy - r2 * 0.45f, r1 * 0.5f, r2 * 0.15f);
            nvgFillColor(vg, nvgRGBAf(1, 1, 1, 0.25f));
            nvgFill(vg);
        }
    }

    void drawShadowBox(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        NVGpaint shadow;

        if (up) {
            shadow = nvgBoxGradient(vg, x, y, w, h, r * 2, 10, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.196f), nvgRGBAf(0.f, 0.0f, 0.0f, 0.0f));
        }
        else {
            shadow = nvgBoxGradient(vg, x, y, w, h, r * 2, 10, nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f), nvgRGBAf(0.f, 0.0f, 0.0f, 0.0f));
        }

        nvgBeginPath(vg);

        nvgRect(vg, x - 10, y - 10, w + 20, h + 20);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgPathWinding(vg, NVG_HOLE);
        nvgFillPaint(vg, shadow);
        nvgFill(vg);

        NVGpaint gradient;

        if (up) {
            gradient = nvgLinearGradient(vg, x, y, x, y + h, nvgRGBAf(1.0f, 1.0f, 1.0f, 0.784f), baseCol);
        }
        else {
            gradient = nvgLinearGradient(vg, x, y, x, y + h, baseCol, nvgRGBAf(1.0f, 1.0f, 1.0f, 0.3921f));
        }

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillPaint(vg, gradient);
        nvgFill(vg);
    }

    void drawOvalFLAT(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        nvgBeginPath(vg);
        nvgEllipse(vg, x + w * 0.5f, y + h * 0.5f, w * 0.5f, h * 0.5f);
        nvgFillColor(vg, baseCol);
        nvgFill(vg);
    }

    void drawOval(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        NVGcolor highlight = up ? nvgRGBAf(1.0f, 1.0f, 1.0f, 0.3921f) : nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f);
        NVGcolor shadow = up ? nvgRGBAf(0.0f, 0.0f, 0.0f, 0.3921f) : nvgRGBAf(1.0f, 1.0f, 1.0f, 0.3921f);

        NVGpaint grad = nvgRadialGradient(vg, x + w * 0.5f, y + h * 0.5f, w * 0.1f, w * 0.5f, highlight, shadow);

        nvgBeginPath(vg);
        nvgEllipse(vg, x + w * 0.5f, y + h * 0.5f, w * 0.5f, h * 0.5f);
        nvgFillColor(vg, baseCol);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgEllipse(vg, x + w * 0.5f, y + h * 0.5f, w * 0.5f, h * 0.5f);
        nvgFillPaint(vg, grad);
        nvgFill(vg);
    }

    void draw_nice_round_box(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool pressed) {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        // Drop Shadow
        NVGpaint shadow = nvgBoxGradient(vg, x, y + 2, w, h, r, 12.0f, nvgRGBAf(0, 0, 0, 0.25f), nvgRGBAf(0, 0, 0, 0.0f));

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y + 2, w, h, r);
        nvgFillPaint(vg, shadow);
        nvgFill(vg);

        // Main Background Gradient
        NVGcolor topCol = pressed ? shadowCol : nvgRGBAf(baseCol.r * 1.08f, baseCol.g * 1.08f, baseCol.b * 1.08f, baseCol.a);
        NVGcolor bottomCol = pressed ? baseCol : shadowCol;

        NVGpaint bg = nvgLinearGradient(vg, x, y, x, y + h, topCol, bottomCol);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillPaint(vg, bg);
        nvgFill(vg);

        // Top Highlight

        NVGpaint highlight = nvgLinearGradient(vg, x, y, x, y + h * 0.5f, nvgRGBAf(1, 1, 1, pressed ? 0.05f : 0.18f), nvgRGBAf(1, 1, 1, 0.0f));
        nvgBeginPath(vg);
        nvgRoundedRect(vg, x + 1, y + 1, w - 2, h - 2, r - 1);
        nvgFillPaint(vg, highlight);
        nvgFill(vg);

        // Inner Shadow (Depth)
        NVGpaint innerShadow = nvgLinearGradient(vg, x, y, x, y + h, nvgRGBAf(0, 0, 0, pressed ? 0.15f : 0.08f), nvgRGBAf(0, 0, 0, 0.0f));

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x + 1, y + 1, w - 2, h - 2, r - 1);
        nvgFillPaint(vg, innerShadow);
        nvgFill(vg);

        // Border
        nvgBeginPath(vg);
        nvgRoundedRect(vg, x + 0.5f, y + 0.5f, w - 1, h - 1, r);
        nvgStrokeColor(vg, nvgRGBAf(0, 0, 0, 0.25f));
        nvgStrokeWidth(vg, 1.0f);
        nvgStroke(vg);
    }

    //TODO FIX ME TO CREATE BETTER WIDGETS!!!!!!
    void draw_nice_squre(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool pressed) {
        NVGpaint shadowPaint;
        float thumb = 60.0f;
        nvgBeginPath(vg);
        nvgRoundedRect(vg, dim.pos.x, dim.pos.y, thumb, thumb, 5);
        nvgFill(vg);
        shadowPaint = nvgBoxGradient(vg, dim.pos.x - 1, dim.pos.y, thumb + 2, thumb + 2, 5, 3, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
        nvgBeginPath(vg);
        nvgRect(vg, dim.pos.x - 5, dim.pos.y - 5, thumb + 10, thumb + 10);
        nvgRoundedRect(vg, dim.pos.x, dim.pos.y, thumb, thumb, 6);
        nvgPathWinding(vg, NVG_HOLE);
        nvgFillPaint(vg, shadowPaint);
        nvgFill(vg);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, dim.pos.x + 0.5f, dim.pos.y + 0.5f, thumb - 1, thumb - 1, 4 - 0.5f);
        nvgStrokeWidth(vg, 1.0f);
        nvgStrokeColor(vg, nvgRGBA(255, 255, 255, 192));
        nvgStroke(vg);
    }

    void draw_box(NVGcontext* vg, BOX_TYPE b, Dim_float_t dim, float cornerRadius, float strokeWidth, NVGcolor c, NVGcolor shadowCol, bool up) {
        switch (b) {
        case FRTK_NO_BOX: {
            return; //DRAW Nothing
        }

        case FRTK_FLAT_BOX: {
            drawFilledRect(vg, dim, cornerRadius, strokeWidth, c, shadowCol, false);
        }break;

        case FRTK_UP_BOX:
        case FRTK_DOWN_BOX:
            drawBoxUpDown(vg, dim, cornerRadius, strokeWidth, c, shadowCol, b == FRTK_UP_BOX && up);
            break;

        case FRTK_THIN_UP_BOX:
        case FRTK_THIN_DOWN_BOX:
            drawBoxUpDown(vg, dim, cornerRadius, FRTK_THIN_BORDER, c, shadowCol, b == FRTK_THIN_UP_BOX && up);
            break;

        case FRTK_ROUNDED_BOX_UP:
        case FRTK_ROUNDED_BOX_DOWN:
            drawBoxUpDown(vg, dim, cornerRadius + 10.f, strokeWidth, c, shadowCol, b == FRTK_ROUNDED_BOX_UP && up);
            break;

        case FRTK_ROUND_UP_BOX:
        case FRTK_ROUND_DOWN_BOX:
            drawSolidCircleWithState(vg, dim, cornerRadius, FRTK_THIN_BORDER, c, shadowCol, b == FRTK_ROUND_UP_BOX && up);
            break;

        case FRTK_ROUND_FLAT_BOX:
            drawOvalFLAT(vg, dim, cornerRadius, FRTK_NO_BORDER, c, shadowCol, false);
            break;

        case FRTK_UP_FRAME:
        case FRTK_DOWN_FRAME:
            drawFrameRect(vg, dim, cornerRadius, FRTK_THICK_BORDER, c, shadowCol, b == FRTK_UP_FRAME && up);
            break;

        case FRTK_ROUNDED_UP_FRAME:
        case FRTK_ROUNDED_DOWN_FRAME:
            drawFrameRect(vg, dim, cornerRadius + 10.f, FRTK_THIN_BORDER, c, shadowCol, b == FRTK_ROUNDED_UP_FRAME && up);
            break;

        case FRTK_THIN_UP_FRAME:
        case FRTK_THIN_DOWN_FRAME:
            drawFrameRect(vg, dim, cornerRadius, FRTK_NORMAL_BORDER, c, shadowCol, b == FRTK_THIN_UP_FRAME && up);
            break;

        case FRTK_ROUND_SHADOW_UP_BOX:
        case FRTK_ROUND_SHADOW_DOWN_BOX:
            drawFilledRect(vg, dim, cornerRadius + 8.0f, FRTK_NORMAL_BORDER, c, shadowCol, b == FRTK_ROUND_SHADOW_UP_BOX && up);
            drawShadowBox(vg, dim, cornerRadius + 12.0f, FRTK_NORMAL_BORDER, c, shadowCol, b == FRTK_ROUND_SHADOW_UP_BOX && up);
            break;

        case FRTK_DIAMOND_UP_BOX:
        case FRTK_DIAMOND_DOWN_BOX:
            drawDiamondWithState(vg, dim, cornerRadius, FRTK_NORMAL_BORDER, c, shadowCol, b == FRTK_DIAMOND_UP_BOX && up);
            break;

        case FRTK_OVALFLAT_BOX:
            drawOval(vg, dim, cornerRadius, FRTK_NORMAL_BORDER, c, shadowCol, false);
            break;
        case FRTK_OVAL_UP_BOX:
        case FRTK_OVAL_DOWN_BOX:
            drawSolidOvalWithState(vg, dim, cornerRadius, FRTK_NORMAL_BORDER, c, shadowCol, b == FRTK_OVAL_UP_BOX && up);
            break;

        case FRTK_OVAL_UP_FRAME:
        case FRTK_OVAL_DOWN_FRAME:
            drawOvalFrameWithState(vg, dim, cornerRadius, FRTK_NORMAL_BORDER, c, shadowCol, b == FRTK_OVAL_UP_FRAME && up);
            break;

        case FRTK_OSHADOW_UP_BOX:
        case FRTK_OSHADOW_DOWN_BOX:
            drawShadowBox(vg, dim, cornerRadius, FRTK_THICK_BORDER, c, shadowCol, b == FRTK_OSHADOW_UP_BOX && up);
            break;
        }
    }
    // Function to draw a check mark
    void drawCheckMark(NVGcontext* vg, float x, float y, float size, NVGcolor col) {
        nvgBeginPath(vg);
        nvgMoveTo(vg, x, y + size * 0.5f);
        nvgLineTo(vg, x + size * 0.3f, y + size);
        nvgLineTo(vg, x + size, y);
        nvgStrokeColor(vg, col);
        nvgStrokeWidth(vg, 5.0f);
        nvgStroke(vg);
    }

    ///////////////////////***************************************////////////////////////////////////////////////////
    ///                            Text related drawings                                                           ///
    ///////////////////////***************************************////////////////////////////////////////////////////

    float getTextWidth(NVGcontext* vg, const std::string& str, float fontSize, const char* fontName)
    {
        nvgFontFace(vg, fontName);
        nvgFontSize(vg, fontSize);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE); // neutral alignment for measuring width
        float bounds[4];
        nvgTextBounds(vg, 0.0f, 0.0f, str.c_str(), nullptr, bounds);
        return bounds[2] - bounds[0];
    }

    float getTextLeftBearing(NVGcontext* vg, const std::string& text, const font_t& fnt)
    {
        nvgFontSize(vg, fnt.fontSize);
        nvgFontFace(vg, fnt.fName.c_str());
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE);

        float bounds[4];
        nvgTextBounds(vg, 0.0f, 0.0f, text.c_str(), nullptr, bounds);

        return -bounds[0];
    }

    ////Draws text inside/outside a box with alignment, shadow, and optional rotation
    //void drawTextInBox(NVGcontext* vg, const std::string& text, font_t& fnt, bool isLabel, FontData_t& fnttData)
    //{
    //    nvgFontSize(vg, fnt.fontSize);
    //    nvgFontFace(vg, fnt.fName.c_str());

    //    int align = isLabel ? fnt.lblAlign : fnt.txtAlign;
    //    bool inside = (align & NVG_ALIGN_INSIDE) != 0;

    //    int nvgAlign = (align & 0x7F) | NVG_ALIGN_BASELINE;
    //    nvgTextAlign(vg, nvgAlign);

    //    float asc, desc, lineh;
    //    nvgTextMetrics(vg, &asc, &desc, &lineh);

    //    const float boxX = fnt.pos.x;
    //    const float boxY = fnt.pos.y;
    //    const float boxW = fnt.size.w;
    //    const float boxH = fnt.size.h;

    //    float drawX = boxX;
    //    float baselineY = boxY;
    //    float textW = getTextWidth(vg, text, fnt.fontSize, fnt.fName.c_str());

    //    // Horizontal alignment
    //    if (align & NVG_ALIGN_CENTER) {
    //        //This will generate error if the lbl is inside
    //        drawX = boxX + boxW * 0.5f - textW * 0.5f;
    //       // FRTK_CORE_WARN("NVG_ALIGN_CENTER when inside is not supported!");
    //    }
    //    else if (align & NVG_ALIGN_RIGHT) {
    //        if (inside) {
    //            drawX = boxX + boxW - textW;
    //        }
    //        else
    //        {
    //            drawX = boxX + boxW + (asc - desc) * 0.5f;
    //        }
    //    }
    //    else if (align & NVG_ALIGN_LEFT)
    //        if (inside) {
    //            drawX = boxX;
    //        }
    //        else
    //        {
    //            drawX = boxX - textW - (asc - desc) * 0.5f;
    //        }

    //    // Vertical alignment
    //    if (inside)
    //    {
    //        if (align & NVG_ALIGN_TOP)
    //            baselineY = boxY + asc * 1.2;
    //        else if (align & NVG_ALIGN_MIDDLE)
    //            baselineY = boxY + (boxH - (asc - desc)) * 0.5f;
    //        else if (align & NVG_ALIGN_BOTTOM)
    //            baselineY = boxY + boxH - desc;
    //        else
    //            baselineY = boxY + asc;
    //    }
    //    else
    //    {
    //        if (align & NVG_ALIGN_TOP)
    //            baselineY = boxY - (asc - desc) * 0.6f;
    //        else if (align & NVG_ALIGN_BOTTOM)
    //            baselineY = boxY + boxH + (asc - desc) * 0.4f;
    //        else if (align & NVG_ALIGN_MIDDLE) {
    //            //Here we have left and right which works , middle dose not work!!
    //            baselineY = boxY + (boxH - (asc - desc)) * 0.5f;
    //        }
    //    }
    //    if(!isLabel){
    //        fnt.realPos.x = drawX;
    //        fnt.realPos.y = baselineY;
    //    }
    //    // Draw
    //    nvgSave(vg);
    //    nvgTranslate(vg, drawX, baselineY);

    //    if (fnt.Rotate != 0.0f)
    //        nvgRotate(vg, glm::radians(fnt.Rotate));

    //    // Shadow
    //    if (fnt.blur > 0.0f)
    //    {
    //        nvgFontBlur(vg, fnt.blur);
    //        nvgFillColor(vg, fnt.shadowCol);
    //        nvgText(vg, fnt.shadowOffs.x, fnt.shadowOffs.y, text.c_str(), nullptr);
    //    }

    //    // Main text
    //    nvgFontBlur(vg, 0.0f);
    //    nvgFillColor(vg, fnt.forgColor);
    //    nvgText(vg, 0.0f, 0.0f, text.c_str(), nullptr);
    //    nvgRestore(vg);
    //}



void drawTextInBox(NVGcontext* vg, const std::string& text, font_t& fnt, bool isLabel, FontData_t& fnttData , const char* secrete)
{
    nvgFontSize(vg, fnt.fontSize);
    nvgFontFace(vg, fnt.fName.c_str());

    int align = isLabel ? fnt.lblAlign : fnt.txtAlign;
    bool inside = (align & NVG_ALIGN_INSIDE) != 0;

    int nvgAlign = (align & 0x7F) | NVG_ALIGN_BASELINE;
    nvgTextAlign(vg, nvgAlign);

    float asc, desc, lineh;
    nvgTextMetrics(vg, &asc, &desc, &lineh);

    const float boxX = fnt.pos.x;
    const float boxY = fnt.pos.y;
    const float boxW = fnt.size.w;
    const float boxH = fnt.size.h;

    float textW = getTextWidth(vg, text, fnt.fontSize, fnt.fName.c_str());

    // Compute visual left edge for horizontal alignment
    float visualX = boxX;
    if (align & NVG_ALIGN_CENTER) {
        visualX = boxX + boxW * 0.5f - textW * 0.5f;
    }
    else if (align & NVG_ALIGN_RIGHT) {
        visualX = inside ? (boxX + boxW - textW) : (boxX + boxW );
    }
    else if (align & NVG_ALIGN_LEFT) {
        visualX = inside ? boxX : (boxX - textW - (asc - desc) * 0.5f);
    }

    // Compute baseline Y for vertical alignment
    float visualY = boxY;
    if (inside) {
        if (align & NVG_ALIGN_TOP) visualY = boxY + asc * 1.2f;
        else if (align & NVG_ALIGN_MIDDLE) { 
            if (isLabel) 
                visualY = boxY + boxH * 0.5F + (asc + desc) * 0.5f; 
            else 
                visualY = boxY + boxH * 0.5F - (asc + desc) * 0.5f; 
        }
        else if (align & NVG_ALIGN_BOTTOM) visualY = boxY + boxH - desc;
        else visualY = boxY + asc;
    }
    else {
        if (align & NVG_ALIGN_TOP) visualY = boxY - (asc - desc) * 0.6f;
        else if (align & NVG_ALIGN_MIDDLE) visualY = boxY + boxH *.5 - (asc +desc) * 0.5f;
        else if (align & NVG_ALIGN_BOTTOM) visualY = boxY + boxH + (asc - desc) * 0.4f;
    }

    // Store visual origin in fnt.realPos for hit-testing
    if (!isLabel) {
        fnt.realPos.x = visualX;   // left edge of text
        fnt.realPos.y = visualY;   // baseline Y
    }

    // Draw text relative to visual origin
    nvgSave(vg);
    nvgTranslate(vg, visualX, visualY);
    if (fnt.Rotate != 0.0f)
        nvgRotate(vg, glm::radians(fnt.Rotate));

    // Shadow
    if (fnt.blur > 0.0f) {
        nvgFontBlur(vg, fnt.blur);
        nvgFillColor(vg, fnt.shadowCol);
        if (secrete!=0) {
            size_t maskLen = strlen(secrete);
            size_t len = text.size(); // number of chars

            std::vector<char> buf(len * maskLen + 1); // +1 for null
            char* p = buf.data();

            for (size_t i = 0; i < len; ++i)
            {
                memcpy(p, secrete, maskLen);
                p += maskLen;
            }

            *p = '\0'; // null-terminate
            nvgText(vg, fnt.shadowOffs.x, fnt.shadowOffs.y, buf.data(), nullptr);
            nvgFontBlur(vg, 0.0f);
            nvgFillColor(vg, fnt.forgColor);
            nvgText(vg, 0.0f, 0.0f, buf.data(), nullptr);

        }
        else
        {
            nvgText(vg, fnt.shadowOffs.x, fnt.shadowOffs.y, text.c_str(), nullptr);
            
            // Main text
            nvgFontBlur(vg, 0.0f);
            nvgFillColor(vg, fnt.forgColor);
            nvgText(vg, 0.0f, 0.0f, text.c_str(), nullptr);
        }
    }
    nvgRestore(vg);
}
}