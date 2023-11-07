//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
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

#include <../src/ThreeDWidgets/fr_wgroup.h>

namespace FR {
    int FR::Fr_Group::handel(int events)
    {
        return 0;
    }
    Fr_Group::Fr_Group(glm::vec3 position, std::vector<glm::vec3> verticies, std::vector<float> indicies, std::string label) :Fr_Widget(position, verticies, indicies, label)
    {
    }
    Fr_Group::~Fr_Group()
    {
    }
    void Fr_Group::draw()
    {
    }
    void Fr_Group::draw_children()
    {
        for (auto& widget : m_children) {
            widget->draw();
        }
    }
    void Fr_Group::draw_lbl_children()
    {
        for (auto& widget : m_children) {
            widget->lbl_draw();
        }

    }
    void Fr_Group::update_child(std::unique_ptr <Fr_Widget> wd)
    {
        wd->redraw();
    }
    bool Fr_Group::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        return false;
    }
    void Fr_Group::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
    }
    bool Fr_Group::SetupShadowMap(ShadowMapInfo& info)
    {
        return false;
    }
    void Fr_Group::RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview)
    {
    }
    void Fr_Group::Render(RenderInfo& info, const glm::mat4& modelview)
    {
    }
    int Fr_Group::find(std::unique_ptr<Fr_Widget> &wd) const
    {
        auto it = std::find(m_children.begin(), m_children.end(), wd);
        if (it != m_children.end())
        {
            auto index = std::distance(m_children.begin(), it);
            return index;
        }
        return -1;
    }

    void Fr_Group::insert(Fr_Widget& wd, int index_before)
    {
    }
    int Fr_Group::remove(Fr_Widget& wd)
    {
        auto it = std::find(m_children.begin(), m_children.end(), wd);
        if (it != m_children.end())
        {
            auto index = std::distance(m_children.begin(), it);
            //m_children.erase(index); wrong!!
        }

        return 0;
    }
    int Fr_Group::remove(int index)
    {
        return 0;
    }
    int Fr_Group::getTabIndex()
    {
        return 0;
    }
    void Fr_Group::setTabIndex(int tabIndex)
    {
    }
    void Fr_Group::addResizable(std::unique_ptr <Fr_Widget> wd)
    {
    }
    bool Fr_Group::Resizable(std::unique_ptr <Fr_Widget> wd)
    {
        return false;
    }
    void Fr_Group::addWidget(std::unique_ptr <Fr_Widget> wid)
    {
    }
    void Fr_Group::removeWidget(std::unique_ptr <Fr_Widget> wid)
    {
    }
    void Fr_Group::redraw()
    {
    }
}