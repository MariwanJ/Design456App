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

#ifndef FR_SCENE_H
#define FR_SCENE_H
//#include<frtk.h>
#include<fr_core.h>
#include <fr_group.h>
#include<fr_transform.h>
#include <fr_primatives.h>
#include <fr_primativeShader.h>
#include <fr_modelnodeShader.h>
#include <fr_light.h>
#include <fr_mesh.h>
#include<fr_camera.h>
#include<fr_light.h>
#include<fr_genID.h>
#include <fr_grid.h>
#include <fr_axis3D.h>
#include<fr_node.h>
#include<typeindex>
#include <optional>
#include <sceneItem/fr_sceneItem.h>
/**
 * The scene root
 */

namespace FR {
    typedef struct {
        float r;
        float g;
        float b;
        float a; //alpha
    } bkgC;

    class FRTK_API Fr_Scene : public Group {
    public:
        /**
         * Default Constructor
         */
        Fr_Scene();
        /**
         * Sets the background color
         */
        void SetBackgroud(float r, float g, float b);
        void SetBackgroud(float r, float g, float b, float alfa);

        void add3DObject(std::string fName);
        void delete3DObject(std::shared_ptr<Transform>& obj);

        /**
         * Renders the scene
         * Throws runtime_error if there's no camera
         */
        virtual void RenderScene();
 

    private:
        bkgC  background_;

        void setBackgroud(float r, float g, float b, float alfa);
        void setBackgroud(glm::vec4 color);

        std::shared_ptr<Camera> setupActiveCamera(std::string_view name, Node::RenderInfo& info);
        std::shared_ptr<Camera> setupActiveCamera(CameraList val, Node::RenderInfo& info);

        void CreateDefaultCameras(void);

        void Render(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderSilhouette(const glm::mat4& mvp);
        void RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview);

        SceneItemStruct CreateDefaultSunLight(void);
        CameraList active_camera_;

        // Function to find all occurrences of a specific type in the m_world vector

        bool replaceItemByID(int id, SceneItemStruct& newItem);
        bool deleteItemByID(int id);
        bool deleteItemByID(std::string_view str);

        // find all occurrences of a specific type of object
        template <typename T>
        void  findOccurrencesOfType(std::vector<T>& vect, const NODETYPE& type) {
            for (size_t i = 0; i < m_world.size(); ++i) {
                const auto& sceneItem = m_world[i];
                if (sceneItem.Sceneitem->isOfType(type)) {
                    vect.push_back(sceneItem.Sceneitem);
                }
            }
        }

        template <typename T>
        void replaceItemByName(std::shared_ptr<T>other, std::string_view name) {
            for (int i = 0; i < m_world.size(); i++) {
                if (m_world[i].name == name) {
                    m_world[i] = other;
                }
            }
            answer = std::nullptr_t; // item was not found
        }

        template <typename T>
        void replaceItemByName(std::shared_ptr<T>other, genID id) {
            for (int i = 0; i < m_world.size(); i++) {
                if (m_world[i].id == id) {
                    m_world[i] = other;
                }
            }
            answer = std::nullptr_t; // item was not found
        }

        template <typename T>
        void findItemByName(std::shared_ptr<T>answer, std::string_view name) {
            for (int i = 0; i < m_world->size(); i++) {
                if (m_world[i]->name == name) {
                    answer<T> = m_world[i];
                }
            }
            answer =nullptr_t; // item was not found
        }

        template <typename T>
        void Fr_Scene::findItemByName(std::shared_ptr<T>answer, genID id) {
            for (int i = 0; i < m_world.size(); i++) {
                if (m_world[i]->id == id) {
                    answer<T> = m_world[i];
                }
            }
            answer = std::nullptr_t; // item was not found
        }
        void addObject(SceneItemStruct&& item);

    private:
        SceneItemStruct CreateGrid();
        SceneItemStruct CreateAxis();

        //Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
        void setupScene();

    private:
        glm::vec4 m_Background;
        std::shared_ptr<std::vector<SceneItemStruct>> m_world;
    };
}
#endif
