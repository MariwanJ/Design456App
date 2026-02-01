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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//



//Mouse Picker Object
#include<fr_window.h>
#include <frtk.h>
namespace FR {
    glm::vec2 Fr_Window::getNormalisedDeviceCoordinates()
    {
        float ndcX, ndcY;
        ndcX = (2.0f * (float)m_systemEvents.mouse.activeX/ float(m_ViewPort.w)) - 1.0f;
        ndcY = 1.0f - (2.0f * (float)m_systemEvents.mouse.activeY / float(m_ViewPort.h));
        return (glm::vec2(ndcX, ndcY));
    }

    glm::vec3 Fr_Window::calculateMouseRay()
    {
        glm::vec2 deviceCoords = getNormalisedDeviceCoordinates();
        glm::vec4 clipCoords = glm::vec4(deviceCoords.x, deviceCoords.y, -1.0f, 1.0f);
        glm::vec4 eyeCoords = toEyeCoords(clipCoords);
        glm::vec3 worldRay = toWorldCoords(eyeCoords);
        return (worldRay); //
    }

    glm::vec4 Fr_Window::toEyeCoords(const glm::vec4& clipCoords)
    {
        glm::mat4 invertedProjection = glm::inverse(activeScene->m_cameras[activeScene->m_active_camera].getProjection());
        glm::vec4 eyeCoords = invertedProjection * clipCoords;

        //eyeCoords /= eyeCoords.w;
        eyeCoords.w = 0.0f;
        eyeCoords.z = -1;
        return eyeCoords;
    }

    glm::vec3 Fr_Window::toWorldCoords(const glm::vec4& eyeCoords)
    {
        glm::mat4 invertedView = activeScene->m_cameras[activeScene->m_active_camera].GetInverseViewMatrix();
        glm::vec4 rayWorld = invertedView * eyeCoords;
        glm::vec3 mouseRay = glm::normalize(glm::vec3(rayWorld));
        return rayWorld;
    }

    glm::vec3 Fr_Window::getPointOnRay(const glm::vec3& ray, float distance)
    {
        glm::vec3 camPos = activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].GetCamPosition();
        return (camPos + ray * distance);
    }

    glm::vec3 Fr_Window::calculateMouseWorldPos()
    {
        // 1. Read depth buffer
        float depth = 1.0f;
        glm::vec2 mm = glm::vec2(m_systemEvents.mouse.activeX, (m_ViewPort.h - m_systemEvents.mouse.activeY));

        glReadPixels(
            (int)mm.x,
            (int)mm.y,
            1, 1,
            GL_DEPTH_COMPONENT,
            GL_FLOAT,
            &depth
        );
        if (depth == 1.0f) {
            return glm::vec3(0.0f);
        }

        // 2. Normalized device coordinates
        float x = (2.0f * (float)m_systemEvents.mouse.activeX) / (float)m_ViewPort.w - 1.0f;
        float y = 1.0f - (2.0f * (float)m_systemEvents.mouse.activeY) / (float)m_ViewPort.h; // try removing 1.0f - (...) if double-flip
        float z = depth * 2.0f - 1.0f;
        glm::vec4 ndcCoords(x, y, z, 1.0f);

        // 3. Eye space
        glm::mat4 proj = activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].getProjection();
        glm::vec4 eyeCoords = glm::inverse(proj) * ndcCoords;
        eyeCoords /=  eyeCoords.w;

        // 4. World space
        glm::mat4 view = activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].GetViewMatrix();
        glm::vec4 worldCoords = glm::inverse(view) * eyeCoords;
        worldCoords /= worldCoords.w;
        return glm::vec3(worldCoords);
    }

    //--------------------------------------------------------------------------------
    void Fr_Window::calculateScreenRay() {
        glm::mat4 view = activeScene->m_cameras[activeScene->m_active_camera].GetViewMatrix();
        glm::mat4 proj = activeScene->m_cameras[activeScene->m_active_camera].getProjection();

        float mouseX = (float) m_systemEvents.mouse.activeX;
        float mouseY = (float) m_ViewPort.h - m_systemEvents.mouse.activeY;  //Flip the y axis (OpenGL requires that)

        glm::vec3 nearPoint = glm::unProject(
            glm::vec3(mouseX, mouseY, 0.0f),
            view,
            proj,
            glm::vec4(0, 0, m_ViewPort.w, m_ViewPort.h)
        );

        glm::vec3 farPoint = glm::unProject(
            glm::vec3(mouseX, mouseY, 1.0f),
            view,
            proj,
            glm::vec4(0, 0, m_ViewPort.w, m_ViewPort.h)
        );

        glm::vec3 direction = glm::normalize(farPoint - nearPoint);
        ray_t result;
        result.position = nearPoint;
        result.direction = direction;
        activeScene->setRayValue(result);
    }

}