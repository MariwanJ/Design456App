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
#include <widget/fr_point_widget.h>
#include <glm/gtx/transform.hpp>
#include <fr_window.h>
namespace FR {
    Fr_Point_Widget::Fr_Point_Widget( std::shared_ptr<std::vector<float>> vertices,
                                    std::shared_ptr<std::vector<unsigned int>> indices, 
                                    std::string label): Fr_Widget(vertices, indices, label), m_pointPicker(false)
    {
        m_normals = std::make_shared<std::vector<float>>();
        m_textureCoord = std::make_shared<std::vector<float>>();
        pointSize(m_pointSize); 
        init();           // Initialize buffers, VAO, VBO, etc.
        m_WidgType = NODETYPE::FR_POINT_WIDGET;
    }


    Fr_Point_Widget::~Fr_Point_Widget()
    {
    }

    void Fr_Point_Widget::draw()
    {
        initializeVBO();
        draw_2d();
    }


    void Fr_Point_Widget::redraw()
    {
        CalculateNormals();
        initializeVBO();
        draw_2d();
    }

    void Fr_Point_Widget::lbl_draw()
    {
       
    }

    void Fr_Point_Widget::lbl_redraw()
    {
        lbl_draw();
    }

    void Fr_Point_Widget::pointPicker(bool val)
    {
        m_pointPicker = val;
    }
    bool Fr_Point_Widget::pointPicker()
    {
        return m_pointPicker;
    }

    void Fr_Point_Widget::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights) {
        size_t nlights = std::min(lights.size(), kMaxLights);
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
        program->SetUniformCamPosition("camPos");

    }
    void Fr_Point_Widget::RenderSelection(RenderInfo& info) {
        if (!m_active)
            return;
        auto mvp = info.projection * info.modelview * m_Matrix;
        m_shader->wdg_selection_prog->Enable();
        m_shader->wdg_selection_prog->SetAttribLocation("position", 0);
        m_shader->wdg_selection_prog->SetAttribLocation("selectionMask", 1); // depending on the status, it will give yellow color or color
        m_shader->wdg_selection_prog->SetUniformMat4("mvp", mvp);
        
        m_shader->wdg_selection_prog->SetUniformVec4("baseColor", m_color.baseColor);
        m_shader->wdg_selection_prog->SetUniformVec4("faceSelectColor", m_color.faceSelectColor);
        m_shader->wdg_selection_prog->SetUniformVec4("edgeSelectColor", m_color.edgeSelectColor);
        m_shader->wdg_selection_prog->SetUniformVec4("vertexSelectColor", m_color.vertexSelectColor);
        m_shader->wdg_selection_prog->SetUniformInteger("selectionMask", m_currentSelMode);
        m_shader->wdg_selection_prog->SetUniformFloat("pointSize", pointSize());
        updateVBO_Selection();
        draw_2d_sel();  //draw_points();
        m_shader->wdg_selection_prog->Disable();
    }
    
    void Fr_Point_Widget::Render(RenderInfo& info) {
        if (!m_active)
            return;

        auto mvp = info.projection * info.modelview * m_Matrix;
        auto normalmatrix = glm::transpose(glm::inverse(info.modelview));
        m_shader->wdg_prog->Enable();
        LoadLights(m_shader->wdg_prog, info.lights);
        m_shader->wdg_prog->SetAttribLocation("position", POSITION_VERTEX_VB);  //Position variable has (layout(location =0) inside vs shader
        m_shader->wdg_prog->SetAttribLocation("texCoord", POSITION_TEXCOORD_VB);  //Position variable has (layout(location =1 inside vs shader
        m_shader->wdg_prog->SetAttribLocation("normal", POSITION_NORMAL_VB);  //Position variable has (layout(location =1 inside vs shader
        m_shader->wdg_prog->SetUniformMat4("modelview", info.modelview);
        m_shader->wdg_prog->SetUniformMat4("normalmatrix", normalmatrix);
        m_shader->wdg_prog->SetUniformMat4("mvp", mvp);
        m_shader->wdg_prog->SetUniformVec4("color", m_color.baseColor);       //Object color - not light color
        m_shader->wdg_prog->SetUniformInteger("hasTexture", false);
        draw();      //You should make a draw call to get that  done
        lbl_draw();
        m_shader->wdg_prog->Disable();
        RenderSelection(info);
        info.id++;
    }

    int Fr_Point_Widget::handle(int e)
    {
        if (!m_active)
            return 0; //we don't use the event/we don't care

        return 0;
    }
}