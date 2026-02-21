//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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
#include <frtk.h>
#include <ft2build.h>
#include <cassert>
#include FT_FREETYPE_H

namespace FR {
    //Constructor
    Fr_Widget::Fr_Widget(std::shared_ptr<std::vector <float>> vertices,
        std::shared_ptr<std::vector <unsigned int>> indicies,
        std::string label) :m_vertices(std::move(vertices)),
        m_Matrix(glm::mat4(1.0f)), m_indices(std::move(indicies)), m_vao(0), m_vbo{ 0 },
        m_lineWidth(1), m_selectionlineWidth(5), m_pointSize(10), m_WdgPosition(0), m_label(0), m_sel_vao({ 0 }), m_silhouette(DEFAULT_SIHOUETTE)
    {
        m_lineType = FR_NOT_DEFINED; //You should define it before use it

        m_normals = NULL;
        m_textureCoord = NULL;
        m_shader = { 0 };
        m_callback_ = NULL;
        m_boundBox = nullptr;

        m_active = true;
        m_visible = true;
        m_focus = false;
        m_resizable = true;
        m_WidgType = NODETYPE::FR_WIDGET;   //widget type
        m_tabIndex = -1;
        m_hasTexture = 0;
        // Attributes
        m_color.baseColor = glm::vec4(FR_ANTIQUEWHITE);
        m_color.faceSelectColor = glm::vec4(FR_LIGHTYELLOW);
        m_color.edgeSelectColor = glm::vec4(FR_LIGHTGOLDENRODYELLOW);
        m_color.vertexSelectColor = glm::vec4(FR_YELLOW);

        //Change ALFA (transparency)
        m_color.faceSelectColor.a = m_color.edgeSelectColor.a = m_color.vertexSelectColor.a = 0.5f;

        m_texture = 0; //used to return the texture for imgui rendering inside window.
        m_shader = std::make_shared<Shader_t>();
    }

    void Fr_Widget::ReadMeshString(const std::string& mshData) {
        std::istringstream input(mshData);
        if (!m_vertices) {
            m_vertices = std::make_shared<std::vector<float>>();
        }
        if (!m_indices) {
            m_indices = std::make_shared<std::vector<unsigned int>>();
        }
        if (!m_normals) {
            m_normals = std::make_shared<std::vector<float>>();
        }
        std::string header;
        std::getline(input, header);

        size_t nVertices, nTriangles, nQuads;
        input >> nVertices >> nTriangles >> nQuads;

        m_vertices->resize(nVertices * 3);
        for (size_t i = 0; i < m_vertices->size(); ++i)
            input >> m_vertices->at(i);

        m_indices->resize((nTriangles + 2 * nQuads) * 3);
        size_t idx = 0;
        for (size_t i = 0; i < nTriangles + nQuads; ++i) {
            int polygon;
            input >> polygon;
            if (polygon == 3) {
                input >> m_indices->at(idx++);
                input >> m_indices->at(idx++);
                input >> m_indices->at(idx++);
            }
            else {
                float quad[4];              /// TODO: This is really not supported yet
                input >> quad[0] >> quad[1] >> quad[2] >> quad[3];
                m_indices->at(idx++) = quad[0];
                m_indices->at(idx++) = quad[1];
                m_indices->at(idx++) = quad[2];
                m_indices->at(idx++) = quad[2];
                m_indices->at(idx++) = quad[3];
                m_indices->at(idx++) = quad[0];
            }
        }
        std::vector<MyMesh::VertexHandle> vhandles;
        vhandles.reserve(nVertices);
        for (size_t i = 0; i < nVertices; ++i) {
            MyMesh::Point p((*m_vertices)[3 * i], (*m_vertices)[3 * i + 1], (*m_vertices)[3 * i + 2]);
            vhandles.push_back(m_mesh.add_vertex(p));
        }
        for (size_t i = 0; i < nTriangles; ++i) {
            std::vector<MyMesh::VertexHandle> faceV;
            for (int j = 0; j < 3; ++j) {
                unsigned int idx = (*m_indices)[3 * i + j];
                faceV.push_back(vhandles[idx]); // use stored handles!
            }
            auto fh = m_mesh.add_face(faceV);
            if (!fh.is_valid()) {
                std::cerr << "Failed to add face " << i << std::endl;
            }
        }
    }
    glm::vec3 Fr_Widget::position(void)
    {
        return m_WdgPosition;
    }
    void Fr_Widget::position(glm::vec3 val)
    {
        m_WdgPosition = val;
        /*TODO: FIXME .. THIS SHOULD AFFECT THE VERTICES,
            USING ONLY glm::translate will not affect the internal
            vertices we have inside m_vertices.
            We need to find out how to re-calculate them or not??
            */
    }

    void Fr_Widget::ReadFile(const std::string& path) {
        if (!m_vertices) {
            m_vertices = std::make_shared < std::vector<float>>();
        }
        if (!m_indices) {
            m_indices = std::make_shared < std::vector<unsigned int>>();
        }
        if (!OpenMesh::IO::read_mesh(m_mesh, path))
        {
            throw std::runtime_error("Failed to read mesh from " + path);
        }
        m_vertices->reserve(m_mesh.n_vertices() * 3);
        m_indices->reserve(m_mesh.n_faces() * 3); // TODO: We need to make sure there are only 3 vert/obj
        for (auto vit = m_mesh.vertices_begin(); vit != m_mesh.vertices_end(); ++vit) {
            MyMesh::Point p = m_mesh.point(*vit);
            m_vertices->emplace_back(static_cast<float>(p[0]));
            m_vertices->emplace_back(static_cast<float>(p[1]));
            m_vertices->emplace_back(static_cast<float>(p[2]));
        }
        for (auto fit = m_mesh.faces_begin(); fit != m_mesh.faces_end(); ++fit) {
            for (auto fvit = m_mesh.fv_iter(*fit); fvit.is_valid(); ++fvit) {
                m_indices->emplace_back(fvit.handle().idx());
            }
        }
    }

    void Fr_Widget::init(void) {
        FRTK_CORE_APP_ASSERT(!m_vertices->empty() && "ERROR: You should provide vertices before initializing the object");
        CreateShader();
        m_boundBox = std::make_shared <cBoundBox3D>();
        m_boundBox->setVertices(m_vertices);
        CalculateNormals();
        createBuffers();
        initSelectionVAOs();
        initializeVAO();
        CreateShader();
        calcualteTextCoor();  //TODO:  ??? don't think it is correct
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
        m_shader->wdg_prog = std::make_shared<ShaderProgram>(shaderpath + "wdgshader");
        m_shader->wdg_selection_prog = std::make_shared<ShaderProgram>(shaderpath + "wdg_selection");
        m_shader->silhouette_prog = std::make_shared<ShaderProgram>(shaderpath + "silhouette");
    }
    void Fr_Widget::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
        return; //You should override this
    }

    void Fr_Widget::Render(RenderInfo& info)
    {
        (void)info;
        return; //do nothing , should be sub-classed
    }

    void Fr_Widget::RenderSelection(RenderInfo& info)
    {
        (void)info;
        return; //do nothing should be sub-classed
    }

    void RenderText(RenderInfo& info) {
        (void)info;
        return;//do nothing should be sub-classed
    }

    GLuint Fr_Widget::getCurrentTexturer(void)
    {
        return GLuint();
    }

    void Fr_Widget::draw()
    {
        return; //do nothing should be sub-classed
    }

    void Fr_Widget::redraw()
    {
        return; //do nothing should be sub-classed
    }

    void Fr_Widget::lbl_redraw()
    {
        return; //do nothing should be sub-classed
    }

    bool Fr_Widget::setup()
    {
        return false;   //Should be sub-classed to change that.
    }

    void Fr_Widget::RenderText(RenderInfo& info) {
        return; //should be sub-classed to define this
    }

    void Fr_Widget::resize(std::shared_ptr<std::vector<float>>vertices_,
        std::shared_ptr<std::vector <unsigned int>> indicies_)
    {
        m_vertices = std::move(vertices_);
        m_indices = std::move(indicies_);
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
        m_color.baseColor = color;
        silhouette = silhouette;
    }

    void Fr_Widget::SetColor(glm::vec4 c)
    {
        m_color.baseColor = c;
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
        m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), axis);
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
    std::shared_ptr<std::vector<float>> Fr_Widget::getVertices() {
        return m_vertices;
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
        return; //should be sub-classed
    }
    void Fr_Widget::CalculateTrianglesNormals() {
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
            uint32_t v[3] = { m_indices->at(i), m_indices->at(i + 1), m_indices->at(i + 2) };
            glm::vec3 triangle[3] = {
                GetVertex(v[0], m_vertices->data()),
                GetVertex(v[1], m_vertices->data()),
                GetVertex(v[2], m_vertices->data())
            };
            glm::vec3 v0_to_v1 = triangle[1] - triangle[0];
            glm::vec3 v0_to_v2 = triangle[2] - triangle[0];
            glm::vec3 t_normal = glm::normalize(glm::cross(v0_to_v1, v0_to_v2));
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

    void Fr_Widget::calcualteTextCoor()
    {
        if (m_mesh.n_faces() == 0)
            return;

        // Request required OpenMesh properties
        if (!m_mesh.has_halfedge_texcoords2D())
            m_mesh.request_halfedge_texcoords2D();

        if (!m_mesh.has_vertex_normals())
            m_mesh.request_vertex_normals();

        if (!m_mesh.has_face_normals())
            m_mesh.request_face_normals();

        m_mesh.update_normals();

        // Allocate output buffer
        if (!m_textureCoord)
            m_textureCoord = std::make_shared<std::vector<float>>();

        m_textureCoord->clear();
        m_textureCoord->reserve(m_mesh.n_faces() * 6); // at least triangles

        // Assign UVs and export them
        for (auto f : m_mesh.faces())
        {
            std::vector<OpenMesh::HalfedgeHandle> halfedges;
            for (auto h : m_mesh.fh_range(f))
                halfedges.push_back(h);

            int n = (int)halfedges.size();

            // Triangle
            if (n == 3)
            {
                OpenMesh::Vec2f uv[3] = {
                    {0.0f, 0.0f},
                    {1.0f, 0.0f},
                    {0.0f, 1.0f}
                };

                for (int i = 0; i < 3; ++i)
                {
                    m_mesh.set_texcoord2D(halfedges[i], uv[i]);
                    m_textureCoord->push_back(uv[i][0]);
                    m_textureCoord->push_back(uv[i][1]);
                }
            }
            // Quad (split as two triangles)
            else if (n == 4)
            {
                OpenMesh::Vec2f uv[4] = {
                    {0.0f, 0.0f},
                    {1.0f, 0.0f},
                    {1.0f, 1.0f},
                    {0.0f, 1.0f}
                };

                int tri[6] = { 0, 1, 2, 0, 2, 3 };

                for (int i = 0; i < 6; ++i)
                {
                    int idx = tri[i];
                    m_mesh.set_texcoord2D(halfedges[idx], uv[idx]);
                    m_textureCoord->push_back(uv[idx][0]);
                    m_textureCoord->push_back(uv[idx][1]);
                }
            }
            // N-gon (fan triangulation)
            else if (n > 2)
            {
                for (int i = 1; i < n - 1; ++i)
                {
                    OpenMesh::Vec2f uv0(0.0f, 0.0f);
                    OpenMesh::Vec2f uv1(1.0f, 0.0f);
                    OpenMesh::Vec2f uv2(0.0f, 1.0f);

                    m_mesh.set_texcoord2D(halfedges[0], uv0);
                    m_mesh.set_texcoord2D(halfedges[i], uv1);
                    m_mesh.set_texcoord2D(halfedges[i + 1], uv2);

                    m_textureCoord->push_back(uv0[0]);
                    m_textureCoord->push_back(uv0[1]);
                    m_textureCoord->push_back(uv1[0]);
                    m_textureCoord->push_back(uv1[1]);
                    m_textureCoord->push_back(uv2[0]);
                    m_textureCoord->push_back(uv2[1]);
                }
            }
        }
    }

    bool Fr_Widget::SetupTexture2D() {
        //Dummy code does nothing should be sub-classed
        /*(void)info;*/
        return false;
    }

     void Fr_Widget::RenderTexture2D() {
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

    void Fr_Widget::lblDraw(void)
    {
        //Should be subclassed
    }

    void Fr_Widget::lblredraw(void)
    {
        //Should be subclassed
    }

    void Fr_Widget::CalculateNormals(void) {
        // Correct way to calculate the normals but make the screen black

        if (m_vertices->size() % 3 != 0) {
            return; // invalid vertex data
        }
        if (!m_normals) {
            m_normals = std::make_shared<std::vector<float>>(m_vertices->size(), 0.0f);
        }
        else {
            m_normals->resize(m_vertices->size());
            std::fill(m_normals->begin(), m_normals->end(), 0.0f);
        }
        size_t vertexCount = m_vertices->size() / 3;
        if (!m_indices || m_indices->empty()) {
            return;
        }
        if (m_indices->size() % 3 == 0) {
            std::vector<glm::vec3> pre_normals(vertexCount, glm::vec3(0.0f));
            for (size_t i = 0; i + 2 < m_indices->size(); i += 3) {
                unsigned int v0 = m_indices->at(i);
                unsigned int v1 = m_indices->at(i + 1);
                unsigned int v2 = m_indices->at(i + 2);

                if (v0 >= vertexCount || v1 >= vertexCount || v2 >= vertexCount)
                    continue;

                glm::vec3 p0(
                    m_vertices->at(v0 * 3),
                    m_vertices->at(v0 * 3 + 1),
                    m_vertices->at(v0 * 3 + 2));
                glm::vec3 p1(
                    m_vertices->at(v1 * 3),
                    m_vertices->at(v1 * 3 + 1),
                    m_vertices->at(v1 * 3 + 2));
                glm::vec3 p2(
                    m_vertices->at(v2 * 3),
                    m_vertices->at(v2 * 3 + 1),
                    m_vertices->at(v2 * 3 + 2));

                glm::vec3 faceNormal = glm::cross(p1 - p0, p2 - p0);
                if (glm::dot(faceNormal, faceNormal) < 1e-12f)
                    continue;
                pre_normals[v0] += faceNormal;
                pre_normals[v1] += faceNormal;
                pre_normals[v2] += faceNormal;
            }

            // Normalize accumulated vertex normals
            for (size_t i = 0; i < vertexCount; ++i) {
                glm::vec3 n = pre_normals[i];
                if (glm::dot(n, n) > 1e-12f)
                    n = glm::normalize(n);

                (*m_normals)[i * 3 + 0] = n.x;
                (*m_normals)[i * 3 + 1] = n.y;
                (*m_normals)[i * 3 + 2] = n.z;
            }
        }
        else if (m_indices->size() % 2 == 0) {
            for (size_t i = 0; i + 1 < m_indices->size(); i += 2) {
                unsigned int v0 = m_indices->at(i);
                unsigned int v1 = m_indices->at(i + 1);
                if (v0 >= vertexCount || v1 >= vertexCount)
                    continue;
                glm::vec3 p0(
                    m_vertices->at(v0 * 3),
                    m_vertices->at(v0 * 3 + 1),
                    m_vertices->at(v0 * 3 + 2));
                glm::vec3 p1(
                    m_vertices->at(v1 * 3),
                    m_vertices->at(v1 * 3 + 1),
                    m_vertices->at(v1 * 3 + 2));
                glm::vec3 dir = glm::normalize(p1 - p0);
                glm::vec3 normal;
                if (std::abs(dir.z) < 1e-6f) {
                    normal = glm::vec3(-dir.y, dir.x, 0.0f);
                }
                else {
                    glm::vec3 up(0.0f, 0.0f, 1.0f);
                    normal = glm::normalize(glm::cross(dir, up));
                }
                (*m_normals)[v0 * 3 + 0] = normal.x;
                (*m_normals)[v0 * 3 + 1] = normal.y;
                (*m_normals)[v0 * 3 + 2] = normal.z;

                (*m_normals)[v1 * 3 + 0] = normal.x;
                (*m_normals)[v1 * 3 + 1] = normal.y;
                (*m_normals)[v1 * 3 + 2] = normal.z;
            }
        }
        else {
            std::fill(m_normals->begin(), m_normals->end(), 0.0f);
        }
    }

    void Fr_Widget::NormalizeVertices(void) {
        if (!m_vertices) {
            throw std::runtime_error("ERROR: m_vertices are not initialized");
        }

        constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
        constexpr float FLOAT_MIN = -FLOAT_MAX;

        glm::vec3 m_min(FLOAT_MAX, FLOAT_MAX, FLOAT_MAX);
        glm::vec3 m_max(FLOAT_MIN, FLOAT_MIN, FLOAT_MIN);

        for (size_t i = 0; i < m_vertices->size(); i += 3) {
            if (i + 2 >= m_vertices->size()) {
                break;
            }

            m_min.x = std::min(m_min.x, m_vertices->at(i));       // x
            m_min.y = std::min(m_min.y, m_vertices->at(i + 1));   // y
            m_min.z = std::min(m_min.z, m_vertices->at(i + 2));   // z

            m_max.x = std::max(m_max.x, m_vertices->at(i));       // x
            m_max.y = std::max(m_max.y, m_vertices->at(i + 1));   // y
            m_max.z = std::max(m_max.z, m_vertices->at(i + 2));   // z
        }
        glm::vec3 range = m_max - m_min;
        if (range.x == 0 && range.y == 0 && range.z == 0) {
            //we have zero range, fill all vertices to zero
            std::fill(m_vertices->begin(), m_vertices->end(), 0.0f);
            //TODO : CHECK ME - WHEN THIS CAN HAPPEN, AND WHY? DO WE DO A CORRECT DECISISION? !!!
            return;
        }
        for (size_t i = 0; i < m_vertices->size(); i += 3) {
            if (i + 2 >= m_vertices->size()) {
                break;
            }

            glm::vec3 vertex(
                m_vertices->at(i),
                m_vertices->at(i + 1),
                m_vertices->at(i + 2)
            );

            // Normalize the vertex to fit between -1 and 1
            glm::vec3 normalized = (vertex - m_min) / range * 2.0f - 1.0f;
            m_vertices->at(i) = normalized.x;
            m_vertices->at(i + 1) = normalized.y;
            m_vertices->at(i + 2) = normalized.z;
        }
    }
}