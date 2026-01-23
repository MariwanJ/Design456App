//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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
#include <grid/fr_primatives.h>
namespace FR {
    Fr_Primatives::Fr_Primatives() :vbo_{ 0, 0, 0 }, vao_(0), drawType(GL_LINES), m_lineWidth(1) {
    }

    Fr_Primatives::~Fr_Primatives() {
        if (vao_ != 0) {
            glCheckFunc(glDeleteVertexArrays(1, &vao_));
            glCheckFunc(glDeleteBuffers(NUM_OF_VBO_BUFFERS, vbo_));
        }
    }

    void Fr_Primatives::Draw()
    {
        glBindVertexArray(vao_);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);

        float lw = (drawType == GL_LINES || drawType == GL_LINE_STRIP || drawType == GL_LINE_LOOP) ? m_lineWidth : 1.0f;

        glLineWidth(lw);

        GLsizei vertexCount = static_cast<GLsizei>(vertices_.size() / 3);

        if (drawType == GL_TRIANGLES)
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(drawType, 0, vertexCount);

        glBindVertexArray(0);

        glLineWidth(1.0f);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
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
        InitializeVBO();
    }

    void Fr_Primatives::lineWidth(float wid)
    {
        m_lineWidth = wid;
    }

    float Fr_Primatives::lineWidth()
    {
        return m_lineWidth;
    }

    void Fr_Primatives::InitializeVBO()
    {
        glGenVertexArrays(1, &vao_);
        glGenBuffers(2, vbo_);
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        if (drawType == GL_TRIANGLES)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);
        }
        glBindVertexArray(0);
    }
}