

#include "Grid.h"


#include <ToonShaderNode.h>
//Temprary code to have somthing to show.
std::shared_ptr<Transform>CreateGrid() {
        auto floor = std::make_shared<Transform>();

        auto quad = std::make_shared<Mesh>("E:/Projects/Design456App/resources/mesh/xy_plane.off");

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
            strip_t->Scale(2.5, 1.0, 0.2);
            floor->AddNode(strip_t);
            strip_t->AddNode(strip);
        }
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
