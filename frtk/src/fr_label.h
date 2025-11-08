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
#ifndef FR_LABEL_H
#define FR_LABEL_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <frtk.h>
#include <fr_core.h>

#include <fr_shader_program.h>

namespace FR {
    typedef struct {
        GLuint TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint Advance;
    }Character_t;

    typedef struct {
        glm::vec3 pos;        // Position relative to the widget,TODO: SHOULD BE RELATIVE OR ABS
        std::string text;
        std::string fnFont; // freetype Font used for rendering, file-path
        glm::vec4 color;
        bool visible;              // Visibility flag
        uint8_t type;               //ORTHO - PERSPECTIVE
        size_t pixelSize;
        float scale;
    }label_t;

    class Fr_Label {
    public:
        Fr_Label(label_t lblData = {
            glm::vec3(10.0f,10.0f,0.0f),                      //Pos
            "Label",                                        //label
            DEFAULT_FONT,    //Default font
            glm::vec4(FR_WHITE),                            //color
            true,                                           //visible
            PERSPECTIVE,                                    //type perspective or ortho,
            350,                                            //Pixel size - Choose big and scale down
            0.006f                                          //Scale
            });
        void initialize_vbo(void);
        ~Fr_Label();
        void RenderText(RenderInfo& info);

        void LoadFont(const std::string& fontPath = DEFAULT_FONT);



        void label(std::string& lbl);
        void label(const char* lbl);
        std::string label() const;
        void font(std::string& forntName);
        const std::string& font() const;
        void fontSize(int size_);
        void fontColor(glm::vec4 col);
        void fontColor(float r, float g, float b, float a);
        void pos(glm::vec3 nval);
        void lbl_visible(bool v);
        bool lbl_visible();
        void lblType(uint8_t lbltype);
        const uint8_t lblType(void);


    protected:
        std::shared_ptr<std::vector<size_t>> m_selected;
        std::shared_ptr<std::vector<unsigned int>> m_indices;
        std::shared_ptr<std::vector<float>> m_normals;
        std::shared_ptr<std::vector<glm::vec3>> m_triangles_normals;
        std::shared_ptr <ShaderProgram> txtFont_program;
    private:

        std::shared_ptr<ShaderProgram> m_shader;
        std::map<char, Character_t> m_Characters;
        GLuint m_vao, m_vbo;
        label_t m_lblData;
    };
}

#endif //FR_TEXT_H
