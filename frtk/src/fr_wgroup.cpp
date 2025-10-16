//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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

#include <fr_wgroup.h>
#include <fr_scene.h>
namespace FR {
    //Consumed handle = 1 , not consumed = 0

    //void Fr_WGroup::setLinkToScene(std::shared_ptr<Fr_Scene> linkTo)
    //{
    //    linkTomainScene = linkTo;
    //}
    Fr_WGroup::Fr_WGroup(std::shared_ptr<std::vector <float>>verticies, 
                        std::shared_ptr<std::vector <unsigned int>> indicies,
                        std::string label):Fr_Widget(verticies, indicies, label)
    {
        m_children.clear();
    }
    Fr_WGroup::~Fr_WGroup()
    {
    }
    void Fr_WGroup::draw()
    {
        draw_children();
        draw_lbl_children();
        FRTK_CORE_ERROR("WHY DRAW?!!");     //The widget itself shouldn't need draw if we are not planning to make it visible
    }
    void Fr_WGroup::draw_children()
    {
        for (auto& node : m_children) {
            //TODO: FIXME
            //auto dm = std::dynamic_pointer_cast<Fr_Widget>(node.Sceneitem->getPointer());
            //dm->draw();
        }
    }
    void Fr_WGroup::draw_lbl_children()
    {
        for (auto  node : m_children) {
             //TODO : FIXME
           // node->lbl_draw();
        }
    }
    void Fr_WGroup::update_child(std::shared_ptr <Fr_Widget> wd)
    {
        wd->redraw();
    }

    //std::shared_ptr<std::vector<SceneItemStruct>> Fr_WGroup::getChildren() const
    //{
    //    return std::make_shared<std::vector<SceneItemStruct>>(m_children);
    //}


    void Fr_WGroup::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
        for (auto& node : m_children) {
            node.Sceneitem->SetupLight(modelview, lights);
        }
    }
    void Fr_WGroup::Render(RenderInfo& info)
    {
        for (auto& node : m_children) {
            node.Sceneitem->Render(info);
            //FRTK_CORE_INFO("{},{}", "info", info.id);       //Just a debug info - TODO : remove me 
        }
    }

    int Fr_WGroup::find(std::shared_ptr<Fr_Widget>& wd) const {
        // Iterate through the m_children vector, which holds shared pointers to SceneItemStruct
        for (size_t i = 0; i < m_children.size(); ++i) {
            // Check if the Sceneitem in the current SceneItemStruct matches the given wd
            if (m_children.at(i).Sceneitem== wd) {
                return static_cast<int>(i); // Return the index if found
            }
        }
        return -1; // Return -1 if not found
    }


    //int Fr_WGroup::insert(std::shared_ptr <Fr_Widget>wd, int index_before)
    //{
    //    if (m_children.begin() + index_before <= m_children.end())
    //    {
    //        m_children->insert(m_children->begin() + index_before, std::move(wd));
    //        return 0;
    //    }
    //    return -1; //error
    //}

    void Fr_WGroup::addWidget(std::shared_ptr <Fr_Widget> wid)
    {
        SceneItemStruct nItem(wid, "NoName");
        m_children.emplace_back(std::move(nItem));
        }
    int Fr_WGroup::removeWidget(std::shared_ptr<Fr_Widget> wd) {
        // Iterate through m_children to find the widget
        for (auto it = m_children.begin(); it != m_children.end(); ++it) {
            // Check if the Sceneitem matches the provided wd
            if ((*it).Sceneitem == wd) {
                // Found the widget, perform the removal
                //linkTomainScene->deleteItemByID((*it).id); // Call deleteItemByID with the item's ID
                m_children.erase(it); // Erase using the iterator
                return 0; // Successful removal
            }
        }
        return -1; // Widget not found
    }

    int Fr_WGroup::removeWidget(int index)
    {
        m_children.erase(m_children.begin() + index);
        return 0;
    }
    void Fr_WGroup::redraw()
    {
        FRTK_CORE_INFO("Why redraw?");  //This shouldn't be needed if we are not planning to draw the group itself
        draw();
    }
    std::shared_ptr<std::vector<SceneItemStruct>> Fr_WGroup::getChildren() const
    {
        //immutable ref to the m_childer
        return std::make_shared<std::vector<SceneItemStruct>>(m_children);
    }
    std::shared_ptr<std::vector<SceneItemStruct>> Fr_WGroup::getMutChildren() const
    {
        return std::make_shared<std::vector<SceneItemStruct>>(m_children);
    }

}