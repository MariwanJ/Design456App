

#include "Grid.h"


#include <ObjectShaderNode.h>
//Temprary code to have somthing to show.
std::shared_ptr<Transform>CreateGrid() {
    auto floor = std::make_shared<Transform>();
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0.9, -0.6, 1.2);
    bunny_t->Scale(5, 5, 5);
    bunny_t->Rotate(45, 1, 0, 0);
    bunny_t->Rotate(45, 0, 1, 0);
    auto bunny = std::make_shared<ObjectShaderNode>(0xAA55AA, 0.02);
    bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/resources/mesh/xy_plane.off"));
    //bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/try things/Scene-Graph-222_Important/src/data/bunny.off"));
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
