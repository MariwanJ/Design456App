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

#ifndef FRTK_TOOLBAR_BUTTON_H
#define FRTK_TOOLBAR_BUTTON_H

#include <gui_widget/frtk_button.h> 

class Frtk_Toolbar;

namespace FR {
	class Frtk_ToolBar_Button : public Frtk_Button
	{
		friend Frtk_Toolbar;
	public:
		Frtk_ToolBar_Button(NVGcontext* vg, float x, float y, float w , float h , std::string l="ToolbarBTN", BOX_TYPE b = FRTK_UP_BOX);


		void setThicknessPadding(float padding, float thickness);

	protected:
		virtual void drawVerticalDivider();
		virtual void draw() override;


	private:
		bool m_divider;
		float m_padding;
		float m_thickness;
		NVGcolor m_lineColor;


	};
}
#endif // FRTK_TOOLBAR_BUTTON_H
