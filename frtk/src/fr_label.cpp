#include "fr_label.h"
#include <ft2build.h>
#include FT_CONFIG_OPTIONS_H
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <fr_window.h>
// Constructor
namespace FR {


    Fr_Label::Fr_Label(label_t lbl) {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        std::string shaderpath = EXE_CURRENT_DIR + "/resources/shaders/txtFont";
        txtFont_program = std::make_shared <ShaderProgram>(shaderpath);


    }
    void Fr_Label::initializem_vbo(void) {
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
    // Destructor
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

        // Positioning text at the top corner 

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_lblData.pos); // Translate to position
        model = model * glm::scale(model, glm::vec3(m_lblData.scale, m_lblData.scale, 1.0f)); // Scale uniformly
        if (m_lblData.type == ORTHOGRAPHIC) {
            mvp = glm::ortho(0.0f, (float)info.screenDim.w, 0.0f, (float)info.screenDim.h);
        }
        else {
            mvp = info.projection * info.modelview * model;// Perspective
        }
        txtFont_program->SetUniformMat4("mvp", mvp);

        x = 0;
        y = 0;
        for (auto c : m_lblData.text) {
            Character_t ch = m_Characters[c];
            float xpos = x + ch.Bearing.x;
            float ypos = y - (ch.Size.y - ch.Bearing.y);

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
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo );
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
}