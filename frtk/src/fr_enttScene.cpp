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
#include<fr_item.h>
#include <glm/gtc/matrix_transform.hpp>
#include<fr_grid.h>
#include<fr_axis3D.h>
#include<fr_node.h>
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

    Fr_Item Fr_enttScene::createItemWithID(genID id, const std::string& name)
    {
        Fr_Item  newItem = { m_Registry.create(), this };
        newItem.addItem<moudleID>(id);
        newItem.addItem<Transform>();
        auto& tag = newItem.addItem<moudleName>();
        tag.m_Name = name.empty() ? "Item" : name;
        m_ItemMap[id] = newItem;
        return newItem;
    }

    Fr_Item Fr_enttScene::createItem(const std::string& name)
    {
        return createItemWithID(genID(), name);
    }

    Fr_enttScene::Fr_enttScene(entt::entity ID, Fr_enttScene* scene)
    {
    }

    void Fr_enttScene::removeItem(Fr_Item ItemVal)
    {
    }

    Fr_Item Fr_enttScene::findItemByName(std::string_view name)
    {
        auto view = m_Registry.view<moudleName>();
        for (auto Item : view)
        {
            const moudleName& tc = view.get<moudleName>(Item);
            if (tc.m_Name == name)
                return Fr_Item{ Item, this };
        }
        return {};
    }

    Fr_Item Fr_enttScene::getItemByUUID(genID id)
    {
        if (m_ItemMap.find(id) != m_ItemMap.end())
            return { m_ItemMap.at(id), this };
        return {};
    }

    void Fr_enttScene::setBackgroud(float r, float g, float b, float alfa) {
        m_Background = glm::vec4(r, g, b, alfa);
    }

    void Fr_enttScene::setBackgroud(glm::vec4 color) {
        m_Background = color;
    }

    /**
     * Setup active camera by taking the name .
     * It will activate the camera and update the view matrix
     * \param name  Reference to a string which is the name of the camera Perspective,Orthographic, Top, Bottom, ..etc
     * \return a reference to the active camera
     */
    Fr_Item& Fr_enttScene::setupActiveCamera(std::string& name) {
        auto cameraGroup = m_Registry.group<moudleName, Camera>();
        for (auto ent : cameraGroup) {
            Fr_Item cameraItem = { ent,this };
            auto actCam = cameraItem.GetItem<Camera>();
            actCam.isActive(true);
            if (name.compare(cameraItem.GetName()) == 0) {
                actCam.isActive(true);
                actCam.updateViewMatrix(); //TODO FIXME: TRANFORM MUST BE UPDATED ALSO.
                return cameraItem;
            }
            else {
                actCam.isActive(false);
            }
        }
    }
    Fr_Item& Fr_enttScene::setupActiveCamera(CameraList  val)
    {
        std::string CamName = camNames[int(val)];
        return setupActiveCamera(CamName);
    }

    void Fr_enttScene::CreateDefaultCameras(void)
    {
        for (int i = 0; i < TOTAL_CAMS; i++) {
            std::string st = camNames[i];
            auto camMod = createItem(st);
            auto newCam = camMod.addItem<Camera>();
            newCam.setType(CameraList(i));
            auto trans = camMod.GetItem<Transform>();
            newCam.setLinkToMatrix(trans.GetMatrixPointer());
        }
    }

    void Fr_enttScene::CreateDefaultSunLight(void)
    {   //TODO : how many sun we should have???
        auto sunMod = createItem("Sun");
        auto sun = sunMod.addItem<Light>();
        sun.SetPosition(0.0f, 0.0f, 1000.0f);
        sun.SetDiffuse(0.25f, 0.25f, 0.25f);
        sun.SetAmbient(0.2f, 0.2f, 0.2f);
        sun.EnableShadowMap(glm::vec3(0, 0, 1), glm::vec3(0, 0, 4), glm::ortho<float>(-10, 10, -10, 10, 100, 114));
        sun.SetActive(true);
    }

    void Fr_enttScene::CreateGrid() {
        auto sunMod = createItem("Grid");
        auto sun = sunMod.addItem<Grid>();
    }
    void Fr_enttScene::CreateAxis() {
        auto sunMod = createItem("Axis3D");
        auto sun = sunMod.addItem<Axis3D>();
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

        //Camera
        Node::RenderInfo render_info;
        auto cam = setupActiveCamera(active_camera_);
        auto actCam = cam.GetItem<Camera>();
        render_info.modelview = actCam.GetViewMatrix();
        auto trans = cam.GetItem<Transform>();
        auto tranform = trans.GetMatrix();
        if (!SetupCamera(render_info.projection, render_info.modelview))
            throw std::runtime_error("Scene::Render(): Camera not found");
        //Light
        std::string_view str = "Sun";
        Fr_Item sun_item = findItemByName(str);
        auto sun =sun_item.GetItem<Light>();
        sun.SetupLight(render_info.modelview, render_info.lights);
        
        int draw_framebuffer = 0;
        glCheckFunc(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer));
        glCheckFunc(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


        render_info.id = 0;
        render_info.render_transparent = false;


        Render(render_info, render_info.modelview);
        render_info.id = 0;
        render_info.render_transparent = true;
        Render(render_info, render_info.modelview);

        RenderIMGui();
        RenderPrimativeShapes();
        RenderWidgetToolkit();
    }
}