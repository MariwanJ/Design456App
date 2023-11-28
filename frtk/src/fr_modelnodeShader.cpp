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
#include <fr_modelnodeShader.h>
#include <glad/glad.h>
#include<fr_primatives.h>

/**
 * This file is the implementation of shape object based on Mesh data
 * It has all parts needed to draw a 3D object in mesh format
 * .
 */
ModelNode::Shared* ModelNode::shared_ = nullptr;

static const glm::mat4 kShadowMapBiasMatrix(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);
/*(
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);*/

ModelNode::ModelNode(unsigned int color, float silhouette) :
    mesh_{ nullptr },
    silhouette_(silhouette) {
    SetColor(color);
    if (!shared_) {
        shared_ = new Shared;
        shared_->object_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/objectshader");
        shared_->silhouette_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/silhouette");
        shared_->shadowmap_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/shadowmap");
        shared_->texture_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/texture");
    }
    type(NODETYPE::FR_ModelNode);
}

ModelNode::ModelNode(glm::vec4 color, float silhouette) :mesh_{ nullptr },
silhouette_(silhouette), m_Texture2D{ nullptr } {
    SetColor(color);
    if (!shared_) {
        shared_ = new Shared;
        shared_->object_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/objectshader");
        shared_->silhouette_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/silhouette");
        shared_->shadowmap_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/shadowmap");
        shared_->texture_program= new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/texture");
    }
    type(NODETYPE::FR_ModelNode);
}

ModelNode::~ModelNode() {
}

void ModelNode::SetColor(unsigned int color, float alpha) {
    color_ = glm::vec4(
        ((color >> 16) & 0xFF) / 255.0f,
        ((color >> 8) & 0xFF) / 255.0f,
        (color & 0xFF) / 255.0f,
        alpha
    );
}

void ModelNode::SetColor(glm::vec4 color, float alpha)
{
    color[3] = alpha; //just in case it is not what you have in the color
    color_ = color;
}

void ModelNode::SetOpacity(float alpha) {
    color_.a = alpha;
}

void ModelNode::SetMesh(std::shared_ptr<Shape> mesh) {
    mesh_ = mesh;
    mesh_->build();
}

void ModelNode::SetMesh(const std::string& mesh) {
    mesh_ = std::make_shared<Shape>(mesh);
    mesh_->build();
}

void ModelNode::LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights) {
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

void ModelNode::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (!active_ ||
        (info.render_transparent && color_.a == 1) ||
        (!info.render_transparent && color_.a < 1))
        return;

    auto mvp = info.projection * modelview;
    auto normalmatrix = glm::transpose(glm::inverse(modelview));

    if (color_.a == 1)
        RenderSilhouette(mvp);

    ShaderProgram* program = shared_->object_program;
    program->Enable();
    LoadLights(program, info.lights);
    program->SetAttribLocation("position", 0);  //Position variable has (layout(location =0) inside objectshader_vs.glsl
    program->SetAttribLocation("normal", 1);    //normal variable has (layout(location =2) inside objectshader_vs.glsl
    program->SetUniformMat4("modelview", modelview);
    program->SetUniformMat4("normalmatrix", normalmatrix);
    program->SetUniformMat4("mvp", mvp);
    program->SetUniformVec4("color", color_);       //Object color - not light color
    mesh_->Draw();//You should make a draw call to get that  done
    program->Disable();
    info.id++;

    //Render texture also here.
    program = shared_->texture_program;
    program->Enable();
    program->SetAttribLocation("position", 0);  //Position variable has (layout(location =0) inside objectshader_vs.glsl
    program->SetAttribLocation("texCoord", 1);  //Position variable has (layout(location =1 inside objectshader_vs.glsl
    program->SetUniformVec4("color", color_);       //Object color - not light color
    program->SetUniformMat4("modelview", modelview);
    m_Texture2D->Bind(1);
    mesh_->Draw();      //You should make a draw call to get that  done
    m_Texture2D->Unbind();   
    program->Disable();
}

void ModelNode::calculateTextureCoord()
{
    mesh_->calcualteTextCoor(m_Texture2D->getWidth(), m_Texture2D->getHgeith());
}

void ModelNode::RenderSilhouette(const glm::mat4& mvp) {
    if (!active_)
        return;
    if (!(mesh_))//Not defined 
        return;

    ShaderProgram* program = shared_->silhouette_program;
    program->Enable();
    program->SetAttribLocation("position", 0);
    program->SetAttribLocation("normal", 1);
    program->SetUniformFloat("silhouette", silhouette_);
    program->SetUniformMat4("mvp", mvp);
    mesh_->Draw();
    program->Disable();
}

 