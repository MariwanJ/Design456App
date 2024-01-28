//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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
#ifndef FR_DRAW_H
#define FR_DRAW_H

#include<Fr_Core.h>
#include<frtk.h>

namespace FR {
    //More will be added later

    typedef enum twodType {
        FR_LINES = 0,
        FR_OPEN_LOOP,
        FR_CLOSED_LOOP, //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
        FR_CIRCLE,
        FR_CURVE,
        FR_ARC,
        FR_BSPLINE,
    };

    class FRTK_API Fr_TwoD_Drawing {
    public:
        Fr_TwoD_Drawing();
        Fr_TwoD_Drawing(Fr_TwoD_Drawing& obj);
        Fr_TwoD_Drawing(twodType type, std::shared_ptr<std::vector<float>> verticies,
            std::shared_ptr < std::vector<unsigned int>>indicies,
            glm::vec4 color = glm::vec4(FR_123D));
        ~Fr_TwoD_Drawing();

        void Verticies(std::shared_ptr<std::vector<float>> vert);
        std::shared_ptr<std::vector<float>>  Verticies();

   /*     void Indices(std::shared_ptr < std::vector<unsigned int>>indc);
        void TextureCoord(std::shared_ptr<std::vector<float>> tex);*/

        std::shared_ptr < std::vector<unsigned int>>Indicies();
        
        std::shared_ptr<std::vector<float>> Normals();
        std::shared_ptr<std::vector<float>> TextCoord();

        int initializeVBO();

        void Type(twodType type);
        twodType Type(void);

        virtual void Draw();
        void lineWidth(unsigned int wid);
        unsigned int lineWidth();

        void Color(glm::vec4 color);
        glm::vec4 Color();

    protected:
        unsigned int m_vbo[NUM_OF_VBO_BUFFERS];
        unsigned int m_vao;
        std::shared_ptr<std::vector<float>> m_Vertices;
        std::shared_ptr<std::vector<unsigned int>> m_Indices;
        std::shared_ptr<std::vector<float>> m_Normals;
        std::shared_ptr<std::vector<float>> m_Textcoord;

        std::string m_label;
    private:
        twodType m_Type;
        unsigned int m_lineWidth;
        glm::vec4 m_Color;
    };
}
#endif
