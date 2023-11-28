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

#ifndef FR_GROUP_H
#define FR_GROUP_H

#include<frtk.h>
#include<fr_core.h>
#include <fr_node.h>

/**
 * A container for other nodes
 */
class FRTK_API Group : public Node {
public:
    Group();
    /**
     * Virtual destructor
     */
    ~Group();

    /**
     * Adds a node to the group
     */
    void AddNode(std::shared_ptr<Node> node);
    void delNode(std::shared_ptr<Node> node);//add the object to the scene graph vector, return the index

    int getNodeIndex(std::shared_ptr<Node> node);//add the object to the scene graph vector, return the index
    /**
     * Retrive a pointer to the desired Node given by id number.
     *
     * \param id    Node number
     * \return pointer to the node if exists. or nullpntr
     */
    std::shared_ptr<Node> getNode(int id);

    virtual std::vector<std::shared_ptr<Node>> getNodes();
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
    virtual void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) override;

    /**
     * Renders the node
     */
    virtual void Render(RenderInfo& info, const glm::mat4& modelview) override;

protected:
    /** Group's children */
    std::vector<std::shared_ptr<Node>> nodes_;

private:
};

#endif