/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#include <Scene.h>
GLFWwindow* Scene::linkToglfw=nullptr;

Scene::Scene() :
    background_{ 0.8, 0.8, 0.8,1.0 }{
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


void Scene::RenderScene() {
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    RenderInfo render_info;
    if (!SetupCamera(render_info.projection, render_info.modelview))
        throw std::runtime_error("Scene::Render(): Camera not found");
    SetupLight(render_info.modelview, render_info.lights);

    int draw_framebuffer = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer);

    SetupShadowMap(render_info.shadowmap);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_info.shadowmap.framebuffer);
    glViewport(0, 0, render_info.shadowmap.width, render_info.shadowmap.height);
   // glClear(GL_DEPTH_BUFFER_BIT);
    RenderShadowMap(render_info.shadowmap, render_info.shadowmap.modelview);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render_info.id = 0;
    render_info.render_transparent = false;
    Render(render_info, render_info.modelview);
    render_info.id = 0;
    render_info.render_transparent = true;
    Render(render_info, render_info.modelview);
   // glDrawArrays(GL_TRIANGLES, 0, draw_framebuffer);

    // draw our first triangle
    //glUseProgram(shaderProgram);
    //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, render_info.shadowmap.width);
    glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    if (linkToglfw!=nullptr){
    glfwSwapBuffers(linkToglfw);
    glfwPollEvents();
    glad_glFlush();
    }
    else {
        std::cout << "link to glfw not defined\n";
    }
}

