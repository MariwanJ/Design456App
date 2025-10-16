/*

#include <fr_text.h>
#include <glad/glad.h>
namespace FR {
#include "Fr_Text.h"
#include <iostream>

    Fr_Text::Fr_Text(std::shared_ptr<ShaderProgram> shader, const std::string& fontPath)
        : m_shader(shader), m_fFont(fontPath) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        loadCharacters();
    }

    void Fr_Text::loadCharacters() {
        FT_Library ft;
        FT_Face face;

        if (FT_Init_FreeType(&ft)) {
            std::cerr << "Could not initialize FreeType" << std::endl;
            return;
        }

        if (FT_New_Face(ft, m_fFont.c_str(), 0, &face)) {
            std::cerr << "Could not open font" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Could not load character '" << c << "'" << std::endl;
                continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
                GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character ch = {
                texture,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                face->glyph->bitmap_left,
                face->glyph->bitmap_top,
                face->glyph->advance.x >> 6 // Convert from 26.6 to integer
            };
            characters[c] = ch;
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void Fr_Text::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color) {
        m_shader->SetUniformVec3("textColor", color); // Set text color

        glBindVertexArray(VAO);

        for (const char& c : text) {
            Character ch = characters[c];

            float xpos = x + ch.bearingX * scale;
            float ypos = y - (ch.height - ch.bearingY) * scale;

            float w = ch.width * scale;
            float h = ch.height * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f }, // Top left
                { xpos,     ypos,       0.0f, 1.0f }, // Bottom left
                { xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
                { xpos,     ypos + h,   0.0f, 0.0f }, // Top left
                { xpos + w, ypos,       1.0f, 1.0f }, // Bottom right
                { xpos + w, ypos + h,   1.0f, 0.0f }  // Top right
            };

            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (ch.advance >> 6) * scale; // Advance to next glyph
        }

        glBindVertexArray(0);
    }
}

*/