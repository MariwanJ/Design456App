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

        NVGcolor top = nvgLerpRGBA(baseCol, nvgRGBA(255, 255, 255, 255), 0.1f);
        NVGcolor bot = nvgLerpRGBA(baseCol, nvgRGBA(0, 0, 0, 255), 0.1f);
        NVGpaint grad = nvgLinearGradient(vg, x, y, x, y + h - r, top, bot);

        nvgBeginPath(vg);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgFillPaint(vg, grad);
        nvgFill(vg);

        NVGcolor highlight = nvgLerpRGBA(
            baseCol, nvgRGBA(255, 255, 255, baseCol.a), 0.4f);
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

        NVGcolor top = up ? nvgRGBA(255, 255, 255, 100) : nvgRGBA(0, 0, 0, 100);
        NVGcolor bottom = up ? nvgRGBA(0, 0, 0, 100) : nvgRGBA(255, 255, 255, 100);
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
        nvgStrokeColor(vg, up ? shadowCol : nvgRGBA(100, 100, 100, 100));
        nvgStroke(vg);
    }

    void drawSolidCircleWithState(NVGcontext* vg, Dim_float_t dim, float r, float t, NVGcolor baseCol, NVGcolor shadowCol, bool up)
    {
        float x = dim.pos.x;
        float y = dim.pos.y;
        float w = dim.size.w;
        float h = dim.size.h;

        NVGcolor top = up ? nvgRGBA(255, 255, 255, 100) : nvgRGBA(0, 0, 0, 100);
        NVGcolor bottom = up ? nvgRGBA(0, 0, 0, 100) : nvgRGBA(255, 255, 255, 100);
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
        nvgStrokeColor(vg, up ? shadowCol : nvgRGBA(100, 100, 100, 100));
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

        float r1 = w * 0.5f;
        float r2 = h * 0.5f;
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
            shadow = nvgBoxGradient(vg, x, y, w, h, r * 2, 10, nvgRGBA(0, 0, 0, 50), nvgRGBA(0, 0, 0, 0));
        }
        else {
            shadow = nvgBoxGradient(vg, x, y, w, h, r * 2, 10, nvgRGBA(0, 0, 0, 100), nvgRGBA(0, 0, 0, 0));
        }

        nvgBeginPath(vg);

        nvgRect(vg, x - 10, y - 10, w + 20, h + 20);
        nvgRoundedRect(vg, x, y, w, h, r);
        nvgPathWinding(vg, NVG_HOLE);
        nvgFillPaint(vg, shadow);
        nvgFill(vg);

        NVGpaint gradient;

        if (up) {
            gradient = nvgLinearGradient(vg, x, y, x, y + h, nvgRGBA(255, 255, 255, 200), baseCol);
        }
        else {
            gradient = nvgLinearGradient(vg, x, y, x, y + h, baseCol, nvgRGBA(255, 255, 255, 100));
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

        NVGcolor highlight = up ? nvgRGBA(255, 255, 255, 100) : nvgRGBA(0, 0, 0, 100);
        NVGcolor shadow = up ? nvgRGBA(0, 0, 0, 100) : nvgRGBA(255, 255, 255, 100);

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

    void draw_box(NVGcontext* vg, BOX_TYPE b, Dim_float_t dim, float cornerRadius, float strokeWidth, NVGcolor c, NVGcolor shadowCol, bool up) {
        switch (b) {
        case FRTK_NO_BOX: {
            return; //DRAW Nothing
        }break;

        case FRTK_FLAT_BOX: {
            drawFilledRect(vg, dim, cornerRadius, strokeWidth, c, shadowCol, false);
        }break;

        case FRTK_UP_BOX:
        case FRTK_DOWN_BOX:
            drawBoxUpDown(vg, dim, cornerRadius, strokeWidth, c, shadowCol, b == FRTK_UP_BOX);
            break;

        case FRTK_THIN_UP_BOX:
        case FRTK_THIN_DOWN_BOX:
            drawBoxUpDown(vg, dim, cornerRadius, THIN_BORDER, c, shadowCol, b == FRTK_THIN_UP_BOX);
            break;

        case FRTK_ROUNDED_BOX_UP:
        case FRTK_ROUNDED_BOX_DOWN:
            drawBoxUpDown(vg, dim, cornerRadius + 10.f, strokeWidth, c, shadowCol, b == FRTK_ROUNDED_BOX_UP);
            break;

        case FRTK_ROUND_UP_BOX:
        case FRTK_ROUND_DOWN_BOX:
            drawSolidCircleWithState(vg, dim, cornerRadius, THIN_BORDER, c, shadowCol, b == FRTK_ROUND_UP_BOX);
            break;

        case FRTK_ROUND_FLAT_BOX:
            drawOvalFLAT(vg, dim, cornerRadius, NO_BORDER, c, shadowCol, false);
            break;

        case FRTK_UP_FRAME:
        case FRTK_DOWN_FRAME:
            drawFrameRect(vg, dim, cornerRadius, THICK_BORDER, c, shadowCol, b == FRTK_UP_FRAME);
            break;

        case FRTK_ROUNDED_UP_FRAME:
        case FRTK_ROUNDED_DOWN_FRAME:
            drawFrameRect(vg, dim, cornerRadius + 10.f, THIN_BORDER, c, shadowCol, b == FRTK_ROUNDED_UP_FRAME);
            break;

        case FRTK_THIN_UP_FRAME:
        case FRTK_THIN_DOWN_FRAME:
            drawFrameRect(vg, dim, cornerRadius, NORMAL_BORDER, c, shadowCol, b == FRTK_THIN_UP_FRAME);
            break;

        case FRTK_ROUND_SHADOW_UP_BOX:
        case FRTK_ROUND_SHADOW_DOWN_BOX:
            drawFilledRect(vg, dim, cornerRadius + 8.0f, NORMAL_BORDER, c, shadowCol, b == FRTK_ROUND_SHADOW_UP_BOX);
            drawShadowBox(vg, dim, cornerRadius + 12.0f, NORMAL_BORDER, c, shadowCol, b == FRTK_ROUND_SHADOW_UP_BOX);
            break;

        case FRTK_DIAMOND_UP_BOX:
        case FRTK_DIAMOND_DOWN_BOX:
            drawDiamondWithState(vg, dim, cornerRadius, NORMAL_BORDER, c, shadowCol, b == FRTK_DIAMOND_UP_BOX);
            break;

        case FRTK_OVALFLAT_BOX:
            drawOval(vg, dim, cornerRadius, NORMAL_BORDER, c, shadowCol, false);
            break;
        case FRTK_OVAL_UP_BOX:
        case FRTK_OVAL_DOWN_BOX:
            drawSolidOvalWithState(vg, dim, cornerRadius, NORMAL_BORDER, c, shadowCol, b == FRTK_OVAL_UP_BOX);
            break;

        case FRTK_OVAL_UP_FRAME:
        case FRTK_OVAL_DOWN_FRAME:
            drawOvalFrameWithState(vg, dim, cornerRadius, NORMAL_BORDER, c, shadowCol, b == FRTK_OVAL_UP_FRAME);
            break;

        case FRTK_OSHADOW_UP_BOX:
        case FRTK_OSHADOW_DOWN_BOX:
            drawShadowBox(vg, dim, cornerRadius, THICK_BORDER, c, shadowCol, b == FRTK_OSHADOW_UP_BOX);
            break;
        }
    }
    float getTextWidth(NVGcontext* vg, const std::string& str, float fontSize, const char* fontFace, int align)
    {
        nvgFontFace(vg, fontFace);
        nvgFontSize(vg, fontSize);
        nvgTextAlign(vg, align);
        float bounds[4];
        nvgTextBounds(vg, 0.0f, 0.0f, str.c_str(), nullptr, bounds);
        return bounds[2] - bounds[0];
    }

    //Horizontal = NVG_ALIGN_CENTER,    NVG_ALIGN_LEFT / NVG_ALIGN_CENTER / NVG_ALIGN_RIGHT
    //Vertical =  NVG_ALIGN_MIDDLE    NVG_ALIGN_TOP / NVG_ALIGN_MIDDLE / NVG_ALIGN_BOTTOM
    void drawTextInBox(NVGcontext* vg, const std::string& text, font_t& fnt)
    {
        nvgFontSize(vg, fnt.fontSize);
        nvgFontFace(vg, fnt.fName.c_str());

        nvgTextAlign(vg, fnt.hAlign | NVG_ALIGN_TOP);

        float asc, desc, lineh;
        nvgTextMetrics(vg, &asc, &desc, &lineh);

        float baselineY = fnt.pos.y;
        switch (fnt.vAlign)
        {
        case NVG_ALIGN_TOP:
            baselineY = fnt.pos.y + asc;
            break;

        case NVG_ALIGN_MIDDLE:
            baselineY = fnt.pos.y + (fnt.size.h - lineh) * 0.4f + asc;
            break;

        case NVG_ALIGN_BOTTOM:
            baselineY = fnt.pos.y + fnt.size.h - lineh + asc;
            break;
        }

        float drawX = fnt.pos.x;
        if (fnt.hAlign & NVG_ALIGN_CENTER)
            drawX = fnt.pos.x + fnt.size.w * 0.5f;
        else if (fnt.hAlign & NVG_ALIGN_RIGHT)
            drawX = fnt.pos.x + fnt.size.w;

        if (fnt.blur > 0.0f)
        {
            nvgFontBlur(vg, fnt.blur);
            nvgFillColor(vg, fnt.shadowCol);
            nvgText(
                vg,
                drawX + fnt.shadowOffs.x,
                baselineY + fnt.shadowOffs.y,
                text.c_str(),
                nullptr
            );
        }
        nvgFontBlur(vg, 0.0f);
        nvgFillColor(vg, fnt.forgColor);
        nvgText(vg, drawX, baselineY, text.c_str(), nullptr);
    }
}