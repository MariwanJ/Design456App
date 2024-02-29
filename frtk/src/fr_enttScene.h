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

#include<../vendor/EnTT/entt.hpp>
#include<fr_camera.h>
#include<fr_light.h>
#include<fr_genID.h>

namespace FR {
    class FRTK_API Fr_enttScene {
        friend class Fr_Item;
        friend Fr_GL3Window;
    public:

        Fr_enttScene();
        ~Fr_enttScene();
        Fr_enttScene(entt::entity ID, Fr_enttScene* scene);
        Fr_enttScene(const Fr_enttScene& other) = default;  //shallow copy of the member variables

        Fr_Item createItem(const std::string& name = std::string());
        Fr_Item createItemWithID(genID id, const std::string& name = std::string());

        void removeItem(Fr_Item ItemVal);
        //Item DuplicateItem(Item ItemVal);
        //Item copy(Item ItemVal);
        //void paste(Item ItemVal);

        Fr_Item findItemByName(std::string_view name);
        Fr_Item getItemByUUID(genID uuid);

        template<typename... Components>
        auto GetAllEntitiesWith()
        {
            return m_Registry.view<Components...>();
        }

        void setBackgroud(float r, float g, float b, float alfa);
        void setBackgroud(glm::vec4 color);

        Fr_Item& setupActiveCamera(std::string& name);
        Fr_Item& setupActiveCamera(CameraList val);

        void CreateDefaultCameras(void);

        void Render(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview);
        void RenderSilhouette(const glm::mat4& mvp);
        void RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview);

        void CreateDefaultSunLight(void);

        std::vector<std::shared_ptr<Camera>> cameraList; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT,
        CameraList active_camera_;
        void RenderScene();

    protected:
        static Fr_GL3Window* linkToglfw;

    private:
        void CreateGrid();
        void CreateAxis();

        //Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
        void setupScene();

    private:

        glm::vec4 m_Background;
        entt::registry m_Registry;
        std::unordered_map<genID, entt::entity> m_ItemMap;
    };
}
#endif
