//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include <glm/gtx/transform.hpp>
#include <grid/fr_grid_shader.h>
#include <fr_shader_program.h>
#include <glad/glad.h>
#include <fr_window.h>
namespace FR {
    //static const glm::mat4 kShadowMapBiasMatrix(
    //    0.5, 0.0, 0.0, 0.0,
    //    0.0, 0.5, 0.0, 0.0,
    //    0.0, 0.0, 0.5, 0.0,
    //    0.5, 0.5, 0.5, 1.0);
    static const glm::mat4 kShadowMapBiasMatrix(
        0.25, 0.0, 0.0, 0.0,
        0.0, 0.25, 0.0, 0.0,
        0.0, 0.0, 0.25, 0.0,
        0.25, 0.25, 0.25, 1.0);

    void Fr_GridShader::defaultShaders()
    {
        //Default programs
        std::string shaderpath= EXE_CURRENT_DIR + "/resources/shaders/";
        m_f_objectshader = shaderpath+"primativeshader";
        m_f_silhouette   = shaderpath + "silhouette";
        m_f_texture      = shaderpath +"texture";
        m_f_text = shaderpath + "txtFont";
    }
    /** Shader file name and path */
    void Fr_GridShader::setObjectshader(const char* newValue)
    {
        m_f_objectshader = newValue;
    }
    /** Silhouette Shader file name and path */
    void Fr_GridShader::setSilhouette(const char* newValue)
    {
        m_f_silhouette = newValue;
    }
    /** Text (font rendering) Shader file name and path */
    void Fr_GridShader::setText(const char* newValue)
    {
        m_f_text = newValue;

    }
    
    void Fr_GridShader::setTexture(const char* newValue)
    {
        m_f_texture = newValue;
    }

        // Constructor with unsigned int color
    Fr_GridShader::Fr_GridShader(unsigned int color, float silhouette) :
            m_shared{ 0, 0, 0, 0, 0 },
            m_Primative{ nullptr }, silhouette_(silhouette) {
            SetColor(color);
            InitializeSharedPrograms();
        }

        // Constructor with glm::vec4 color
    Fr_GridShader::Fr_GridShader(glm::vec4 color, float silhouette) :
            m_Primative{ nullptr }, silhouette_(silhouette) {
            SetColor(color);
            InitializeSharedPrograms();
        }

        // Constructor with float array color
    Fr_GridShader::Fr_GridShader(float color[4], float silhouette) :
            m_Primative{ nullptr }, silhouette_(silhouette), m_Color{ color[0], color[1], color[2], color[3] } {
            InitializeSharedPrograms();
        }
 
     void Fr_GridShader::InitializeSharedPrograms() {
            defaultShaders();
            m_shared.wdg_prog = std::make_shared <ShaderProgram>(m_f_objectshader);
            m_shared.silhouette_prog= std::make_shared <ShaderProgram>(m_f_silhouette);
            m_shared.texture_prog = std::make_shared <ShaderProgram>(m_f_texture);
            m_shared.txtFont_program= std::make_shared <ShaderProgram>(m_f_text);
        }

    Fr_GridShader::~Fr_GridShader() {
    }

    void Fr_GridShader::SetColor(glm::vec4 color) {
        m_Color = color;
    }

    void Fr_GridShader::SetColor(unsigned int color, float alpha) {
        m_Color = glm::vec4(
            ((color >> 16) & 0xFF) / 255.0f,
            ((color >> 8) & 0xFF) / 255.0f,
            (color & 0xFF) / 255.0f,
            alpha
        );
    }

    void Fr_GridShader::SetOpacity(float alpha) {
        m_Color.a = alpha;
    }

    void Fr_GridShader::SetPrimative(std::shared_ptr<Fr_Primatives> primative) {
        m_Primative = primative;
    }

    void Fr_GridShader::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights) {
        unsigned int nlights = std::min(lights.size(), kMaxLights);
        program->SetUniformInteger("nlights", nlights);
        for (size_t i = 0; i < nlights; ++i) {
            auto id = "lights[" + std::to_string(i) + "].";
            program->SetUniformVec4(id + "position", lights[i].position);
            program->SetUniformVec4(id + "diffuse", lights[i].diffuse);
            program->SetUniformVec4(id + "specular", lights[i].specular);
            program->SetUniformVec4(id + "ambient", lights[i].ambient);
            program->SetUniformVec3(id + "attenuation", lights[i].attenuation);
            program->SetUniformInteger(id + "is_spot", lights[i].is_spot);
            program->SetUniformVec3(id + "direction", lights[i].direction);
            program->SetUniformFloat(id + "cutoff", lights[i].cutoff);
            program->SetUniformFloat(id + "exponent", lights[i].exponent);
            program->SetUniformInteger("hasTexture", 0); ///TODO DO WE NEED THIS!!!!! 
            program->SetUniformCamPosition("camPos");
        }
    }

    void Fr_GridShader::Render(RenderInfo& info) {
        if (/*!m_active ||*/
            (info.render_transparent && m_Color.a == 1) ||
            (!info.render_transparent && m_Color.a < 1))
            return;
        auto mvp = info.projection * info.modelview;
        auto normalmatrix = glm::transpose(glm::inverse(info.modelview));

        if (m_Color.a == 1)
            RenderSilhouette(mvp);

         m_shared.wdg_prog->Enable();
        LoadLights(m_shared.wdg_prog, info.lights);

        m_shared.wdg_prog->SetAttribLocation("position", 0);
        m_shared.wdg_prog->SetAttribLocation("normal", 1);
        m_shared.wdg_prog->SetUniformMat4("modelview", info.modelview);
        m_shared.wdg_prog->SetUniformMat4("normalmatrix", normalmatrix);
        m_shared.wdg_prog->SetUniformMat4("mvp", mvp);
        m_shared.wdg_prog->SetUniformVec4("color", m_Color);

        //for returning the texture keep the id
        //_texture = info.shadowmap.texture;
        m_Primative->Draw();
        m_shared.wdg_prog->Disable();
        info.id++;
    }

    void Fr_GridShader::RenderSilhouette(const glm::mat4& mvp) {
        m_shared.silhouette_prog->Enable();
        m_shared.silhouette_prog->SetAttribLocation("position", 0);
        m_shared.silhouette_prog->SetAttribLocation("texCoord", 1);
        m_shared.silhouette_prog->SetAttribLocation("normal", 2);
        m_shared.silhouette_prog->SetUniformFloat("silhouette", silhouette_);
        m_shared.silhouette_prog->SetUniformMat4("mvp", mvp);
        m_Primative->Draw();
        m_shared.silhouette_prog->Disable();
    }
}