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

#include <fr_scene.h>
#include <Fr_GL3Window.h>
namespace FR {
    Fr_Scene::Fr_Scene() : active_camera_(CameraList(0)),
        background_{ 0.9, 0.9, 0.9,1.0 } {
        type(NODETYPE::FR_SCENE);

        glCheckFunc(glEnable(GL_DEPTH_TEST));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        glCheckFunc(glEnable(GL_BLEND));
        glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void Fr_Scene::SetBackgroud(float r, float g, float b) {
        background_.r = r;
        background_.g = g;
        background_.b = b;
        background_.a = 1.0;
    }
    void Fr_Scene::SetBackgroud(float r, float g, float b, float alfa) {
        background_.r = r;
        background_.g = g;
        background_.b = b;
        background_.a = alfa;
    }

    void Fr_Scene::add3DObject(std::string fName)
    {
        std::shared_ptr<ModelNode> newObj = std::make_shared<ModelNode>(); //  color and
        newObj->Translate(0, 0, 0);
        newObj->Scale(1, 1, 1);
        newObj->Rotate(0, 1, 0, 0); //TODO CHECK ME
        //texture
        newObj->m_Texture2D = std::make_shared<Fr_Texture2D>();
        //std::string imag = ("E:/Projects/Design456App/resources/Texture/test.png");
      //  std::string imag = ("E:/Projects/Design456App/resources/Texture/ts.png");
        //std::string imag = ("E:/Projects/Design456App/resources/Texture/2.png");
        //std::string imag = ("E:/Projects/Design456App/resources/Texture/3.png");
        //std::string imag = ("E:/Projects/Design456App/resources/Texture/default.png");

        //if (newObj->m_Texture2D->set2DTexture(imag))
        //{
        //        newObj->m_Texture2D->setup2DTexture();      //Don't forget to do this always
        //}else
        //    DEBUG_BREAK;
        newObj->m_Texture2D->setup2DTexture();      //Don't forget to do this always
        if (fName.find(".off") != std::string::npos) {
            newObj->SetMesh(std::make_shared<Shape>(fName));
        }
        else {
            //Not implemented yet  - here .obj should be treated.
        }
        auto rightlight_spot = std::make_shared<Light>();
        rightlight_spot->isActive(true);
        rightlight_spot->SetPosition(2.956f, -0.514f, 1.074f);
        rightlight_spot->SetupSpot(1.0f, 0.0f, -0.1f, 45.0f, 16.0f);
        rightlight_spot->SetDiffuse(0.0f, 0.0f, 0.0f);
        rightlight_spot->SetAmbient(0.42f, 0.42f, 0.42f);
        rightlight_spot->SetAttenuation(1.0f, 0.002f, 0.0f);
        newObj->AddNode(rightlight_spot);
        newObj->isActive(true);
        newObj->AddNode(newObj);

        SceneItemStruct newtT(newObj, fName);
        m_world.push_back(newtT);
    }

    void Fr_Scene::delete3DObject(SceneItemStruct& obj)
    {
        auto it = std::find(m_world.begin(), m_world.end(), obj);
        if (it != m_world.end()) {
            m_world.erase(it); // Erase the item if found
        }
        else {
            std::cout << "Item not found." << std::endl;
        }
    }

    void Fr_Scene::delete3DObject(std::shared_ptr<Node> obj)
    {
        auto it = std::find_if(m_world.begin(), m_world.end(), [&](const SceneItemStruct& item) {

            return item.Sceneitem==obj;
            });
        if (it != m_world.end()) {
            m_world.erase(it); // Erase the item if found
        }
        else {
            std::cout << "Item not found." << std::endl;
        }
    }
    

    void Fr_Scene::setBackgroud(float r, float g, float b, float alfa) {
        m_Background = glm::vec4(r, g, b, alfa);
    }

    void Fr_Scene::setBackgroud(glm::vec4 color) {
        m_Background = color;
    }

    /**
     * Setup active camera by taking the name .
     * It will activate the camera and update the view matrix
     * \param name  Reference to a string which is the name of the camera Perspective,Orthographic, Top, Bottom, ..etc
     * \return a reference to the active camera
     */
    std::shared_ptr<Camera> Fr_Scene::setupActiveCamera(std::string_view name, Node::RenderInfo& info) {
        std::shared_ptr<Camera> cam;
        findItemByName(cam, name);
        if (cam)
        {
            cam->isActive(true);
            cam->SetupCamera(info.projection, info.modelview);
        }
        return cam;
    }

    std::shared_ptr<Camera> Fr_Scene::setupActiveCamera(CameraList  val, Node::RenderInfo& info)
    {
        std::string CamName = camNames[int(val)];
        return setupActiveCamera(CamName, info);
    }

    void Fr_Scene::CreateDefaultCameras(void)
    {
        for (int i = 0; i < TOTAL_CAMS; i++) {         
            std::shared_ptr<Camera> nItem = std::make_shared<Camera>();
            nItem->setType(CameraList(i));
            nItem->type(NODETYPE::FR_CAMERA);
            nItem->setupCameraHomeValues();

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
                nItem->Rotate(glm::vec3(0.7429f, 0.307f, 0.594f), -69.7f);
            }break;
            case 1: {
                //ORTHOGRAPHIC

                nItem->Rotate(glm::vec3(0.74290609f, 0.30772209f, 0.59447283f), 69.7f);
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
                nItem->Rotate(glm::vec3(0.0f, 0.0, 1.0f), 0);
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
                nItem->Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 180);
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
                nItem->Rotate(glm::vec3(-1.0f, 0, 0), 270.0f);
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
                nItem->Rotate(glm::vec3(0.f, -0.70710683, -0.70710671f), 270.0f);
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
                nItem->Rotate(glm::vec3(-0.577f, -0.577f, -0.577f), 240.f);
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
                nItem->Rotate(glm::vec3(0.57f, -0.57f, -0.57f), 270.0f);
            }break;
            }

            SceneItemStruct camMods = SceneItemStruct(nItem, camNames[i]);
            m_world.push_back(camMods);
        }
    }

    SceneItemStruct Fr_Scene::CreateDefaultSunLight(void)
    {   //TODO : how many sun we should have???
        std::shared_ptr<Light> sun = std::shared_ptr<Light>(new Light);
        sun->SetPosition(0.0f, 0.0f, 1000.0f);
        sun->SetDiffuse(0.25f, 0.25f, 0.25f);
        sun->SetAmbient(0.2f, 0.2f, 0.2f);
        sun->EnableShadowMap(glm::vec3(0, 0, 1), glm::vec3(0, 0, 4), glm::ortho<float>(-10, 10, -10, 10, 100, 114));
        sun->isActive(true);
        SceneItemStruct sunItem(sun, "Sun");
        m_world.push_back(sunItem);
        return sunItem;
    }

    SceneItemStruct  Fr_Scene::CreateGrid() {
        auto gr = std::shared_ptr<Fr_Grid>(new Fr_Grid);
        SceneItemStruct gridsItem(gr, "Grid");
        gr->CreateGrid();
        m_world.push_back(gridsItem);
        return gridsItem;
    }

    SceneItemStruct  Fr_Scene::CreateAxis() {
        auto ax = std::shared_ptr<Fr_Axis3D>(new Fr_Axis3D);
        SceneItemStruct   allAxis(ax, "Axis3D"); 
        ax->CreateAxis3D();
        m_world.push_back(allAxis);
        return allAxis;
    }

    void Fr_Scene::setupScene() {
        //Add all cameras
        //auto t= addTest();
        //auto f = t.get_mut<test>(); // Now this should work
        //f->printme();
        CreateDefaultCameras();
        CreateDefaultSunLight();
        CreateAxis();
        CreateGrid();
    }

    /**
     * Scene Render  .
     * This should render everything we have inside the scene.
     *
     */

    void Fr_Scene::RenderScene() {
        float wWidth = (float)ImGui::GetWindowWidth();
        float wHeight = (float)ImGui::GetWindowHeight();
        Fr_GL3Window::getfr_Gl3Window()->sceneBuffer->RescaleFrameBuffer(wWidth, wHeight);
        glCheckFunc(glEnable(GL_DEPTH_TEST));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        glCheckFunc(glEnable(GL_BLEND));
        glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //Camera
        Node::RenderInfo render_info;
        auto cam = setupActiveCamera(active_camera_, render_info);
        render_info.modelview = cam->GetViewMatrix();

        //render_info.modelview = render_info.modelview * cam.trans.GetMatrix();
        render_info.modelview = render_info.modelview;//temp code
        render_info.projection = cam->getPorjection();

        //Light
        std::string_view str = "Sun";
        std::shared_ptr<Light> sunItem;
        findItemByName(sunItem, "Sun");
        if (sunItem)
            sunItem->SetupLight(render_info.modelview, render_info.lights);
        int draw_framebuffer = 0;
        glCheckFunc(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &draw_framebuffer));
        glCheckFunc(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_framebuffer));
        glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        // Render all object here
        render_info.id = 0;
        render_info.render_transparent = false;

        Fr_GL3Window::getfr_Gl3Window()->sceneBuffer->Bind();
        Render(render_info, render_info.modelview);
        RenderPrimativeShapes(render_info, render_info.modelview);
        RenderWidgetToolkit(render_info, render_info.modelview);

        //Render transparent items
        render_info.id = 0;
        render_info.render_transparent = true;
        Render(render_info, render_info.modelview);
    }

    /// object management part
    ///

    bool Fr_Scene::deleteItemByID(std::string_view str) {
        auto it = std::remove_if(m_world.begin(), m_world.end(),
            [str](const SceneItemStruct& obj) { return obj.name == str; });
        if (it != m_world.end()) {
            m_world.erase(it, m_world.end());
            return true;
        }
        return false;
    }

    bool Fr_Scene::replaceItemByID(int id, SceneItemStruct& newItem) {
        auto it = std::find_if(m_world.begin(), m_world.end(),
            [id](const SceneItemStruct& obj) { return obj.id == id; });
        if (it != m_world.end()) {
            *it = std::move(newItem);
            return true;
        }
        return false;
    }

    // Item management functions

    void Fr_Scene::addObject(SceneItemStruct&& item) {
        m_world.push_back(std::move(item));
    }

    // Delete a SceneItemStruct by its unique identifier
    bool Fr_Scene::deleteItemByID(int id) {
        auto it = std::remove_if(m_world.begin(), m_world.end(),
            [id](const SceneItemStruct& obj) { return obj.id == id; });

        if (it != m_world.end()) {
            m_world.erase(it, m_world.end());
            return true;
        }
        return false;
    }

    void Fr_Scene::Render(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
        //3D Mesh model
        std::vector<std::shared_ptr<ModelNode>> model;
        findOccurrencesOfType(model, NODETYPE::FR_MODEL_NODE);
        if (model.size()>0){
        for (auto item : model) {
            item->Render(info, modelview);
            }
        }
    }

    void Fr_Scene::RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
        // Iterate over entities with Fr_Grid and ItemName components
        std::vector<std::shared_ptr<Fr_Grid>> grid;
        findOccurrencesOfType(grid, NODETYPE::FR_GRID);

        for (int i = 0; i < grid.size(); i++) {
            grid[i]->getGridShader()->Render(info, modelview);
        }
         std::shared_ptr<Fr_Axis3D>  axis;
         findItemByName(axis, "Axis3D");

        auto blue = axis->getBlue();
        auto green = axis->getGreen();
        auto red = axis->getRed();
        auto zblue = axis->getZBlue();

        blue->Render(info, modelview);
        green->Render(info, modelview);
        red->Render(info, modelview);
        zblue->Render(info, modelview);
    }

    void Fr_Scene::RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
    }
    void Fr_Scene::RenderSilhouette(const glm::mat4& mvp) {
    }

    void Fr_Scene::RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview) {
        userData_ data;
        //Render GLFW stuff or Our 3D drawing
        Fr_GL3Window::getfr_Gl3Window()->renderimGUI(data);
    }
}