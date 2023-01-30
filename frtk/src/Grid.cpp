

#include "Grid.h"


#include <ObjectShaderNode.h>

//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
static Transform* sun = nullptr;
static std::shared_ptr<Transform> CreateSun() {
    sun = new Transform();

    auto sun_height = std::make_shared<Transform>();
    sun_height->Translate(30, 500, 30);
    sun->AddNode(sun_height);

    auto light = std::make_shared<Light>();
    light->SetPosition(0, 0, 0);
    light->SetDiffuse(0.5, 0.5, 0.5);
    light->SetAmbient(0.4, 0.4, 0.4);
    light->EnableShadowMap(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::ortho<float>(-50, 50, -50, 50, 400, 600));
    sun_height->AddNode(light);
    return std::shared_ptr<Transform>(sun);
}



std::shared_ptr<Transform>CreateGrid() {
    //auto floor = std::make_shared<Transform>();
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0, 0, 10);
    bunny_t->Scale(5, 5, 5);
    bunny_t->Rotate(0, 1, 0, 0);
    //bunny_t->Rotate(0, 0, 0, 1);
    //bunny_t->Rotate(90, 0, 0, 1);

    auto bunny = std::make_shared<ObjectShaderNode>(0x59a0d6, 0.001);
    //bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/resources/mesh/xy_plane.off"));
    bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/frtk/src/data/bunny.off"));
    bunny_t->AddNode(bunny);





    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(true);
    rightlight_spot->SetPosition(2.956, -0.514, 1.074);
    rightlight_spot->SetupSpot(1, 0, -0.1, 45, 16);
    rightlight_spot->SetDiffuse(0, 0, 0);
    rightlight_spot->SetAmbient(0.42, 0.42, 0.42);
    rightlight_spot->SetAttenuation(1, 0.002, 0);

   // bunny_t->AddNode(rightlight_spot);










    //floor->AddNode(bunny_t);
  //  bunny_t->AddNode(CreateSun());
    return bunny_t;
}

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::setDimentionPoints(int x1, int y1, int x2, int y2, int angle)
{
}

void Grid::setDimention(int x, int y, int width, int angle)
{
}

void Grid::Render(RenderInfo& info, const glm::mat4& modelview)
{

}

void Grid::setGridSize(int sizeINmm)
{
}