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

#include <../src/halfEdge/fr_new_mesh.h>
#include <../src/Fr_GL3Window.h>

Shape::Shape(const std::string& path) :
    vbo_{ 0, 0, 0 },
    vao_(0), normalized_(false) {
    ReadFile(path, vertices_, normals_, indices_);
    InitializeVBO(vertices_, normals_, indices_);
    linktoMainWindow = Fr_GL3Window::getfr_Gl3Window();
}
Shape::Shape() : vbo_{ 0, 0, 0 }, vao_(0), id(0), normalized_(false) {
}

Shape::~Shape() {
    if (vao_ != 0) {
        glCheckFunc(glDeleteVertexArrays(1, &vao_));
        glCheckFunc(glDeleteBuffers(3, vbo_));
    }
}


int Shape::build()
{
    //TODO : FIXME : NOT FINISHED

    std::vector<std::shared_ptr<mesh_face>> faces;
    std::vector < std::shared_ptr < mesh_halfedge>> hedg;
    std::vector < std::shared_ptr < mesh_vertex>> vert_e;
    for(unsigned int i=0;i<nTriangles;i++){
        std::shared_ptr <mesh_face>tempSh= std::make_shared <mesh_face>();
        tempSh->fshape = this;
        faces.push_back(tempSh);
    }
    for (unsigned int i = 0; i < nTriangles-1; i++) {
        faces[i]->next= faces[i+1];
    }
    faces[nTriangles - 1]->next = faces[0];

    for (unsigned int i = 1; i < nTriangles; i++) {
        faces[i]->prev = faces[i- 1];
    }
    faces[0]->prev = faces[nTriangles-1];
    for (unsigned int i = 0; i < nTriangles *3; i++) {
        hedg.push_back(std::make_shared <mesh_halfedge>());
    }
    for (unsigned int i = 0; i < nVertexes; i++) {
        vert_e.push_back(std::make_shared <mesh_vertex>());
    }

    //make a loop of the faces
    faces[nTriangles - 1]->next = faces[0];
    faces[0]->prev = faces[nTriangles - 1];
    
    //create the vertexes in the same order as the verticies
    unsigned int faceNo = 0;
    for (unsigned int i = 0; i < nVertexes; i++) {
        vert_e[i]->vertexValue = glm::vec3(vertices_[i*3 + 1], vertices_[i*3 + 1], vertices_[i*3 + 2]);
    }
    for (unsigned int i = 0; i < nTriangles; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            hedg[3*i+j]->vertex = vert_e[indices_[i + j]];
        }
    }

    //half edges build
    for (unsigned int i = 0; i < nTriangles; i++) {
        for (unsigned int j = 0; j < 3; j++) {

            //half edges connection to vertexes
            hedg[i + j]->face = faces[i];
            hedg[i + j]->face = faces[i];
            hedg[i + j]->face = faces[i];
        }
    }
    for (unsigned int i = 0; i < nTriangles*3; i=i+3) {
            //half-edge loop inside each face
            hedg[i]->next = hedg[i + 1];
            hedg[i + 1]->next = hedg[i + 2];
            hedg[i + 2]->next = hedg[i];
        }
    
    for (unsigned int i = 0; i < nTriangles*3;i= i + 3) {
        //half-edge loop in reverse for each face
        hedg[i]->prev = hedg[i + 2];
        hedg[i+1]->prev = hedg[i ];
        hedg[i+2]->prev = hedg[i + 1];
    }



    //half-edge twin build - the most difficult

    for (unsigned int i = 0; i < nTriangles * 3; i++) {
        for (unsigned int j = i + 1; j < nTriangles * 3; j++) {
            if ((hedg[i]->vertex->vertexValue == hedg[j]->next->vertex->vertexValue) && hedg[i]->face != hedg[j]->face)
            {
                hedg[i]->twin = hedg[j];
                break;
            }
        }
        //CONTINUE TO DEVELOP THIS.
    }
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

void Shape::ReadOFF(const std::string& path, std::vector<float>& vertices,
    std::vector<unsigned int>& indices) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    input.open(path);

    input.ignore(3);  
    input >> nVertexes >> nTriangles >> nQuads;

    vertices.resize(nVertexes * 3);
    for (size_t i = 0; i < vertices.size(); ++i)
        input >> vertices[i];

    indices.resize((nTriangles + 2 * nQuads) * 3);
    size_t idx = 0;
    for (size_t i = 0; i < nTriangles + nQuads; ++i) {
        int polygon;
        input >> polygon;

        if (polygon == 3) {
            input >> indices[idx++];
            input >> indices[idx++];
            input >> indices[idx++];
        }
        else {
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

int Shape::updateVerticies(void)
{
    return 0;
}

mesh_vertex::mesh_vertex():vertexValue(glm::vec3(0.0, 0.0, 0.0)),
                            visible(true)
{
}

mesh_vertex::~mesh_vertex()
{
}

mesh_halfedge::mesh_halfedge() 
{
}

mesh_halfedge::~mesh_halfedge()
{
    
}

mesh_face::mesh_face() :ID(0),
visible(true),
selected(false),
normal(glm::vec3(0.0, 0.0, 0.0))
{
}

mesh_face::~mesh_face()
{
}
 