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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FR_LIGHT_H
#define FR_LIGHT_H

#include<frtk.h>
#include<fr_core.h>

#include <fr_node.h>
namespace FR {
    class FRTK_API Light : public Node {
    public:
        /**
         * Default constructor
         */
        Light(glm::vec4 lightcolor = glm::vec4(1, 1, 1, 1));
        /**
        * Light color
        */
        void SetLightColor(glm::vec4 lightColor);

        /**
        * Sets the light position
        */
        void SetPosition(glm::vec4 pos);

        /**
         * Sets the light position
         * Default = 0, 0, 0
         */
        void SetPosition(float x, float y, float z, float w = 1.0f);

        /**
         * Sets the ambient component
         * Default = 0.2, 0.2, 0.2, 1.0
         */
        void SetAmbient(float r, float g, float b, float a = 1.0f);

        /**
         * Sets the diffuse component
         * Default = 0.4, 0.4, 0.4, 1.0
         */
        void SetDiffuse(float r, float g, float b, float a = 1.0f);

        /**
         * Sets the specular component
         * Default = 0.4, 0.4, 0.4, 1.0
         */
        void SetSpecular(float r, float g, float b, float a = 1.0f);

        /**
         * Sets the attenuation: 1 / (c + l*d + q*d^2)
         * Default = (1, 0, 0)
         */
        void SetAttenuation(float c, float l, float q);

        /**
        * Setup spot
        */
        void SetupSpot(float x, float y, float z, float cutoffAngle, float exponent);

        /**
         * Enables the shadow map
         */
        void EnableShadowMap(const glm::vec3& center, const glm::vec3& up, const glm::mat4& projection);

        /**
         * Sets the lights
         * Returns the light info by reference
         */
        void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) override;

    public:
        int getLightID();
        glm::vec4 getPosition();
        glm::vec4 gtAmbient();
        glm::vec4 getDiffuse();
        glm::vec4 getSpecular();
        glm::vec3 getAttenuation();

    private:
        // Constants
        const int kShadowmapWidth = 1024;
        const int kShadowmapHeight = kShadowmapWidth;

        // Attributes
        glm::vec4 lightColor_;
        int light_id_;
        glm::vec4 position_;
        glm::vec4 ambient_;
        glm::vec4 diffuse_;
        glm::vec4 specular_;
        glm::vec3 attenuation_;
        bool spot_enabled_;
        glm::vec4 spot_direction_;
        float spot_cutoff_Ang;
        float spot_exponent_;

        bool sm_enable_;
        glm::vec3 sm_direction_;
        glm::vec3 sm_up_;
        glm::mat4 sm_projection_;
        unsigned int sm_framebuffer_;
        unsigned int sm_renderbuffer_;
        unsigned int shadowMapTexture_;
    };
}
#endif
