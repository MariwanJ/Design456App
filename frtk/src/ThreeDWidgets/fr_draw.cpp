#include "fr_draw.h"
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
namespace FR {



    Fr_TwoD_Drawing::Fr_TwoD_Drawing() :m_Vertices {0}, m_Indices{0}, m_Normals{0}, m_Type(FR_LINE), m_vbo{0}, m_vao{0}
    {
    }

    Fr_TwoD_Drawing::Fr_TwoD_Drawing(Fr_TwoD_Drawing& obj)
    {
        m_Vertices = std::move(obj.m_Vertices);
        m_Indices = std::move(obj.m_Indices);
        m_Normals = std::move(obj.m_Normals);
        m_Type = obj.m_Type;
        m_Type;
        m_vbo[0] = obj.m_vbo[0];
        m_vbo[1] = obj.m_vbo[1];
        m_vbo[2] = obj.m_vbo[2];
        m_vao=obj.m_vao;
        m_lineWidth=obj.m_lineWidth;
    }

    Fr_TwoD_Drawing::Fr_TwoD_Drawing(twodType type, std::shared_ptr<std::vector<float>> verticies, std::shared_ptr<std::vector<unsigned int>>& indicies)
    {
        m_Vertices = std::move(verticies);
        m_Indices = std::move(indicies);
        m_Type = type;
    }

    Fr_TwoD_Drawing::~Fr_TwoD_Drawing()
    {
    }

    void Fr_TwoD_Drawing::Verticies(std::shared_ptr<std::vector<float>> vert)
    {
        m_Vertices = std::move(vert);
    }

    std::shared_ptr<std::vector<float>> Fr_TwoD_Drawing::Verticies()
    {
        return m_Vertices;
    }

    void Fr_TwoD_Drawing::Indicies(std::shared_ptr<std::vector<unsigned int>> indc)
    {
        m_Indices = std::move(indc);
    }

    std::shared_ptr<std::vector<unsigned int>> Fr_TwoD_Drawing::Indicies()
    {
        return m_Indices;
    }


    void Fr_TwoD_Drawing::Type(twodType type)
    {
        m_Type = type;
    }

    twodType Fr_TwoD_Drawing::Type(void)
    {
        return twodType();
    }

    void Fr_TwoD_Drawing::Draw()
    {
    }

    void Fr_TwoD_Drawing::lineWidth(unsigned int wid)
    {
        m_lineWidth = wid;
    }

    unsigned int Fr_TwoD_Drawing::lineWidth()
    {
        return m_lineWidth;
    }

    int Fr_TwoD_Drawing::initializeVBO()
    {
        //todo fixme

        //    glCheckFunc(glGenBuffers(1, vbo_));
        //    glCheckFunc(glGenVertexArrays(1, &vao_));
        //    glCheckFunc(glBindVertexArray(vao_));       //Keeps all instructions related this object

        //    glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]));        //First object buffer
        //    glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW));
        //    glCheckFunc(glEnableVertexAttribArray(0));
        //    glCheckFunc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL));
        //}
        //glCheckFunc(glBindVertexArray(0)); 
        return 0;//todo fixme
    }
    
}
