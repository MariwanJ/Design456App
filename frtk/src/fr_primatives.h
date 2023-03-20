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
#ifndef FR_PRIMATIVES_H
#define FR_PRIMATIVES_H

#include <FR.h>
#include <fr_core.h>
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