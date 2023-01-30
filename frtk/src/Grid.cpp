

#include "Grid.h"


#include <ObjectShaderNode.h>
//Temporary code to have something to show.
std::shared_ptr<Transform>CreateGrid() {
    auto floor = std::make_shared<Transform>();
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
    floor->AddNode(bunny_t);
    return floor;
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