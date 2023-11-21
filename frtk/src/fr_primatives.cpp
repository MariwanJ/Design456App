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
#include <fr_primatives.h>

Fr_Primatives::Fr_Primatives() :vbo_{ 0, 0, 0 }, vao_(0), drawType(GL_LINES),m_lineWidth(1) {
}

Fr_Primatives::~Fr_Primatives() {
    if (vao_ != 0) {
        glCheckFunc(glDeleteVertexArrays(1, &vao_));
        glCheckFunc(glDeleteBuffers(3, vbo_));
    }
}

void Fr_Primatives::Draw()
{
    if (drawType == GL_LINES) {
        glCheckFunc(glBindVertexArray(vao_));
        glCheckFunc(glDrawArrays(GL_LINES, 0, vertices_.size()));
        glCheckFunc(glBindVertexArray(0));
        glCheckFunc(glLineWidth(m_lineWidth));
    }
    else if (drawType == GL_LINE_STRIP) {
        glCheckFunc(glBindVertexArray(vao_));
        glCheckFunc(glDrawArrays(GL_LINE_STRIP, 0, vertices_.size()));
        glCheckFunc(glBindVertexArray(0));
        glCheckFunc(glLineWidth(m_lineWidth));
    }
    else if (drawType == GL_LINE_LOOP) {
        glCheckFunc(glBindVertexArray(vao_));
        glCheckFunc(glDrawArrays(GL_LINE_LOOP, 0, vertices_.size()));
        glCheckFunc(glBindVertexArray(0));
        glCheckFunc(glLineWidth(m_lineWidth));
    }
    else if (drawType == GL_TRIANGLES) {
        glCheckFunc(glBindVertexArray(vao_));
        glCheckFunc(glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0));
        glCheckFunc(glBindVertexArray(0));
        glCheckFunc(glLineWidth(m_lineWidth));
    }
}

void Fr_Primatives::setDrawType(int type)
{
    drawType = type;
}

int Fr_Primatives::getDrawType() const
{
    return drawType;
}

void Fr_Primatives::GetPrimatives(std::vector<float>& vertices, std::vector<float>& normals, std::vector<unsigned int>& indices) {
    vertices = vertices_;
    normals = normals_;
    indices = indices_;
}

void Fr_Primatives::SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    vertices_ = vertices;
    indices_ = indices;
    InitializeVBO(vertices_, normals_, indices_);
}

void Fr_Primatives::lineWidth(unsigned int wid)
{
    m_lineWidth=wid;
}

unsigned int Fr_Primatives::lineWidth()
{
    return m_lineWidth;
}

glm::vec3 Fr_Primatives::GetVertex(unsigned int index, const float vertices[]) {
    return glm::vec3(
        vertices[index * 3],
        vertices[index * 3 + 1],
        vertices[index * 3 + 2]
    );
}

void Fr_Primatives::SetVertex(unsigned int index, float vertices[], const glm::vec3& vertex) {
    vertices[index * 3] = vertex[0];
    vertices[index * 3 + 1] = vertex[1];
    vertices[index * 3 + 2] = vertex[2];
}

void Fr_Primatives::InitializeVBO(const std::vector<float>& vertices,
    const std::vector<float>& normals,
    const std::vector<unsigned int> indices) {
    if (drawType == GL_TRIANGLES) {
        glCheckFunc(glGenBuffers(1, vbo_));
        glCheckFunc(glGenVertexArrays(1, &vao_));
        glCheckFunc(glBindVertexArray(vao_));

        glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[0]));
        glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
    }
    else
    {
        glCheckFunc(glGenBuffers(1, vbo_));
        glCheckFunc(glGenVertexArrays(1, &vao_));
        glCheckFunc(glBindVertexArray(vao_));       //Keeps all instructions related this object

        glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]));        //First object buffer
        glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW));
        glCheckFunc(glEnableVertexAttribArray(0));
        glCheckFunc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL));
    }
    glCheckFunc(glBindVertexArray(0));
}