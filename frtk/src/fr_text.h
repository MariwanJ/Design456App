#ifndef FR_TEXT_H
#define FR_TEXT_H

/*
#include <ft2build.h>
#include FT_FREETYPE_H 
#include <frtk.h>
#include <fr_shader_program.h>

namespace FR{
    class Fr_Text {
    public:
        Fr_Text(std::shared_ptr<ShaderProgram> shader, const std::string& fontPath);
        void load(const std::string& text, float x, float y, float scale, const glm::vec3& color);
        void renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color);

    private:
        struct Character {
            GLuint textureID;   // Texture ID
            int width;          // Width of the character
            int height;         // Height of the character
            int bearingX;       // Offset from the baseline to left edge
            int bearingY;       // Offset from the baseline to top edge
            int advance;        // Horizontal offset to advance to next character
        };

        std::shared_ptr<ShaderProgram> m_shader;
        std::string m_fFont;
        std::map<char, Character> characters;
        GLuint VAO, VBO;

        void loadCharacters();
    };
}
*/












#include <frtk.h>
#include <fr_core.h>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FR {
    struct Character {
        GLuint TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint Advance;
    };

        class TextRenderer {
        public:
            TextRenderer(unsigned int screenWidth, unsigned int screenHeight);
            ~TextRenderer();
            bool LoadFont(const std::string& fontPath, unsigned int pixelSize);
            void RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color);
            void SetProjection(unsigned int screenWidth, unsigned int screenHeight);

        private:
            GLuint CreateShaderProgram(const char* vertSrc, const char* fragSrc);
            bool CheckCompileErrors(GLuint shader, const std::string& type);

            unsigned int Width, Height;
            GLuint VAO, VBO;
            GLuint shaderProgram;
            std::map<char, Character> Characters;
            bool fontLoaded; // Flag to check if font is loaded

            static const char* vertexShaderSrc;
            static const char* fragmentShaderSrc;
        };

    } // namespace FR

 
#endif //FR_TEXT_H
