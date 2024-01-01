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
#include <cmath>
#include <glm/gtx/transform.hpp>
#include<fr_shader_program.h>

namespace FR {


  

    Fr_Widget::Fr_Widget(const Fr_Widget& t) :m_position{ 0.f,0.f,0.f }, m_callback_(t.m_callback_),
        m_verticies(std::move(t.m_verticies)), m_indicies(std::move(t.m_indicies))
    {
        m_label = t.m_label;
        m_active = t.m_active;
        m_visible = t.m_visible;
        m_Matrix = glm::mat4(1.0f);
        type(NODETYPE::FR_WIDGET);
      
    }

    Fr_Widget::Fr_Widget(glm::vec3 position, 
        std::shared_ptr<std::vector <float>> verticies,
        std::shared_ptr<std::vector <unsigned int>> indicies, 
        std::string label) :m_callback_{ NULL },
        m_label(""), m_draw{0}, m_verticies(std::move(verticies)), m_indicies(std::move(m_indicies))
    {
       
    }

    Fr_Widget::~Fr_Widget()
    {
        delete widget_program;
    }

    bool Fr_Widget::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        return false;
    }

    void Fr_Widget::CreateShader() {
        widget_program = new ShaderProgram("E:/Projects/Design456App/frtk/src/shaders/widgetshader");
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

    bool Fr_Widget::setup()
    {
        return false;   //Should be sub-classed to change that.
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
    void Fr_Widget::resize(std::shared_ptr<std::vector<float>>verticies_, 
                           std::shared_ptr<std::vector <unsigned int>> m_indicies)
    {
        m_verticies = std::move(verticies_);
        m_indicies = std::move(m_indicies);
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

    int Fr_Widget::handle(int handel)
    {
        throw NotImplementedException();
        //This must be sub-classed. 
        return 0;
    }

    void Fr_Widget::show()
    {
        //This must be sub-classed. 
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
    void Fr_Widget::hasTexture(int val) {
        m_hasTexture = val;
    }
    int Fr_Widget::hasTexture() {
        return m_hasTexture; 
    }
    void Fr_Widget::Rotate(float x, float y, float z, float angle)
    {
        m_Matrix = glm::rotate(glm::mat4{ 1 }, glm::radians(angle), glm::vec3(x, y, z));

    }
    void Fr_Widget::Rotate(glm::vec3 axis, float angle)
    {
        m_Matrix = glm::rotate(glm::mat4{ 1 }, glm::radians(angle), axis);

    }
    void Fr_Widget::Translate(glm::vec3 v)
    {
        m_Matrix = glm::translate(glm::mat4{ 1 }, v);

    }
    void Fr_Widget::Translate(float x, float y, float z)
    {
        m_position = glm::vec3(x, y, z);
        m_Matrix = glm::translate(m_Matrix, m_position);

    }
    void Fr_Widget::Scale(float x, float y, float z)
    {
        m_Matrix = glm::scale(m_Matrix, glm::vec3(x, y, z));

    }
    void Fr_Widget::Scale(glm::vec3 value)
    {
        m_Matrix = glm::scale(m_Matrix, value);

    }
    glm::mat4 Fr_Widget::GetMatrix()
    {
        return m_Matrix;
    }

    glm::mat4 Fr_Widget::GetInvers()
    {
        return (glm::inverse(m_Matrix));
    }
 
    void Fr_Widget::SetPosition(float x, float y, float z)
    {
        m_position = glm::vec3(x, y, z);
        Translate(m_position);
    }
    void Fr_Widget::SetPosition(glm::vec3 pos)
    {
        m_position = pos;
        Translate(pos);
    }

    void Fr_Widget::diffCalculateNormals() {
        glm::vec3 m_min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
        glm::vec3 m_max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
        for (size_t i = 0; i < m_verticies->size(); i += 3) {
            for (size_t j = 0; j < 3; ++j) {
                
                m_min[j] = std::min(m_min[j], m_verticies->at(i + j) );
                m_max[j] = std::max(m_max[j], m_verticies->at(i + j) - m_min[j]);
            }
        }
        if (m_normals->size() == 0)
            m_normals->reserve(m_verticies->size());
        m_normals->resize(m_verticies->size());
        std::fill(m_normals->begin(), m_normals->end(), 0);
        for (size_t i = 0; i < m_verticies->size() / 3; ++i) {
            glm::vec3 vertex = GetVertex(i, m_verticies->data());
            glm::vec3 normalized = (vertex / (m_max - m_min));
            SetVertex(i, m_normals->data(), normalized);
        }
    }
    glm::vec3 Fr_Widget::GetVertex(unsigned int index, const float vertices[]) {
        return glm::vec3(
            vertices[index * 3],
            vertices[index * 3 + 1],
            vertices[index * 3 + 2]
        );
    }

    void Fr_Widget::SetVertex(unsigned int index, float vertices[], const glm::vec3& vertex) {
        vertices[index * 3] = vertex[0];
        vertices[index * 3 + 1] = vertex[1];
        vertices[index * 3 + 2] = vertex[2];
    }

    void Fr_Widget::calcualteTextCoor(int width, int height) {
        // Calculate texture coordinates based on vertex positions
            // Loop through the vertices and calculate texture coordinates
        if (m_normals->size() == 0)
            diffCalculateNormals();
        for (int i = 0; i < m_normals->size(); i += 3)
        {
            //Get the vertex position
            GLfloat x = m_normals->at(i);
            GLfloat y = m_normals->at(i + 1);
            GLfloat z = m_normals->at(i + 2);

            // Calculate texture coordinates based on vertex position
            GLfloat u = (x);
            GLfloat v = (y);

            //   Store the texture coordinates in the vertices array
            m_textCoord->push_back(u);
            m_textCoord->push_back(v);

        }
    }
}
