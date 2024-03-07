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

#include <../src/ThreeDWidgets/fr_wgroup.h>

namespace FR {
    int FR::Fr_WGroup::handle(int events)
    {
        for (auto& widget : m_children) {
            if (widget->handle(events) != 0) {
                return 0;  //We are done. Events is consumed and we no longer need to send it to other widgets.
            }
        }
        return 1;//We didn't use the event, let other part of the system use it.
    }
    Fr_WGroup::Fr_WGroup(glm::vec3 position, std::shared_ptr<std::vector <float>>verticies, 
                        std::shared_ptr<std::vector <unsigned int>> indicies, 
                        std::string label):Fr_Widget(position, verticies, indicies, label)
    {
    }
    Fr_WGroup::~Fr_WGroup()
    {
    }
    void Fr_WGroup::draw()
    {
    }
    void Fr_WGroup::draw_children()
    {
        for (auto& widget : m_children) {
            widget->draw();
        }
    }
    void Fr_WGroup::draw_lbl_children()
    {
        for (auto& widget : m_children) {
            widget->lbl_draw();
        }
    }
    void Fr_WGroup::update_child(std::shared_ptr <Fr_Widget> wd)
    {
        wd->redraw();
    }
    bool Fr_WGroup::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        for (auto& widget : m_children) {
            if (widget->SetupCamera(projection, modelview))
                return true;
        }
        return false;
    }
    void Fr_WGroup::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
        for (auto& widget : m_children) {
            widget->SetupLight(modelview, lights);
        }
    }
    void Fr_WGroup::Render(RenderInfo& info, const glm::mat4& modelview)
    {
        for (auto& widget : m_children) {
            widget->Render(info, modelview);
        }
    }

    int Fr_WGroup::find(std::shared_ptr<Fr_Widget>& wd) const
    {
        auto it = std::find(m_children.begin(), m_children.end(), wd);
        if (it != m_children.end())
        {
            auto index = std::distance(m_children.begin(), it);
            return index;
        }
        return -1;
    }

    int Fr_WGroup::insert(std::shared_ptr <Fr_Widget>wd, int index_before)
    {
        if (m_children.begin() + index_before <= m_children.end())
        {
            m_children.insert(m_children.begin() + index_before, std::move(wd));
            return 0;
        }
        return -1; //error
    }

    void Fr_WGroup::addWidget(std::shared_ptr <Fr_Widget> wid)
    {
        m_children.push_back(std::move(wid));
    }
    int Fr_WGroup::removeWidget(std::shared_ptr <Fr_Widget> wd)
    {
        auto it = std::find(m_children.begin(), m_children.end(), wd);
        if (it != m_children.end())
        {
            auto index = std::distance(m_children.begin(), it);
            //TODO CHECK ME !
            m_children.erase(m_children.begin() + index);
            return 0;
        }
        return -1; //not found!!
    }
    int Fr_WGroup::removeWidget(int index)
    {
        m_children.erase(m_children.begin() + index);
        return 0;
    }
    void Fr_WGroup::redraw()
    {
    }
}