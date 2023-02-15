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

#ifndef NODE_H
#define NODE_H

#include <frtk.h>
#include <fr_core.h>
#include <glm/glm.hpp>

/**
 * A generic node that can be attached to the graph
 * It offers an empty implementation to it's methods
 * Will be sub-classed by several other classes like (Group, Light, ..etc)
 */
class Node {
public:

    /**
     * Holds the light information
     */
    struct LightInfo {
        glm::vec4 position;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 ambient;
        glm::vec3 attenuation;
        bool is_spot;
        glm::vec3 direction;
        float cutoff;
        float exponent;
    };

    /**
     * Holds the shadow map information
     */
    struct ShadowMapInfo {
        std::vector<glm::mat4> mvp;
        std::vector<glm::mat4> mvp_transparent;
        glm::mat4 modelview;
        glm::mat4 projection;
        unsigned int light_id;
        unsigned int framebuffer;
        unsigned int texture;
        unsigned int width;
        unsigned int height;
    };

    /**
     * Holds the render information
     */
    struct RenderInfo {
        int id;
        glm::mat4 modelview;
        glm::mat4 projection;
        std::vector<LightInfo> lights;
        ShadowMapInfo shadowmap;
        bool render_transparent;
    };

    /**
     * Constructor
     */
    Node();

    /**
     * Virtual destructor
     */
    virtual ~Node();

    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    virtual void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

    /**
     * Sets the shadow map
     */
    virtual bool SetupShadowMap(ShadowMapInfo& info);

    /**
     * Renders the shadow map
     */
    virtual void RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview);

    /**
     * Renders the node
     */
    virtual void Render(RenderInfo& info, const glm::mat4& modelview);

    /**
     * Sets whether the node is active
     */
    void SetActive(bool active);

    /**
     * Gets whether the node is active
     */
    bool GetActive();

protected:
    bool active_;
};

#endif

