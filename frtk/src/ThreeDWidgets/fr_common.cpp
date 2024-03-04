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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include "fr_common.h"
#include <Fr_GL3Window.h>

namespace FR {
	bool intersectLine(glm::vec3 p1, glm::vec3 p2)
	{
		return false;
	}

	class MousePicker {
	private:
#define   RECURSION_COUNT  200
#define  RAY_RANGE   600
		glm::vec2 mousePos;

		glm::vec3 currentRay;

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		Camera camera;
		glm::vec3 currentTerrainPoint;

	public:
		Fr_GL3Window* win = Fr_GL3Window::getfr_Gl3Window();
		// std::shared_ptr<Camera> activeCamera = win->m_cameraList[(unsigned int)win->active_camera_];

		 //MousePicker(Camera cam, glm::mat4 projection, glm::vec2 mosueCursor) :mousePos(mosueCursor) {
		 //    camera = cam;
		 //    projectionMatrix = projection;
		 //    viewMatrix = activeCamera->GetViewMatrix();
		 //}

		 //    glm::vec3 getCurrentTerrainPoint() {
		 //        return currentTerrainPoint;
		 //    }

		 //    glm::vec3 getCurrentRay() {
		 //        return currentRay;
		 //    }

		 //    glm::vec3 getCurrentTerrainPoint() {
		 //        return currentTerrainPoint;
		 //    }

		 //    glm::vec3 getCurrentRay() {
		 //        return currentRay;
		 //    }

		 //    void update() {
		 //        viewMatrix = activeCamera->GetViewMatrix();
		 //        currentRay = calculateMouseRay();
		 //        if (intersectionInRange(0, RAY_RANGE, currentRay)) {
		 //            currentTerrainPoint = binarySearch(0, 0, RAY_RANGE, currentRay);
		 //        }
		 //        else {
		 //            currentTerrainPoint = NULL;
		 //        }
		 //    }

		 //private:
		 //    glm::vec3 calculateMouseRay() {
		 //        float mouseX = mousePos.x;
		 //        float mouseY = mousePos.y;
		 //        glm::vec2 normalizedCoords = getNormalisedDeviceCoordinates(mouseX, mouseY);
		 //        glm::vec4 clipCoords =   glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		 //        glm::vec4 eyeCoords = toEyeCoords(clipCoords);
		 //        glm::vec3 worldRay = toWorldCoords(eyeCoords);
		 //        return worldRay;
		 //    }

		 //    glm::vec3 toWorldCoords(glm::vec4 eyeCoords) {
		 //        glm::mat invertedView = glm::inverse(viewMatrix);
		 //        glm::vec4 rayWorld = (invertedView* eyeCoords);
		 //        glm::vec3 mouseRay =   glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
		 //        glm::normalize(mouseRay);
		 //        return mouseRay;
		 //    }

		 //    glm::vec4 toEyeCoords(glm::vec4 clipCoords) {
		 //        glm::mat4 invertedProjection = glm::inverse(projectionMatrix);
		 //        glm::vec4 eyeCoords = (invertedProjection* clipCoords);
		 //        return   glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
		 //    }

		 //    glm::vec2 getNormalisedDeviceCoordinates(float mouseX, float mouseY) {
		 //        float x = (2.0f * mouseX) / win->getPortViewDimensions().z - 1.f;
		 //        float y = (2.0f * mouseY) / win->getPortViewDimensions().w- 1.f;
		 //        return   glm::vec2(x, y);
		 //    }

		 //    //**********************************************************

		 //    glm::vec3 getPointOnRay(glm::vec3 ray, float distance) {
		 //        glm::vec3 camPos = activeCamera->GetCamPosition();
		 //        glm::vec3 start =   glm::vec3(camPos.x, camPos.y, camPos.z);
		 //        glm::vec3 scaledRay =   glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
		 //        return (start, scaledRay);
		 //    }

		 //    glm::vec3 binarySearch(int count, float start, float finish, glm::vec3 ray) {
		 //        float half = start + ((finish - start) / 2.f);
		 //        if (count >= RECURSION_COUNT) {
		 //            glm::vec3 endPoint = getPointOnRay(ray, half);
		 //            Terrain terrain = getTerrain(endPoint.getX(), endPoint.getZ());
		 //            if (terrain != null) {
		 //                return endPoint;
		 //            }
		 //            else {
		 //                return null;
		 //            }
		 //        }
		 //        if (intersectionInRange(start, half, ray)) {
		 //            return binarySearch(count + 1, start, half, ray);
		 //        }
		 //        else {
		 //            return binarySearch(count + 1, half, finish, ray);
		 //        }
		 //    }

		 //    boolean intersectionInRange(float start, float finish, glm::vec3 ray) {
		 //        glm::vec3 startPoint = getPointOnRay(ray, start);
		 //        glm::vec3 endPoint = getPointOnRay(ray, finish);
		 //        if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
		 //            return true;
		 //        }
		 //        else {
		 //            return false;
		 //        }
		 //    }

		 //    boolean isUnderGround(glm::vec3 testPoint) {
		 //        Terrain terrain = getTerrain(testPoint.getX(), testPoint.getZ());
		 //        float height = 0;
		 //        if (terrain != null) {
		 //            height = terrain.getHeightOfTerrain(testPoint.getX(), testPoint.getZ());
		 //        }
		 //        if (testPoint.y < height) {
		 //            return true;
		 //        }
		 //        else {
		 //            return false;
		 //        }
		 //    }

		 //    Terrain getTerrain(float worldX, float worldZ) {
		 //        return terrain;
		 //    }
	};
}