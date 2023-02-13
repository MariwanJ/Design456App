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

#ifndef GROUP_H
#define GROUP_H

#include<frtk.h>
#include<Fr_Core.h>
#include <Node.h>

/**
 * A container for other nodes
 */
class Group : public Node {
public:
    /**
     * Virtual destructor
     */
    ~Group();

    /**
     * Adds a node to the group
     */
    void AddNode(std::shared_ptr<Node> node);

    /**
     * Retrive a pointer to the desired Node given by id number.
     * 
     * \param id    Node number
     * \return pointer to the node if exists. or nullpntr
     */
    std::shared_ptr<Node> getNode(int id);

    /**
     * Return a pointer to the vector nodes (all of them).
     * 
     * \return pointer to the vector nodes even if there is no children (which will be an empty vector
     */
    std::vector<std::shared_ptr<Node>> getNodes();
    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview) override;

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    virtual void SetupLight(const glm::mat4& modelview,  std::vector<LightInfo>& lights) override;

    /**
     * Sets the shadow map
     */
    virtual bool SetupShadowMap(ShadowMapInfo& info) override;

    /**
     * Renders the shadow map
     */
    virtual void RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) override;

    /**
     * Renders the node
     */
    virtual void Render(RenderInfo& info, const glm::mat4& modelview) override;

private:
    /** Group's children */
    std::vector<std::shared_ptr<Node>> nodes_;
};

#endif

