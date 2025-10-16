//Mouse Picker Object
#include<fr_window.h>
#include <frtk.h>
namespace FR{
     
    glm::vec2 Fr_Window::getNormalisedDeviceCoordinates()
    {
        float ndcX, ndcY;
        ndcX = (2.0f * mouseEvent.Old_x / float(m_ViewPort.w)) - 1.0f;
        ndcY = 1-(2.0f * mouseEvent.Old_y / float(m_ViewPort.h));
        //printf("mouse xy, %f, %f\n", ndcX, ndcY);
        return (glm::vec2(ndcX, ndcY)); // Return device coordinates
    }

    glm::vec3 Fr_Window::calculateMouseRay()
    {
        glm::vec2 deviceCoords = getNormalisedDeviceCoordinates(); // Get device coordinates directly
        glm::vec4 clipCoords = glm::vec4(deviceCoords.x, deviceCoords.y, -1.0f, 1.0f);
         //Convert to eye coordinates
        glm::vec4 eyeCoords = toEyeCoords(clipCoords);
        // Convert to world coordinates
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
         //Transform eye coordinates to world coordinates
        glm::vec4 rayWorld = invertedView * eyeCoords;

        glm::vec3 mouseRay = glm::normalize(glm::vec3(rayWorld));
   /*     printf("\n-------------------\n");
        printf("normalized %f %f %f\n", mouseRay.x, mouseRay.y, mouseRay.z);
        printf("rayworld %f %f %f\n", rayWorld.x, rayWorld.y, rayWorld.z);  
        printf("\n-------------------\n");*/
        //calculateMouseWorldPos();
        //return  (mouseRay);
        return rayWorld;
    }
 
    glm::vec3 Fr_Window::getPointOnRay(const glm::vec3& ray, float distance)
    {
        glm::vec3 camPos = activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].GetCamPosition();
        return (camPos+ray * distance); 
    } 


    glm::vec3 Fr_Window::calculateMouseWorldPos()
    {
            // 1. Read depth buffer
            float depth = 1.0f;
            
            glm::vec2 mm=glm::vec2 (mouseEvent.Old_x, (m_ViewPort.h- mouseEvent.Old_y));
            /*glm::vec2 mm = glm::vec2(
                (mouseEvent.Old_x - (m_ViewPort.w / 2.0f)) * (2.0f / m_ViewPort.w),  // Normalize X to [-1, 1]
                ((m_ViewPort.h / 2.0f) - mouseEvent.Old_y) * (2.0f / m_ViewPort.h)   // Normalize Y to [-1, 1]
            )*/

            glReadPixels(
                (int) mm.x,
                (int)mm.y,
                1, 1,
                GL_DEPTH_COMPONENT,
                GL_FLOAT,
                &depth
            );

           // printf("DEPTH = %f -  mouse %f %f\n", depth, mm.x,mm.y);

            if (depth == 1.0f) {
                // background (no object under cursor)
                return glm::vec3(0.0f);
            }

            // 2. Normalized device coordinates
            float x = (2.0f * mouseEvent.Old_x) / m_ViewPort.w- 1.0f;
            float y = 1.0f - (2.0f * mouseEvent.Old_y) / m_ViewPort.h; // try removing 1.0f - (...) if double-flip
            float z = depth * 2.0f - 1.0f;
            glm::vec4 ndcCoords(x, y, z, 1.0f);

            // 3. Eye space
            glm::mat4 proj = activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].getProjection();
            glm::vec4 eyeCoords = glm::inverse(proj) * ndcCoords;
            eyeCoords /= eyeCoords.w;

            // 4. World space
            glm::mat4 view = activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].GetViewMatrix();
            glm::vec4 worldCoords = glm::inverse(view) * eyeCoords;
            worldCoords /= worldCoords.w; 

            printf("WORLD %f %f %f \n", worldCoords.x, worldCoords.y, worldCoords.z);

            return glm::vec3(worldCoords);
        }

   //--------------------------------------------------------------------------------
    //New calculation
    ray_t Fr_Window::GetScreenToWorldRay() {
        ray_t result;
        glm::mat4 view = activeScene->m_cameras[activeScene->m_active_camera].GetViewMatrix();
        glm::mat4 proj = activeScene->m_cameras[activeScene->m_active_camera].getProjection(); // Corrected spelling

        // Mouse in window space (pixels)
        float mouseX = mouseEvent.Old_x;
        float mouseY = m_ViewPort.h - mouseEvent.Old_y; // Flip Y for OpenGL window coords

        // Z = 0 -> near plane, Z = 1 -> far plane (window-space depth)
        glm::vec3 nearPoint = glm::unProject(
            glm::vec3(mouseX, mouseY, 0.0f),
            view,
            proj,
            glm::vec4(m_ViewPort.x, m_ViewPort.y, m_ViewPort.w, m_ViewPort.h)
        );

        glm::vec3 farPoint = glm::unProject(
            glm::vec3(mouseX, mouseY, 1.0f),
            view,
            proj,
            glm::vec4(m_ViewPort.x, m_ViewPort.y, m_ViewPort.w, m_ViewPort.h)
        );

        glm::vec3 direction = glm::normalize(farPoint - nearPoint);

        // Check if the camera is orthographic
        if (activeScene->m_active_camera==ORTHOGRAPHIC) {
            result.position = nearPoint;
        }
        else { // ALL OTHER CAMERAS ARE PERSPECTIVE
            result.position = activeScene->m_cameras[activeScene->m_active_camera].GetCamPosition();
        }
        result.direction = direction;
        return  (result);
    }

}
