#include "Axis3D.h"

#include <ObjectShaderNode.h>
#include <fr_primativeShader.h>
//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Axis3D::~Axis3D()
{
}

void Axis3D::setCenterPosition(glm::vec3 pos)
{
    centerPos_ = pos;
}

void Axis3D::setAngle(float Angle)
{
    axis3DRotation_[3] = glm::radians(Angle);
}

void Axis3D::setRotation(glm::vec4 rotation)
{
    axis3DRotation_ = rotation;
}

glm::vec4 Axis3D::getRotation(void) {
    return axis3DRotation_;
}

void Axis3D::setVisible(bool status)
{
    active_ = status;
}

void Axis3D::setAxis3DSize(unsigned int sizeINmm)
{
    axis3DSize_ = sizeINmm;
}

unsigned int Axis3D::getAxis3DSize(void) const
{
    return axis3DSize_;
}

std::shared_ptr<Transform> Axis3D::CreateAxis3D()
{

}