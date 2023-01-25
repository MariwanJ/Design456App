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
#ifndef TOONSHADERNODE_H
#define TOONSHADERNODE_H

#include <memory>

#include "Node.h"

class Mesh;
class ShaderProgram;

class ToonShaderNode : public Node {
public:
    /**
     * Constructor
     */
    ToonShaderNode(unsigned int color = 0x111111, float silhouette = 0.005);

    /**
     * Destructor
     */
    ~ToonShaderNode();

    /**
     * Sets the color
     */
    void SetColor(unsigned int color, float alpha = 1.0f);

    /**
     * Sets the opacity
     */
    void SetOpacity(float alpha);

    /**
     * Sets the mesh
     */
    void SetMesh(std::shared_ptr<Mesh> mesh);

    /**
     * Sets the mesh
     */
    void SetMesh(const std::string& mesh);

    /**
     * Renders the shadow map
     */
    void RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) override;

    /**
     * Renders the node
     */
    void Render(RenderInfo& info, const glm::mat4& modelview) override;

private:
    /**
     * Sets the uniform light data
     */
    void LoadLights(ShaderProgram *program, const std::vector<LightInfo>& lights);

    /**
     * Renders the silhouette
     */
    void RenderSilhouette(const glm::mat4& mvp);

    // Constants
    const size_t kMaxLights = 8;

    // Shared between instances
    struct Shared {
        ShaderProgram *toon_program;
        ShaderProgram *silhouette_program;
        ShaderProgram *shadowmap_program;
    };
    static Shared *shared_;

    // Attributes
    std::shared_ptr<Mesh> mesh_;
    glm::vec4 color_;
    float silhouette_;
};

#endif

