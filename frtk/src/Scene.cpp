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
    //glCheckFunc(glEnable(GL_TEXTURE_2D)); Not a OPENGL3+ function
    glCheckFunc(glEnable(GL_DEPTH_TEST));
    glCheckFunc(glEnable(GL_BLEND));
    glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glCheckFunc(glClearColor(background_.r, background_.g, background_.b, 1.0));

    RenderInfo render_info;
    if (!SetupCamera(render_info.projection, render_info.modelview)){
        //throw std::runtime_error("Scene::Render(): Camera not found");
        std::cout << "not found" << std::endl;
    }
    std::cout << "ok" << std::endl;
    SetupLight(render_info.modelview, render_info.lights);

    int draw_framebuffer = 0;
    glCheckFunc(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer));

    SetupShadowMap(render_info.shadowmap);

    //glCheckFunc(glPushAttrib(GL_VIEWPORT_BIT));  NOT OPENGL3+ Function
    glCheckFunc(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_info.shadowmap.framebuffer));
    glCheckFunc(glViewport(0, 0, render_info.shadowmap.width, render_info.shadowmap.height));
    glCheckFunc(glClear(GL_DEPTH_BUFFER_BIT)); 
    RenderShadowMap(render_info.shadowmap, render_info.shadowmap.modelview);
    //glCheckFunc(glPopAttrib());

    glCheckFunc(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer));
    glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    render_info.id = 0;
    render_info.render_transparent = false;
    Render(render_info, render_info.modelview);
    render_info.id = 0;
    render_info.render_transparent = true;
    Render(render_info, render_info.modelview);
}

