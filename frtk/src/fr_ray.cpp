//Mouse Picker Object
#include<fr_window.h>
#include <frtk.h>
namespace FR {
    glm::vec2 Fr_Window::getNormalisedDeviceCoordinates()
    {
        float ndcX, ndcY;
        ndcX = (2.0f * (float)mouseEvent.Old_x / float(m_ViewPort.w)) - 1.0f;
        ndcY = 1.0f - (2.0f * (float)mouseEvent.Old_y / float(m_ViewPort.h));
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
        glm::vec2 mm = glm::vec2(mouseEvent.Old_x, (m_ViewPort.h - mouseEvent.Old_y));

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
        float x = (2.0f * (float) mouseEvent.Old_x) / (float)m_ViewPort.w - 1.0f;
        float y = 1.0f - (2.0f * (float)mouseEvent.Old_y) / (float)m_ViewPort.h; // try removing 1.0f - (...) if double-flip
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

        float mouseX = (float)mouseEvent.Old_x;
        float mouseY =(float) m_ViewPort.h - mouseEvent.Old_y;  //Flip the y axis (OpenGL requires that)

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