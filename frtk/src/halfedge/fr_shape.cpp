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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <halfedge/fr_shape.h>
#include <fr_window.h>

namespace FR {
    static const glm::mat4 kShadowMapBiasMatrix(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0);

    Fr_Shape::Fr_Shape(const std::string& fpath, glm::vec4 color, float silhouette) :Fr_Widget(NULL, NULL, "Shape"),
        linktoMainWindow(NULL), normalized_(false)
    {
        m_label = std::make_shared<Fr_Label>(); //default constructor with default values

        if (!m_shader) {
            m_shader = std::make_shared<Shader_t>();
        }
        if (std::filesystem::exists(fpath))
        {
            ReadFile(fpath); //Read vertices
        }
        else if (fpath.substr(0, 3) == "OFF") {
            ReadMeshString(fpath);
        }
        else {
            FRTK_CORE_APP_ASSERT("ERROR: No mesh provided to the class");
        }
        init(); //This will initializes all Openmesh, vertices, edget ..etc

        if (m_label) {
            m_label->pos(glm::vec3(m_boundBox->minX(), m_boundBox->maxY(), 0.0f));
            m_label->LoadFont();
        }
        m_WidgType = NODETYPE::FR_SHAPE;
    }
#if 0 //For debugging only

    void printCharacterAsDots(FT_GlyphSlot glyph) {
        int width = glyph->bitmap.width;
        int height = glyph->bitmap.rows;

        // Loop through each pixel in the bitmap
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                uint8_t alpha = glyph->bitmap.buffer[y * width + x];
                // Print a dot for opaque pixels, otherwise print a space
                if (alpha > 128) {
                    std::cout << ".";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl; // New line for the next row
        }
    }

    void printStringAsDots(const std::string& text, FT_Face face) {
        for (char c : text) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Failed to load Glyph: " << c << std::endl;
                continue;
            }
            std::cout << "Character: " << c << std::endl;
            printCharacterAsDots(face->glyph);
            std::cout << std::endl; // Space between characters
        }
    }
#endif

    //Default constructor with no vertices defined
    Fr_Shape::Fr_Shape() : Fr_Widget(NULL, NULL, "") {
    }

    Fr_Shape::~Fr_Shape() {
        //Think about cleanup here ?????

/*        if (m_vao != 0) {
            glCheckFunc(glDeleteVertexArrays(1, &m_vao));
            glCheckFunc(glDeleteBuffers(NUM_OF_VBO_BUFFERS, m_vbo));
        }
        */
    }

    void Fr_Shape::draw() {
        initializeVBO();
        glCheckFunc(glBindVertexArray(m_vao));
        glCheckFunc(glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, 0));
        glCheckFunc(glBindVertexArray(0));
    }

    void Fr_Shape::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights) {
        unsigned int nlights = (unsigned int)(std::min(lights.size(), kMaxLights));
        program->SetUniformInteger("nlights", nlights);
        for (size_t i = 0; i < nlights; ++i) {
            auto uniformVarNameInObjShader = "lights[" + std::to_string(i) + "].";
            program->SetUniformVec4(uniformVarNameInObjShader + "color", lights[i].lightcolor);
            program->SetUniformVec4(uniformVarNameInObjShader + "position", lights[i].position);       //Here we send the name of the variable as "lights[xxx=number]." wher xxx= a number from 0 to nlights
            program->SetUniformVec4(uniformVarNameInObjShader + "diffuse", lights[i].diffuse);
            program->SetUniformVec4(uniformVarNameInObjShader + "specular", lights[i].specular);
            program->SetUniformVec4(uniformVarNameInObjShader + "ambient", lights[i].ambient);
            program->SetUniformVec3(uniformVarNameInObjShader + "attenuation", lights[i].attenuation);
            program->SetUniformInteger(uniformVarNameInObjShader + "is_spot", lights[i].is_spot);
            program->SetUniformVec3(uniformVarNameInObjShader + "direction", lights[i].direction);
            program->SetUniformFloat(uniformVarNameInObjShader + "cutoff", lights[i].cutoff);
            program->SetUniformFloat(uniformVarNameInObjShader + "exponent", lights[i].exponent);
            program->SetUniformCamPosition("camPos");
        }
    }

    void Fr_Shape::Render(RenderInfo& info) {
        if (!m_active)
            return;
        //auto mvp = info.projection * info.modelview * m_Matrix; //TODO: This is not correct as modelview = m_Matrix. We should separate these two things.
        auto mvp = info.projection * info.modelview;
        if (m_color.baseColor.a == 1)
            RenderSilhouette(mvp);

        //Render texture also here.
        auto normalmatrix = glm::transpose(glm::inverse(info.modelview));
        m_shader->wdg_prog->Enable();
        m_Texture2D->Bind(0);
        m_shader->wdg_prog->SetUniformInteger("ourTexture", 0);
        LoadLights(m_shader->wdg_prog, info.lights);
        m_shader->wdg_prog->SetUniformMat4("modelview", info.modelview);
        m_shader->wdg_prog->SetUniformMat4("normalmatrix", normalmatrix);
        m_shader->wdg_prog->SetUniformMat4("mvp", mvp);

        std::shared_ptr<FR::Fr_Window> win = FR::Fr_Window::getFr_Window();
        FRTK_CORE_APP_ASSERT(win);
        if (m_mesh.isMeshSelected())
            m_shader->wdg_prog->SetUniformVec4("color", glm::vec4(FR_YELLOW));       //Object color - not light color
        else
            m_shader->wdg_prog->SetUniformVec4("color", m_color.baseColor);       //Object color - not light color
        m_shader->wdg_prog->SetUniformInteger("hasTexture", hasTexture());
        draw();
        m_Texture2D->Unbind();
        m_shader->wdg_prog->Disable();
        info.id++;
        RenderSelection(info);
    }

    void Fr_Shape::RenderSilhouette(const glm::mat4& mvp)
    {
        if (!m_active)
            return;

        m_shader->silhouette_prog->Enable();
        m_shader->silhouette_prog->SetAttribLocation("position", 0);
        m_shader->silhouette_prog->SetAttribLocation("normal", 1);

        m_shader->silhouette_prog->SetUniformMat4("mvp", mvp);
        m_shader->silhouette_prog->SetUniformFloat("silhouette", m_silhouette);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);

        draw();

        glDepthMask(GL_TRUE);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);

        m_shader->silhouette_prog->Disable();
    }

    void Fr_Shape::RenderText(RenderInfo& info) {
        if (m_label) {
            m_label->RenderText(info);
        }
    }
    void Fr_Shape::RenderSelection(RenderInfo& info)
    {
        if (!m_active)
            return;

        auto mvp = info.projection * info.modelview * m_Matrix;

        m_shader->wdg_selection_prog->Enable();
        m_shader->wdg_selection_prog->SetAttribLocation("position", 0);
        m_shader->wdg_selection_prog->SetUniformMat4("mvp", mvp);
        m_shader->wdg_selection_prog->SetUniformVec4("baseColor", m_color.baseColor);
        m_shader->wdg_selection_prog->SetUniformVec4("faceSelectColor", m_color.faceSelectColor);
        m_shader->wdg_selection_prog->SetUniformVec4("edgeSelectColor", m_color.edgeSelectColor);
        m_shader->wdg_selection_prog->SetUniformVec4("vertexSelectColor", m_color.vertexSelectColor);
        m_shader->wdg_selection_prog->SetUniformInteger("selectionMask", (int)m_currentSelMode);
        m_shader->wdg_selection_prog->SetUniformFloat("pointSize", pointSize());

        updateVBO_Selection();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);

        glDisable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(-1.0f, -1.0f);

        draw_2d_sel();

        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_BLEND);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);

        m_shader->wdg_selection_prog->Disable();
    }

    /*
        Hints : how to extract indices from openmesh
        typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;

        int main() {
            MyMesh mesh;

            // Add vertices to the mesh
            MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(0.0, 0.0, 0.0));
            MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(1.0, 0.0, 0.0));
            MyMesh::VertexHandle v3 = mesh.add_vertex(MyMesh::Point(0.0, 1.0, 0.0));

            // Create a face
            mesh.add_face(v1, v2, v3);

            // Extract vertex indices
            std::vector<unsigned int> vertexIndices;
            for (const auto& vh : mesh.vertices()) {
                vertexIndices.push_back(vh.idx());
            }

            // Extract face indices
            std::vector<unsigned int> faceIndices;
            for (const auto& face : mesh.faces()) {
                for (const auto& vh : mesh.fv(face)) {
                    faceIndices.push_back(vh.idx());
                }
            }

            // Output indices
            std::cout << "Vertex Indices:" << std::endl;
            for (const auto& idx : vertexIndices) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;

            std::cout << "Face Indices:" << std::endl;
            for (const auto& idx : faceIndices) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;

            return 0;

    */

    int Fr_Shape::handle(int e) {
        if (!m_active)
            return 0; //we don't use the event/we don't care

        std::shared_ptr<FR::Fr_Window> win = FR::Fr_Window::getFr_Window();
        //TODO : Implement mouse-over for all types, mesh, face, edge, & Vertex.
        switch (e) {
        case FR_MOUSE_MOVE: {
            return 0;//
        }

        case  FR_LEFT_PUSH: {
            ray_t ray = win->activeScene->getRayValue();
            return 0;
        } 

        case FR_KEYBOARD: {
        } break;
        case FR_LEFT_DRAG_PUSH: {
        } break;
        }
        return 0;
    }
}