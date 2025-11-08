//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
#include <fr_draw.h>
#include <fr_core.h>
#include <fr_widget.h>
#include <frtk.h>

namespace FR {
    void Fr_Widget::draw_2d()
    {
        glCheckFunc(glBindVertexArray(m_vao));
        glCheckFunc(glLineWidth(m_lineWidth));

        switch (lineType()) {
        case FR_POINT: {

        }
        case FR_LINES: {
            glCheckFunc(glDrawElements(GL_LINES,(int) m_indices->size(), GL_UNSIGNED_INT, 0));

        }break;
        case FR_OPEN_LOOP: {
            glCheckFunc(glDrawElements(GL_LINE_LOOP, (int)m_indices->size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!

        }break;
        case FR_CLOSED_LOOP: {  //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
            glCheckFunc(glDrawElements(GL_TRIANGLE_FAN,(int) m_indices->size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!            break;

        }break;
        case FR_CIRCLE: {
            FRTK_CORE_INFO("NOT IMPLEMENTED YET!");


        }break;
        case FR_CURVE: {
            FRTK_CORE_INFO("NOT IMPLEMENTED YET!");

        }break;
        case FR_ARC: {
            FRTK_CORE_INFO("NOT IMPLEMENTED YET!");


        }break;
        case FR_BSPLINE: {
            FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
            break;
        }
        }
        glCheckFunc(glBindVertexArray(0));
    }

    void Fr_Widget::DrawPoints() {
        glCheckFunc(glBindVertexArray(m_vao_points));
        glCheckFunc(glPointSize(m_pointSize)); // Set the size of the points
        glCheckFunc(glDrawArrays(GL_POINTS, 0, m_vertices->size() / 3));
        glBindVertexArray(0);
    }
    void Fr_Widget::lbl_Draw()
    {
    }
    //Label Draw and Font rendering
    void Fr_Widget::lbl_draw()
    {
        return; //do nothing should be sub-classed
    }

    void Fr_Widget::pointSize(float val)
    {
        m_pointSize = val;
    }

    float Fr_Widget::pointSize()
    {
        return m_pointSize;
    }

    void Fr_Widget::lineWidth(float wid)
    {
        m_lineWidth = wid;
    }

    float Fr_Widget::lineWidth()
    {
        return m_lineWidth;
    }
    //You must override this if you want to draw differntly 
    int Fr_Widget::initializeVBO() {
        glCheckFunc(glGenBuffers(NUM_OF_VBO_BUFFERS, m_vbo));
        glCheckFunc(glGenVertexArrays(1, &m_vao_points));
        glCheckFunc(glGenVertexArrays(1, &m_vao));
        glCheckFunc(glBindVertexArray(m_vao));

        // VERTICES
        if (m_vertices)
            if (!m_vertices->empty()) {
                glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_VERTEX_VB]));
                glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices->size(), m_vertices->data(), GL_STATIC_DRAW));
                glCheckFunc(glEnableVertexAttribArray(POSITION_VERTEX_VB));
                glCheckFunc(glVertexAttribPointer(SHADER_POS_VERTEX_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL)); // m_positionVB = 0

            }

        // TEXTURE COORDINATES
        if (m_textureCoord)
            if (!m_textureCoord->empty()) {
                glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_TEXCOORD_VB]));
                glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_textureCoord->size(), m_textureCoord->data(), GL_STATIC_DRAW));
                glCheckFunc(glEnableVertexAttribArray(POSITION_TEXCOORD_VB));
                glCheckFunc(glVertexAttribPointer(SHADER_POS_TEXTURE_VB, 2, GL_FLOAT, GL_FALSE, 0, NULL)); // POSITION_TEXCOORD_VB = 2
            }

        // ELEMENTS (Indices)
        if (m_indices)
            if (!m_indices->empty()) {
                glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDICES_VB]));
                glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices->size() * sizeof(unsigned int), m_indices->data(), GL_STATIC_DRAW));
            }

        // NORMALS
        if (m_normals)
            if (!m_normals->empty()) {
                glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_NORMAL_VB]));
                glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_normals->size(), m_normals->data(), GL_STATIC_DRAW));
                glCheckFunc(glEnableVertexAttribArray(POSITION_NORMAL_VB)); // POSITION_NORMAL_VB should correspond to the layout in your shader, typically 2
                glCheckFunc(glVertexAttribPointer(SHADER_POS_NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL)); // Corrected to use a valid offset and index
                glCheckFunc(glBindVertexArray(0));
            }
        

        //TODO : SHOULD WE ALWASY CREATE m_selected ???? 
        if (m_selected->size() > 0) {
            //2 Points for each edge
            glCheckFunc(glBindVertexArray(m_vao_points));
            glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_POINTS_VB]));
            glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices->size(), m_vertices->data(), GL_STATIC_DRAW));
            glCheckFunc(glEnableVertexAttribArray(SHADER_POS_POINTS_VB)); 
            glCheckFunc(glVertexAttribPointer(SHADER_POS_POINTS_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL)); 
            glCheckFunc(glBindVertexArray(0));
        }
        //selection data

   
        return 0;
    }

}