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
#ifndef FR_ENTTSENE_H
#define FR_ENTTSENE_H

#include<fr_camera.h>
#include<fr_light.h>
#include<fr_genID.h>
#include <sceneItem/fr_sceneItem.h>
#include <fr_grid.h>
#include <fr_axis3D.h>

namespace FR {
    class FRTK_API Fr_enttScene {
        friend Fr_GL3Window;
    public:

        Fr_enttScene();
        ~Fr_enttScene();
        Fr_enttScene(const Fr_enttScene& other) = default;  //shallow copy of the member variables

        void setBackgroud(float r, float g, float b, float alfa);
        void setBackgroud(glm::vec4 color);

        SceneItemStruct<Camera> setupActiveCamera(std::string_view name, Node::RenderInfo& info);
        SceneItemStruct<Camera> setupActiveCamera(CameraList val, Node::RenderInfo& info);

        void CreateDefaultCameras(void);

        void Render(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderSilhouette(const glm::mat4& mvp);
        void RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview);

        SceneItemStruct<Light> CreateDefaultSunLight(void);        
        CameraList active_camera_;
        void RenderScene();

        template<typename T, typename ...Args>
        SceneItemStruct<T> createItem(std::string&& name, Args && ...args);

        template<typename T>
        SceneItemStruct<T> findItemByName(std::string_view name);

        template<typename T>
        SceneItemStruct<T> findItemByID(genID id);

        template<typename T, typename ...Args>
        bool replaceItemByID(int id, const T& newItem, Args && ...args);

        bool deleteItemByID(int id);

        bool replaceItemByName(const std::string& name, const T& newItem);

        const std::vector<SceneItemStruct<T>>& getAllItems() const;

    protected:
        static Fr_GL3Window* linkToglfw;

    private:
        SceneItemStruct<Fr_Grid> CreateGrid();
        SceneItemStruct<Axis3D> CreateAxis();

        //Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
        void setupScene();

    private:
        glm::vec4 m_Background;

        template <typename T>
        using SceneItemVector = std::vector<SceneItemStruct<T>>;
        SceneItemVector<T> m_world;
    };
}
#endif
