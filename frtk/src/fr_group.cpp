//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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

#include <fr_group.h>
namespace FR {
    Group::Group()
    {
        type(NODETYPE::FR_GROUP);
    }

    Group::~Group() {
    }

    void Group::AddNode(std::shared_ptr<Node> node) {
        nodes_.push_back(node);
    }

    bool Group::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
        if (active_)
            for (auto& node : nodes_)
                //If the node is not subclassed and it is only a node, this will always return false.
                if (node->SetupCamera(projection, modelview))
                    return true;
        return false;
    }

    void Group::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) {
        if (active_)
            for (auto& node : nodes_)
                node->SetupLight(modelview, lights);
    }

    void Group::Render(RenderInfo& info, const glm::mat4& modelview) {
        if (active_)
            for (auto& node : nodes_)
                node->Render(info, modelview);
    }

    std::shared_ptr<Node> Group::getNode(int id)
    {
        if (nodes_.size() > 0)
            return nodes_[id];
        else
            return nullptr;
    }

    std::vector<std::shared_ptr<Node>> Group::getNodes()
    {
        //We don't care if nodes doesn't contain any children. Developer must know to deal with that.
        return nodes_;
    }
}