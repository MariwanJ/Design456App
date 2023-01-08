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

#ifndef  FR_BASIC_SHAPES_H
#define  FR_BASIC_SHAPES_H

#include<frtk.h>
#include <../deps/linmath.h>

int draw_triangle(GLuint& vertexBuffer, GLFWwindow* pWindow);

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
unsigned int CompileShader(unsigned int type, const std::string& source);

extern const char* fragmentShaderSource;
extern const char* vertexShaderSource;

#endif