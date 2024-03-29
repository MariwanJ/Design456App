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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <fr_mesh.h>

Mesh::Mesh(const std::string& path) :
    vbo_{ 0, 0, 0 },
    vao_(0), normalized_(false) {
    ReadFile(path, vertices_, normals_, indices_);
    InitializeVBO();
}
Mesh::Mesh() : vbo_{ 0, 0, 0, 0 }, vao_(0) {
}

Mesh::~Mesh() {
    if (vao_ != 0) {
        glCheckFunc(glDeleteVertexArrays(1, &vao_));
        glCheckFunc(glDeleteBuffers(3, vbo_));
    }
}

void Mesh::Draw() {
    glCheckFunc(glBindVertexArray(vao_));
    glCheckFunc(glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0));
    glCheckFunc(glBindVertexArray(0));
}

void Mesh::GetMesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<unsigned int>& indices) {
    vertices = vertices_;
    normals = normals_;
    indices = indices_;
}

void Mesh::SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    vertices_ = vertices;
    indices_ = indices;
}
/**
 * Change verticies size to be inbetween -1 and 1.
 * This is left as an option might not be used.
 * Call this before reading the mesh.
 * \param value
 */
void Mesh::SetNormalizeMesh(bool value)
{
    normalized_ = true;
}

bool Mesh::getNormalizeMesh()
{
    return normalized_;
}

glm::vec3 Mesh::GetVertex(unsigned int index, const float vertices[]) {
    return glm::vec3(
        vertices[index * 3],
        vertices[index * 3 + 1],
        vertices[index * 3 + 2]
    );
}

void Mesh::SetVertex(unsigned int index, float vertices[], const glm::vec3& vertex) {
    vertices[index * 3] = vertex[0];
    vertices[index * 3 + 1] = vertex[1];
    vertices[index * 3 + 2] = vertex[2];
}

void Mesh::ReadFile(const std::string& path, std::vector<float>& vertices,
    std::vector<float>& normals, std::vector<unsigned int>& indices) {
    std::string extension = path.substr(path.rfind('.'));
    if (extension == ".off") {
        ReadOFF(path, vertices, indices);
        if (normalized_) {
            CalculateNormals(vertices, indices, normals);
            NormalizeVertices(vertices_);
        }
    }
    else if (extension == ".msh") {
        ReadMSH(path, vertices, normals, indices);
    }
    else {
        throw std::runtime_error("Unknown mesh extension: " + extension);
    }
}

void Mesh::ReadOFF(const std::string& path, std::vector<float>& vertices,
    std::vector<unsigned int>& indices) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    input.open(path);

    size_t nVertices, nTriangles, nQuads;
    input.ignore(3);
    input >> nVertices >> nTriangles >> nQuads;

    vertices.resize(nVertices * 3);
    for (size_t i = 0; i < vertices.size(); ++i)
        input >> vertices[i];

    indices.resize((nTriangles + 2 * nQuads) * 3);
    size_t idx = 0;
    for (size_t i = 0; i < nTriangles + nQuads; ++i) {
        int polygon;
        input >> polygon;

        if (polygon == 3) {
            m_MeshType = FR_POLYGON;
            input >> indices[idx++];
            input >> indices[idx++];
            input >> indices[idx++];
        }
        else {
            m_MeshType = FR_QUAD;
            float quad[4];
            input >> quad[0] >> quad[1] >> quad[2] >> quad[3];
            indices[idx++] = quad[0];
            indices[idx++] = quad[1];
            indices[idx++] = quad[2];
            indices[idx++] = quad[2];
            indices[idx++] = quad[3];
            indices[idx++] = quad[0];
        }
    }
    int totalInd = 2 * vertices_.size() / 9;
    textcoord_.reserve(totalInd); //2dimention, 
    textcoord_.assign(totalInd, 0.0); //coord 1,1
}

void Mesh::ReadMSH(const std::string& path, std::vector<float>& vertices,
    std::vector<float>& normals, std::vector<unsigned int>& indices) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    input.open(path);

    size_t nVertices, nTriangles;
    input >> nVertices >> nTriangles;

    vertices.resize(nVertices * 3);
    normals.resize(nVertices * 3);
    for (size_t i = 0; i < nVertices; ++i) {
        int id;
        input >> id;
        input >> vertices[3 * i]
            >> vertices[3 * i + 1]
            >> vertices[3 * i + 2];
        input >> normals[3 * i]
            >> normals[3 * i + 1]
            >> normals[3 * i + 2];
    }

    indices.resize(nTriangles * 3);
    for (size_t i = 0; i < nTriangles; ++i) {
        int id;
        input >> id;
        input >> indices[3 * i]
            >> indices[3 * i + 1]
            >> indices[3 * i + 2];
    }
    int totalInd = 2 * vertices_.size() / 9;
    textcoord_.reserve(totalInd); //2dimention, 
    textcoord_.assign(totalInd, 0.0); //coord 1,1
}

void Mesh::NormalizeVertices(std::vector<float>& vertices) {
    glm::vec3 min(std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    float max = std::numeric_limits<float>::min();

    for (size_t i = 0; i < vertices.size(); i += 3) {
        for (size_t j = 0; j < 3; ++j) {
            min[j] = std::min(min[j], vertices[i + j]);
            max = std::max(max, vertices[i + j] - min[j]);
        }
    }

    for (size_t i = 0; i < vertices.size() / 3; ++i) {
        glm::vec3 vertex = GetVertex(i, vertices.data());
        glm::vec3 normalized = (vertex - min) / max - 0.5f;
        SetVertex(i, vertices.data(), normalized);
    }
}

void Mesh::CalculateNormals(const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    std::vector<float>& normals) {
    // Initialize the normals
    std::vector<glm::vec3> pre_normals(vertices.size() / 3);
    for (size_t i = 0; i < pre_normals.size(); ++i) {
        pre_normals[i] = { 0, 0, 0 };
    }

    // Calculate the normals for each triangle vertex
    for (size_t i = 0; i < indices.size() - 3; i += 3) {
        // Triangle vertices' indices
        unsigned int v[3] = { indices[i], indices[i + 1], indices[i + 2] };

        // Triangle's vertices
        glm::vec3 triangle[3] = {
            GetVertex(v[0], vertices.data()),
            GetVertex(v[1], vertices.data()),
            GetVertex(v[2], vertices.data())
        };

        // Vectors created by the triangle's vertexes
        glm::vec3 v0_to_v1 = triangle[1] - triangle[0];
        glm::vec3 v0_to_v2 = triangle[2] - triangle[0];
        glm::vec3 v1_to_v2 = triangle[2] - triangle[1];

        auto angleBetween = [](const glm::vec3& u, const glm::vec3& v) {
            return acos(glm::dot(u, v) / (glm::length(u) * glm::length(v)));
            };

        // Angle between the vectors
        float angle[3];
        angle[0] = angleBetween(v0_to_v1, v0_to_v2);
        angle[1] = angleBetween(v1_to_v2, -v0_to_v1);
        angle[2] = M_PI - angle[0] - angle[1];

        // Triangle's normal
        glm::vec3 t_normal = glm::normalize(glm::cross(v0_to_v1, v0_to_v2));

        // Vertex normal += triangle normal * vertex angle in the triangle
        for (size_t j = 0; j < 3; ++j)
            pre_normals[v[j]] = pre_normals[v[j]] + t_normal * angle[j];
    }

    normals.resize(vertices.size());
    for (size_t i = 0; i < pre_normals.size(); ++i)
        SetVertex(i, normals.data(), glm::normalize(pre_normals[i]));
}

void Mesh::InitializeVBO(){
    glCheckFunc(glGenBuffers(NUM_OF_VBO_BUFFERS, vbo_)); //3 
glCheckFunc(glGenVertexArrays(1, &vao_));
glCheckFunc(glBindVertexArray(vao_));
//VERTICIES 
glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]));
glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertices_.size(), vertices_.data(), GL_STATIC_DRAW));
glCheckFunc(glEnableVertexAttribArray(FR_POSITION_VB));
glCheckFunc(glVertexAttribPointer(FR_POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL));                //POSITION_VB = 0

///Texture 
glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]));
glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float)* textcoord_.size(), textcoord_.data(), GL_STATIC_DRAW));
glCheckFunc(glEnableVertexAttribArray(FR_TEXCOORD_VB));
glCheckFunc(glVertexAttribPointer(FR_TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, NULL));        //TEXCOORD_VB=1   NOTE: SHADER MUST HAVE THE SAME SEQUENCE

//this is the object shader - look at the shader, it uses uniform. so the binding MUST be uniform
//NORMALS
glCheckFunc(glBindBuffer(GL_UNIFORM_BUFFER, vbo_[2]));          //Using GL_UNIFORM_BUFFER draw the line around the object but now nothing? why?
glCheckFunc(glBufferData(GL_UNIFORM_BUFFER, sizeof(float)* normals_.size(), normals_.data(), GL_STATIC_DRAW));

//?? Not sure for what purpose we send this??
glCheckFunc(glEnableVertexAttribArray(2));
glCheckFunc(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL));
glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[3]));
glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW));
glCheckFunc(glBindVertexArray(0));
}


meshType Mesh::getMeshType()
{
    return m_MeshType;
}
