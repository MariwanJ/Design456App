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


#include<FR.h>

int FR::glfw_e_x = 0;  //SAVE X AND Y OF LAST CLICK INSIDE GLFW
int FR::glfw_e_y = 0;

int FR::glfw_click = 0;     // 0 no, 1 yes
int FR::glfw_double_click = 0; // 0 no, 1 yes
int FR::glfw_MouseClicked = -1; //no mouse click
int FR::glfw_MouseButton  = -1; //no mouse button

//Avoid running GLFW OR GLAD CODE whiel GLFW is not created
bool FR::s_GLFWInitialized = false;
bool FR::s_GladInitialized = false;
