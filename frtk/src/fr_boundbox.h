//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
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
#ifndef FR_BOUNDBOX_H
#define FR_BOUNDBOX_H


#include <glm/glm.hpp>
#include<frtk.h>
/**
 * 2D BoundBox class definition.
 */
class cBoundBox2D {
public:
    /**
     * Class constructor.
     * 
     */
    cBoundBox2D();
    ~cBoundBox2D();

public:
    //functions:
    /**
     * Boolean function return true if a point is inside the polygon.
     * 
     * \param point 2D vertex 
     * \return true if the vertex inside the polygon, false if not
     */
    virtual bool isInside(glm::vec2 point);
    /**
     * .
     * 
     * \return 
     */
    /**
     * Calculate diagonal length of the 2D polygon.
     * 
     * \return diagonal length of the 2D polygon
     */
    virtual float DiagonalLength();
    /**
     * .
     * 
     * \return 
     */
    /**
     * Get max value of X in the vertices (Boundbox).
     * 
     * \return float value represent max X
     */
    virtual float XgetMax();
    /**
     * Get max value of Y in the vertices (Boundbox).
     * 
     * \return float value represent max Y
     */
    virtual float YgetMax();
    /**
     * Calculate boundbox which is all max,min, diagonal length, ..etc  values .
     * 
     */
    virtual void calBoundBox();
    /**
     * .
     * 
     * \param points
     */
    virtual void setVertices(std::shared_ptr<std::vector<glm::vec2>>points);
    float minX();  
    float maxX();  
    float minY(); 
    float maxY(); 

    float Xlength();
    float Ylength();

protected:

    float m_minX; //Min X value of the BoundBox
    float m_maxX; //Max X value of the BoundBox
    float m_minY; //Min Y value of the BoundBox
    float m_maxY; //Max Y value of the BoundBox
    
    float m_Xlength;
    float m_Ylength;
    float m_DiagonalLength;
private:
    std::shared_ptr<std::vector<glm::vec2>>m_points;
};


class cBoundBox :public cBoundBox2D{
public:

    cBoundBox();
     ~cBoundBox();
     void calBoundBox();
 public:
     virtual bool isInside(glm::vec3 point);
     virtual float DiagonalLength();
     virtual float ZgetMax();
protected:
    float m_minZ;
    float m_maxZ;

    float m_Zlength;
private:
    std::shared_ptr<std::vector<glm::vec3>>m_points;
};

#endif

/*
 This class represents a bounding box.
 |  A bounding box is a rectangular cuboid which is a way to describe outer
 |  boundaries and is obtained from a lot of 3D types.
 |  It is often used to check if a 3D entity lies in the range of another object.
 |  Checking for bounding interference first can save a lot of computing time!
 |  An invalid BoundBox is represented by inconsistent values at each direction:
 |  The maximum float value of the system at the minimum coordinates, and the
 |  opposite value at the maximum coordinates.
 |
 |  The following constructors are supported:
 |
 |  BoundBox()
 |  Empty constructor. Returns an invalid BoundBox.
 |
 |  BoundBox(boundBox)
 |  Copy constructor.
 |  boundBox : Base.BoundBox
 |
 |  BoundBox(xMin, yMin=0, zMin=0, xMax=0, yMax=0, zMax=0)
 |  Define from the minimum and maximum values at each direction.
 |  xMin : float
 |      Minimum value at x-coordinate.
 |  yMin : float
 |      Minimum value at y-coordinate.
 |  zMin : float
 |      Minimum value at z-coordinate.
 |  xMax : float
 |      Maximum value at x-coordinate.
 |  yMax : float
 |      Maximum value at y-coordinate.
 |  zMax : float
 |      Maximum value at z-coordinate.
 |
 |  App.BoundBox(min, max)
 |  Define from two containers representing the minimum and maximum values of the
 |  coordinates in each direction.
 |  min : Base.Vector, tuple
 |      Minimum values of the coordinates.
 |  max : Base.Vector, tuple
 |      Maximum values of the coordinates.
 |
 |  Method resolution order:
 |      BoundBox
 |      builtins.PyObjectBase
 |      builtins.object
 |
 |  Methods defined here:
 |
 |  __delattr__(self, name, /)
 |      Implement delattr(self, name).
 |
 |  __getattribute__(self, name, /)
 |      Return getattr(self, name).
 |
 |  __init__(self, /, *args, **kwargs)
 |      Initialize self.  See help(type(self)) for accurate signature.
 |
 |  __repr__(self, /)
 |      Return repr(self).
 |
 |  __setattr__(self, name, value, /)
 |      Implement setattr(self, name, value).
 |
 |  add(...)
 |      add(minMax) -> None
 |      add(x, y, z) -> None
 |
 |      Increase the maximum values or decrease the minimum values of this BoundBox by
 |      replacing the current values with the given values, so the bounding box can grow
 |      but not shrink.
 |
 |      minMax : Base.Vector, tuple
 |          Values to enlarge at each direction.
 |      x : float
 |          Value to enlarge at x-direction.
 |      y : float
 |          Value to enlarge at y-direction.
 |      z : float
 |          Value to enlarge at z-direction.
 |
 |  closestPoint(...)
 |      closestPoint(point) -> Base.Vector
 |      closestPoint(x, y, z) -> Base.Vector
 |
 |      Get the closest point of the bounding box to the given point.
 |
 |      point : Base.Vector, tuple
 |          Coordinates of the given point.
 |      x : float
 |          X-coordinate of the given point.
 |      y : float
 |          Y-coordinate of the given point.
 |      z : float
 |          Z-coordinate of the given point.
 |
 |  enlarge(...)
 |      enlarge(variation) -> None
 |
 |      Decrease the minimum values and increase the maximum values by the given value.
 |      A negative value shrinks the bounding box.
 |
 |      variation : float
 |
 |  getEdge(...)
 |      getEdge(index) -> tuple of Base.Vector
 |
 |      Get the edge points of the given index.
 |      The index must be in the range of [0, 11].
 |
 |      index : int
 |
 |  getIntersectionPoint(...)
 |      getIntersectionPoint(base, dir, epsilon=0.0001) -> Base.Vector
 |
 |      Calculate the intersection point of a line with the bounding box.
 |      The base point must lie inside the bounding box, if not an exception is thrown.
 |
 |      base : Base.Vector
 |          Base point of the line.
 |      dir : Base.Vector
 |          Direction of the line.
 |      epsilon : float
 |          Bounding box size tolerance.
 |
 |  getPoint(...)
 |      getPoint(index) ->Base.Vector
 |
 |      Get the point of the given index.
 |      The index must be in the range of [0, 7].
 |
 |      index : int
 |
 |  intersect(...)
 |      intersect(boundBox2) -> bool
 |      intersect(base, dir) -> bool
 |
 |      Checks if the given object intersects with this bounding box. That can be
 |      another bounding box or a line specified by base and direction.
 |
 |      boundBox2 : Base.BoundBox
 |      base : Base.Vector, tuple
 |      dir : Base.Vector, tuple
 |
 |  intersected(...)
 |      intersected(boundBox2) -> Base.BoundBox
 |
 |      Returns the intersection of this and the given bounding box.
 |
 |      boundBox2 : Base.BoundBox
 |
 |  isCutPlane(...)
 |      isCutPlane(base, normal) -> bool
 |
 |      Check if the plane specified by base and normal intersects (cuts) this bounding
 |      box.
 |
 |      base : Base.Vector
 |      normal : Base.Vector
 |
 |  isInside(...)
 |      isInside(object) -> bool
 |      isInside(x, y, z) -> bool
 |
 |      Check if a point or a bounding box is inside this bounding box.
 |
 |      object : Base.Vector, Base.BoundBox
 |          Object to check if it is inside this bounding box.
 |      x : float
 |          X-coordinate of the point to check.
 |      y : float
 |          Y-coordinate of the point to check.
 |      z : float
 |          Z-coordinate of the point to check.
 |
 |  isValid(...)
 |      isValid() -> bool
 |
 |      Checks if the bounding box is valid.
 |
 |  move(...)
 |      move(displacement) -> None
 |      move(x, y, z) -> None
 |
 |      Move the bounding box by the given values.
 |
 |      displacement : Base.Vector, tuple
 |          Displacement at each direction.
 |      x : float
 |          Displacement at x-direction.
 |      y : float
 |          Displacement at y-direction.
 |      z : float
 |          Displacement at z-direction.
 |
 |  scale(...)
 |      scale(factor) -> None
 |      scale(x, y, z) -> None
 |
 |      Scale the bounding box by the given values.
 |
 |      factor : Base.Vector, tuple
 |          Factor scale at each direction.
 |      x : float
 |          Scale at x-direction.
 |      y : float
 |          Scale at y-direction.
 |      z : float
 |          Scale at z-direction.
 |
 |  setVoid(...)
 |      setVoid() -> None
 |
 |      Invalidate the bounding box.
 |
 |  transformed(...)
 |      transformed(matrix) -> Base.BoundBox
 |
 |      Returns a new BoundBox containing the transformed rectangular cuboid
 |      represented by this BoundBox.
 |
 |      matrix : Base.Matrix
 |          Transformation matrix.
 |
 |  united(...)
 |      united(boundBox2) -> Base.BoundBox
 |
 |      Returns the union of this and the given bounding box.
 |
 |      boundBox2 : Base.BoundBox
 |
 |  ----------------------------------------------------------------------
 |  Static methods defined here:
 |
 |  __new__(*args, **kwargs) from builtins.type
 |      Create and return a new object.  See help(type) for accurate signature.
 |
 |  ----------------------------------------------------------------------
 |  Data descriptors defined here:
 |
 |  Center
 |      Center point of the bounding box.
 |
 |  DiagonalLength
 |      Diagonal length of the bounding box.
 |
 |  XLength
 |      Length of the bounding box in x direction.
 |
 |  XMax
 |      The maximum x boundary position.
 |
 |  XMin
 |      The minimum x boundary position.
 |
 |  YLength
 |      Length of the bounding box in y direction.
 |
 |  YMax
 |      The maximum y boundary position.
 |
 |  YMin
 |      The minimum y boundary position.
 |
 |  ZLength
 |      Length of the bounding box in z direction.
 |
 |  ZMax
 |      The maximum z boundary position.
 |
 |  ZMin
 |      The minimum z boundary position.

*/




