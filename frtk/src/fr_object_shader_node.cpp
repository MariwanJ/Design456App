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
#include <fr_shader_program.h>
#include <fr_object_shader_node.h>
#include <glad/glad.h>
#include<fr_primatives.h>

ObjectShaderNode::Shared* ObjectShaderNode::shared_ = nullptr;

static const glm::mat4 kShadowMapBiasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);

ObjectShaderNode::ObjectShaderNode(unsigned int color, float silhouette) :
    mesh_{ nullptr },
    silhouette_(silhouette) {
    SetColor(color);
    if (!shared_) {
        shared_ = new Shared;
        shared_->object_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/objectshader");
        shared_->silhouette_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/silhouette");
        shared_->shadowmap_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/shadowmap");
    }
    type(NODETYPE::FR_OBJECTSHADERNODE);
}

ObjectShaderNode::ObjectShaderNode(glm::vec4 color, float silhouette):mesh_{ nullptr },
        silhouette_(silhouette) {
        SetColor(color);
        if (!shared_) {
            shared_ = new Shared;
            shared_->object_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/objectshader");
            shared_->silhouette_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/silhouette");
            shared_->shadowmap_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/shadowmap");
        }
        type(NODETYPE::FR_OBJECTSHADERNODE);
}

ObjectShaderNode::~ObjectShaderNode() {
}

void ObjectShaderNode::SetColor(unsigned int color, float alpha) {
    color_ = glm::vec4(
        ((color >> 16) & 0xFF) / 255.0f,
        ((color >> 8) & 0xFF) / 255.0f,
        (color & 0xFF) / 255.0f,
        alpha
    );
}

void ObjectShaderNode::SetColor(glm::vec4 color, float alpha)
{
    color[3] = alpha; //just in case it is not what you have in color
    color_ = color;
}

void ObjectShaderNode::SetOpacity(float alpha) {
    color_.a = alpha;
}

void ObjectShaderNode::SetMesh(std::shared_ptr<Shape> mesh) {
    mesh_ = mesh;
    mesh_->build();
}

void ObjectShaderNode::SetMesh(const std::string& mesh) {
    mesh_ = std::make_shared<Shape>(mesh);
    mesh_->build();
}

void ObjectShaderNode::LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights) {
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
        program->SetUniformVec3(   uniformVarNameInObjShader + "direction", lights[i].direction);
        program->SetUniformFloat(  uniformVarNameInObjShader + "cutoff", lights[i].cutoff);
        program->SetUniformFloat(  uniformVarNameInObjShader + "exponent", lights[i].exponent);
    }
}

void ObjectShaderNode::RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) {
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
    program->SetAttribLocation("position", 0);      //Position variable has (layout(location =0) inside objectshader_vs.glsl
    program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();
    program->Disable();
}

void ObjectShaderNode::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (!active_ ||
        (info.render_transparent && color_.a == 1) ||
        (!info.render_transparent && color_.a < 1))
        return;

    auto mvp = info.projection * modelview;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));
    auto sm_mvp = color_.a == 1 ? info.shadowmap.mvp[info.id] :
        info.shadowmap.mvp_transparent[info.id];

    if (color_.a == 1)
        RenderSilhouette(mvp);

    ShaderProgram* program = shared_->object_program;
    program->Enable();

    LoadLights(program, info.lights);
    program->SetAttribLocation("position", 0);  //Position variable has (layout(location =0) inside objectshader_vs.glsl
    program->SetAttribLocation("normal", 1);    //normal variable has (layout(location =1) inside objectshader_vs.glsl
    program->SetUniformMat4("modelview", modelview);
    program->SetUniformMat4("normalmatrix", normalmatrix);
    program->SetUniformMat4("mvp", mvp);
    program->SetUniformVec4("color", color_);       //Object color - not light color
    program->SetUniformMat4("sm_mvp", kShadowMapBiasMatrix * sm_mvp);
    program->SetUniformInteger("sm_light", info.shadowmap.light_id);

    glCheckFunc(glActiveTexture(GL_TEXTURE0));
    glCheckFunc(glBindTexture(GL_TEXTURE_2D, info.shadowmap.texture));
    
    mesh_->Draw();
    shared_->object_program->SetUniformInteger("sm_texture", 0);
    program->Disable();
    info.id++;
}

GLuint ObjectShaderNode::getCurrentTexturer(void)
{
    return _texture;
}

void ObjectShaderNode::RenderSilhouette(const glm::mat4& mvp) {
    ShaderProgram* program = shared_->silhouette_program;
    program->Enable();
    program->SetAttribLocation("position", 0);
    program->SetAttribLocation("normal", 1);
    program->SetUniformFloat("silhouette", silhouette_);
    program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();
    program->Disable();
}