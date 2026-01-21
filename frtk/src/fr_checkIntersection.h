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

#ifndef FR_CHECKINTERSECTION_H
#define FR_CHECKINTERSECTION_H

#include<frtk.h>
#include<fr_core.h>

namespace FR {
	const float DEFAULT_VERTEX_TOLERANCE = 0.01f;
	/**
	 * .
	 */
	bool intersectPointIn3D(const ray_t& RAY, const glm::vec3& vertex, float tolerance = DEFAULT_VERTEX_TOLERANCE);
	bool intersectLineSegment3D(const ray_t& ray, const std::vector<glm::vec3>& line, glm::vec3& intersectionPoint, float &t);
	bool intersectRayTriangle(const ray_t& RAY, const std::vector<glm::vec3>& triangle, glm::vec3& intersectionPoint, float& t); //only one triangle
	bool intersectRayOpenMesh(const ray_t& ray, const FrOpenMesh& mesh, glm::vec3& intersectionPoint);

	//TODO: should this be here?
	void selectCoplanarFaces(FrOpenMesh& mesh, OpenMesh::FaceHandle seedFace, float normalThreshold = 0.999f, float planeThreshold = 1e-4f);
}

#endif