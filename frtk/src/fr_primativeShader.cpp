//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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
#include <fr_mesh.h>
#include <fr_primatives.h>
#include <fr_shader_program.h>
#include <fr_primativeShader.h>
#include <glad/glad.h>
namespace FR {
    Fr_PrimaitiveShader::Shared* Fr_PrimaitiveShader::shared_ = nullptr;

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
    void Fr_PrimaitiveShader::defaultShaders()
    {
        f_objectshader_ = "E:/Projects/Design456App/frtk/src/shaders/primativeshader";
        f_silhouette_ = "E:/Projects/Design456App/frtk/src/shaders/silhouette";
        ///f_texture_  = "E:/Projects/Design456App/frtk/src/shaders/texture";
    }
    /** Shader file name and path */
    void Fr_PrimaitiveShader::setObjectshader(const char* newValue)
    {
        f_objectshader_ = newValue;
    }
    /** Silhouette Shader file name and path */
    void Fr_PrimaitiveShader::setSilhouette(const char* newValue)
    {
        f_silhouette_ = newValue;
    }
    Fr_PrimaitiveShader::Fr_PrimaitiveShader(glm::vec4 color, float silhouette) :
        m_Primative{ nullptr },  
        silhouette_(silhouette) {
        SetColor(color);
        defaultShaders();
        if (!shared_) {
            shared_ = new Shared;
            shared_->primative_program = new ShaderProgram(f_objectshader_);
            shared_->silhouette_program = new ShaderProgram(f_silhouette_);
        }
        type(NODETYPE::FR_PRIMATIVESHADER);
    }

    // Copy constructor
    Fr_PrimaitiveShader::Fr_PrimaitiveShader(const Fr_PrimaitiveShader& other)
        : Node(other), m_Color(other.m_Color), silhouette_(other.silhouette_), f_objectshader_(other.f_objectshader_), f_silhouette_(other.f_silhouette_), f_texture_(other.f_texture_), _texture(other._texture)
    {
        // Deep copy the shared_ptr members
        if (other.m_Primative)
            m_Primative = std::make_shared<Fr_Primatives>(*other.m_Primative);
        if (other.m_Texture2D)
            m_Texture2D = std::make_shared<Fr_Texture2D>(*other.m_Texture2D);
    }

    // Move constructor
    Fr_PrimaitiveShader::Fr_PrimaitiveShader(Fr_PrimaitiveShader&& other) noexcept
        : Node(std::move(other)), m_Color(std::move(other.m_Color)), silhouette_(std::move(other.silhouette_)), f_objectshader_(std::move(other.f_objectshader_)), f_silhouette_(std::move(other.f_silhouette_)), f_texture_(std::move(other.f_texture_)), _texture(std::move(other._texture))
    {
        // Move the shared_ptr members
        m_Primative = std::move(other.m_Primative);
        m_Texture2D = std::move(other.m_Texture2D);
    }

    // Copy assignment operator
    Fr_PrimaitiveShader& Fr_PrimaitiveShader::operator=(const Fr_PrimaitiveShader& other)
    {
        if (this != &other)
        {
            Node::operator=(other);
            m_Color = other.m_Color;
            silhouette_ = other.silhouette_;
            f_objectshader_ = other.f_objectshader_;
            f_silhouette_ = other.f_silhouette_;
            f_texture_ = other.f_texture_;
            _texture = other._texture;

            // Deep copy the shared_ptr members
            if (other.m_Primative)
                m_Primative = std::make_shared<Fr_Primatives>(*other.m_Primative);
            else
                m_Primative.reset();

            if (other.m_Texture2D)
                m_Texture2D = std::make_shared<Fr_Texture2D>(*other.m_Texture2D);
            else
                m_Texture2D.reset();
        }
        return *this;
    }

    // Move assignment operator
    Fr_PrimaitiveShader& Fr_PrimaitiveShader::operator=(Fr_PrimaitiveShader&& other) noexcept
    {
        if (this != &other)
        {
            Node::operator=(std::move(other));
            m_Color = std::move(other.m_Color);
            silhouette_ = std::move(other.silhouette_);
            f_objectshader_ = std::move(other.f_objectshader_);
            f_silhouette_ = std::move(other.f_silhouette_);
            f_texture_ = std::move(other.f_texture_);
            _texture = std::move(other._texture);

            // Move the shared_ptr members
            m_Primative = std::move(other.m_Primative);
            m_Texture2D = std::move(other.m_Texture2D);
        }
        return *this;
    }


    Fr_PrimaitiveShader::~Fr_PrimaitiveShader()
    {
        if (shared_){
            delete shared_->primative_program;
            delete shared_->shadowmap_program;
            delete shared_->silhouette_program;
            delete shared_->texture_program;
            delete shared_;
            }
        }

    void Fr_PrimaitiveShader::SetColor(glm::vec4 color) {
        m_Color = color;
    }

    void Fr_PrimaitiveShader::SetColor(unsigned int color, float alpha) {
        m_Color = glm::vec4(
            ((color >> 16) & 0xFF) / 255.0f,
            ((color >> 8) & 0xFF) / 255.0f,
            (color & 0xFF) / 255.0f,
            alpha
        );
    }

    void Fr_PrimaitiveShader::SetOpacity(float alpha) {
        m_Color.a = alpha;
    }

    void Fr_PrimaitiveShader::SetPrimative(std::shared_ptr<Fr_Primatives> primative) {
        m_Primative = primative;
    }

    void Fr_PrimaitiveShader::LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights) {
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
        }
    }

    void Fr_PrimaitiveShader::Render(RenderInfo& info, const glm::mat4& modelview) {
        if (!active_ ||
            (info.render_transparent && m_Color.a == 1) ||
            (!info.render_transparent && m_Color.a < 1))
            return;
        auto mvp = info.projection * modelview;
        auto normalmatrix = glm::transpose(glm::inverse(modelview));

        if (m_Color.a == 1)
            RenderSilhouette(mvp);

        ShaderProgram* program = shared_->primative_program;
        program->Enable();

        LoadLights(program, info.lights);

        program->SetAttribLocation("position", 0);
        program->SetAttribLocation("normal", 1);
        program->SetUniformMat4("modelview", modelview);
        program->SetUniformMat4("normalmatrix", normalmatrix);
        program->SetUniformMat4("mvp", mvp);
        program->SetUniformVec4("color", m_Color);

        //for returning the texture keep the id
        //_texture = info.shadowmap.texture;
        m_Primative->Draw();
        program->Disable();
        info.id++;
    }

    void Fr_PrimaitiveShader::RenderSilhouette(const glm::mat4& mvp) {
        ShaderProgram* program = shared_->silhouette_program;
        program->Enable();
        program->SetAttribLocation("position", 0);
        program->SetAttribLocation("texCoord", 1);
        program->SetAttribLocation("normal", 2);
        program->SetUniformFloat("silhouette", silhouette_);
        program->SetUniformMat4("mvp", mvp);
        m_Primative->Draw();
        program->Disable();
    }
}