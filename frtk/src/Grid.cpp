

#include "Grid.h"


#include <ObjectShaderNode.h>

//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<Transform>bunny() {
    //auto floor = std::make_shared<Transform>();
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0, 0, 10);
    bunny_t->Scale(5, 5, 5);
    bunny_t->Rotate(0, 1, 0, 0);
    //bunny_t->Rotate(0, 0, 0, 1);
    //bunny_t->Rotate(90, 0, 0, 1);

    auto bunny = std::make_shared<ObjectShaderNode>(0xbc5e13, 0.005); //  color and 
    //bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/resources/mesh/xy_plane.off"));
    bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/frtk/src/data/bunny.off"));

    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(false);
    rightlight_spot->SetPosition(2.956, -0.514, 1.074);
    rightlight_spot->SetupSpot(1.0, 0, -0.1, 45, 16);
    rightlight_spot->SetDiffuse(0, 0, 0);
    rightlight_spot->SetAmbient(0.42, 0.42, 0.42);
    rightlight_spot->SetAttenuation(1, 0.002, 0);
    bunny_t->AddNode(rightlight_spot);
    bunny_t->AddNode(bunny);
    return bunny_t;
}


std::shared_ptr<Transform>CreateGrid() {
    auto grid_t = std::make_shared<Transform>();

    int slices = 50;
    unsigned int vao;
    unsigned int vbo;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int j = 0; j <= slices; ++j) {
        for (int i = 0; i <= slices; ++i) {
            float x = (float)i / (float)slices;
            float y = 0;
            float z = (float)j / (float)slices;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    for (int j = 0; j < slices; ++j) {
        for (int i = 0; i < slices; ++i) {

            int row1 = j * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            indices.push_back(row1 + i);
            indices.push_back(row1 + i + 1);
            indices.push_back(row1 + i + 1);
            indices.push_back(row2 + i + 1);

            indices.push_back(row2 + i + 1);
            indices.push_back(row2 + i );
            indices.push_back(row2 + i );
            indices.push_back(row1 + i);

        }
    }
    grid_t->Scale(50, 50, 50);
    std::shared_ptr<Mesh> mymesh =  std::make_shared<Mesh>();
    mymesh->SetVertexes(vertices, indices);
    auto grid = std::make_shared<ObjectShaderNode>(0xbc5e13, 0.005); //  color and 
    grid->SetMesh(mymesh);
    grid_t->AddNode(grid);
    return grid_t;
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