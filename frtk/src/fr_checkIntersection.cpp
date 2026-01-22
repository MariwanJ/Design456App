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

    bool intersectPointIn3D( const ray_t& ray, const glm::vec3& vertex,   float tolerance, float& tRayOut)
    {
        glm::vec3 rayDir = glm::normalize(ray.direction);
        glm::vec3 toVertex = vertex - ray.position;

        float tRay = glm::dot(toVertex, rayDir);

        if (tRay < 0.0f)
            return false;

        glm::vec3 closestPoint = ray.position + tRay * rayDir;
        float distance = glm::length(vertex - closestPoint);
        if (distance > tolerance)
            return false;

        tRayOut = tRay;
        return true;
    }

    //Works but not perfect,
    //bool intersectLineSegment3D( const ray_t& ray, const std::vector<glm::vec3>& line, glm::vec3& intersectionPoint, float& tOut)
    //{
    //    if (line.size() < 2)
    //        return false;

    //    const glm::vec3& A = line[0];
    //    const glm::vec3& B = line[1];

    //    glm::vec3 AB = B - A;
    //    glm::vec3 C = ray.position;
    //    glm::vec3 d = glm::normalize(ray.direction);

    //    float abLen2 = glm::dot(AB, AB);
    //    if (abLen2 < 1e-6f)
    //        return false;

    //    glm::vec3 AC = A - C;

    //    float abDotD = glm::dot(AB, d);
    //    float abDotAC = glm::dot(AB, AC);
    //    float dDotAC = glm::dot(d, AC);

    //    float denom = abLen2 - abDotD * abDotD;

    //    float tSeg, sRay;

    //    if (fabs(denom) < 1e-6f)
    //    {
    //        tSeg = glm::clamp(abDotAC / abLen2, 0.0f, 1.0f);
    //        sRay = glm::dot(A + tSeg * AB - C, d);
    //    }
    //    else
    //    {
    //        tSeg = (abDotD * dDotAC - abDotAC) / denom;
    //        tSeg = glm::clamp(tSeg, 0.0f, 1.0f);
    //        sRay = dDotAC + abDotD * tSeg;
    //    }

    //    if (sRay < 0.0f)
    //        return false;

    //    glm::vec3 pSeg = A + tSeg * AB;
    //    glm::vec3 pRay = C + sRay * d;


    //    Fr_Window* win = Fr_Window::getFr_Window();
    //    assert(win);

    //    userData_ data;
    //    win->activeScene->getActiveCamera().getCamData(data);

    //    // Vertical FOV in radians
    //    float fovY = data.fovy_;
    //    float screenHeight = (float)win->h();

    //    // World units per pixel at depth sRay
    //    float worldPerPixel = 2.0f * sRay * tanf(fovY * 0.5f) / screenHeight;

    //    float pickRadiusWorld =
    //        win->m_MousePickerRadius * worldPerPixel;

    //    float dist2 = glm::dot(pSeg - pRay, pSeg - pRay);
    //    if (dist2 > pickRadiusWorld * pickRadiusWorld)
    //        return false;

    //    intersectionPoint = pSeg;
    //    tOut = tSeg;
    //    return true;
    //}

bool intersectLineSegment3D(const ray_t& ray, const std::vector<glm::vec3>& line, glm::vec3& intersectionPoint, float& tOut)
{
    if (line.size() < 2)
        return false;

    Fr_Window* win = Fr_Window::getFr_Window();
    assert(win);
    const glm::vec3& A = line[0];
    const glm::vec3& B = line[1];
    glm::mat4 view = win->activeScene->getActiveCamera().GetViewMatrix();
    glm::mat4 proj = win->activeScene->getActiveCamera().getProjection();
    glm::vec2 viewport((float)win->w(), (float)win->h());

    auto WorldToScreen = [&](const glm::vec3& p)
        {
            glm::vec4 clip = proj * view * glm::vec4(p, 1.0f);
            if (clip.w <= 0.0f)
                return glm::vec2(-1.0f);

            glm::vec3 ndc = glm::vec3(clip) / clip.w;
            return glm::vec2( (ndc.x * 0.5f + 0.5f) * viewport.x, 
                              (1.0f - (ndc.y * 0.5f + 0.5f)) * viewport.y);
        };

    glm::vec2 A2 = WorldToScreen(A);
    glm::vec2 B2 = WorldToScreen(B);
    if (A2.x < 0.0f || B2.x < 0.0f)
        return false;

    glm::vec2 mousePx = glm::vec2(win->getMouseEvents().Old_x,  win->getMouseEvents().Old_y);
    glm::vec2 AB2 = B2 - A2;
    float tScreen = glm::dot(mousePx - A2, AB2) / glm::dot(AB2, AB2);
    tScreen = glm::clamp(tScreen, 0.0f, 1.0f);

    glm::vec2 closest2D = A2 + tScreen * AB2;
    float distPx = glm::length(mousePx - closest2D);

    if (distPx > win->m_MousePickerRadius)
        return false;

    glm::vec3 hit = A + tScreen * (B - A);

    // Snap hit point onto ray for stability
    glm::vec3 d = glm::normalize(ray.direction);
    float s = glm::dot(hit - ray.position, d);
    if (s < 0.0f)
        return false;

    intersectionPoint = ray.position + s * d;
    tOut = tScreen;
    return true;
}

   //only ONE triangle
    bool intersectRayTriangle(const ray_t& ray, const std::vector<glm::vec3>& triangle, glm::vec3& intersectionPoint, float &t)
    {
        const float EPS = 1e-6f;
        const glm::vec3& v0 = triangle[0];
        const glm::vec3& v1 = triangle[1];
        const glm::vec3& v2 = triangle[2];

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
        if (t <= EPS)
            return false;
        intersectionPoint = ray.position + t * ray.direction;
        return true;
    }



    //bool intersectRayPolygon( const ray_t& ray, const std::vector<glm::vec3>& polygon, glm::vec3& intersectionPoint, float& t)
    //{
    //    if (polygon.size() < 3)
    //        return false;

    //    bool hit = false;
    //    float closestT = std::numeric_limits<float>::max();

    //    const glm::vec3& v0 = polygon[0];

    //    for (size_t i = 1; i + 1 < polygon.size(); ++i)
    //    {
    //        float triT;
    //        glm::vec3 triHit;

    //        if (intersectRayTriangle( ray, v0, polygon[i], polygon[i + 1], intersectionPoint))
    //        {
    //            if (triT < closestT)
    //            {
    //                closestT = triT;
    //                intersectionPoint = triHit;
    //                hit = true;
    //            }
    //        }
    //    }

    //    if (hit)
    //        t = closestT;

    //    return hit;
    //}


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

    inline glm::vec3 toGLM(const OpenMesh::Vec3f& v)
    {
        return { v[0], v[1], v[2] };
    }

    void selectCoplanarFaces(FrOpenMesh& mesh, OpenMesh::FaceHandle seedFace, float normalThreshold, float planeThreshold )
    {
        if (!seedFace.is_valid())
            return;

        // --- Build plane from seed face ---
        auto fv = mesh.fv_iter(seedFace);
        glm::vec3 p0 = toGLM(mesh.point(*fv)); ++fv;
        glm::vec3 p1 = toGLM(mesh.point(*fv)); ++fv;
        glm::vec3 p2 = toGLM(mesh.point(*fv));

        glm::vec3 planeNormal = glm::normalize(glm::cross(p1 - p0, p2 - p0));
        float planeD = -glm::dot(planeNormal, p0);

        std::stack<OpenMesh::FaceHandle> stack;
        std::unordered_set<int> visited;

        stack.push(seedFace);

        while (!stack.empty())
        {
            OpenMesh::FaceHandle fh = stack.top();
            stack.pop();

            if (visited.find(fh.idx()) != visited.end()) {
                continue; // Skip if already visited
            }

            visited.insert(fh.idx());

            // face normal 
            auto it = mesh.fv_iter(fh);
            glm::vec3 a = toGLM(mesh.point(*it)); ++it;
            glm::vec3 b = toGLM(mesh.point(*it)); ++it;
            glm::vec3 c = toGLM(mesh.point(*it));

            glm::vec3 n = glm::normalize(glm::cross(b - a, c - a));

            // Normal similarity test
            if (std::abs(glm::dot(n, planeNormal)) < normalThreshold)
                continue;

            // Plane distance test
            bool onPlane = true;
            for (auto fv = mesh.fv_iter(fh); fv.is_valid(); ++fv)
            {
                glm::vec3 v = toGLM(mesh.point(*fv));
                if (std::abs(glm::dot(planeNormal, v) + planeD) > planeThreshold)
                {
                    onPlane = false;
                    break;
                }
            }

            if (!onPlane)
                continue;

            // Resulted face
            mesh.toggleFaceSelection(fh);
            for (auto ff = mesh.ff_iter(fh); ff.is_valid(); ++ff)
                stack.push(*ff);
        }
    }



}