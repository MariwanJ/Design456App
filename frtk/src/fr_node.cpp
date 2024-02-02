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
#include <fr_node.h>
#include <Fr_GL3Window.h>

Node::Node() :type_(NODETYPE::FR_NODE), m_Parent(-1),
active_{ true}
{
 
}

Node::~Node() {
}

bool Node::SetupCamera(glm::mat4& projection, glm::mat4& modelview) {
    //Dummy code doese nothing should  be subclassed
    //(void)projection;
    //(void)modelview;
    return false;
}

void Node::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) {
    //Dummy code doese nothing should  be subclassed
   /*/ (void)modelview;
    (void)lights;*/
}

bool Node::SetupTexture2D( ) {
    //Dummy code does nothing should be subclassed
    /*(void)info;*/
    return false;
}

//void Node::RenderTexture2D() {
//    //Dummy code does nothing should be subclassed
//    /*(void)info;
//    (void)modelview;*/
//}
Fr_GL3Window *Node::m_parentGl3Win = 0;
void Node::Render(RenderInfo& info, const glm::mat4& modelview) {
    //Dummy code does nothing should be subclassed
    /*(void)info;
    (void)modelview;*/
}

void Node::SetActive(bool active) {
    active_ = active;
}

bool Node::GetActive() {
    return active_;
}

NODETYPE Node::type()
{
    return type_;
}

void Node::type(NODETYPE newVal)
{
    type_ = newVal;
}
int Node::Parent() {
    return m_Parent;
}

void Node::Parent(int index)
{
    m_Parent = index;
}

Fr_GL3Window* Node::ParentGL3Window(){
    return m_parentGl3Win;
}
void Node::setParentlink(Fr_GL3Window* p)
{
    m_parentGl3Win = p;
};