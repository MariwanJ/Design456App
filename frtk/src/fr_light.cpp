//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
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

Light::Light() :
    light_id_(0),
    position_(0, 0, 0, 1),
    ambient_(0.2, 0.2, 0.2, 1),
    diffuse_(0.4, 0.4, 0.4, 1),
    specular_(0.4, 0.4, 0.4, 1),
    attenuation_(1, 0, 0),
    spot_enabled_(false),
    sm_projection_(0),
    sm_framebuffer_(0),
    sm_renderbuffer_(0),
    sm_texture_(0),
    sm_enable_(false) {
    type(NODETYPE::FR_LIGHT);
}

void Light::SetPosition(float x, float y, float z, float w) {
    position_ = glm::vec4(x, y, z, w);
}

void Light::SetAmbient(float r, float g, float b, float a) {
    ambient_ = glm::vec4(r, g, b, a);
}

void Light::SetDiffuse(float r, float g, float b, float a) {
    diffuse_ = glm::vec4(r, g, b, a);
}

void Light::SetSpecular(float r, float g, float b, float a) {
    specular_ = glm::vec4(r, g, b, a);
}

void Light::SetAttenuation(float c, float l, float q) {
    attenuation_ = glm::vec3(c, l, q);
}

void Light::SetupSpot(float x, float y, float z, float cutoff, float exponent) {
    spot_enabled_ = true;
    spot_direction_ = glm::vec4(glm::normalize(glm::vec3(x, y, z)), 1);
    spot_cutoff_ = cos(glm::radians(cutoff));
    spot_exponent_ = exponent;
}

void Light::EnableShadowMap(const glm::vec3& center, const glm::vec3& up, const glm::mat4& projection) {
    sm_enable_ = true;
    sm_center_ = center;
    sm_up_ = up;
    sm_projection_ = projection;

    int width = kShadowmapWidth;
    int height = kShadowmapHeight;

    // Create Framebuffer
    glCheckFunc(glGenFramebuffers(1, &sm_framebuffer_));
    glCheckFunc(glBindFramebuffer(GL_FRAMEBUFFER, sm_framebuffer_));

    // Create Renderbuffer
    glCheckFunc(glGenRenderbuffers(1, &sm_renderbuffer_));
    glCheckFunc(glBindRenderbuffer(GL_RENDERBUFFER, sm_renderbuffer_));
    glCheckFunc(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));
    glCheckFunc(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, sm_renderbuffer_));

    // Create texture
    glCheckFunc(glGenTextures(1, &sm_texture_));
    glCheckFunc(glBindTexture(GL_TEXTURE_2D, sm_texture_));
    glCheckFunc(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));
    glCheckFunc(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCheckFunc(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCheckFunc(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, sm_texture_, 0));

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Couldn't create shadowmap frame buffer");

    glCheckFunc(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    glCheckFunc(glBindTexture(GL_TEXTURE_2D, 0));
    glCheckFunc(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Light::SetupLight(const glm::mat4& modelview,
    std::vector<LightInfo>& lights) {
    if (!active_)
        return;

    auto normalmatrix = glm::transpose(glm::inverse(modelview));

    LightInfo info;
    info.position = modelview * position_;
    info.diffuse = diffuse_;
    info.specular = specular_;
    info.ambient = ambient_;
    info.attenuation = attenuation_;
    info.is_spot = spot_enabled_;
    info.direction = glm::normalize(glm::vec3(normalmatrix * spot_direction_));
    info.cutoff = spot_cutoff_;
    info.exponent = spot_exponent_;
    lights.push_back(info);
    light_id_ = lights.size() - 1;
}

bool Light::SetupShadowMap(ShadowMapInfo& info) {
    if (!active_)
        return false;

    info.projection = sm_projection_;
    info.modelview = glm::lookAt(glm::vec3(position_), sm_center_, sm_up_);
    info.light_id = light_id_;
    info.framebuffer = sm_framebuffer_;
    info.texture = sm_texture_;
    info.width = kShadowmapWidth;
    info.height = kShadowmapHeight;
    return true;
}