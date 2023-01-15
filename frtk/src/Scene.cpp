/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include "Scene.h"

Scene::Scene() :
    background_{ 0.8, 0.8, 0.8,1.0 } {
}

void Scene::SetBackgroud(float r, float g, float b) {
    background_.r = r;
    background_.g = g;
    background_.b = b;
}

void Scene::RenderScene() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(background_.r, background_.g, background_.b, 1.0);

    RenderInfo render_info;
    if (!SetupCamera(render_info.projection, render_info.modelview)){
        //throw std::runtime_error("Scene::Render(): Camera not found");
        std::cout << "not fourn" << std::endl;
    }
    SetupLight(render_info.modelview, render_info.lights);

    int draw_framebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer);

    SetupShadowMap(render_info.shadowmap);

    glPushAttrib(GL_VIEWPORT_BIT);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_info.shadowmap.framebuffer);
    glViewport(0, 0, render_info.shadowmap.width, render_info.shadowmap.height);
    glClear(GL_DEPTH_BUFFER_BIT); 
    RenderShadowMap(render_info.shadowmap, render_info.shadowmap.modelview);
    glPopAttrib();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    render_info.id = 0;
    render_info.render_transparent = false;
    Render(render_info, render_info.modelview);
    render_info.id = 0;
    render_info.render_transparent = true;
    Render(render_info, render_info.modelview);
}

