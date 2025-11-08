#ifndef FR_LABEL_H
#define FR_LABEL_H

 
#include <ft2build.h>
#include FT_FREETYPE_H 
#include <frtk.h>
#include <fr_shader_program.h>

namespace FR{ 
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
            glm::vec3(0.0f,0.0f,0.0f),                      //Pos
            "Label",                                        //label
            DEFAULT_FONT,    //Default font
            glm::vec4(FR_WHITE),                            //color
            true,                                           //visible
            PERSPECTIVE,                                    //type perspective or ortho
            250,                                            //Pixel size - Choose big and scale down
            0.005f                                          //Scale 
            });
        void initializem_vbo(void);
        void initializeVBO(void);
        void RenderText(RenderInfo& info);

        void LoadFont(const std::string& fontPath=DEFAULT_FONT);


    protected:
        std::shared_ptr<std::vector<size_t>> m_selected;
        std::shared_ptr<std::vector<unsigned int>> m_indices; 
        std::shared_ptr<std::vector<float>> m_normals;
        std::shared_ptr<std::vector<glm::vec3>> m_triangles_normals;
        std::shared_ptr <ShaderProgram> txtFont_program;
    private:
       
        std::shared_ptr<ShaderProgram> m_shader;
        std::map<char, Character> m_Characters;
        GLuint m_vao, m_vbo;
        label_t m_lblData;
    };
}
 












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
