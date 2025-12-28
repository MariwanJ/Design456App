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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <glm/gtc/matrix_transform.hpp>
#include <fr_light.h>
#include <fr_widget.h>
namespace FR {
    Fr_Light::Fr_Light(glm::vec4 m_lightColor) :Fr_Widget(NULL,NULL,""),
                                                m_lightColor(m_lightColor),
                                                m_position(0, 0, 0, 1),
                                                m_ambient(0.2, 0.2, 0.2, 1),
                                                m_diffuse(0.4, 0.4, 0.4, 1),
                                                m_specular(0.4, 0.4, 0.4, 1),
                                                m_attenuation(1.0, 0.0, 0.0),//MAYBE WRONG??
                                                m_spot_enabled(false),
                                                m_sm_projection(0),
                                                m_sm_framebuffer(0),
                                                m_sm_renderbuffer(0),
                                                m_shadowMapTexture(0),
                                                m_sm_enable(false)
    {
        m_WidgType = NODETYPE::FR_LIGHT;
        m_spot_cutoff_Ang = 0.0f;
        m_spot_direction = glm::vec4(0, 0, 0, 0);
        m_spot_exponent = 0.0f;
    }
    Fr_Light::Fr_Light():Fr_Widget(NULL, NULL, ""), m_lightColor(m_lightColor),
                                                    m_position(0, 0, 0, 1),
                                                    m_ambient(0.2, 0.2, 0.2, 1),
                                                    m_diffuse(0.4, 0.4, 0.4, 1),
                                                    m_specular(0.4, 0.4, 0.4, 1),
                                                    m_attenuation(1, 0, 0),
                                                    m_spot_enabled(false),
                                                    m_sm_projection(0),
                                                    m_sm_framebuffer(0),
                                                    m_sm_renderbuffer(0),
                                                    m_shadowMapTexture(0),
                                                    m_sm_enable(false)
    {
        m_lightColor = glm::vec4(1, 1, 1, 1);
    }
    void Fr_Light::SetLightColor(glm::vec4 lightColor) {
        m_lightColor = lightColor;
    }

    void Fr_Light::SetPosition(glm::vec4 pos) {
        m_position = pos;
    }

    void Fr_Light::SetPosition(float x, float y, float z, float w) {
        m_position = glm::vec4(x, y, z, w);
    }

    void Fr_Light::SetAmbient(float r, float g, float b, float a) {
        m_ambient = glm::vec4(r, g, b, a);
    }

    void Fr_Light::SetDiffuse(float r, float g, float b, float a) {
        m_diffuse = glm::vec4(r, g, b, a);
    }

    void Fr_Light::SetSpecular(float r, float g, float b, float a) {
        m_specular = glm::vec4(r, g, b, a);
    }

    void Fr_Light::SetAttenuation(float c, float l, float q) {
        m_attenuation = glm::vec3(c, l, q);
    }

    void Fr_Light::SetupSpot(float x, float y, float z, float cutoffAngle, float exponent) {
        m_spot_enabled = true;
        m_spot_direction = glm::vec4(glm::normalize(glm::vec3(x, y, z)), 1);
        m_spot_cutoff_Ang = cos(glm::radians(cutoffAngle));
        m_spot_exponent = exponent;
    }

    void Fr_Light::EnableShadowMap(const glm::vec3& center, const glm::vec3& up, const glm::mat4& projection)
    {
        // Enable shadow mapping
        m_sm_enable = true;
        m_sm_direction = center;
        m_sm_up = up;
        m_sm_projection = projection;

        // 1. Create Framebuffer
        glGenFramebuffers(1, &m_sm_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_sm_framebuffer);

        // 2. Create Depth Texture
        glGenTextures(1, &m_shadowMapTexture);
        glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
            kShadowmapWidth, kShadowmapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        // Texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

        // Attach depth texture to FBO
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMapTexture, 0);

        // No color output
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        // Check completeness
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("Shadow map FBO incomplete");

        // Unbind
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }


    void Fr_Light::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) {
        if (!m_active)
            return;

        auto normalmatrix = glm::transpose(glm::inverse(modelview));

        LightInfo info;
        info.position = modelview * m_position;
        info.diffuse = m_diffuse;
        info.specular = m_specular;
        info.ambient = m_ambient;
        info.attenuation = m_attenuation;
        info.is_spot = m_spot_enabled;
        info.direction = glm::normalize(glm::vec3(normalmatrix * m_spot_direction));
        info.cutoff = m_spot_cutoff_Ang;
        info.exponent = m_spot_exponent;
        lights.push_back(info);
    }


    glm::vec4 Fr_Light::getPosition()
    {
        return m_position;
    }

    glm::vec4 Fr_Light::gtAmbient()
    {
        return m_ambient;
    }

    glm::vec4 Fr_Light::getDiffuse()
    {
        return m_diffuse;
    }

    glm::vec4 Fr_Light::getSpecular()
    {
        return m_specular;
    }

    glm::vec3 Fr_Light::getAttenuation()
    {
        return m_attenuation;
    }
}