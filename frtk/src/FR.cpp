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






#include<FR.h>


int FR::glfw_e_x=0;  //SAVE X AND Y OF LAST CLICK INSIDE GLFW
int FR::glfw_e_y=0;

int FR::glfw_click=0;     // 0 no, 1 yes
int FR::glfw_double_click=0; // 0 no, 1 yes

//Avoid running GLFW OR GLAD CODE whiel GLFW is not created
bool FR::s_GLFWInitialized=false;
bool FR::s_GladInitialized=false;
