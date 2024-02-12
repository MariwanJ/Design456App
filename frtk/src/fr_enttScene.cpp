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

#include <fr_enttScene.h>
#include<fr_components.h>
#include<fr_transform.h>
#include<fr_module.h>

GLFWwindow* FR::Fr_enttScene::linkToglfw = nullptr;

namespace FR {
    
    Fr_enttScene::Fr_enttScene() {
        
    }
    Fr_enttScene::~Fr_enttScene()
    {
    }

    Fr_enttScene::Fr_enttScene(entt::entity ID, Fr_enttScene* scene)
    {
    }

    Fr_Module Fr_enttScene::createModule(const std::string& name)
    {
        return createModuleWithID(genID(), name);
    }


    void Fr_enttScene::removeModule(Fr_Module moduleVal)
    {
    }

    Fr_Module Fr_enttScene::findModuleByName(std::string_view name)
    {
        return Fr_Module();
    }

    Fr_Module Fr_enttScene::getModuleByUUID(UUID uuid)
    {
        return Fr_Module();
    }
 
    Fr_Module Fr_enttScene::createModuleWithID(genID id, const std::string& name)
    {
        Fr_Module  newModule = { m_Registry.create(), this };
        newModule.addModule<moudleID>(id);
        newModule.addModule<Transform>();
        auto& tag = newModule.addModule<moudleName>();
        tag.m_Name = name.empty() ? "Module" : name;
        m_ModuleMap[id] = newModule;
        return newModule;
    }
    void Fr_enttScene::setBackgroud(float r, float g, float b, float alfa) {
        m_Background = glm::vec4(r, g, b, alfa);
    }

    void Fr_enttScene::setBackgroud(glm::vec4 color) {
        m_Background = color;
    }
    void Fr_enttScene::setupActiveCamera(std::string name) {
        auto cameras=m_Registry.view<Transform, Camera>();
        for (auto ent : cameras) {
            const moudleName& nm = ent.get<moudleName>(ent);

            }
        }
    }
    void Fr_enttScene::defaultCameras(void)
    {
         
    }

    void Fr_enttScene::defaultSunLight(void)
    {
    }


    void Fr_enttScene::RenderScene() {
        glCheckFunc(glEnable(GL_DEPTH_TEST));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        glCheckFunc(glEnable(GL_BLEND));
        glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    }
    void Fr_enttScene::setupScene() {
        //Add all cameras
    
         // Entity
         //. |
         //  ___Transform
         //  ---Tag - name
         //  ---Camera instance
         //
        //TODO: Dose it make sence to create 8 cameras, or you should just keep the configurations? 
        //Note: I cannot create a group to keep track of these cameras. I will wait with that.
        for (int i = 0; i< 8; i++) {
            Fr_Module  newModule = { m_Registry.create(), this };//Entity
            newModule=createModuleWithID(genID(), camNames[i]);
            newModule.addModule<Camera>();
        }
    }
}
