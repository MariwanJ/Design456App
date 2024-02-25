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
#include<Fr_GL3Window.h>


namespace FR {
    
    

    Fr_enttScene::Fr_enttScene() :active_camera_((CameraList)4){
        //Add all cameras
        CreateDefaultSunLight();
        CreateAxis();
        //CreateGrid();
        CreateDefaultCameras();
        
    }
    Fr_enttScene::~Fr_enttScene()
    {
    }

    Fr_Item Fr_enttScene::createItemWithID(genID id, const std::string& name)
    {
        Fr_Item  newItem = { m_Registry.create(), this };
        newItem.addItem<ItemID>(id);
        newItem.addItem<Transform>();
        auto& tag = newItem.addItem<ItemName>();
        tag.m_Name = name.empty() ? "Item" : name;
        m_ItemMap[id] = newItem;
        return newItem;
    }

    Fr_Item Fr_enttScene::createItem(const std::string& name)
    {
        return createItemWithID(genID(), name);
    }

    void Fr_enttScene::removeItem(Fr_Item ItemVal)
    {
    }

    Fr_Item Fr_enttScene::findItemByName(std::string_view name)
    {
        auto view = m_Registry.view<ItemName>();
        for (auto Item : view)
        {
            const ItemName& tc = view.get<ItemName>(Item);
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
        auto cameraGroup = m_Registry.group<ItemName, Camera>();
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
            cameraList.push_back(std::make_shared<Camera>(newCam)); //TODO : Do we need the vector as this was used before??? !!!
            newCam.setType(CameraList(i));
            auto trans = camMod.GetItem<Transform>();
            newCam.setupCameraHomeValues();
            trans.SetMatrix(newCam.GetViewMatrix());
            switch (i) {
                //TODO: FIXME: If you create more than 6, you should add it here
            case 0: {
                /*Normal view PERSPECTIVE, HOME
                        position 17.463835 -17.463825 13.463827\n
                        orientation 0.74290609 0.30772209 0.59447283  1.2171158\n
                        nearDistance 0.42925534\n
                        farDistance 1761.75\n
                        aspectRatio 1\n
                        focalDistance 30.248238\n
                        heightAngle 0.78539819\n\n}\n'
                */
                trans.Rotate(glm::vec3(0.7429f, 0.307f, 0.594f), -69.7f);
            }break;
            case 1: {
                //ORTHOGRAPHIC

                trans.Rotate(glm::vec3(0.74290609f, 0.30772209f, 0.59447283f), 69.7f);
            }break;
            case 2: {
                /*TOP
                 position 15.337841 10.960548 102.60384\n
                 orientation 0 0 1  0\n
                 nearDistance 102.50124\n
                 farDistance 102.70644\n
                 aspectRatio 1\n
                 focalDistance 100\n
                 height 44.932899\n\n}\n'
                */
                trans.Rotate(glm::vec3(0.0f, 0.0, 1.0f), 0);
            }break;
            case 3: {
                /*Bottom
                 position 10.531155 7.5401545 -97.396126\n
                 orientation -0.99999994 1.4210855e-014 9.4830476e-008  3.1415935\n
                 nearDistance 97.298668\n
                 farDistance 97.493576\n
                 aspectRatio 1\n
                 focalDistance 100\n
                 height 44.932903\n\n}\n'
                */
                trans.Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 180);
            }break;
            case 4: {
                /**
                 *  FRONT
                  position 28.817665 -89.039444 2.6038942\n
                  orientation -1 4.214686e-007 8.4293717e-008  4.7123895\n
                  nearDistance 34.005363\n
                  farDistance 144.1835\n
                  aspectRatio 1\n
                  focalDistance 100\n
                  height 44.932899\n\n}\n'
                         *
                 */
                trans.Rotate(glm::vec3(-1.0f, 0, 0), 270.0f);
            }break;
            case 5: {
                /*REAR
                    position 15.337867 110.96054 2.6038241\n
                    orientation 1.4901161e-008 - 0.70710683 - 0.70710671  3.141593\n
                    nearDistance 55.904575\n
                    farDistance 166.1265\n
                    aspectRatio 1\n
                    focalDistance 100\n
                    height 44.932899\n\n}\n'
                    */
                trans.Rotate(glm::vec3(0.f, -0.70710683, -0.70710671f), 270.0f);
            }break;
            case 6: {
                /*
                RIGHT
                    position 115.33784 10.960509 2.6038659\n
                    orientation - 0.57735032 - 0.57735026 - 0.5773502  4.1887908\n
                    nearDistance 60.277466\n
                    farDistance 170.50819\n
                    aspectRatio 1\n
                    focalDistance 100\n
                    height 44.932899\n\n
                    */
                trans.Rotate(glm::vec3(-0.577f, -0.577f, -0.577f), 240.f);
            }break;

            case 7: {
                /*LEFT
                    position - 71.182274 10.960546 2.6038406\n
                    orientation 0.57735014 - 0.5773505 - 0.5773502  2.0943947\n
                    nearDistance 16.166088\n
                    farDistance 126.30847\n
                    aspectRatio 1\n
                    focalDistance 100\n
                    height 44.932899\n\n}\n'
                    */
                trans.Rotate(glm::vec3(0.57f, -0.57f, -0.57f), 270.0f);
            }break;
            }
        }
    }

    void Fr_enttScene::CreateDefaultSunLight(void)
    {   //TODO : how many sun we should have???
        auto sunItem = createItem("Sun");
        auto sun = sunItem.addItem<Light>();
        sun.SetPosition(0.0f, 0.0f, 1000.0f);
        sun.SetDiffuse(0.25f, 0.25f, 0.25f);
        sun.SetAmbient(0.2f, 0.2f, 0.2f);
        sun.EnableShadowMap(glm::vec3(0, 0, 1), glm::vec3(0, 0, 4), glm::ortho<float>(-10, 10, -10, 10, 100, 114));
        sun.SetActive(true);
    }

    void Fr_enttScene::CreateGrid() {
        auto gridsItem = createItem("Grid");
        auto gr= gridsItem.addItem<Fr_Grid>();
        gr.CreateGrid();
        
    }

    void Fr_enttScene::CreateAxis() {
        auto axisItems = createItem("Axis3D_axis");
        auto allAxis = axisItems.addItem<Axis3D>();
        allAxis.CreateAxis3D();
    }

    void Fr_enttScene::setupScene() {
    }

    /**
     * Scene Render  .
     * This should render everything we have inside the scene.
     *
     */
    void Fr_enttScene::RenderScene() {
        float wWidth = (float)ImGui::GetWindowWidth();
        float wHeight = (float)ImGui::GetWindowHeight();
        linkToglfw->sceneBuffer->RescaleFrameBuffer(wWidth, wHeight);
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
        render_info.modelview = render_info.modelview * trans.GetMatrix();
        render_info.projection = actCam.getPorjection();

        //Light
        std::string_view str = "Sun";
        Fr_Item sun_item = findItemByName(str);
        auto sun = sun_item.GetItem<Light>();
        sun.SetupLight(render_info.modelview, render_info.lights);
        int draw_framebuffer = 0;
        glCheckFunc(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer));
        glCheckFunc(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        // Render all object here
        render_info.id = 0;
        render_info.render_transparent = false;

        linkToglfw->sceneBuffer->Bind();
        Render(render_info, render_info.modelview);
        RenderPrimativeShapes(render_info, render_info.modelview);
        RenderWidgetToolkit(render_info, render_info.modelview);

        //Render transparent items
        render_info.id = 0;
        render_info.render_transparent = true;
        Render(render_info, render_info.modelview);
        
    }



}