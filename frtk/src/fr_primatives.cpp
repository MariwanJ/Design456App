#include <fr_primatives.h>

Fr_Primatives::Fr_Primatives() :vbo_{ 0, 0, 0 }, vao_(0), drawType(GL_LINES){
}

Fr_Primatives::~Fr_Primatives() {
    if (vao_ != 0) {
        glCheckFunc(glDeleteVertexArrays(1, &vao_));
        glCheckFunc(glDeleteBuffers(3, vbo_));
    }
}

void Fr_Primatives::Draw()
{
    GLuint length;
    if (drawType==GL_LINES){
        glCheckFunc(glBindVertexArray(vao_));
        length = (GLuint)indices_.size() * 2;
        glCheckFunc(glDrawArrays(GL_LINES, 0, vertices_.size()));
        glCheckFunc(glBindVertexArray(0));
    }
}

void Fr_Primatives::setDrawType(int type)
{
    drawType = type;
}

int Fr_Primatives::getDrawType() const
{
    return drawType;
}

void Fr_Primatives::GetPrimatives(std::vector<float>& vertices, std::vector<float>& normals, std::vector<unsigned int>& indices) {
    vertices = vertices_;
    normals = normals_;
    indices = indices_;
}

void Fr_Primatives::SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    vertices_ = vertices;
    indices_ = indices;

    //CalculateNormals(vertices, indices, normals_);
    NormalizeVertices(vertices_);
    InitializeVBO(vertices_, normals_, indices_);
}

glm::vec3 Fr_Primatives::GetVertex(unsigned int index, const float vertices[]) {
    return glm::vec3(
        vertices[index * 3],
        vertices[index * 3 + 1],
        vertices[index * 3 + 2]
    );
}

void Fr_Primatives::SetVertex(unsigned int index, float vertices[], const glm::vec3& vertex) {
    vertices[index * 3] = vertex[0];
    vertices[index * 3 + 1] = vertex[1];
    vertices[index * 3 + 2] = vertex[2];
}

void Fr_Primatives::CalculateNormals(const std::vector<float>& vertices,
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

void Fr_Primatives::NormalizeVertices(std::vector<float>& vertices) {
    glm::vec3 min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
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

void Fr_Primatives::InitializeVBO(const std::vector<float>& vertices,
                                 const std::vector<float>& normals,
                                 const std::vector<unsigned int> indices) {

    glCheckFunc(glGenBuffers(3, vbo_));
    glCheckFunc(glGenVertexArrays(1, &vao_));
    glCheckFunc(glBindVertexArray(vao_));       //Keeps all instructions related this object
    /*
    glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]));        //First object buffer
    glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW));
    glCheckFunc(glEnableVertexAttribArray(0));
    glCheckFunc(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), NULL));
    */
    glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]));
    glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, normals.data(), GL_STATIC_DRAW));
    glCheckFunc(glEnableVertexAttribArray(1));
    glCheckFunc(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL));

    glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]));
    glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER,3 * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
    glCheckFunc(glBindVertexArray(0));
    
    
}