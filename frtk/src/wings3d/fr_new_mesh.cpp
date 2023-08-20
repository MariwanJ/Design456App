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

#include <wings3d/fr_new_mesh.h>

Shape::Shape(const std::string& path) :
    vbo_{0, 0, 0},
    vao_(0),normalized_(false) {
    ReadFile(path, vertices_, normals_, indices_);
    InitializeVBO(vertices_, normals_, indices_);

}
Shape::Shape(): vbo_{ 0, 0, 0 }, vao_(0),id(0), normalized_(false){
}

Shape::~Shape() {
    if (vao_ != 0) {
        glCheckFunc(glDeleteVertexArrays(1, &vao_));
        glCheckFunc(glDeleteBuffers(3, vbo_));
    }
}

int Shape::build()
{
    std::vector<std::shared_ptr<struct face>> 	 fs;				 //gb_tree containing faces
    std::vector<std::shared_ptr<struct edge>> 	 es;				 //gb_tree containing edges
    std::vector<std::shared_ptr<glm::vec3>> 	 vs;		         //gb_tree containing vertices
    std::vector < std::shared_ptr<struct edge>> he;					 //gb_sets containing hard edges
    unsigned int totalVert= vertices_.size();
    //Verticies
    for (unsigned i = 0; i < totalVert; i++) {
        std::shared_ptr<glm::vec3> vstemp=std::make_shared<glm::vec3>(glm::vec3(vertices_[i], vertices_[i + 1], vertices_[i + 2]));
        vs.push_back(vstemp);
    }

    //Edges    
    for (unsigned i = 0; i < totalVert -3; i = i + 3) {
            std::shared_ptr<struct edge> ed = std::make_shared <struct edge>();
            ed->vs = glm::vec3(vertices_[i], vertices_[i + 1], vertices_[i + 2]);       //start
            ed->ve = glm::vec3(vertices_[i + 3], vertices_[i + 4], vertices_[i + 5]);   //end
            es.push_back(ed);
        }
        //add last verticies
        std::shared_ptr<struct edge> ed = std::make_shared <struct edge>();
        ed->vs = glm::vec3(vertices_[totalVert-3], vertices_[totalVert-2], vertices_[totalVert-1]);       //start
        ed->ve = glm::vec3(vertices_[0], vertices_[1], vertices_[2]);   //end
        es.push_back(ed);


    
    return 0;// TODO:FIXME: check this return if it should be somehting else
}

void Shape::Draw() {
    glCheckFunc(glBindVertexArray(vao_));
    glCheckFunc(glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0));
    glCheckFunc(glBindVertexArray(0));
}

void Shape::GetMesh(std::vector<float>& vertices, std::vector<float>& normals, std::vector<unsigned int>& indices) {
    vertices = vertices_;
    normals = normals_;
    indices = indices_;

}

void Shape::SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices) {  
    vertices_ = vertices;
    indices_ = indices;
}
/**
 * Change verticies size to be inbetween -1 and 1.
 * This is left as an option might not be used. 
 * Call this before reading the mesh.
 * \param value
 */
void Shape::SetNormalizeMesh(bool value)
{
    normalized_ = true;
}

bool Shape::getNormalizeMesh()
{
    return normalized_;
}


glm::vec3 Shape::GetVertex(unsigned int index, const float vertices[]) {
    return glm::vec3(
        vertices[index * 3],
        vertices[index * 3 + 1],
        vertices[index * 3 + 2]
    );
}

void Shape::SetVertex(unsigned int index, float vertices[], const glm::vec3& vertex) {
    vertices[index * 3] = vertex[0];
    vertices[index * 3 + 1] = vertex[1];
    vertices[index * 3 + 2] = vertex[2];
}

void Shape::ReadFile(const std::string& path, std::vector<float>& vertices,
        std::vector<float>& normals, std::vector<unsigned int>& indices) {
    std::string extension = path.substr(path.rfind('.'));
    if (extension == ".off") {
        ReadOFF(path, vertices, indices);
        if (normalized_){
        CalculateNormals(vertices, indices, normals);
        NormalizeVertices(vertices_);
        }
    } else if (extension == ".msh") {
        ReadMSH(path, vertices, normals, indices);
    } else {
        throw std::runtime_error("Unknown mesh extension: " + extension);
    }
}

void Shape::ReadOFF(const std::string& path, std::vector<float>& vertices,
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
    
    indices.resize( (nTriangles + 2 * nQuads) * 3 );
    size_t idx = 0;
    for (size_t i = 0; i < nTriangles + nQuads; ++i) {
        int polygon;
        input >> polygon;

        if (polygon == 3) {
            input >> indices[idx++];
            input >> indices[idx++];
            input >> indices[idx++];
        } else {
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
}

void Shape::ReadMSH(const std::string& path, std::vector<float>& vertices,
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
}

void Shape::NormalizeVertices(std::vector<float>& vertices) {
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

void Shape::CalculateNormals(const std::vector<float>& vertices, 
                            const std::vector<unsigned int>& indices, 
                            std::vector<float>& normals) {

    // Initialize the normals
    std::vector<glm::vec3> pre_normals(vertices.size() / 3);
    for (size_t i = 0; i < pre_normals.size(); ++i) {
        pre_normals[i] = {0, 0, 0};
    }

    // Calculate the normals for each triangle vertex
    for (size_t i = 0; i < indices.size()-3; i += 3) {
        // Triangle vertices' indices
        unsigned int v[3] = {indices[i], indices[i + 1], indices[i + 2]};

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

void Shape::InitializeVBO(const std::vector<float>& vertices,
                            const std::vector<float>& normals,
                            const std::vector<unsigned int> indices) {

    glCheckFunc(glGenBuffers(3, vbo_));
    glCheckFunc(glGenVertexArrays(1, &vao_));
    glCheckFunc(glBindVertexArray(vao_));
    
    glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]));
    glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW));
    glCheckFunc(glEnableVertexAttribArray(0));
    glCheckFunc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
    
    glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]));
    glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW));
    glCheckFunc(glEnableVertexAttribArray(1));
    glCheckFunc(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL));

    glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]));
    glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
    
    glCheckFunc(glBindVertexArray(0));
}

