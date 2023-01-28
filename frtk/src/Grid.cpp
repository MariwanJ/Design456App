

#include "Grid.h"


#include <ObjectShaderNode.h>
//Temprary code to have somthing to show.
std::shared_ptr<Transform>CreateGrid() {
    auto floor = std::make_shared<Transform>();
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0.9, -0.6, 1.2);
    bunny_t->Scale(1, 1, 1);
    bunny_t->Rotate(90, 1, 0, 0);
    bunny_t->Rotate(90, 0, 1, 0);
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
