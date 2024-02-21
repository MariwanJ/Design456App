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
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#ifndef FR_PRIMATIVESHADER_H
#define FR_PRIMATIVESHADER_H

#include <memory>
#include <fr_node.h>
namespace FR {
    class FRTK_API Fr_Primatives;
    class FRTK_API ShaderProgram;

    class FRTK_API Fr_PrimaitiveShader : public Node {
    public:
        /**
         * Constructor
         */
        Fr_PrimaitiveShader(glm::vec4 color=glm::vec4(FR_RED), float silhouette = 0.005);
        Fr_PrimaitiveShader(const Fr_PrimaitiveShader& obj) ;
        Fr_PrimaitiveShader& operator=(const Fr_PrimaitiveShader& obj);

        /**
         * Destructor
         */
        ~Fr_PrimaitiveShader();

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

        void Render(RenderInfo& info, const glm::mat4& modelview) override;

        std::shared_ptr< Fr_Texture2D> m_Texture2D;

        void setObjectshader(const char* newValue);
        void setSilhouette(const char* newValue);

        GLuint getCurrentTexturer(void);
    private:
        /**
         * Sets the uniform light data
         */
        void LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights);

        /**
         * Renders the silhouette
         */
        void RenderSilhouette(const glm::mat4& mvp);

        //void RenderTexture2D(const glm::mat4& mvp);

        // Constants
        const size_t kMaxLights = 8;

        void defaultShaders();
        // Shared between instances
        struct Shared {
            ShaderProgram* primative_program;
            ShaderProgram* silhouette_program;          //the dark shape and outline of object
            ShaderProgram* shadowmap_program;
            ShaderProgram* texture_program;
        };
        static Shared* shared_;

        // Attributes
        std::shared_ptr <Fr_Primatives> m_Primative;
        glm::vec4 m_Color;
        float silhouette_;
        std::string f_objectshader_;
        std::string f_silhouette_;
        std::string f_texture_;

        GLuint _texture; //used to return the texture for imgui rendering inside window.
    };
}
#endif
