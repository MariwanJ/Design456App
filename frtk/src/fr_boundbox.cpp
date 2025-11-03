#include <fr_boundbox.h>
#include<fr_core.h>

namespace FR {
    //******************************************************************************************************
    cBoundBox3D::cBoundBox3D(bool type) :m_threeD(type)
    {
        m_minX = m_maxX = m_minY = m_maxY = m_minY = m_maxY = m_Xlength = m_Ylength = m_Zlength = m_minZ = m_maxZ = 0.0f;
        pad = 0.5f;
    }

    float cBoundBox3D::minX()
    {
        return m_minX;
    }

    float cBoundBox3D::maxX()
    {
        return m_maxX;
    }

    float cBoundBox3D::minY()
    {
        return m_minY;
    }

    float cBoundBox3D::maxZ()
    {
        return m_maxZ;
    }
    float cBoundBox3D::minZ()
    {
        return m_minZ;
    }
    float cBoundBox3D::maxY()
    {
        return m_maxY;
    }
    float cBoundBox3D::Xlength()
    {
        return abs(m_maxX - m_minX);
    }

    float cBoundBox3D::Ylength()
    {
        return abs(m_maxY - m_minY);
    }

    float cBoundBox3D::Zlength()
    {
        return abs(m_maxZ - m_minZ);
    }

    cBoundBox3D::~cBoundBox3D()
    {
    }
    void cBoundBox3D::ThreeD(bool val)
    {
        m_threeD = val;
    }
    bool cBoundBox3D::ThreeD()
    {
        return m_threeD;
    }
    void cBoundBox3D::calBoundBox()
    {
        if (m_points->empty()) {
            m_minX = m_minY = m_minZ = std::numeric_limits<float>::max();
            m_maxX = m_maxY = m_maxZ = std::numeric_limits<float>::lowest();
            return;
        }
        m_minX = m_maxX = (*m_points)[0];
        m_minY = m_maxY = (*m_points)[1];
        m_minZ = m_maxZ = (*m_points)[2];

        for (size_t i = 0; i < m_points->size(); i += 3) {
            m_minX = std::min(m_minX, (*m_points)[i]);
            m_minY = std::min(m_minY, (*m_points)[i + 1]);
            m_minZ = std::min(m_minZ, (*m_points)[i + 2]);

            m_maxX = std::max(m_maxX, (*m_points)[i]);
            m_maxY = std::max(m_maxY, (*m_points)[i + 1]);
            m_maxZ = std::max(m_maxZ, (*m_points)[i + 2]);
        }

        m_minX -= pad; m_maxX += pad;
        m_minY -= pad; m_maxY += pad;
        m_minZ -= pad; m_maxZ += pad;

        m_Xlength = abs(m_maxX - m_minX);
        m_Ylength = abs(m_maxY - m_minY);
        m_Zlength = abs(m_maxZ - m_minZ);

        DiagonalLength();
        Center();
    }

    void cBoundBox3D::setVertices(std::shared_ptr<std::vector<float>> pnts)
    {
        m_points = pnts;
        calBoundBox(); 
    }

    float cBoundBox3D::DiagonalLength()
    {
        m_DiagonalLength = std::sqrt(m_Xlength * m_Xlength + m_Ylength * m_Ylength + m_Zlength * m_Zlength);
        return m_DiagonalLength;
    }

    glm::vec3 cBoundBox3D::Center()
    {
        m_center = glm::vec3((m_minX + m_maxX) / 2,
            (m_minY + m_maxY) / 2,
            (m_minZ + m_maxZ) / 2);
        return m_center;
    }
    bool cBoundBox3D::isInside(glm::vec3 point)
    {
        if (m_minZ == -1 && m_maxZ == -1)
            return ((point.x >= m_minX && point.x <= m_maxX) &&
                (point.y >= m_minY && point.y <= m_maxY));
        else
            return ((point.x >= m_minX && point.x <= m_maxX) &&
                (point.y >= m_minY && point.y <= m_maxY) &&
                (point.z >= m_minZ && point.z <= m_maxZ));
    }

    /**
     * Find out if a ray is inside a bound box of an object.
     *
     * \param Ray  rat_t struct consists of two vectors, direction and position
     * \return true if the ray is inside the boundbox otherwise false.
     */
    bool cBoundBox3D::isRayInsideBoundingBox(const ray_t& Ray)
    {
        /*
                https://tavianator.com/2022/ray_box_boundary.html
        */
        bool result = true;
        glm::vec3 invDir = 1.0f / glm::vec3(
            Ray.direction.x != 0.0f ? Ray.direction.x : 1e-8f,
            Ray.direction.y != 0.0f ? Ray.direction.y : 1e-8f,
            Ray.direction.z != 0.0f ? Ray.direction.z : 1e-8f
        );

        float tmin = (m_minX - Ray.position.x) * invDir.x;
        float tmax = (m_maxX - Ray.position.x) * invDir.x;
        if (tmin > tmax)
            std::swap(tmin, tmax);

        float tymin = (m_minY - Ray.position.y) * invDir.y;
        float tymax = (m_maxY - Ray.position.y) * invDir.y;
        if (tymin > tymax)
            std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)){
            result = false;
        }
        else {
            tmin = std::max(tmin, tymin);
            tmax = std::min(tmax, tymax);

            float tzmin = (m_minZ - Ray.position.z) * invDir.z;
            float tzmax = (m_maxZ - Ray.position.z) * invDir.z;
            if (tzmin > tzmax)
                std::swap(tzmin, tzmax);

            if ((tmin > tzmax) || (tzmin > tmax)) {
                result = false;
            }
            else {
                tmin = std::max(tmin, tzmin);
                tmax = std::min(tmax, tzmax);

                if (tmax < 0 || tmin > tmax) {
                    result = false;
                }
                else{
                    result = true;
                }
            }
        }
        if (result)
            FRTK_CORE_INFO("inside boundbox\n");
        else
            FRTK_CORE_INFO("not inside boundbox\n");
        return result;
    }
}