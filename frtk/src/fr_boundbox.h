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
    glm::vec2 Center();

protected:

    float m_minX; //Min X value of the BoundBox
    float m_maxX; //Max X value of the BoundBox
    float m_minY; //Min Y value of the BoundBox
    float m_maxY; //Max Y value of the BoundBox
    
    float m_Xlength;
    float m_Ylength;
    float m_DiagonalLength;

private: 
    glm::vec2 m_center;
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
     glm::vec3 Center();

protected:
    float m_minZ;
    float m_maxZ;

    float m_Zlength;
private:
    std::shared_ptr<std::vector<glm::vec3>>m_points;
    glm::vec3 m_center;
};

#endif