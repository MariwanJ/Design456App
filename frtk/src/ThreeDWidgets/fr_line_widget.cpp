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
#include <glm/gtx/transform.hpp>
namespace FR{

Fr_Line_Widget::Fr_Line_Widget(glm::vec3 position, 
                                std::shared_ptr<std::vector <float>> verticies,
                                std::shared_ptr<std::vector <unsigned int>> indicies, 
                                std::string label) : Fr_Widget(position,verticies,indicies,label)
{
 
    lineObj = std::make_shared< Fr_TwoD_Drawing>(FR_LINES,verticies, indicies);
    m_normals= lineObj->Normals();
    m_textCoord = lineObj->TextCoord();
    lineObj->lineWidth(50);

    diffCalculateNormals();
    lineObj->initializeVBO();
    CreateShader();
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
  //  lineObj->Draw();
}

void Fr_Line_Widget::lbl_redraw()
{
    lbl_draw();
}
int Fr_Line_Widget::handle(int e)
{
    switch (e) {
    case FR_PUSH: FRTK_CORE_INFO("Line Widget is clicked");
        return 1; //Consume the event
    case FR_RELEASE: FRTK_CORE_INFO("Line Widget is released");
        return 1;
    }
    return 0;
}
void Fr_Line_Widget::LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights) {
    unsigned int nlights = std::min(lights.size(), kMaxLights);
    program->SetUniformInteger("nlights", nlights);
    for (size_t i = 0; i < nlights; ++i) {
        auto uniformVarNameInObjShader = "lights[" + std::to_string(i) + "].";
        program->SetUniformVec4(uniformVarNameInObjShader + "color", lights[i].lightcolor);
        program->SetUniformVec4(uniformVarNameInObjShader + "position", lights[i].position);       //Here we send the name of the variable as "lights[xxx=number]." wher xxx= a number from 0 to nlights
        program->SetUniformVec4(uniformVarNameInObjShader + "diffuse", lights[i].diffuse);
        program->SetUniformVec4(uniformVarNameInObjShader + "specular", lights[i].specular);
        program->SetUniformVec4(uniformVarNameInObjShader + "ambient", lights[i].ambient);
        program->SetUniformVec3(uniformVarNameInObjShader + "attenuation", lights[i].attenuation);
        program->SetUniformInteger(uniformVarNameInObjShader + "is_spot", lights[i].is_spot);
        program->SetUniformVec3(uniformVarNameInObjShader + "direction", lights[i].direction);
        program->SetUniformFloat(uniformVarNameInObjShader + "cutoff", lights[i].cutoff);
        program->SetUniformFloat(uniformVarNameInObjShader + "exponent", lights[i].exponent);
    }
}


void Fr_Line_Widget::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (!active_)
        return;
 

    auto mvp = info.projection * modelview * m_Matrix;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));
    widget_program->Enable();
    LoadLights(widget_program, info.lights);
    widget_program->SetAttribLocation("position", 0);  //Position variable has (layout(location =0) inside objectshader_vs.glsl
    widget_program->SetAttribLocation("texCoord", 1);  //Position variable has (layout(location =1 inside objectshader_vs.glsl
    widget_program->SetAttribLocation("normal", 2);  //Position variable has (layout(location =1 inside objectshader_vs.glsl
    widget_program->SetUniformMat4("modelview", modelview);
    widget_program->SetUniformMat4("normalmatrix", normalmatrix);
    widget_program->SetUniformMat4("mvp", mvp);
    widget_program->SetUniformVec4("color", m_color);       //Object color - not light color
    widget_program->SetUniformInteger("hasTexture", false);
    draw();      //You should make a draw call to get that  done
    lbl_draw();
    widget_program->Disable();
    info.id++;
    }
void Fr_Line_Widget::Rotate(glm::vec3 axis, float angle)
{
    m_Matrix = glm::rotate(glm::mat4{ 1 }, glm::radians(angle), axis);

}
 

}