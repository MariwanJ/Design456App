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

#include<../src/ThreeDWidgets/fr_widget.h>
namespace FR {



    Fr_Widget::Fr_Widget(const Fr_Widget& t) :m_position{ 0.f,0.f,0.f }, m_callback_(t.m_callback_),
        m_verticies(t.m_verticies), m_indicies(t.m_indicies)
    {
        m_label = t.m_label;
        m_active = t.m_active;
        m_visible = t.m_visible;
    }

    Fr_Widget::Fr_Widget(glm::vec3 position, std::vector<glm::vec3> verticies,
        std::vector<float> indicies, std::string label) :m_callback_{ NULL },
        m_label{ 0 }, m_draw{0}
    {
    }

    Fr_Widget::~Fr_Widget()
    {
    }

    bool Fr_Widget::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        return false;
    }

    void Fr_Widget::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
    }


    void Fr_Widget::Render(RenderInfo& info, const glm::mat4& modelview)
    {
        throw NotImplementedException();
    }

    GLuint Fr_Widget::getCurrentTexturer(void)
    {
        return GLuint();
    }

    void Fr_Widget::draw()
    {
        throw NotImplementedException();
    }

    void Fr_Widget::redraw()
    {
        throw NotImplementedException();
    }

    void Fr_Widget::lbl_draw()
    {
        throw NotImplementedException();
    }

    void Fr_Widget::lbl_redraw()
    {
        throw NotImplementedException();
    }

    void Fr_Widget::label(std::string& lbl)
    {
        m_label = lbl;
    }

    std::string Fr_Widget::label() const
    {
        return m_label;
    }

    void Fr_Widget::font(std::string& forntName)
    {
        m_fontName = forntName;
    }

    std::string Fr_Widget::font() const
    {
        return m_fontName;
    }

    void Fr_Widget::fontSize(int size_)
    {
        m_fontSize = size_;
    }
    void Fr_Widget::resize(std::vector<glm::vec3>& verticies_, std::vector<float>& indicies_)
    {
        m_verticies = verticies_;
        m_indicies = indicies_;
    }

    bool Fr_Widget::Resizable()
    {
        return m_resizable;
    }

    bool Fr_Widget::active()
    {
        return m_active;
    }
    
    void Fr_Widget::activate(bool value)
    {
        m_active = value;
    }

    bool Fr_Widget::has_focus()
    {
        return m_focus;
    }

    void Fr_Widget::has_focus(bool value)
    {
        m_focus = value;
    }

    void Fr_Widget::visible(bool value)
    {
        m_visible = value;
    }

    bool Fr_Widget::visible(void)
    {
        return m_visible;
    }

    int Fr_Widget::handel(int handel)
    {
        throw NotImplementedException();
        //This must be subclassed. 
        return 0;
    }

    void Fr_Widget::show()
    {
        //This must be subclassed. 
        m_visible = true;
    }

    void Fr_Widget::hide()
    {
        m_visible = false;
    }

    Fr_Callback_p Fr_Widget::callback() const
    {
        return Fr_Callback_p();
    }

    glm::vec3 Fr_Widget::getPosition() const
    {
        return m_position;
    }


    void Fr_Widget::WidgetShader(glm::vec4 color, float silhouette)
    {
        m_color = color;
        silhouette = silhouette;
    }

    void Fr_Widget::SetColor(glm::vec4 c)
    {
        m_color = c;
    }

    void Fr_Widget::SetOpacity(float alpha)
    {
        m_color[3] = alpha;
    }

    void Fr_Widget::do_callback()
    {
        throw NotImplementedException();
    }

    void Fr_Widget::LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights)
    {
        throw NotImplementedException();
    }
    int Fr_Widget::tabIndex()const
    {
        return m_tabIndex;
    }
    void Fr_Widget::tabIndex(int index)
    {
        m_tabIndex =index;
    }
}
