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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include <glm/gtx/transform.hpp>
#include <Mesh.h>
#include <fr_primatives.h>
#include <ShaderProgram.h>
#include <fr_primativeShader.h>
#include <glad/glad.h>

Fr_PrimaitiveShader::Shared* Fr_PrimaitiveShader::shared_ = nullptr;

static const glm::mat4 kShadowMapBiasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);

void Fr_PrimaitiveShader::defaultShaders()
{
    f_objectshader_ = "E:/Projects/Design456App/frtk/src/shaders/objectshader";
    f_silhouette_ = "E:/Projects/Design456App/frtk/src/shaders/silhouette";
    f_shadowmap_ = "E:/Projects/Design456App/frtk/src/shaders/shadowmap";
}

void Fr_PrimaitiveShader::setObjectshader(const char* newValue)
{
    f_objectshader_ = newValue;
}

void Fr_PrimaitiveShader::setSilhouette(const char* newValue)
{
    f_silhouette_ = newValue;
}

void Fr_PrimaitiveShader::setShadowmap(const char* newValue)
{
    f_shadowmap_ = newValue;
}

Fr_PrimaitiveShader::Fr_PrimaitiveShader(unsigned int color, float silhouette) :
    primative_{ nullptr }, silhouette_(silhouette) {
    SetColor(color);
    if (!shared_) {
        shared_ = new Shared;
        defaultShaders();
        shared_->primative_program = new ShaderProgram(f_objectshader_);
        shared_->silhouette_program = new ShaderProgram(f_silhouette_);
        shared_->shadowmap_program = new ShaderProgram(f_shadowmap_);
    }
}
Fr_PrimaitiveShader::Fr_PrimaitiveShader(glm::vec4 color, float silhouette) :
    primative_{ nullptr }, silhouette_(silhouette) {
    SetColor(color);
    defaultShaders();
    if (!shared_) {
        shared_ = new Shared;
        shared_->primative_program = new ShaderProgram(f_objectshader_);
        shared_->silhouette_program = new ShaderProgram(f_silhouette_);
        shared_->shadowmap_program = new ShaderProgram(f_shadowmap_);
    }
}

Fr_PrimaitiveShader::~Fr_PrimaitiveShader() {
}

void Fr_PrimaitiveShader::SetColor(glm::vec4 color) {
    color_ = color;
}

void Fr_PrimaitiveShader::SetColor(unsigned int color, float alpha) {
    color_ = glm::vec4(
        ((color >> 16) & 0xFF) / 255.0f,
        ((color >> 8) & 0xFF) / 255.0f,
        (color & 0xFF) / 255.0f,
        alpha
    );
}

void Fr_PrimaitiveShader::SetOpacity(float alpha) {
    color_.a = alpha;
}

void Fr_PrimaitiveShader::SetPrimative(std::shared_ptr<Fr_Primatives> primative) {
    primative_ = primative;
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

void Fr_PrimaitiveShader::RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) {
    if (!active_)
        return;

    auto mvp = info.projection * modelview;

    if (color_.a != 1) {
        info.mvp_transparent.push_back(mvp);
        return;
    }

    info.mvp.push_back(mvp);
    ShaderProgram* program = shared_->shadowmap_program;
    program->Enable();
    program->SetAttribLocation("position", 0);
    program->SetUniformMat4("mvp", mvp);
    primative_->Draw();
    program->Disable();
}

void Fr_PrimaitiveShader::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (!active_ ||
        (info.render_transparent && color_.a == 1) ||
        (!info.render_transparent && color_.a < 1))
        return;

    auto mvp = info.projection * modelview;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));
    ShaderProgram* program = shared_->primative_program;

    //Avoid segmentation fault - Mariwan
    if (info.shadowmap.mvp.size() > 0 && info.id < info.shadowmap.mvp.size() && info.shadowmap.mvp_transparent.size()>0) {
        auto sm_mvp = color_.a == 1 ? info.shadowmap.mvp[info.id] : info.shadowmap.mvp_transparent[info.id];
        program->SetUniformMat4("sm_mvp", kShadowMapBiasMatrix * sm_mvp);
    }
    /*if (color_.a == 1)
        RenderSilhouette(mvp);*/

    program->Enable();
    LoadLights(program, info.lights);

    program->SetAttribLocation("position", 0);
    program->SetAttribLocation("normal", 1);
    program->SetUniformMat4("modelview", modelview);
    program->SetUniformMat4("normalmatrix", normalmatrix);
    program->SetUniformMat4("mvp", mvp);
    program->SetUniformVec4("color", color_);
    program->SetUniformInteger("sm_light", info.shadowmap.light_id);

    //****************************************************************************************FIXME
    //TODO FIXME -- THIS IS OLD OPENGL - DOSENT WORK FO RNEW OPENGL
    glGenTextures(1, &info.shadowmap.texture);
    glCheckFunc(glBindTexture(GL_TEXTURE_2D, info.shadowmap.texture));           //     THIS CAUSE ISSUE FIXME!!!!!!!!!!!!!!!!!!!
    shared_->primative_program->SetUniformInteger("sm_texture", 0);

    primative_->Draw();
    program->Enable();
    program->Disable();
    info.id++;
}

void Fr_PrimaitiveShader::RenderSilhouette(const glm::mat4& mvp) {
    ShaderProgram* program = shared_->silhouette_program;
    program->Enable();
    program->SetAttribLocation("position", 0);
    program->SetAttribLocation("normal", 1);
    program->SetUniformFloat("silhouette", silhouette_);
    program->SetUniformMat4("mvp", mvp);
    primative_->Draw();
    program->Disable();
}