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
GLFWwindow* Scene::linkToglfw=nullptr;

Scene::Scene() :
    background_{ 0.9, 0.9, 0.9,1.0 }{
    type(NODETYPE::FR_SCENE);
}

void Scene::SetBackgroud(float r, float g, float b) {
    background_.r = r;
    background_.g = g;
    background_.b = b;
    background_.a = 1.0;
}
void Scene::SetBackgroud(float r, float g, float b,float alfa) {
    background_.r = r;
    background_.g = g;
    background_.b = b;
    background_.a = alfa;
}

/**
* This is a general process  for drawing camera, shadow map, render shape /faces ..etc
*/
void Scene::RenderScene() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    RenderInfo render_info;
    if (!SetupCamera(render_info.projection, render_info.modelview))
        ;//throw std::runtime_error("Scene::Render(): Camera not found");
    SetupLight(render_info.modelview, render_info.lights);

    int draw_framebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer);

    SetupShadowMap(render_info.shadowmap);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_info.shadowmap.framebuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    RenderShadowMap(render_info.shadowmap, render_info.shadowmap.modelview);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render_info.id = 0;
    render_info.render_transparent = false;
    Render(render_info, render_info.modelview);
    render_info.id = 0;
    render_info.render_transparent = false;
    Render(render_info, render_info.modelview);

}

