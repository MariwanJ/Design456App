#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp> // For glm::distance2
#include<fr_checkIntersection.h>
#include <fr_window.h>
namespace FR {
    // Small epsilon for floating-point checks
    constexpr float EPSILON = 1e-6f;

    // =====================================================
    // 1. Vertex Picking
    // =====================================================
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
        printf("Ray was (%2.0f,%2.0f,%2.0f  ) ", rayDir.x, rayDir.y, rayDir.z);
        printf("%f it was \n", distanceToRay);
        return distanceToRay <= tolerance; // Check if within tolerance
    }

    // =====================================================
    // 2. Line Segment Picking
    // =====================================================
    bool intersectLineSegment3D(const std::vector<glm::vec3>& line, const ray_t& ray, glm::vec3& intersectionPoint, float pickingRadius) {
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

        if (distance <= pickingRadius) {
            intersectionPoint = pointOnSegment;
            return true;
        }
        return false;
    }

    // =====================================================
    // 3. Triangle Picking (Möller–Trumbore)
    // =====================================================
    bool intersectRayTriangle(const ray_t& ray, const std::vector<glm::vec3>& triangle,
        glm::vec3& intersectionPoint) {
        if (triangle.size() < 3) return false;

        glm::vec3 v0 = triangle[0];
        glm::vec3 v1 = triangle[1];
        glm::vec3 v2 = triangle[2];

        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;

        glm::vec3 h = glm::cross(ray.direction, edge2);
        float a = glm::dot(edge1, h);

        if (fabs(a) < EPSILON)
            return false; // Ray parallel to triangle

        float f = 1.0f / a;
        glm::vec3 s = ray.position - v0;
        float u = f * glm::dot(s, h);

        if (u < 0.0f || u > 1.0f)
            return false;

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(ray.direction, q);

        if (v < 0.0f || u + v > 1.0f)
            return false;

        float t = f * glm::dot(edge2, q);
        if (t > EPSILON) {
            intersectionPoint = ray.position + t * ray.direction;
            return true;
        }

        return false;
    }

    // =====================================================
    // 4. Polygon Picking (Triangle Fan)
    // =====================================================
    bool intersectRayPolygon(const ray_t& ray, const std::vector<glm::vec3>& polygon,
        glm::vec3& intersectionPoint) {
        if (polygon.size() < 3)
            return false;

        glm::vec3 v0 = polygon[0];

        // Fan triangulation: only valid for convex polygons
        for (size_t i = 1; i < polygon.size() - 1; ++i) {
            std::vector<glm::vec3> tri = { v0, polygon[i], polygon[i + 1] };
            if (intersectRayTriangle(ray, tri, intersectionPoint)) {
                return true;
            }
        }
        return false;
    }

}