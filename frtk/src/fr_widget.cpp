﻿#include "fr_widget.h"
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
#include <frtk.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace FR {
    //Constructor
    Fr_Widget::Fr_Widget(std::shared_ptr<std::vector <float>> verticies,
        std::shared_ptr<std::vector <unsigned int>> indicies,
        std::string label) :m_vertices(std::move(verticies)),
        m_Matrix(glm::mat4(1.0f)), m_indices(std::move(indicies)), m_vao(0), m_vbo{ 0 },
        m_lineWidth(1), m_pointSize(10)
    {
        m_lineType = FR_NOT_DEFINED; //You should define it before use it

        m_vertCoord = NULL;          //must be calculated internally
        m_normals = NULL;
        m_textCoord = NULL;
        m_shader = { 0 };
        m_callback_ = NULL;
        m_boundBox = nullptr;

        m_label.text = "";
        m_label.fnFont = NULL;// we cannot define it here

        m_label.color = glm::vec4(FR_YELLOW);
        m_label.offset = glm::vec3(0.0f);
        m_label.visible = false; //we don't have font .. disable it you should enabled when you subclass
        m_label.pixelSize = 256;  //size of the pixels -- TODO : HOW MUCH WE SHOULD PUT HERE !!!!!!!!!!!
        m_label.scale = 0.046875f;
        m_label.text = "Change me - Widget say hello";
        m_label.type = PERSPECTIVE;//ORTHOGRAPHIC;

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
        m_selected = std::make_shared <std::vector<size_t>>(); // this is boolean but since boolean is not ok for opengl
        m_shader = std::make_shared<Shader_t>();
    }

    void Fr_Widget::LoadFont(const std::string& fontPath)
    {
        Characters.clear(); // Clear previous font glyphs
        m_label.fnFont.reset(); // Clear old path (remove)
        m_label.fnFont = std::make_shared<std::string>(fontPath);

        static FT_Library ft;
        static bool ftInitialized = false;
        if (!ftInitialized) {
            if (FT_Init_FreeType(&ft)) {
                FRTK_CORE_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
                return;
            }
            ftInitialized = true;
        }

        FT_Face face = nullptr;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
            FRTK_CORE_ERROR("ERROR::FREETYPE: Failed to load font: {}", fontPath);
            return;
        }

        //FT_Set_Pixel_Sizes(face, m_label.pixelSize, m_label.pixelSize);
        FT_Set_Pixel_Sizes(face, 0, 200);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (unsigned char c = 0; c < 128; ++c) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                FRTK_CORE_ERROR("Failed to load Glyph:{} ", c);
                continue;
            }

            // Create an RGBA bitmap
            int width = face->glyph->bitmap.width;
            int height = face->glyph->bitmap.rows;
            std::vector<uint8_t> bitmapRGBA(width * height * 4, 0); // RGBA

            // Populate the RGBA bitmap based on the alpha channel
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int index = (y * width + x) * 4; // RGBA index
                    uint8_t alpha = face->glyph->bitmap.buffer[y * width + x];
                    uint8_t colorValue = 255; // Set your desired color value here (e.g., white)

                    // Set RGBA based on alpha
                    if (alpha > 128) { // Threshold for alpha
                        bitmapRGBA[index] = colorValue;     // Red
                        bitmapRGBA[index + 1] = colorValue; // Green
                        bitmapRGBA[index + 2] = colorValue; // Blue
                        bitmapRGBA[index + 3] = 255;         // Fully opaque
                    }
                    else {
                        bitmapRGBA[index] = 0;               // Transparent
                        bitmapRGBA[index + 1] = 0;
                        bitmapRGBA[index + 2] = 0;
                        bitmapRGBA[index + 3] = 0;           // Fully transparent
                    }
                }
            }

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA, // Change to RGBA format
                width,
                height,
                0,
                GL_RGBA, // Change to RGBA format
                GL_UNSIGNED_BYTE,
                bitmapRGBA.data() // Use the RGBA bitmap
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character_t ch = {
                tex,
                glm::ivec2(width, height),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (GLuint)face->glyph->advance.x
            };

            Characters.insert(std::make_pair(c, ch));
        }

        glBindTexture(GL_TEXTURE_2D, 0);

#if 0	//For debugging only
        printStringAsDots(m_label.text, face);
#endif
        FT_Done_Face(face);

        *m_label.fnFont = fontPath; // Update current font name
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
                float quad[4];              /// This is really not supported yet
                input >> quad[0] >> quad[1] >> quad[2] >> quad[3];
                m_indices->at(idx++) = quad[0];
                m_indices->at(idx++) = quad[1];
                m_indices->at(idx++) = quad[2];
                m_indices->at(idx++) = quad[2];
                m_indices->at(idx++) = quad[3];
                m_indices->at(idx++) = quad[0];
            }
        }
        // Add vertices
        std::vector<MyMesh::VertexHandle> vhandles;
        vhandles.reserve(nVertices);
        for (size_t i = 0; i < nVertices; ++i) {
            MyMesh::Point p((*m_vertices)[3 * i], (*m_vertices)[3 * i + 1], (*m_vertices)[3 * i + 2]);
            vhandles.push_back(m_mesh.add_vertex(p));
        }

        // Add faces
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

        // Reserve space for vertices and indices
        m_vertices->reserve(m_mesh.n_vertices() * 3);
        m_indices->reserve(m_mesh.n_faces() * 3); // TODO: We need to make sure there are only 3 vert/obj

        // Obtain the vertex positions from the mesh
        for (auto vit = m_mesh.vertices_begin(); vit != m_mesh.vertices_end(); ++vit) {
            MyMesh::Point p = m_mesh.point(*vit);
            m_vertices->emplace_back(static_cast<float>(p[0]));
            m_vertices->emplace_back(static_cast<float>(p[1]));
            m_vertices->emplace_back(static_cast<float>(p[2]));
        }

        // Obtain the face indices from the mesh
        for (auto fit = m_mesh.faces_begin(); fit != m_mesh.faces_end(); ++fit) {
            for (auto fvit = m_mesh.fv_iter(*fit); fvit; ++fvit) {
                m_indices->emplace_back(fvit.handle().idx());
            }
        }
    }

    void Fr_Widget::init(void) {
        assert(!m_vertices->empty(), "ERROR: You should provide verticies before initializing the object");

        std::string shaderpath = EXE_CURRENT_DIR + "/resources/shaders/";
        m_shader->wdg_prog = std::make_shared <ShaderProgram>(shaderpath + "wdgshader");
        m_shader->silhouette_prog = std::make_shared <ShaderProgram>(shaderpath + "silhouette");
        m_shader->texture_prog = std::make_shared <ShaderProgram>(shaderpath + "texture");
        m_shader->widgPoits_prog = std::make_shared <ShaderProgram>(shaderpath + "widgPoints");
        m_shader->txtFont_program = std::make_shared <ShaderProgram>(shaderpath + "txtFont");
        m_label.fnFont = std::make_shared <std::string>(DEFAULT_FONT); // DEFAULT FONT
        m_label.text = "Widget";

        //create bound box
        m_boundBox = std::make_shared <cBoundBox3D>();
        m_boundBox->setVertices(m_vertices);
        CalculateNormals();
        calcualteTextCoor(1024, 1024);  //TODO:  ??? dont think it is correct

        initializeVBO();
        CreateShader();
        LoadFont(DEFAULT_FONT); //TODO: Do we need to allow other font at the creation, don't think so.

        //Selection of vertices : TODO: MAKE ME MORE GENERAL .. NOT JUST VERTICEIS
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
        m_shader->wdg_prog = std::make_shared<ShaderProgram>(shaderpath + "wdgshader");
        m_shader->widgPoits_prog = std::make_shared<ShaderProgram>(shaderpath + "widgPoints");
        m_shader->silhouette_prog = std::make_shared<ShaderProgram>(shaderpath + "silhouette");
        m_shader->texture_prog = std::make_shared<ShaderProgram>(shaderpath + "texture");
        m_shader->txtFont_program = std::make_shared<ShaderProgram>(shaderpath + "txtFont");
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
    void Fr_Widget::label(const char* lbl)
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
        m_label.pixelSize = size_;
    }

    void Fr_Widget::fontColor(glm::vec4 col)
    {
        m_label.color = col;
    }
    void Fr_Widget::fontColor(float r, float g, float b, float a)
    {
        m_label.color = glm::vec4(r, g, b, a);
    }

    void Fr_Widget::lblOffset(glm::vec3 nval)
    {
        m_label.offset = nval;
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
    // Method to retrieve a shared pointer to the vector of vertices
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

        if (!m_textCoord) {
            m_textCoord = std::make_shared<std::vector<float>>();
        }
        //The size is 2x (verticies_size/3)
        m_textCoord->reserve(2 * m_vertices->size() / 3);
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
            //we have zero range, fill all verticies to zero 
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

            // Store normalized values back in m_vertices
            m_vertices->at(i) = normalized.x;
            m_vertices->at(i + 1) = normalized.y;
            m_vertices->at(i + 2) = normalized.z;
        }
    }
}