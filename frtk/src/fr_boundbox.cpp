#include "fr_boundbox.h"
cBoundBox2D::cBoundBox2D(): m_minX(0.0f),m_maxX(0.0f),
                            m_minY(0.0f),m_maxY(0.0f),
                            m_Xlength(0.0f),m_Ylength(0.f),
                            m_DiagonalLength(0.0f), m_center(0.0f,0.0f)
{
}

cBoundBox2D::~cBoundBox2D()
{
}

bool cBoundBox2D::isInside(glm::vec2 point)
{
    return false;
}

float cBoundBox2D::DiagonalLength()
{
    return m_DiagonalLength;
}

float cBoundBox2D::XgetMax()
{
    return 0.0f;
}

float cBoundBox2D::YgetMax()
{
    return 0.0f;
}

void cBoundBox2D::calBoundBox()
{
    for ( auto vertex : *m_points) {
        m_minX = std::min(m_minX, vertex.x);
        m_minY = std::min(m_minY, vertex.y);
 
        m_maxX = std::max(m_maxX, vertex.x);
        m_maxY = std::max(m_maxY, vertex.y);
    }
    m_Xlength = m_maxX - m_minX;
    m_Ylength = m_maxY - m_minY;
    m_DiagonalLength= std::sqrt(m_Xlength* m_Xlength+ m_Ylength* m_Ylength);
    m_center = glm::vec2((m_minX + m_maxX) / 2, (m_minY + m_maxY) / 2);
}

void cBoundBox2D::setVertices(std::shared_ptr<std::vector<glm::vec2>> pnts)
{
    m_points = pnts;
}

float cBoundBox2D::minX()
{
    return 0.0f;
}

float cBoundBox2D::maxX()
{
    return 0.0f;
}

float cBoundBox2D::minY()
{
    return 0.0f;
}

float cBoundBox2D::maxY()
{
    return 0.0f;
}

float cBoundBox2D::Xlength()
{
    return 0.0f;
}

float cBoundBox2D::Ylength()
{
    return 0.0f;
}

glm::vec2 cBoundBox2D::Center()
{
    return m_center;
}

cBoundBox::cBoundBox() :cBoundBox2D(),
                        m_Zlength(0.0f), 
                        m_minZ(0.0f),m_maxZ(0.0f),m_center(0.0f,0.0f,0.0f)
{
    m_minX = m_maxX = m_minY = m_maxY = m_minZ= m_maxZ= m_Xlength = m_Ylength =0 ;
}

cBoundBox::~cBoundBox()
{
}
void cBoundBox::calBoundBox()
{
    for (auto vertex : *m_points) {
        m_minX = std::min(m_minX, vertex.x);
        m_minY = std::min(m_minY, vertex.y);
        m_minZ = std::min(m_minZ, vertex.z);
        m_maxX = std::max(m_maxX, vertex.x);
        m_maxY = std::max(m_maxY, vertex.y);
        m_maxZ = std::max(m_maxZ, vertex.z);
    }
    m_Xlength = m_maxX - m_minX;
    m_Ylength = m_maxY - m_minY;
    m_Zlength = m_maxZ - m_minZ;
    
    m_DiagonalLength = std::sqrt(m_Xlength * m_Xlength + m_Ylength * m_Ylength+ m_Zlength * m_Zlength);
    m_center = glm::vec3((m_minX + m_maxX) / 2,
                         (m_minY + m_maxY) / 2,
                         (m_minZ + m_maxZ) / 2);
}
bool cBoundBox::isInside(glm::vec3 point)
{
    return false;
}

float cBoundBox::DiagonalLength()
{
    return 0.0f;
}

float cBoundBox::ZgetMax()
{
    return 0.0f;
}

glm::vec3 cBoundBox::Center()
{
    return m_center;
}
