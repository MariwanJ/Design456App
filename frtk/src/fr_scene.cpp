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

#include <fr_scene.h>
GLFWwindow* Scene::linkToglfw = nullptr;

Scene::Scene() :
    background_{ 0.9, 0.9, 0.9,1.0 } {
    type(NODETYPE::FR_SCENE);

    glCheckFunc(glEnable(GL_DEPTH_TEST));
    glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glCheckFunc(glEnable(GL_BLEND));
    glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Scene::SetBackgroud(float r, float g, float b) {
    background_.r = r;
    background_.g = g;
    background_.b = b;
    background_.a = 1.0;
}
void Scene::SetBackgroud(float r, float g, float b, float alfa) {
    background_.r = r;
    background_.g = g;
    background_.b = b;
    background_.a = alfa;
}

void Scene::add3DObject(std::string fName)
{
    auto newObj_t = std::make_shared<Transform>();
    newObj_t->Translate(0, 0, 0);
    newObj_t->Scale(1, 1, 1);
    newObj_t->Rotate(0, 1, 0, 0); //TODO CHECK ME
    auto newObj = std::make_shared<ModelNode>(glm::vec4(FR_BISQUE), 0.0005f); //  color and


    //texture
    newObj->m_Texture2D = std::make_shared<Fr_Texture2D>();
    std::string imag = ("E:/Projects/Design456App/resources/Texture/test.png");
    //std::string imag = ("E:/Projects/Design456App/resources/Texture/bricks.jpg");
    if (newObj->m_Texture2D->set2DTexture(imag))
    {
            newObj->m_Texture2D->setup2DTexture();      //Dont forget to do this always
    }else
        DEBUG_BREAK;

    if (fName.find(".off") != std::string::npos) {
        newObj->SetMesh(std::make_shared<Shape>(fName));
    }
    else {
        //Not implemented yet  - here .obj should be treated.
    }
    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(true);
    rightlight_spot->SetPosition(2.956f, -0.514f, 1.074f);
    rightlight_spot->SetupSpot(1.0f, 0.0f, -0.1f, 45.0f, 16.0f);
    rightlight_spot->SetDiffuse(0.0f, 0.0f, 0.0f);
    rightlight_spot->SetAmbient(0.42f, 0.42f, 0.42f);
    rightlight_spot->SetAttenuation(1.0f, 0.002f, 0.0f);
    newObj_t->AddNode(rightlight_spot);
    newObj_t->SetActive(true);
    newObj->calculateTextureCoord();
    newObj_t->AddNode(newObj);
    AddNode(newObj_t);
}

void Scene::delete3DObject(std::shared_ptr<Transform>& obj)
{
}

/**
* This is a general process  for drawing camera, shadow map, render shape /faces ..etc
*/
void Scene::RenderScene() {
    
    RenderInfo render_info;
    if (!SetupCamera(render_info.projection, render_info.modelview))
        throw std::runtime_error("Scene::Render(): Camera not found");

    SetupLight(render_info.modelview, render_info.lights);
    int draw_framebuffer = 0;
    glCheckFunc(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer));
    glCheckFunc(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer));
    glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    render_info.id = 0;
    render_info.render_transparent = false;
    Render(render_info, render_info.modelview);
    //render_info.id = 0;
    //render_info.render_transparent = true;
    //Render(render_info, render_info.modelview);
}