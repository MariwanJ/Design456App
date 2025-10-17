#include "fr_widget.h"
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

 
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <fr_widget.h>


namespace FR {
    //Constructor
    Fr_Widget::Fr_Widget(std::shared_ptr<std::vector <float>> verticies,
        std::shared_ptr<std::vector <unsigned int>> indicies,
        std::string label) :m_vertices(std::move(verticies)),
        m_Matrix(glm::mat4(1.0f)), m_indices(std::move(indicies)),m_vao (0),m_vbo{ 0 },
        m_lineWidth(1),m_pointSize(10)
    {
        m_lineType = FR_NOT_DEFINED; //You should define it before use it
        
        m_vertCoord = NULL;          //must be calculated internally
        m_normals = NULL;
        m_textCoord = NULL;
        m_shader = {0};
        m_callback_ = NULL;
        m_boundBox = nullptr;
        
        m_label.text = "";
        m_label.fnFont = NULL;// we cannot define it here
        m_label.size = 10;
        m_label.color = glm::vec4(FR_BLACK);
        m_label.position = glm::vec3( 0.0f );
        m_label.visible = false; //we dont have font .. disable it
        m_label.pixelSize = 18;  //size of the pixesl -- TODO : HOW MUCH WE SHOULD PUT HERE !!!!!!!!!!!
        m_label.text = "Change me - Widget say hello";
        m_label.type = ORTHOGRAPHIC;

        m_active = true;
        m_visible = true;
        m_focus = false;
        m_resizable = true;
        m_WidgType = NODETYPE::FR_WIDGET;   //widget type
        m_tabIndex = -1;
        m_hasTexture = 0;
        // Attributes
        m_color = glm::vec4(FR_ANTIQUEWHITE);
        m_silhouette = 0;
        m_texture = 0; //used to return the texture for imgui rendering inside window. 
        m_selected = std::make_shared <std::vector<uint8_t>>();
        m_shader = std::make_shared<Shader_t>();
    }
    void Fr_Widget::init(void) {
        openEdges.clear();
        std::vector< MyMesh::Point> points;
        if (m_vertices == nullptr)                   //TODO This happens when you create the fr_windows which doesn't have any vertices or indices - can we fix that? !!! 2025-01-03
            return;
        for (size_t i = 0; i < m_vertices->size(); i += 3) {
            auto x = m_vertices->at(1);
            MyMesh::Point point(m_vertices->at(i), m_vertices->at(i + 1), m_vertices->at(i + 2));
            points.push_back(point);
        }
        size_t total = points.size();

        if (total < 2)
            return; //Not enough points
        for (int i = 0; i < total - (total % 2); i += 2) {
            openEdges.push_back(std::make_pair(m_mesh.add_vertex(points.at(i)), m_mesh.add_vertex(points.at(i + 1))));
        }
        if (total % 2 != 0) {
            // Handle the last edge if total is odd
            openEdges.push_back(std::make_pair(m_mesh.add_vertex(points.at(total - 1)), m_mesh.add_vertex(points.at(0))));
        }
        //should not need casting, but just in case, and this will be one true/false per a vertex
        // Resize the vector to initialize all elements to false
        m_selected->reserve(static_cast<size_t>(m_vertices->size()) / 3);
        m_selected->resize(m_selected->capacity(), 0);
    }
    Fr_Widget::~Fr_Widget()
    {
    }

    void Fr_Widget::CreateShader() {
        if (!m_shader)
        {
            m_shader = std::make_shared<Shader_t>();
        }
        std::string shaderpath = EXE_CURRENT_DIR + "/resources/shaders/";
        m_shader->wdg_prog = std::make_shared<ShaderProgram>         (shaderpath+"wdgshader");
        m_shader->widgPoits_prog = std::make_shared<ShaderProgram>   (shaderpath+"widgPoints");
        m_shader->silhouette_prog = std::make_shared<ShaderProgram>  (shaderpath+"silhouette");
        m_shader->texture_prog= std::make_shared<ShaderProgram>      (shaderpath+"texture"); 
    }
    void Fr_Widget::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
        return; //You should override this
    }

    void Fr_Widget::Render(RenderInfo& info)
    {
        return; //do nothing , should be subclassed
    }

    void Fr_Widget::RenderVertexes(RenderInfo& info)
    {
        return; //do nothing should be subclassed
    }

    void RenderText(RenderInfo& info) {
        return;//do nothing should be subclassed
    }

    GLuint Fr_Widget::getCurrentTexturer(void)
    {
        return GLuint();
    }

    void Fr_Widget::draw()
    {
        return; //do nothing should be subclassed
    }

    void Fr_Widget::redraw()
    {
        return; //do nothing should be subclassed
    }

    void Fr_Widget::lbl_redraw()
    {
        return; //do nothing should be subclassed
    }

    bool Fr_Widget::setup()
    {
        return false;   //Should be sub-classed to change that.
    }

    void Fr_Widget::lblType(uint8_t lbltype) {
        m_label.type = lbltype;
    }
    const uint8_t Fr_Widget::lblType(void) {
        return m_label.type;
    }

    void Fr_Widget::RenderText(RenderInfo& info) {
        return; //should be sub-classed to define this
    }

    void Fr_Widget::label(std::string& lbl)
    {
        m_label.text = lbl;
    }

    std::string Fr_Widget::label() const
    {
        return m_label.text;
    }

    void Fr_Widget::font(std::string& forntName)
    {
        m_label.fnFont = std::make_shared<std::string>(forntName);
    }

    std::shared_ptr<std::string> Fr_Widget::font() const
    {
        return m_label.fnFont;
    }

    void Fr_Widget::fontSize(int size_)
    {
        m_label.size = size_;
    }

    void Fr_Widget::fontColor(glm::vec4 col)
    {
        m_label.color = col;
    }
    void Fr_Widget::fontColor(float r, float g, float b, float a)
    {
        m_label.color = glm::vec4(r, g, b, a);
        m_label.position;
    }

    void Fr_Widget::lblPosition(glm::vec3 nval)
    {
        m_label.position = nval;
    }

    void Fr_Widget::lbl_visible(bool v) {
        m_label.visible = v;
    }

    bool Fr_Widget::lbl_visible() {
        return m_label.visible;
    }

    void Fr_Widget::resize(std::shared_ptr<std::vector<float>>verticies_,
        std::shared_ptr<std::vector <unsigned int>> indicies_)
    {
        m_vertices = std::move(verticies_);
        m_indices = std::move(indicies_);
        
        //TODO: Make sure that the code take care of this everywhere 
        // This must be doen always
        m_selected->reserve(static_cast<size_t>(m_vertices->size()) / 3);
        m_selected->resize(m_selected->capacity(), 0);
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

    int Fr_Widget::handle(int ev)
    {
        return 0;
        //This must be sub-classed.
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

    void Fr_Widget::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights)
    {
        throw NotImplementedException();
    }
    int Fr_Widget::tabIndex()const
    {
        return m_tabIndex;
    }
    void Fr_Widget::tabIndex(int index)
    {
        m_tabIndex = index;
    }
    void Fr_Widget::hasTexture(int val) {
        m_hasTexture = val;
    }
    int Fr_Widget::hasTexture() {
        return m_hasTexture;
    }
    void Fr_Widget::Rotate(float x, float y, float z, float angle)
    {
        m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), glm::vec3(x, y, z));
    }
    void Fr_Widget::Rotate(glm::vec3 axis, float angle)
    {
        m_Matrix  = glm::rotate(m_Matrix, glm::radians(angle), axis);
    }
    void Fr_Widget::Translate(glm::vec3 v)
    {
        m_Matrix = glm::translate(m_Matrix, v);
    }
    void Fr_Widget::Translate(float x, float y, float z)
    {
        m_Matrix = glm::translate(m_Matrix, glm::vec3(x, y, z));
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
    // Method to retrieve a shared pointer to the vector of vertices
    std::shared_ptr<std::vector<float>> Fr_Widget::getVertices() {
        return m_vertices;
    }
    void Fr_Widget::CalculateNormals(void) {
        if (!m_vertices) {
            throw("ERRROR: m_vertices are not initizlied");
        }
        if (!m_normals) {
            m_normals = std::make_shared<std::vector<float>>();
        }
        constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
        constexpr float FLOAT_MIN = -std::numeric_limits<float>::max();

        glm::vec3 m_min(FLOAT_MAX, FLOAT_MAX, FLOAT_MAX);
        glm::vec3 m_max(FLOAT_MIN, FLOAT_MIN, FLOAT_MIN); // Corrected initialization

        // Find min and max
        for (size_t i = 0; i < m_vertices->size(); i += 3) {
            m_min.x = std::min(m_min.x, m_vertices->at(i));       // x
            m_min.y = std::min(m_min.y, m_vertices->at(i + 1));   // y
            m_min.z = std::min(m_min.z, m_vertices->at(i + 2));   // z

            m_max.x = std::max(m_max.x, m_vertices->at(i));       // x
            m_max.y = std::max(m_max.y, m_vertices->at(i + 1));   // y
            m_max.z = std::max(m_max.z, m_vertices->at(i + 2));   // z
        }

        // Resize normals vector if necessary
        if (m_normals->empty()) {
            m_normals->resize(m_vertices->size());
        }

        // Initialize normals to zero
        std::fill(m_normals->begin(), m_normals->end(), 0.0f);

        // Normalize vertices and store in m_normals
        for (size_t i = 0; i < m_vertices->size() / 3; ++i) {
            // Read the vertex as a 3D vector from the flat float array
            glm::vec3 vertex(
                m_vertices->at(i * 3),
                m_vertices->at(i * 3 + 1),
                m_vertices->at(i * 3 + 2)
            );

            // Normalize the vertex
            glm::vec3 normalized = (vertex - m_min) / (m_max - m_min); // Normalize

            // Store normalized values back in m_normals
            m_normals->at(i * 3) = normalized.x;
            m_normals->at(i * 3 + 1) = normalized.y;
            m_normals->at(i * 3 + 2) = normalized.z;
        }
    }
    void Fr_Widget::NormalizeVertices(void) {
        m_vertices = m_normals;
    }
    void Fr_Widget::SetNormalizeMesh(bool value)
    {
        m_normalized = true;
    }

    bool Fr_Widget::getNormalizeMesh()
    {
        return m_normalized;
    }
    void Fr_Widget::calculateTextCoor() {
        return; //should be subbclassed
    }
    void Fr_Widget::CalculateTrianglesNormals() {
        // Ensure m_triangles_normals is initialized
        if (!m_triangles_normals) {
            if (m_vertices) { // Check if m_vertices is not null
                m_triangles_normals = std::make_shared<std::vector<glm::vec3>>(); // Store triangle normals as glm::vec3
                m_triangles_normals->reserve(m_indices->size() / 3); // One normal per triangle
            }
            else {
                throw std::runtime_error("m_vertices are not initialized");
            }
        }
        // Calculate the normals for each triangle
        for (size_t i = 0; i < m_indices->size(); i += 3) {
            // Triangle vertices' indices
            uint32_t v[3] = { m_indices->at(i), m_indices->at(i + 1), m_indices->at(i + 2) };

            // Triangle's vertices
            glm::vec3 triangle[3] = {
                GetVertex(v[0], m_vertices->data()),
                GetVertex(v[1], m_vertices->data()),
                GetVertex(v[2], m_vertices->data())
            };

            // Vectors created by the triangle's vertices
            glm::vec3 v0_to_v1 = triangle[1] - triangle[0];
            glm::vec3 v0_to_v2 = triangle[2] - triangle[0];

            // Triangle's normal
            glm::vec3 t_normal = glm::normalize(glm::cross(v0_to_v1, v0_to_v2));

            // Store the triangle normal
            m_triangles_normals->push_back(t_normal);
        }
    }


    // TODO: These are bad -- remove them 2025-01-30
    glm::vec3 Fr_Widget::GetVertex(unsigned int index, const float vertices[]) {
        return glm::vec3(
            vertices[index * 3],
            vertices[index * 3 + 1],
            vertices[index * 3 + 2]
        );
    }
    glm::vec3 Fr_Widget::GetVertex(unsigned int ind) {
        if (ind * 3 + 2 >= m_vertices->size()) {
            throw std::out_of_range("Index out of range in GetVertex");
        }
        return glm::vec3(
            (*m_vertices)[ind * 3],
            (*m_vertices)[ind * 3 + 1],
            (*m_vertices)[ind * 3 + 2]);
    }

   void Fr_Widget::SetVertex(unsigned int ind, const glm::vec3& vertex) {
        if (ind * 3 + 2 >= m_vertices->size()) {
            throw std::out_of_range("Index out of range in SetVertex");
        }
        (*m_vertices)[ind * 3] = vertex.x;
        (*m_vertices)[ind * 3 + 1] = vertex.y;
        (*m_vertices)[ind * 3 + 2] = vertex.z;
    }

    //TODO : FIX ME 
    void Fr_Widget::calcualteTextCoor(int width, int height) {
        // Calculate texture coordinates based on vertex positions
        // Loop through the vertices and calculate texture coordinates
            CalculateNormals();
            if (!m_textCoord) {
                m_textCoord = std::make_shared<std::vector<float>>();
            }
            //The size is 2x (verticies_size/3)
            m_textCoord->reserve(2*m_vertices->size() / 3);
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
    
    bool Fr_Widget::SetupTexture2D() {
        //Dummy code does nothing should be subclassed
        /*(void)info;*/
        return false;
    }

    void Fr_Widget::RenderTexture2D() {
        //Dummy code does nothing should be subclassed
        /*(void)info;
        (void)modelview;*/
    }
    void Fr_Widget::isActive(bool active) {
        m_active = active;
    }

    bool Fr_Widget::isActive() {
        return m_active;
    }

    NODETYPE Fr_Widget::type()
    {
        return m_WidgType;
    }

    twodType_t Fr_Widget::lineType(void)
    {
        return m_lineType;
    }

    void Fr_Widget::lineType(twodType_t ltype)
    {
        m_lineType = ltype;
    }

    void Fr_Widget::type(NODETYPE newVal)
    {
        m_WidgType = newVal;
    }

    bool Fr_Widget::isOfType(const NODETYPE& val)
    {
        return (m_WidgType == val);
    }
    void Fr_Widget::Parent(int index)
    {
        m_Parent = index;
    }
}