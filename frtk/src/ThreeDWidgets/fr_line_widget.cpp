//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
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
#include "fr_line_widget.h"
namespace FR{

Fr_Line_Widget::Fr_Line_Widget(glm::vec3 position, 
                                std::shared_ptr<std::vector <float>> verticies,
                                std::shared_ptr<std::vector <unsigned int>> indicies, 
                                std::string label) : Fr_Widget(position,verticies,indicies,label)
{
 
    lineObj = std::make_shared< Fr_TwoD_Drawing>(FR_LINE,verticies, indicies);
    m_normals= lineObj->Normals();
    m_textCoord = lineObj->TextCoord();
    lineObj->lineWidth(5);
    lineObj->Type(FR::FR_LINE);
    diffCalculateNormals();
    lineObj->initializeVBO();
}

Fr_Line_Widget::~Fr_Line_Widget()
{
}

void Fr_Line_Widget::draw()
{
    lineObj->Draw();
}

void Fr_Line_Widget::lbl_draw()
{
}

void Fr_Line_Widget::lbl_redraw()
{
}
int Fr_Line_Widget::handle(int e)
{
 
    switch (e) {
    case FR_PUSH: FRTK_CORE_INFO("Line Widget is clicked");
        return 1; //Consume the event
    case FR_RELEASE: FRTK_CORE_INFO("Line Widget is released");
    }
    return 0;
}
}