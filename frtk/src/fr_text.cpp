#include <fr_text.h>
#include <ft2build.h>
#include FT_CONFIG_OPTIONS_H
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <fr_window.h>
// Constructor
namespace FR {
    TextRenderer::TextRenderer(unsigned int screenWidth, unsigned int screenHeight)
        : Width(screenWidth), Height(screenHeight), fontLoaded(false) {
        shaderProgram = CreateShaderProgram(vertexShaderSrc, fragmentShaderSrc);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glUseProgram(shaderProgram);
        glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height);
        Fr_Window* win = Fr_Window::getFr_Window();

        GLint loc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, &proj[0][0]);
        glUseProgram(0);
    }

    // Destructor
    TextRenderer::~TextRenderer() {
        for (auto& pair : Characters)
            glDeleteTextures(1, &pair.second.TextureID);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        if (shaderProgram)
            glDeleteProgram(shaderProgram);
    }

    // Load Font Method
    bool  TextRenderer::LoadFont(const std::string& fontPath, unsigned int pixelSize) {
        if (fontLoaded) {
            std::cerr << "Font already loaded." << std::endl;
            return true; // or return false if you want to prevent reloading
        }

        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library\n";
            return false;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
            std::cerr << "ERROR::FREETYPE: Failed to load font\n";
            FT_Done_FreeType(ft);
            return false;
        }

        FT_Set_Pixel_Sizes(face, 0, pixelSize);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; ++c) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "Failed to load Glyph: " << c << std::endl;
                continue;
            }

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character ch = {
                tex,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (GLuint)face->glyph->advance.x
            };
            Characters.insert(std::pair<char, Character>(c, ch));
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        fontLoaded = true; // Set the flag to true after loading
        return true;
    }

    // Render Text Method
    void  TextRenderer::RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUseProgram(shaderProgram);
        glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for (auto c : text) {
            Character ch = Characters[c];
            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch.Advance >> 6) * scale; // Advance to next glyph
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
    }

    // Set Projection Method
    void  TextRenderer::SetProjection(unsigned int screenWidth, unsigned int screenHeight) {
     /*   Width = screenWidth;
        Height = screenHeight;
        glUseProgram(shaderProgram);
        glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height);
        GLint loc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, &proj[0][0]);
        glUseProgram(0);*/
    }

    // Shader Program Creation Method
    GLuint  TextRenderer::CreateShaderProgram(const char* vertSrc, const char* fragSrc) {
        GLuint vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &vertSrc, NULL);
        glCompileShader(vert);
        CheckCompileErrors(vert, "VERTEX");

        GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &fragSrc, NULL);
        glCompileShader(frag);
        CheckCompileErrors(frag, "FRAGMENT");

        GLuint prog = glCreateProgram();
        glAttachShader(prog, vert);
        glAttachShader(prog, frag);
        glLinkProgram(prog);
        CheckCompileErrors(prog, "PROGRAM");

        glDeleteShader(vert);
        glDeleteShader(frag);
        return prog;
    }

    // Shader Compilation Error Check Method
    bool TextRenderer::CheckCompileErrors(GLuint shader, const std::string& type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "| ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                    << infoLog << "\n";
                return false;
            }
        }
        else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "| ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                    << infoLog << "\n";
                return false;
            }
        }
        return true;
    }

    // Shader Source Code
    const char* FR::TextRenderer::vertexShaderSrc = R"glsl(
#version 460 core
layout (location = 0) in vec4 vertex;
out vec2 TexCoords;
uniform mat4 projection;
void main() {
    gl_Position = projection * vec4(vertex.xy,  0.0, 1.0);
    TexCoords = vertex.zw;
}
)glsl";

    const char* FR::TextRenderer::fragmentShaderSrc = R"glsl(
#version 460 core
in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D text;
uniform vec3 textColor;
void main() {
    float alpha = texture(text, TexCoords).r;
    FragColor = vec4(textColor, alpha);
}
)glsl";
}