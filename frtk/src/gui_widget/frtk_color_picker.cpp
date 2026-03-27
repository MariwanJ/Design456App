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

	Frtk_Color_Picker::Frtk_Color_Picker(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b):
		Frtk_Box(vg,X,Y,W,H,lbl,b) {
		t = 0.f;
	}

	glm::vec4 Frtk_Color_Picker::pickedColorRGB()
	{
		return glm::vec4();
	}

	glm::vec4 Frtk_Color_Picker::pickedColorHSV()
	{
		return glm::vec4();
	}

	glm::vec4 Frtk_Color_Picker::pickedColorCMYK()
	{
		return glm::vec4();
	}

	NVGcolor Frtk_Color_Picker::pickedColorNVG()
	{
		return NVGcolor();
	}

	void Frtk_Color_Picker::draw() {

		int i;
		t += 0.1f; //time 
		if (t >= 360.f)
			t = 0.f;
		float r0, r1, ax, ay, bx, by, cx, cy, aeps, r;
		float hue = sinf(t * 0.12f);
		NVGpaint paint;

		nvgSave(m_vg);

		/*	nvgBeginPath(m_vg);
			nvgRect(m_vg, x,y,w,h);
			nvgFillColor(m_vg, nvgRGBA(255,0,0,128));
			nvgFill(m_vg);*/

		cx = m_x + m_w * 0.5f;
		cy = m_y + m_h * 0.5f;
		r1 = (m_w < m_h ? m_w : m_h) * 0.5f - 5.0f;
		r0 = r1 - 20.0f;
		aeps = 0.5f / r1;	// half a pixel arc length in radians (2pi cancels out).

		for (i = 0; i < 6; i++) {
			float a0 = (float)i / 6.0f * NVG_PI * 2.0f - aeps;
			float a1 = (float)(i + 1.0f) / 6.0f * NVG_PI * 2.0f + aeps;
			nvgBeginPath(m_vg);
			nvgArc(m_vg, cx, cy, r0, a0, a1, NVG_CW);
			nvgArc(m_vg, cx, cy, r1, a1, a0, NVG_CCW);
			nvgClosePath(m_vg);
			ax = cx + cosf(a0) * (r0 + r1) * 0.5f;
			ay = cy + sinf(a0) * (r0 + r1) * 0.5f;
			bx = cx + cosf(a1) * (r0 + r1) * 0.5f;
			by = cy + sinf(a1) * (r0 + r1) * 0.5f;
			paint = nvgLinearGradient(m_vg, ax, ay, bx, by, nvgHSLA(a0 / (NVG_PI * 2), 1.0f, 0.55f, 255), nvgHSLA(a1 / (NVG_PI * 2), 1.0f, 0.55f, 255));
			nvgFillPaint(m_vg, paint);
			nvgFill(m_vg);
		}

		nvgBeginPath(m_vg);
		nvgCircle(m_vg, cx, cy, r0 - 0.5f);
		nvgCircle(m_vg, cx, cy, r1 + 0.5f);
		nvgStrokeColor(m_vg, nvgRGBAf(0.f, 0.f, 0.f, 0.25f));
		nvgStrokeWidth(m_vg, 1.0f);
		nvgStroke(m_vg);

		// Selector
		nvgSave(m_vg);
		nvgTranslate(m_vg, cx, cy);
		nvgRotate(m_vg, hue * NVG_PI * 2);

		// Marker on
		nvgStrokeWidth(m_vg, 2.0f);
		nvgBeginPath(m_vg);
		nvgRect(m_vg, r0 - 1, -3, r1 - r0 + 2, 6);
		nvgStrokeColor(m_vg, nvgRGBAf(1.f, 1.f, 1.f, 0.75f));
		nvgStroke(m_vg);

		paint = nvgBoxGradient(m_vg, r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, nvgRGBAf(0.f, 0.f, 0.f, 0.5f), nvgRGBAf(0.f, 0.f, 0.f, 0.f));
		nvgBeginPath(m_vg);
		nvgRect(m_vg, r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
		nvgRect(m_vg, r0 - 2, -4, r1 - r0 + 4, 8);
		nvgPathWinding(m_vg, NVG_HOLE);
		nvgFillPaint(m_vg, paint);
		nvgFill(m_vg);

		// Center triangle
		r = r0 - 6;
		ax = cosf(120.0f / 180.0f * NVG_PI) * r;
		ay = sinf(120.0f / 180.0f * NVG_PI) * r;
		bx = cosf(-120.0f / 180.0f * NVG_PI) * r;
		by = sinf(-120.0f / 180.0f * NVG_PI) * r;
		nvgBeginPath(m_vg);
		nvgMoveTo(m_vg, r, 0);
		nvgLineTo(m_vg, ax, ay);
		nvgLineTo(m_vg, bx, by);
		nvgClosePath(m_vg);
		paint = nvgLinearGradient(m_vg, r, 0, ax, ay, nvgHSLA(hue, 1.0f, 0.5f, 255), nvgRGBAf(1.f, 1.f, 1.f, 1.f));
		nvgFillPaint(m_vg, paint);
		nvgFill(m_vg);
		paint = nvgLinearGradient(m_vg, (r + ax) * 0.5f, (0 + ay) * 0.5f, bx, by, nvgRGBAf(0.f, 0.f, 0.f, 0.f), nvgRGBAf(0.0f, 0.f, 0.f, 1.0f));
		nvgFillPaint(m_vg, paint);
		nvgFill(m_vg);
		nvgStrokeColor(m_vg, nvgRGBAf(0.f, 0.f, 0.f, 0.25f));
		nvgStroke(m_vg);

		// Select circle on triangle
		ax = cosf(120.0f / 180.0f * NVG_PI) * r * 0.3f;
		ay = sinf(120.0f / 180.0f * NVG_PI) * r * 0.4f;
		nvgStrokeWidth(m_vg, 2.0f);
		nvgBeginPath(m_vg);
		nvgCircle(m_vg, ax, ay, 5);
		nvgStrokeColor(m_vg, nvgRGBAf(1.f, 1.f, 1.f, 0.75f));
		nvgStroke(m_vg);

		paint = nvgRadialGradient(m_vg, ax, ay, 7, 9, nvgRGBAf(0.f, 0.f, 0.f, 0.25f), nvgRGBAf(0.f, 0.f, 0.f, 0.f));
		nvgBeginPath(m_vg);
		nvgRect(m_vg, ax - 20, ay - 20, 40, 40);
		nvgCircle(m_vg, ax, ay, 7);
		nvgPathWinding(m_vg, NVG_HOLE);
		nvgFillPaint(m_vg, paint);
		nvgFill(m_vg);

		nvgRestore(m_vg);

		nvgRestore(m_vg);
	}
	int Frtk_Color_Picker::handle(int ev)
	{
		return 0;
	}
}