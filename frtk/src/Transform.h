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
// copipies of the Software, and to permit persons to whom the Software is
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
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <memory>

#include "Group.h"

class Manipulator;

class Transform : public Group {
public:
    /**
     * Constructor
     * Loads the identity by default
     */
    Transform();

    /**
     * Loads the identity matrix
     */
    void LoadIndentity();

    /**
     * Multiply the current matrix by a rotation matrix
     */
    void Rotate(float x, float y, float z, float angle);

    /**
     * Multiply the current matrix by a translation matrix
     */
    void Translate(float x, float y, float z);

    /**
     * Multiply the current matrix by a translation matrix
     */
    void Scale(float x, float y, float z);

    /**
     * Sets the manipulator
     */
    void SetManipulator(std::unique_ptr<Manipulator> manipulator);

    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    //bool SetupCamera(glm::mat4& projection, glm::mat4& modelview) override;

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

    /**
     * Sets the shadow map
     */
    bool SetupShadowMap(ShadowMapInfo& info) override;

    /**
     * Renders the shadow map
     */
    void RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) override;

    /**
     * Renders the node
     */
    void Render(RenderInfo& info, const glm::mat4& modelview) override;

private:
    std::unique_ptr<Manipulator> manipulator_;
    glm::mat4 matrix_;
    glm::mat4 inverse_;
};

#endif

