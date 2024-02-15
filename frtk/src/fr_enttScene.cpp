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
#include <glm/gtc/matrix_transform.hpp>
#include<fr_grid.h>
#include<fr_axis3D.h>
GLFWwindow* FR::Fr_enttScene::linkToglfw = nullptr;

namespace FR {
    Fr_enttScene::Fr_enttScene() {
        //Add all cameras
        CreateDefaultSunLight();
        CreateDefaultCameras();
        CreateGrid();
    }
    Fr_enttScene::~Fr_enttScene()
    {
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

    Fr_Module Fr_enttScene::createModule(const std::string& name)
    {
        return createModuleWithID(genID(), name);
    }

    Fr_enttScene::Fr_enttScene(entt::entity ID, Fr_enttScene* scene)
    {
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

   
    void Fr_enttScene::setBackgroud(float r, float g, float b, float alfa) {
        m_Background = glm::vec4(r, g, b, alfa);
    }

    void Fr_enttScene::setBackgroud(glm::vec4 color) {
        m_Background = color;
    }

    void Fr_enttScene::setupActiveCamera(std::string& name) {
        auto cameraGroup = m_Registry.group<moudleName, Camera>();
        for (auto ent : cameraGroup) {
            Fr_Module cameraModule = { ent,this };
            auto actCam = cameraModule.GetModule<Camera>();
            actCam.isActive(true);
            if (name.compare(cameraModule.GetName()) == 0) {
                actCam.isActive(true);
                actCam.updateViewMatrix(); //TODO FIXME: TRANFORM MUST BE UPDATED ALSO.
            }
            else {
                actCam.isActive(false);
            }
        }
    }
    void Fr_enttScene::setupActiveCamera(CameraList  val)
    {
        std::string CamName = camNames[int(val)];
        setupActiveCamera(CamName);
    }

    void Fr_enttScene::CreateDefaultCameras(void)
    {
        for (int i = 0; i < TOTAL_CAMS; i++){
            std::string st = camNames[i];
            auto camMod = createModule(st);
            auto newCam=camMod.addModule<Camera>();
            newCam.setType(CameraList(i));
            newCam.setupCameraHomeValues();
        }
    }

    void Fr_enttScene::CreateDefaultSunLight(void)
    {   //TODO : how many sun we should have??? 
        auto sunMod = createModule("Sun");
        auto sun=sunMod.addModule<Light>();
        sun.SetPosition(0.0f, 0.0f, 1000.0f);
        sun.SetDiffuse(0.25f, 0.25f, 0.25f);
        sun.SetAmbient(0.2f, 0.2f, 0.2f);
        sun.EnableShadowMap(glm::vec3(0, 0, 1), glm::vec3(0, 0, 4), glm::ortho<float>(-10, 10, -10, 10, 100, 114));
        sun.SetActive(true);
    }


    void Fr_enttScene::CreateGrid() {
        auto sunMod = createModule("Grid");
        auto sun = sunMod.addModule<Grid>();
    }
    void Fr_enttScene::CreateAxis() {
        auto sunMod = createModule("Axis3D");
        auto sun = sunMod.addModule<Axis3D>();
    }

    void Fr_enttScene::setupScene() {

    }

    /**
     * Scene Render  .
     * This should render everything we have inside the scene. 
     * 
     */
    void Fr_enttScene::RenderScene() {
        glCheckFunc(glEnable(GL_DEPTH_TEST));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        glCheckFunc(glEnable(GL_BLEND));
        glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }
}