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
    int FR::Fr_Group::handle(int events)
    {
        return 0;
    }
    Fr_Group::Fr_Group(glm::vec3 position, std::shared_ptr<std::vector <float>>verticies, std::shared_ptr<std::vector <float>> indicies, std::string label) :Fr_Widget(position, verticies, indicies, label)
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
    void Fr_Group::update_child(std::shared_ptr <Fr_Widget> wd)
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
    void Fr_Group::Render(RenderInfo& info, const glm::mat4& modelview)
    {
    }
    int Fr_Group::find(std::shared_ptr<Fr_Widget>& wd) const
    {
        auto it = std::find(m_children.begin(), m_children.end(), wd);
        if (it != m_children.end())
        {
            auto index = std::distance(m_children.begin(), it);
            return index;
        }
        return -1;
    }

    int Fr_Group::insert(std::shared_ptr <Fr_Widget>wd, int index_before)
    {
        auto it = std::find(m_children.begin(), m_children.end(), wd);
        if (m_children.begin() + index_before <= m_children.end())
        {
            auto it = m_children.begin();

            m_children.insert(m_children.begin() + index_before, std::move(wd));
            return 0;
        }
        return -1; //error
    }

    int Fr_Group::tabIndex(std::shared_ptr <Fr_Widget>& wid)
    {
        return wid->tabIndex();
    }
    void Fr_Group::tabIndex(std::shared_ptr <Fr_Widget>& wid, int index)
    {
        wid->tabIndex(index);
    }
    void Fr_Group::addResizable(std::shared_ptr <Fr_Widget> wd)
    {
    }
    bool Fr_Group::Resizable(std::shared_ptr <Fr_Widget> wd)
    {
        return wd->Resizable();
    }
    void Fr_Group::addWidget(std::shared_ptr <Fr_Widget> wid)
    {
        m_children.push_back(std::move(wid));
    }
    int Fr_Group::removeWidget(std::shared_ptr <Fr_Widget> wd)
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
    int Fr_Group::removeWidget(int index)
    {
        m_children.erase(m_children.begin() + index);
        return 0;
    }
    void Fr_Group::redraw()
    {
    }
}