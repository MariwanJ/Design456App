/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                        *
 Copyright (C) 2023                                                     *
                                                                        *
 This library is free software; you can redistribute it and/or          *
 modify it under the terms of the GNU Lesser General Public             *
 License as published by the Free Software Foundation; either           *
 version 2 of the License, or (at your option) any later version.       *
                                                                        *
 This library is distributed in the hope that it will be useful,        *
 but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 Lesser General Public License for more details.                        *
                                                                        *
 You should have received a copy of the GNU Lesser General Public       *
 License along with this library; if not, If not, see                   *
 <http://www.gnu.org/licenses/>										*
 .																*
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                       *
*/

#include <fr_widgets/fr_basic_shapes.h>


// An array of 3 vectors which represents 3 vertices
static const GLfloat buffer[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

void draw_triangle(GLuint& vertexBuffer) {

    glGenBuffers(1, &vertexBuffer);
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
        2,
        GL_FLOAT, GL_FALSE,
        sizeof(float) * 2,
        (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
/*    glVertexAttribPointer(
        0,
        3,              // size
        GL_FLOAT,       // type
        GL_FALSE,       // normalized?
        0,              // stride   
        (void*)0        // array buffer offset
    );*/
    // Draw the triangle !
    glDisableVertexAttribArray(0);

  

}