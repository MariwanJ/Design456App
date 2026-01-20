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

#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp> // For glm::distance2
#include<fr_checkIntersection.h>
#include <fr_window.h>
#include <fr_openmesh.h>

namespace FR {
    // Small epsilon for floating-point checks
    constexpr float EPSILON = 1e-6f;

    bool intersectPointIn3D(const ray_t& ray, const glm::vec3& vertex, float tolerance) {
        glm::vec3 rayDir = glm::normalize(ray.direction); // Normalize the direction
        glm::vec3 toVertex = vertex - ray.position; // Vector from ray origin to vertex

        // Project toVertex onto ray direction
        float t = glm::dot(toVertex, rayDir);

        // If the projection point is behind the ray origin
        if (t < 0.0f) {
            // Check distance to the ray origin
            return glm::length(vertex - ray.position) <= tolerance;
        }

        // Closest point on the ray to the vertex
        glm::vec3 closestPoint = ray.position + t * rayDir;

        // Calculate the distance from the vertex to the closest point on the ray
        float distanceToRay = glm::length(vertex - closestPoint);
        printf("Ray was (%2.0f,%2.0f,%2.0f  \n) ", rayDir.x, rayDir.y, rayDir.z);
        printf("%.2f it was \n", distanceToRay);
        return distanceToRay <= tolerance; // Check if within tolerance
    }

    bool intersectLineSegment3D(const ray_t& ray, const std::vector<glm::vec3>& line, glm::vec3& intersectionPoint) {
        if (line.size() < 2) return false;

        glm::vec3 A = line[0];
        glm::vec3 B = line[1];
        glm::vec3 AB = B - A;           //Vector between the end of these two vectors. 

        glm::vec3 C = ray.position;
        glm::vec3 d = glm::normalize(ray.direction);

        // Solve closest points between line segment (A + t*AB) and ray (C + s*d)
        glm::vec3 AC = C - A;       //Distance between A and C 

        //Dot product : is Length: positive if they are in the same direction, negative if they are opposite, zero if 90 degree

        float abDotab = glm::dot(AB, AB);       //Square length of AB 
        float abDotd = glm::dot(AB, d);         //distance between the A&B to the direction vector 
        float dDotd = glm::dot(d, d);                   float abDotAC = glm::dot(AB, AC);
        float dDotAC = glm::dot(d, AC);

        float denom = abDotab * dDotd - abDotd * abDotd;
        if (fabs(denom) < EPSILON) {
            return false; // Ray and line are parallel
        }

        float t = (abDotd * dDotAC - dDotd * abDotAC) / denom;
        float s = (abDotab * dDotAC - abDotd * abDotAC) / denom;

        // Clamp t to [0,1] so point is within segment
        if (t < 0.0f || t > 1.0f) 
            return false;
        if (s < 0.0f) 
            return false; // intersection behind ray

        glm::vec3 pointOnSegment = A + t * AB;
        glm::vec3 pointOnRay = C + s * d;

        float distance = glm::length(pointOnSegment - pointOnRay);
        Fr_Window* win = Fr_Window::getFr_Window();
        assert(win );
        if (distance <= win->m_MousePickerRadius) {
            intersectionPoint = pointOnSegment;
            return true;
        }
        return false;
    }

    bool intersectRayTriangle(const ray_t& ray, const std::vector<glm::vec3>& triangle,glm::vec3& intersectionPoint, float & t) {
            const float EPS = 1e-6f;
            const glm::vec3 v0 = triangle[0];
            const glm::vec3 v1 = triangle[1];
            const glm::vec3 v2 = triangle[2];

            glm::vec3 e1 = v1 - v0;
            glm::vec3 e2 = v2 - v0;

            glm::vec3 p = glm::cross(ray.direction, e2);
            float det = glm::dot(e1, p);

            if (fabs(det) < EPS)
                return false;

            float invDet = 1.0f / det;
            glm::vec3 s = ray.position - v0;
            float u = invDet * glm::dot(s, p);

            if (u < 0.0f || u > 1.0f)
                return false;

            glm::vec3 q = glm::cross(s, e1);
            float v = invDet * glm::dot(ray.direction, q);

            if (v < 0.0f || u + v > 1.0f)
                return false;

            t = invDet * glm::dot(e2, q);
            return t > EPS;
        }



    bool intersectRayPolygon(const ray_t& ray, const std::vector<glm::vec3>& polygon,
        glm::vec3& intersectionPoint, float& t) {
        if (polygon.size() < 3)
            return false;

        glm::vec3 v0 = polygon[0];
        // Fan triangulation: only valid for convex polygons
        for (size_t i = 1; i < polygon.size() - 1; ++i) {
            std::vector<glm::vec3> tri = { v0, polygon[i], polygon[i + 1] };
            if (intersectRayTriangle(ray, tri, intersectionPoint, t)) {
                return true;
            }
        }
        return false;
    }

    //TODO FIX ME THIS IS NOT CORRECT 
    bool intersectRayOpenMesh(
        const ray_t& ray,
        const FrOpenMesh& mesh,
        glm::vec3& intersectionPoint)   // pass by reference!
    {
        bool hit = false;
        float closestDist = std::numeric_limits<float>::max();
        float t;
        for (auto f : mesh.faces())
        {
            std::vector<glm::vec3> faceVerts;
            for (auto fv : mesh.fv_range(f))
            {
                const auto& pt = mesh.point(fv);
                faceVerts.push_back(glm::vec3(pt[0], pt[1], pt[2]));
            }

            if (faceVerts.size() < 3) continue; // skip degenerate faces

            // Fan triangulation: v0,v1,v2; v0,v2,v3; ...
            glm::vec3 v0 = faceVerts[0];
            
            for (size_t i = 1; i < faceVerts.size() - 1; ++i)
            {
                std::vector<glm::vec3> tri = { v0, faceVerts[i], faceVerts[i + 1] };
                glm::vec3 p;
                if (intersectRayTriangle(ray, tri, p,t))
                {
                    float dist = glm::length(p - ray.position);  // use ray.origin

                    if (dist < closestDist)
                    {
                        closestDist = dist;
                        intersectionPoint = p;
                        hit = true;
                    }
                }
            }
        }

        return hit;
    }

}