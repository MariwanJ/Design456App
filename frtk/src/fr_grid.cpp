//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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

#include <fr_modelnodeShader.h>
#include <fr_primativeShader.h>
//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
///std::shared_ptr<Fr_Texture2D> saveme;

//std::shared_ptr<Transform>bunny() {
//    auto bunny_t = std::make_shared<Transform>();
//    bunny_t->Translate(0, 0, 0);
//    bunny_t->Scale(1, 1, 1);
//    auto bunny = std::make_shared<ModelNode>(glm::vec4(FR_123D), 0.02f); //  color and
//
//   // bunny->SetMesh(std::make_shared<Shape>("E:/Projects/Design456App/resources/mesh/cube.off"));
//    bunny->SetMesh(std::make_shared<Shape>("E:/Projects/Design456App/resources/mesh/CubeCenter.off"));
//    //bunny->SetMesh(std::make_shared<Shape>("E:/Projects/Design456App/resources/mesh/Pyramid.off"));
//    bunny->m_Texture2D = std::make_shared<Fr_Texture2D>();
//    //std::string imag = ("E:/Projects/Design456App/resources/Texture/test.png");
//    //std::string imag = ("E:/Projects/Design456App/resources/Texture/ts.png");
//    //std::string imag = ("E:/Projects/Design456App/resources/Texture/Surface.png");
//   // std::string imag = ("E:/Projects/Design456App/resources/Texture/2.png");
//    //std::string imag = ("E:/Projects/Design456App/resources/Texture/3.png");
//    //std::string imag = ("E:/Projects/Design456App/resources/Texture/default.png");
//    ///*if (!bunny->m_Texture2D->set2DTexture(imag)) {
//    //    DEBUG_BREAK;
//    //}*/
//    bunny->m_Texture2D->setup2DTexture();
//    //bunny->SetMesh(std::make_shared<Shape>("E:/Projects/Design456App/resources/mesh/Wedge.off"));
//    auto Bunny_spot = std::make_shared<Light>();
//    Bunny_spot->SetActive(true);
//    Bunny_spot->SetPosition(0.f, 2.f, 5.0f);
//    // Bunny_spot->SetupSpot(-1.0f, -10.0f, 5.0f, 25.0f, 1.0f);
//    Bunny_spot->SetDiffuse(.2f, .2f, 0.2);
//    Bunny_spot->SetAmbient(0.2f, 0.2f, 0.2f);
//    Bunny_spot->SetAttenuation(0.50f, 0.2f, 0.50f);
//    Bunny_spot->SetSpecular(FR_METAL);
//    //bunny_t->AddNode(Bunny_spot);
//    //bunny_t->AddNode(bunny);
//    bunny->SetActive(true);
// 
//    //bunny->calculateTextureCoord();
//    return bunny_t;
//}
/**
 * Grid constructor.
 *
 */

namespace FR{
Grid::Grid()
{
    setGridParam();//default values. Otherwise you have to use setGridParam
    type(NODETYPE::FR_GRID);
}
/**
 * .
 *
 * \param sections No of line sections. default = 50
 * \param gridWidth Distance between each line. default = 1mm
 * \param pos Center of the grid. Defualt is the origin (0,0,0)
 * \param scale Scale of the grid - defualt is (1.0f,1.0f,1.0f)
 */

void Grid::setGridParam(unsigned int sections,
    unsigned int gridWidth,
    glm::vec3 pos,
    glm::vec3 scale) {
    sections_ = sections;
    gridWidth_ = gridWidth;
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

void Grid::setgridWidth(unsigned int sizeINmm)
{
    gridWidth_ = sizeINmm;
}

unsigned int Grid::getgridWidth(void) const
{
    return gridWidth_;
}

std::shared_ptr<Fr_PrimaitiveShader> Grid::CreateGrid()
{
    std::vector<float> vertices;
    float x, y, z;
    x = y = z = 0;
    float totalLength = gridWidth_ * sections_;
    glm::vec3 limmitValue = glm::vec3(centerPos_[0] - (totalLength / 2), centerPos_[1] - (totalLength / 2), centerPos_[2]);
    //First lines
    for (int i = 0; i <= (sections_); i++) {
        for (int j = 0; j <= sections_; j += sections_) {
            x = limmitValue[0] + i * gridWidth_;
            y = limmitValue[1] + (float)j * gridWidth_;
            z = limmitValue[2];
            if ((x == 0 && y == 0) ||
                (x == 0 && z == 0) ||
                (y == 0 && z == 0)) {
                //We don't draw the axis line as we draw them separately
                continue;
            }
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
    //Second lines to create the squre plane
    for (int i = 0; i <= (sections_); i++) {
        for (int j = 0; j <= sections_; j += sections_) {
            x = limmitValue[0] + (float)j * gridWidth_;
            y = limmitValue[1] + (float)i * gridWidth_;
            z = limmitValue[2];
            if ((x == 0 && y == 0) ||
                (x == 0 && z == 0) ||
                (y == 0 && z == 0)) {
                //We don't draw the axis line as we draw them separately
                continue;
            }
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    std::vector<unsigned int> indices;
    for (int i = 0; i <= vertices.size(); i++) {
        indices.push_back(i);
    }
    std::shared_ptr<Fr_Primatives> primative = std::make_shared<Fr_Primatives>();
    primative->SetVertexes(vertices, indices);
    std::shared_ptr gridS = std::make_shared<Fr_PrimaitiveShader>(gridColor_, 0.005); //  color and
    gridS->SetPrimative(primative);
    return gridS;
}
}