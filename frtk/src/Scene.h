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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef SCENE_H
#define SCENE_H
//#include<frtk.h>
#include<Fr_Core.h>
#include <Group.h>
/**
 * The scene root
 */
typedef struct {
    float r;
    float g;
    float b;
    float a; //alpha
} bkgC;

class Scene : public Group {
public:
    /**
     * Default Constructor
     */
    Scene();
    /**
     * Sets the background color
     */ 
    void SetBackgroud(float r, float g, float b);
    void SetBackgroud(float r, float g, float b, float alfa);

    /**
     * Renders the scene
     * Throws runtime_error if there's no camera
     */
    virtual void RenderScene();
    static GLFWwindow*linkToglfw;

private:
    bkgC  background_;
};

#endif

