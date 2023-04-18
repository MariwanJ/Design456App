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

#include <fr_group.h>
unsigned int Group::lastAddedNodeID = 0;//Keep the last node number

#include <Fr_GL3Window.h>

Group::Group()
{
    type(NODETYPE::FR_GROUP);
}

Group::~Group() {
}

nodes* Group::InsertNode(nodes* root, nodes* newNode) {
    if (root == nullptr) {
        //We have no items in the tree
        return newNode;
    }
    if (root->data->NodeID() > newNode->data->NodeID()) {
        root->right = InsertNode(root->right, newNode);
        root->right->parent = newNode;
        return root; //return higher value nodes
    }
    else if (root->data->NodeID() < newNode->data->NodeID()) {
        root->left = InsertNode(root->left, newNode);
        root->left->parent = root;
        return root; //return the same node
    }
    else {
        //This shouldn't happen, but we don't allow mistkes
        //Update the current id         nd->data->NodeID==id
        Fr_Log::GetFRTKLogger()->warn("Warning!: Node already exists, update it");
        if(root!=nullptr)
            root->data = newNode->data;
        return root;
    }
}
void Group::AddNode(std::shared_ptr<Node> node) {

    nodes* root_ = Fr_GL3Window::getfr_Gl3Window()->getRoot();
    nodes* item = new nodes();
    item->data = node;
    item->data->setNodeID(lastAddedNodeID++);
    item->left = nullptr;
    item->right = nullptr;
    item->parent = nullptr;
    root_ = InsertNode(root_, item);
    Fr_GL3Window::getfr_Gl3Window()->setRoot(root_);
    lastAddedNodeID++;
}

nodes* Group::deleteNode(nodes* root_, nodes* nd)
{
    if (nd == nullptr) {
        return nullptr; //nothing to delete
    }

    if (nd->data->NodeID() < root_->data->NodeID()) {
        root_->left = deleteNode(root_->left, nd);
    }
    else
        if (nd->data->NodeID() > root_->data->NodeID()) {
            root_->right = deleteNode(root_->right, nd);
        }
        else {
            //root->data->NodeID()==nd->data->NordID()
            if (root_->right == nullptr) {
                root_->left->parent = nd->parent;
                return root_->left;
            }

            if (root_->left == nullptr) {
                root_->right->parent = nd->parent;
                return root_->right;
            }
            auto temp = root_->right;
            while (temp->left != nullptr)
                temp = temp->left;
            root_->data = temp->data;
            root_->right = deleteNode(root_->right, temp);
            return root_;
        }
}

bool Group::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    int ww = 0;
    if (active_) {
        nodes* nd = getFirst();
        if (nd == nullptr)
            return false;//Nothing to do- just in case
        while (nd != nullptr) {
            //If the node is not subclassed and it is only a node, this will always return false.
            if (nd->data->SetupCamera(projection, modelview))
                return true;
            nd = getNext(nd);
        }
        return false;
    }
}

void Group::SetupLight(const glm::mat4& modelview,
    std::vector<LightInfo>& lights) {
    if (active_) {
        nodes* nd = getFirst();
        if (nd == nullptr)
            return;//Nothing to do - just in case
        while (nd != nullptr) {
            nd->data->SetupLight(modelview, lights);
            nd = getNext(nd);
        }
    }
}

bool Group::SetupShadowMap(ShadowMapInfo& info) {
    if (active_) {
        nodes* nd = getFirst();
        if (nd == nullptr)
            return false;//Nothing to do - just in case
        while (nd != nullptr) {
            if (nd->data->SetupShadowMap(info))
                return true;
            nd = getNext(nd);
        }
        return false;
    }
}

void Group::RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) {
    if (active_) {
        nodes* nd = getFirst();
        if (nd == nullptr)
            return;//Nothing to render - just in case
        while (nd != nullptr) {
            nd->data->RenderShadowMap(info, modelview);
            nd = getNext(nd);
        }
    }
}

void Group::Render(RenderInfo& info, const glm::mat4& modelview) {
    if (active_) {
        nodes* nd = getFirst();
        if (nd == nullptr)
            return;//Nothing to render - just in case
        while (nd != nullptr) {
            nd->data->Render(info, modelview);
            nd = getNext(nd);
        }
    }
}
/**
 * Find the node that has the given id.
 *
 * \param nd : Node class object that have the required id
 * \param id  : id of the node that is required
 * \return  a Node class object that has that id
 */
std::shared_ptr<Node> Group::getNodeRecursive(nodes* nd, unsigned int id) {
    std::shared_ptr<Node> result = nullptr;
    if (nd == nullptr)
        return nullptr;
    if (nd->data == nullptr) {
        return nullptr;
    }
    if(nd->data->NodeID() == id) {
        //end of the tree-branch
        return (nd->data);
    }
    auto right = getNodeRecursive(nd->right, id);
    if (right != nullptr) {
        return right;
    }
    auto left = getNodeRecursive(nd->left, id);
    if (left != nullptr)
        return left;
    return nullptr;
}
/**
 *
 * Find nodes struct represengint the node ID needed.
 *
 * \param nd : root node - searching start
 * \param id : ID of the node that is required
 * \return  : return the nodes struct object having the id
 */
nodes* Group::FINDnodesRecursive(nodes* nd, unsigned int id) {
    std::shared_ptr<Node> result = nullptr;
    if (nd == nullptr || nd->data->NodeID() == id) {
        //end of the tree-branch
        return nd;
    }
    auto right = FINDnodesRecursive(nd->right, id);
    if (right != nullptr) {
        return right;
    }
    auto left = FINDnodesRecursive(nd->left, id);
    if (left != nullptr)
        return left;
    return nullptr;
}
/**
 * Find the lowest value.
 *
 * \return found node or nullpntr
 */
nodes* Group::getFirst()
{
    nodes * root_ = Fr_GL3Window::getfr_Gl3Window()->getRoot();
    if (root_ == nullptr)
        return nullptr;
    else
        //This could be a nullptr be aware
        return getLeftMost(root_);
}

nodes* Group::getNext(nodes* nd)
{

    if (nd->right != nullptr)
    {
        return getLeftMost(nd->right);
    }
    else{
        while (nd->parent != nullptr && nd == nd->parent->right)
            nd = nd->parent;
        return nd->parent;
    }
  }
/**
 * Find the lowest node in the tree.
 *
 * \param nd: start node
 * \return found node or nullptr
 */
nodes* Group::getLeftMost(nodes* nd)
{
    if (nd == nullptr)
        return nullptr;
    while (nd->left != nullptr)
        nd = nd->left;
    return nd;
}

std::shared_ptr<Node> Group::getNode(unsigned int id)
{
    nodes* root_ = Fr_GL3Window::getfr_Gl3Window()->getRoot();
    if (root_->data == nullptr)
        return nullptr;
    getNodeRecursive(root_, id);
}

nodes* Group::getNodes()
{
    //We don't care if nodes doesn't contain any children. Developer must know to deal with that.
    nodes* root_ = Fr_GL3Window::getfr_Gl3Window()->getRoot();
    return root_;
}