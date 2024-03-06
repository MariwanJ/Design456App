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
//  Inspired by Hazel engine
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <fr_enttScene.h>
#include<fr_components.h>
#include<fr_transform.h>
#include <glm/gtc/matrix_transform.hpp>
#include<fr_grid.h>
#include<fr_axis3D.h>
#include<fr_node.h>
#include<Fr_GL3Window.h>

namespace FR {
    Fr_enttScene::Fr_enttScene() :active_camera_((CameraList)0) {
    }
    Fr_enttScene::~Fr_enttScene()
    {
    }
    template <typename T, typename... Args>
    SceneItemStruct<T> Fr_enttScene::createItem(std::string&& name, Args&&... args) {
        SceneItemStruct<T> newItem;
        newItem.name = std::move(name);
        newItem.Sceneitem = std::make_shared<T>(std::forward<Args>(args)...); // Initialize the shared_ptr with a new instance
        m_world.push_back(SceneItemStruct<T>(newItem)); //add to the world
        return newItem;
    }
    template <typename T>
    SceneItemStruct<typename std::remove_reference<T>::type>& Fr_enttScene::findItemByName(std::string_view name) {
        for (int i=0;i<m_world.size();i++){
        //for (auto& item : m_world) {
            if (m_world[i].name == name) {
                return (std::remove_reference<T>::type)m_world[i];
            }
        }

        // If the item is not found, you can create a default SceneItemStruct<T> or throw an exception based on your requirements.
        // Here, a default-constructed object is created for demonstration purposes.
        static SceneItemStruct<typename std::remove_reference<T>::type> resultEntity;
        return resultEntity;
     }

    template <typename T>
    SceneItemStruct<T> &Fr_enttScene::findItemByID(genID id)
    {
        SceneItemStruct<T> resultEntity;
        // Iterate over the scene items
        for (const auto& item : sceneItems) { // Assuming sceneItems is a container holding SceneItemStruct<T> objects
            if (item.id == id) { // Check if the name matches
                return const_cast<SceneItemStruct<T>&>(item);
            }
        }
        return resultEntity;
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
    SceneItemStruct<Camera> Fr_enttScene::setupActiveCamera(std::string_view name, Node::RenderInfo& info) {
        SceneItemStruct<Camera> sceneItem = findItemByName<Camera>(name);
        if (sceneItem.name == name) {
            sceneItem.Sceneitem->isActive(true);
            for (unsigned int i = 0; i < sizeof(camNames); i++) {
                if (name == camNames[i])
                    active_camera_ = (CameraList)i;
            }
            sceneItem.Sceneitem->SetupCamera(info.projection);
            sceneItem.trans.SetMatrix(sceneItem.Sceneitem->GetViewMatrix() * sceneItem.trans.GetInverse());
        }
        return sceneItem;
    }

    SceneItemStruct<Camera> Fr_enttScene::setupActiveCamera(CameraList  val, Node::RenderInfo& info)
    {
        std::string CamName = camNames[int(val)];
        return setupActiveCamera(CamName, info);
    }

    void Fr_enttScene::CreateDefaultCameras(void)
    {
        for (int i = 0; i < TOTAL_CAMS; i++) {
            std::string st = camNames[i];
            SceneItemStruct<Camera> camMods = createItem<Camera>(std::move(st));
            camMods.Sceneitem->setType(CameraList(i));
            camMods.Sceneitem->setupCameraHomeValues();
            //camMods.trans.SetMatrix(camMods.Sceneitem->GetViewMatrix());
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
                camMods.trans.Rotate(glm::vec3(0.7429f, 0.307f, 0.594f), -69.7f);
            }break;
            case 1: {
                //ORTHOGRAPHIC

                camMods.trans.Rotate(glm::vec3(0.74290609f, 0.30772209f, 0.59447283f), 69.7f);
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
                camMods.trans.Rotate(glm::vec3(0.0f, 0.0, 1.0f), 0);
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
                camMods.trans.Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 180);
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
                camMods.trans.Rotate(glm::vec3(-1.0f, 0, 0), 270.0f);
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
                camMods.trans.Rotate(glm::vec3(0.f, -0.70710683, -0.70710671f), 270.0f);
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
                camMods.trans.Rotate(glm::vec3(-0.577f, -0.577f, -0.577f), 240.f);
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
                camMods.trans.Rotate(glm::vec3(0.57f, -0.57f, -0.57f), 270.0f);
            }break;
            }
        }
    }

    SceneItemStruct<Light> Fr_enttScene::CreateDefaultSunLight(void)
    {   //TODO : how many sun we should have???
        SceneItemStruct<Light> sunItem = createItem<Light>(std::move("Sun"));
        sunItem.Sceneitem->SetPosition(0.0f, 0.0f, 1000.0f);
        sunItem.Sceneitem->SetDiffuse(0.25f, 0.25f, 0.25f);
        sunItem.Sceneitem->SetAmbient(0.2f, 0.2f, 0.2f);
        sunItem.Sceneitem->EnableShadowMap(glm::vec3(0, 0, 1), glm::vec3(0, 0, 4), glm::ortho<float>(-10, 10, -10, 10, 100, 114));
        sunItem.Sceneitem->SetActive(true);
        return sunItem;
    }

    SceneItemStruct<Fr_Grid> Fr_enttScene::CreateGrid() {
        SceneItemStruct<Fr_Grid> gridsItem = createItem<Fr_Grid>(std::move("Grid")); ;
        gridsItem.Sceneitem->CreateGrid();
        return gridsItem;
    }

    SceneItemStruct<Axis3D> Fr_enttScene::CreateAxis() {
        SceneItemStruct<Axis3D> allAxis = createItem<Axis3D>(std::move("Axis3D_axis"));
        allAxis.Sceneitem->CreateAxis3D();
        return allAxis;
    }

    void Fr_enttScene::setupScene() {
        //Add all cameras
        //auto t= addTest();
        //auto f = t.get_mut<test>(); // Now this should work
        //f->printme();

        CreateDefaultSunLight();
        CreateDefaultCameras();
        CreateAxis();
        CreateGrid();
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
        auto cam = setupActiveCamera(active_camera_, render_info);
        render_info.modelview = cam.Sceneitem->GetViewMatrix();

        //render_info.modelview = render_info.modelview * cam.trans.GetMatrix();
        render_info.modelview = render_info.modelview;//temp code
        render_info.projection = cam.Sceneitem->getPorjection();

        //Light
        std::string_view str = "Sun";
        SceneItemStruct<Light> sunItem = findItemByName<Light>("Sun");
        sunItem.Sceneitem->SetupLight(render_info.modelview, render_info.lights);
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

    // Replace a SceneItemStruct with a new one based on its unique identifier
    template<typename T, typename ...Args>
    bool Fr_enttScene::replaceItemByID(int id, const T& newItem, Args && ...args)
    {
        auto it = std::find_if(m_World.begin(), m_World.end(),
            [id](const SceneItemStruct<T>& obj) { return obj.id == id; });

        if (it != m_World.end()) {
            it->SceneObj = std::make_shared<T>(newItem);
            return true;
        }
        return false;
    }

    // Delete a SceneItemStruct by its unique identifier
    bool Fr_enttScene::deleteItemByID(int id) {
        auto it = std::remove_if(m_world.begin(), m_world.end(),
            [id](const SceneItemStruct<T>& obj) { return obj.id == id; });

        if (it != m_world.end()) {
            m_world.erase(it, m_world.end());
            return true;
        }

        return false;
    }

    // Replace a SceneItemStruct with a new one based on its name
    bool Fr_enttScene::replaceItemByName(const std::string& name, const T& newItem) {
        auto it = std::find_if(m_world.begin(), m_world.end(),
            [name](const SceneItemStruct<T>& obj) { return obj.name == name; });

        if (it != m_world.end()) {
            it->Sceneitem = std::make_shared<T>(newItem);
            return true;
        }
        return false;
    }

    // Get all SceneItemStruct instances
    const std::vector<SceneItemStruct<T>>& Fr_enttScene::getAllItems() const {
        return m_world;
    }
}