#ifndef FR_PRIMATIVES_H
#define FR_PRIMATIVES_H

#include <FR.h>
#include <Fr_Core.h>
#include <glm/glm.hpp>

class Fr_Primatives
{
public:
    Fr_Primatives();
    ~Fr_Primatives();
    

    void Draw();

    void setDrawType(int type);
    int getDrawType() const;

    void GetPrimatives(std::vector<float>& vertices, std::vector<float>& normals, std::vector<unsigned int>& indices);

    void SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices);
private:

    glm::vec3 GetVertex(unsigned int index, const float vertices[]);

    void SetVertex(unsigned int index, float vertices[], const glm::vec3& vertex);

    void CalculateNormals(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, std::vector<float>& normals);

    void InitializeVBO(const std::vector<float>& vertices, 
                                        const std::vector<float>& normals,
                                        const std::vector<unsigned int> indices);

    int drawType;
    std::vector<float> vertices_;
    std::vector<float> normals_;
    std::vector<unsigned int> indices_;
    unsigned int vbo_[3];
    unsigned int vao_;
};

#endif // !FR_PRIMATIVES_H