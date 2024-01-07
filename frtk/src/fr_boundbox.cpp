#include "fr_boundbox.h"
cBoundBox2D::cBoundBox2D(): minX(0),maxX(0),
                            minY(0),maxY(0),
                            Xlength(0),Ylength(0)
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
    return 0.0f;
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
    for ( auto vertex : *points) {
        minX = std::min(minX, vertex.x);
        minY = std::min(minY, vertex.y);
 
        maxX = std::max(maxX, vertex.x);
        maxY = std::max(maxY, vertex.y);
 
    }
}

void cBoundBox2D::setVertices(std::shared_ptr<std::vector<glm::vec2>> pnts)
{
    points = pnts;
}

cBoundBox::cBoundBox() :cBoundBox2D(),
                        Zlength(0), 
                        minZ(0),maxZ(0)
{
    minX = maxX = minY = maxY =minZ=maxZ= Xlength = Ylength =0 ;
}

cBoundBox::~cBoundBox()
{
}
void cBoundBox::calBoundBox()
{
    for (auto vertex : *points) {
        minX = std::min(minX, vertex.x);
        minY = std::min(minY, vertex.y);
        minZ = std::min(minZ, vertex.z);
        maxX = std::max(maxX, vertex.x);
        maxY = std::max(maxY, vertex.y);
        maxZ = std::max(maxZ, vertex.z);
    }
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
