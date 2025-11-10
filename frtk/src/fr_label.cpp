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

#include "fr_label.h"
#include <ft2build.h>
#include FT_CONFIG_OPTIONS_H
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <fr_window.h>
// Constructor
namespace FR {
    Fr_Label::Fr_Label(label_t lbl) :m_lblData(lbl){
        std::string shaderpath = EXE_CURRENT_DIR + "/resources/shaders/txtFont";
        txtFont_program = std::make_shared <ShaderProgram>(shaderpath);
        initialize_vbo();
    }

    void Fr_Label::initialize_vbo(void) {
        //TODO : WE SHOULD MAKE SURE THAT WE CAN RENDER THIS - FIXME:
        //Text font drawing
        glCheckFunc(glGenVertexArrays(1, &m_vao));
        glCheckFunc(glGenBuffers(1, &m_vbo));
        glCheckFunc(glBindVertexArray(m_vao));
        glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
        glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW));
        glCheckFunc(glEnableVertexAttribArray(0));
        glCheckFunc(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
        glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, 0));
        glCheckFunc(glBindVertexArray(0));
    }

    Fr_Label::~Fr_Label() {
        for (auto& pair : m_Characters)
            glDeleteTextures(1, &pair.second.TextureID);
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void Fr_Label::RenderText(RenderInfo& info) {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);

        glCheckFunc(glEnable(GL_BLEND));
        glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        txtFont_program->Enable();
        txtFont_program->SetUniformVec3("textColor", m_lblData.color);
        glCheckFunc(glActiveTexture(GL_TEXTURE0));
        glCheckFunc(glBindVertexArray(m_vao));

        glm::mat4 mvp;
        glm::mat4 scale;

        glm::mat4 model = scale = glm::mat4(1.0f);
        model = glm::translate(model, m_lblData.pos);
         scale= glm::scale(scale, glm::vec3(m_lblData.scale, m_lblData.scale, 1.0f));

        if (m_lblData.type == ORTHOGRAPHIC) {
            mvp = glm::ortho(0.0f, (float)info.screenDim.w, 0.0f, (float)info.screenDim.h) * model;
        }
        else {
            mvp = info.projection * info.modelview * model * scale; 
        }
        txtFont_program->SetUniformMat4("mvp", mvp);

        float x = 0;
        float y = 0;
        float xpos = 0;
        float ypos = 0;
        bool firstime = true;
        for (auto c : m_lblData.text) {
            Character_t ch = m_Characters[c];
            if(!firstime){
                  xpos = x + ch.Bearing.x;
                  ypos = y - (ch.Size.y - ch.Bearing.y);
            }
            else
            {
                firstime = false;
            }

            float w = ch.Size.x;
            float h = ch.Size.y;

            float vertices[6][4] = {
                { xpos + w, ypos + h,   1.0f, 0.0f }, // Top-right
                { xpos,     ypos,       0.0f, 1.0f }, // Bottom-left
                { xpos,     ypos + h,   0.0f, 0.0f }, // Top-left
                { xpos + w, ypos + h,   1.0f, 0.0f }, // Top-right (repeat)
                { xpos,     ypos,       0.0f, 1.0f }, // Bottom-left (repeat)
                { xpos + w, ypos,       1.0f, 1.0f }  // Bottom-right
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Advance the cursor for the next character
            x += (ch.Advance >> 6);
        }

        // Clean up
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        txtFont_program->Disable();
    }

    void Fr_Label::LoadFont(const std::string& fontPath)
    {
        m_Characters.clear(); // Clear previous font glyphs
        m_lblData.fnFont = fontPath;

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
        FT_Set_Pixel_Sizes(face, 0, m_lblData.pixelSize);

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
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int index = (y * width + x) * 4; // RGBA index
                    uint8_t alpha = face->glyph->bitmap.buffer[y * width + x];
                    uint8_t colorValue = 255;

                    // Set RGBA based on alpha
                    if (alpha > 128) {                       // Threshold for alpha
                        bitmapRGBA[index] = colorValue;     // Red
                        bitmapRGBA[index + 1] = colorValue; // Green
                        bitmapRGBA[index + 2] = colorValue; // Blue
                        bitmapRGBA[index + 3] = 255;         // Fully opaque
                    }
                    else {
                        bitmapRGBA[index] = 0;               // Transparent
                        bitmapRGBA[index + 1] = 0;
                        bitmapRGBA[index + 2] = 0;
                        bitmapRGBA[index + 3] = 0;
                    }
                }
            }

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,            // Change to RGBA format
                width,
                height,
                0,
                GL_RGBA,            // Change to RGBA format
                GL_UNSIGNED_BYTE,
                bitmapRGBA.data()   // Use the RGBA bitmap
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    //Without this, you will see distortion at the edges.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character_t ch = {
                tex,
                glm::ivec2(width, height),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (GLuint)face->glyph->advance.x
            };

            m_Characters.insert(std::make_pair(c, ch));
        }

        glBindTexture(GL_TEXTURE_2D, 0);

#if 0	//For debugging only
        printStringAsDots(m_label.text, face);
#endif
        FT_Done_Face(face);
    }



    void Fr_Label::label(std::string& lbl)
    {
        m_lblData.text = lbl;
    }
    void Fr_Label::label(const char* lbl)
    {
        m_lblData.text = lbl;
    }
    std::string Fr_Label::label() const
    {
        return m_lblData.text;
    }

    void Fr_Label::font(std::string& forntName)
    {
        m_lblData.fnFont = forntName;
    }

    const std::string & Fr_Label::font() const
    {
        return m_lblData.fnFont;
    }

    void Fr_Label::fontSize(int size_)
    {
        m_lblData.pixelSize = size_;
    }

    void Fr_Label::fontColor(glm::vec4 col)
    {
        m_lblData.color = col;
    }
    void Fr_Label::fontColor(float r, float g, float b, float a)
    {
        m_lblData.color = glm::vec4(r, g, b, a);
    }

    void Fr_Label::pos(glm::vec3 nval)
    {
        m_lblData.pos = nval;
    }
    glm::vec3 Fr_Label::pos(void) {
        return m_lblData.pos;
    }

    void Fr_Label::lbl_visible(bool v) {
        m_lblData.visible = v;
    }

    bool Fr_Label::lbl_visible() {
        return m_lblData.visible;
    }
    void Fr_Label::lblType(uint8_t lbltype) {
        m_lblData.type = lbltype;
    }
    const uint8_t Fr_Label::lblType(void) {
        return m_lblData.type;
    }
}