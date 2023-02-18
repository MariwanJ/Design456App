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

#include <ObjectShaderNode.h>
#include <fr_primativeShader.h>
//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "fr_axis3D.h"


Axis3D::Axis3D()
{
}

Axis3D::~Axis3D()
{
}

vert Axis3D::CreateAxis3D()
{
    vert axis_t;
    std::vector<float> verticesRed;
    std::vector<float> verticesGreen;
    std::vector<float> verticesBlue;
    float x, y, z;
    x = y = z = 0;

    glColor3f(1.0, 0.0, 0.0); // red x

    verticesRed = {
        -4.0f,  0.0f,  0.0f,
         4.0f,  0.0f,  0.0f,

         4.0f,  0.0f,  0.0f,
         3.0f,  1.0f,  0.0f,
         4.0f,  0.0f,  0.0f,
         3.0f, -1.0f,  0.0f
    };

    glColor3f(0.0, 1.0, 0.0); // green y

    verticesGreen = {
        0.0f, -4.0f,  0.0f,
        0.0f,  4.0f,  0.0f,

        0.0f,  4.0f,  0.0f,
        1.0f,  3.0f,  0.0f,
        0.0f,  4.0f,  0.0f,
       -1.0f,  3.0f,  0.0f
    };


    // z 
    glColor3f(0.0, 0.0, 1.0); // blue z

    verticesBlue = {
        0.0f,  0.0f, -4.0f,
        0.0f,  0.0f,  4.0f,

        0.0f,  0.0f,  4.0f,
        0.0f,  1.0f,  3.0f,
        0.0f,  0.0f,  4.0f,
        0.0f, -1.0f,  3.0f
    };

    std::vector<unsigned int> indicesRed;
    int noOfVerticies = (int)verticesRed.size();
    for (int i = 0; i <= verticesRed.size(); i++) {
        indicesRed.push_back(i);
    }
    std::vector<unsigned int> indicesGreen;
    noOfVerticies = (int)verticesGreen.size();
    for (int i = 0; i <= verticesGreen.size(); i++) {
        indicesGreen.push_back(i);
    }
    std::vector<unsigned int> indicesBlue;
    noOfVerticies = (int)verticesBlue.size();
    for (int i = 0; i <= verticesBlue.size(); i++) {
        indicesBlue.push_back(i);
    }

   
    auto primativeR= std::make_shared<Fr_Primatives>();
    primativeR->SetVertexes(verticesRed, indicesRed);
    auto axRed = std::make_shared<Fr_PrimaitiveShader>(glm::vec4(FR_RED), 0.005); //  color and
    axRed->SetPrimative(primativeR);
    axis_t.Red = std::make_shared<Transform>();
    axis_t.Red->AddNode(axRed);
    
    std::shared_ptr <Fr_Primatives>primativeG = std::shared_ptr<Fr_Primatives>(new Fr_Primatives());
    primativeG->SetVertexes(verticesGreen, indicesGreen);
    auto axGreen = std::make_shared<Fr_PrimaitiveShader>(glm::vec4(FR_GREEN), 0.005); //  color and
    axGreen->SetPrimative(primativeG);
    axis_t.Green=std::make_shared<Transform>();
    axis_t.Green->AddNode(axGreen);

    auto primativeB = std::make_shared<Fr_Primatives>();
    primativeB->SetVertexes(verticesRed, indicesBlue);
    auto axBlue = std::make_shared<Fr_PrimaitiveShader>(glm::vec4(FR_BLUE), 0.005); //  color and
    axBlue->SetPrimative(primativeG);
    axis_t.Blue= std::make_shared<Transform>();
    axis_t.Blue->AddNode(axBlue);
    axis_t.Red->Scale(1, 1, 1);
    axis_t.Green->Scale(1, 1, 1);
    axis_t.Blue->Scale(1, 1, 1);

    return axis_t;
}

void Axis3D::setVisible(bool status)
{
    active_ = status;
}

void Axis3D::setAxis3DSize(unsigned int sizeINmm)
{
    axis3DSize_ = sizeINmm;
}

unsigned int Axis3D::getAxis3DSize(void) const
{
    return axis3DSize_;
}