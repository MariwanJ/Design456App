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

#include <fr_grid.h>

#include <fr_object_shader_node.h>
#include <fr_primativeShader.h>
//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<Transform>bunny() {
    //auto floor = std::make_shared<Transform>();
    auto bunny_t = std::make_shared<Transform>();
    bunny_t->Translate(0, 0, 0);
    bunny_t->Scale(1, 1, 1);
    bunny_t->Rotate(0, 1, 0, 0);
    //bunny_t->Rotate(0, 0, 0, 1);
    //bunny_t->Rotate(90, 0, 0, 1);
    auto bunny = std::make_shared<ObjectShaderNode>(0xc9c9c9, 0.005f); //  color and

    //bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/resources/mesh/xy_plane.off"));
    //bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/frtk/src/data/bunny.off"));
    bunny->SetMesh(std::make_shared<Mesh>("E:/Projects/Design456App/resources/mesh/Cube.off"));

    auto rightlight_spot = std::make_shared<Light>();
    rightlight_spot->SetActive(true);
    rightlight_spot->SetPosition(2.956f, -0.514f, 1.074f);
    rightlight_spot->SetupSpot(1.0f, 0.0f, -0.1f, 45.0f, 16.0f);
    rightlight_spot->SetDiffuse(0.0f, 0.0f, 0.0f);
    rightlight_spot->SetAmbient(0.42f, 0.42f, 0.42f);
    rightlight_spot->SetAttenuation(1.0f, 0.002f, 0.0f);
    bunny_t->AddNode(rightlight_spot);
    bunny_t->AddNode(bunny);
    return bunny_t;
}
/**
 * Grid constructor.
 *
 */
Grid::Grid()
{
    setGridParam();//default values. Otherwise you have to use setGridParam
    type(NODETYPE::FR_GRID);
}
/**
 * .
 *
 * \param sections No of line sections. default = 50
 * \param gridSize Distance between each line. default = 1mm
 * \param pos Center of the grid. Defualt is the origin (0,0,0)
 * \param scale Scale of the grid - defualt is (1.0f,1.0f,1.0f)
 */

void Grid::setGridParam(unsigned int sections,
    unsigned int gridSize,
    glm::vec3 pos,
    glm::vec3 scale) {
    sections_ = sections;
    gridSize_ = gridSize;
    scale_ = scale;
    centerPos_ = pos;
    gridColor_ = (glm::vec4)FR_RED;
}

Grid::~Grid()
{
}

void Grid::setCenterPosition(glm::vec3 pos)
{
    centerPos_ = pos;
}

void Grid::setAngle(float Angle)
{
    gridRotation_[3] = glm::radians(Angle);
}

void Grid::setRotation(glm::vec4 rotation)
{
    gridRotation_ = rotation;
}

glm::vec4 Grid::getRotation(void) {
    return gridRotation_;
}

void Grid::setVisible(bool status)
{
    active_ = status;
}

void Grid::setGridSize(unsigned int sizeINmm)
{
    gridSize_ = sizeINmm;
}

unsigned int Grid::getGridSize(void) const
{
    return gridSize_;
}

std::shared_ptr<Transform> Grid::CreateGrid()
{
    auto grid_t = std::make_shared<Transform>();
    std::vector<float> vertices;
    float x, y, z;
    x = y = z = 0;

    //First lines
    for (int i = 0; i <= sections_; i += gridSize_) {
        for (int j = 0; j <= sections_; j += sections_) {
            x = (float)i * gridSize_;
            y = (float)j * gridSize_;
            float z = 0.0;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
    //Second lines to create the squre plane
    for (int i = 0; i <= sections_; i += gridSize_) {
        for (int j = 0; j <= sections_; j += sections_) {
            x = (float)j * gridSize_;
            y = (float)i * gridSize_;
            float z = 0.0;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    std::vector<unsigned int> indices;
    int noOfVerticies = (int)vertices.size();
    for (int i = 0; i <= sections_ * 2; i++) {
        indices.push_back(i);
    }
    grid_t->Scale(1, 1, 1);
    std::shared_ptr<Fr_Primatives> primative = std::make_shared<Fr_Primatives>();
    primative->SetVertexes(vertices, indices);
    std::shared_ptr gridS = std::make_shared<Fr_PrimaitiveShader>(gridColor_, 0.005); //  color and
    gridS->SetPrimative(primative);
    grid_t->AddNode(gridS);
    return grid_t;
}