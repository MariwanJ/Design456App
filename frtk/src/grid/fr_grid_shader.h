//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#ifndef FR_GRID_SHADER_H
#define FR_GRID_SHADER_H

#include <memory>
#include <fr_shader_program.h>
#include <fr_widget.h>
namespace FR {
    class FRTK_API Fr_Primatives;
    class FRTK_API ShaderProgram;

    class FRTK_API Fr_GridShader   {
    public:
        void setText(const char* newValue);
        void setTexture(const char* newValue);
        /**
         * Constructor
         */
        Fr_GridShader(unsigned int color = 0x111111, float silhouette = 0.005);
        Fr_GridShader(glm::vec4 color, float silhouette = 0.005);
        Fr_GridShader(float color[4], float silhouette = 0.005);

        /**
         * Destructor
         */
        ~Fr_GridShader();

        void SetColor(glm::vec4 color);

        /**
         * Sets the color
         */
        void SetColor(unsigned int color, float alpha = 1.0f);

        /**
         * Sets the opacity
         */
        void SetOpacity(float alpha);

        /**
         * Sets the mesh
         */
        void SetPrimative(std::shared_ptr <Fr_Primatives> primative);

        /**
         * Renders the node
         */

        void Render(RenderInfo& info) ;

        std::shared_ptr <Fr_Texture2D> m_Texture2D;

        void setObjectshader(const char* newValue);
        void setSilhouette(const char* newValue);
 

        GLuint getCurrentTexturer(void);
    private:
        /**
         * Sets the uniform light data
         */
        void LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights);

        /**
         * Renders the silhouette
         */
        void RenderSilhouette(const glm::mat4& mvp);

        //void RenderTexture2D(const glm::mat4& mvp);

        // Constants
        const size_t kMaxLights = 8;
        
        void InitializeSharedPrograms();

        void defaultShaders();
        // Shared between instances

        Shader_t m_shared;

        // Attributes
        std::shared_ptr <Fr_Primatives> m_Primative;
        glm::vec4 m_Color;
        float silhouette_;
        std::string m_f_objectshader;
        std::string m_f_silhouette;
        std::string m_f_texture;
        std::string m_f_text;

        GLuint _texture; //used to return the texture for imgui rendering inside window.
    };
}
#endif //FR_GRID_SHADER_H
