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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//



#include<Fr_Core.h>
#include<Fr_GL3Window.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Scene.h>
#include <Camera.h>
#include <Engine.h>
#include <Light.h>
#include <Manipulator.h>
#include <Mesh.h>
#include <Scene.h>
#include <ToonShaderNode.h>
#include <Transform.h>




 /* Scene and engine*/
static Scene *scene = nullptr;


void Fr_GL3Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (s_GladInitialized && s_GLFWInitialized) {
        glViewport(0, 0, _wGl, _hGl);
    }
}

void Fr_GL3Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Fr_GL3Window::cursor_position_callback(GLFWwindow*, double xpos, double ypos)
{
}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow*, int button, int action, int mods)
{
}

void Fr_GL3Window::scroll_callback(GLFWwindow*, double xoffset, double yoffset)
{
}



/* Cameras and manipulators */
enum CameraList {
    kGlobal,
    kDriver,
    kJeep,
    kNCameras
};
static struct {
    Camera *camera;
    Manipulator *manipulator;
} cameras[kNCameras];
static int curr_camera = kDriver;

/* Other stuff */
static Transform *sun = nullptr;
static float sun_alpha = 0;
static Light *jeep_light = nullptr;

/* Auxiliary functions and glut callbacks */

static void Display();
static void Keyboard(unsigned char key, int x, int y);
static void Idle();
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);
static void CreateScene();
static std::shared_ptr<Camera> CreateCamera(Group *parent, int cameraId);
static std::shared_ptr<Transform> CreateSun();
static std::shared_ptr<Transform> CreateRoad();
static std::shared_ptr<Transform> CreateShip();
static std::shared_ptr<ToonShaderNode> CreateJeepItem(
        std::shared_ptr<Transform> jeep, const std::string& name,
        unsigned int color);
static std::shared_ptr<Transform> CreateJeep();

int FakeMain(int argc, char* argv[]) {
    Fr_GL3Window* win = new Fr_GL3Window(0, 0, 1000, 800, "Modern OpenGL with FLTK support");
    win->setOpenGLWinowSize(70, 60, 600, 600);
    win->resizable(win);
    CreateScene();
    return 0; 
}
    
static void Display() {
    scene->RenderScene();
    //glutSwapBuffers();
}

static void CreateScene() {
    scene = new Scene();
    scene->SetBackgroud(0.69, 0.95, 1.00);

    auto camera = CreateCamera(scene, kGlobal);
    camera->SetEye(20, 5, 20);
    camera->SetCenter(0.5, 0.5, 0);
    camera->SetUp(0, 1, 0);

    scene->AddNode(CreateSun());
    scene->AddNode(CreateRoad());
}

static std::shared_ptr<Camera> CreateCamera(Group *parent, int cameraId) {
    auto camera = std::make_shared<Camera>();
    camera->SetPerspective(40, 0.5, 50);
    camera->SetActive(false);
    parent->AddNode(camera);
    auto manipulator = new Manipulator();
    camera->SetManipulator(std::unique_ptr<Manipulator>(manipulator));

    cameras[cameraId].camera = camera.get();
    cameras[cameraId].manipulator = manipulator;

    return camera;
}

static std::shared_ptr<Transform> CreateSun() {
    sun = new Transform();

    auto sun_height = std::make_shared<Transform>();
    sun_height->Translate(30, 500, 30);
    sun->AddNode(sun_height);

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 0, 0);
    light->SetDiffuse(0.5, 0.5, 0.5);
    light->SetAmbient(0.4, 0.4, 0.4);
    light->EnableShadowMap(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::ortho<double>(-50, 50, -50, 50, 400, 600));
    sun_height->AddNode(light);

    return std::shared_ptr<Transform>(sun);
}

static std::shared_ptr<Transform> CreateRoad() {
    auto floor = std::make_shared<Transform>();

    auto quad = std::make_shared<Mesh>("data/quad.msh");

    auto grass_t = std::make_shared<Transform>();
    grass_t->Scale(1000, 0, 1000);
    floor->AddNode(grass_t);

    auto grass = std::make_shared<ToonShaderNode>(0xBADA5F);
    grass->SetMesh(quad);
    grass_t->AddNode(grass);

    auto road_t = std::make_shared<Transform>();
    road_t->Scale(1000, 1, 10);
    road_t->Translate(0, 0.001, 0);
    floor->AddNode(road_t);

    auto road = std::make_shared<ToonShaderNode>(0x111111);
    road->SetMesh(quad);
    road_t->AddNode(road);

    auto strip = std::make_shared<ToonShaderNode>(0xEEEE11);
    strip->SetMesh(quad);

    for (int i = 0; i < 125; ++i) {
        auto strip_t = std::make_shared<Transform>();
        strip_t->Translate(i * 8 - 500, 0.002, 0);
        strip_t->Scale(2.5, 1, 0.2);
        floor->AddNode(strip_t);
        strip_t->AddNode(strip);
    }

    return floor;
}
//
//static std::shared_ptr<Transform> CreateShip() {
//    auto ship_t = std::make_shared<Transform>();
//    ship_t->Translate(-10, 10, 0);
//    ship_t->Scale(10, 10, 10);
//    ship_t->Rotate(90, 0, -1, 0);
//    ship_t->Rotate(90, -1, 0, 0);
//
//    auto ship = std::make_shared<ToonShaderNode>(0x444444);
//    ship->SetMesh("data/klingon_starship.off");
//    ship_t->AddNode(ship);
//
//    return ship_t;
//}
