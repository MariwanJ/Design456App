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

namespace FR {



    Fr_enttScene::~Fr_enttScene()
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


    void Fr_enttScene::RenderScene() {

       
    }

}
