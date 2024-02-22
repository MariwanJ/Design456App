#include "fr_enttScene.h"
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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//


//#include<fr_components.h>
//#include<fr_transform.h>
//#include<fr_item.h>
//#include <glm/gtc/matrix_transform.hpp>
//#include<fr_grid.h>
//#include<fr_axis3D.h>
//#include<fr_node.h>
#include<fr_primativeShader.h>
#include<fr_components.h>
#include <fr_enttScene.h>
#include<Fr_GL3Window.h>

namespace FR {
 
    void Fr_enttScene::Render(FR::Node::RenderInfo& info, const glm::mat4& modelview) {

    }
    void Fr_enttScene::RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
        auto view = m_Registry.view<Fr_PrimaitiveShader, ItemName>();
        for (auto it : view) {
            auto [primative, name] = view.get<Fr_PrimaitiveShader, ItemName>(it);
            if (name.m_Name.compare("Grid")) {
                primative.Render(info,modelview);
            }
            if (name.m_Name.compare("Axis3D_Red")) {
                primative.Render(info, modelview);
            }
            if (name.m_Name.compare("Axis3D_Green")) {
                primative.Render(info, modelview);
            }
            if (name.m_Name.compare("Axis3D_Blue")) {
                primative.Render(info, modelview);
            }
            if (name.m_Name.compare("Axis3D_ZBlue")) {
                primative.Render(info, modelview);
            }
        }
    }
    void Fr_enttScene::RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview) {

    }
    void Fr_enttScene::RenderSilhouette(const glm::mat4& mvp) {

    }
  
    void Fr_enttScene::RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
        userData_ data;
        //Render GLFW stuff or Our 3D drawing
        linkToglfw->renderimGUI(data);
    }

}