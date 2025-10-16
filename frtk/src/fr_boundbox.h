//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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


#include <frtk.h>
#include <fr_core.h>
#include <glm/glm.hpp>
/**
 * 2D BoundBox class definition.
 */
namespace FR {
    //***********************************************************************************************************
    class cBoundBox3D {
    public:
        cBoundBox3D(bool type = false);
        ~cBoundBox3D();

        void Boxtype(bool val);

        bool Boxtype();

        //functions:
      /**
       * Boolean function return true if a point is inside the polygon.
       *
       * \param point 2D vertex
       * \return true if the vertex inside the polygon, false if not
       */
        virtual bool isInside(glm::vec3 point);

        bool isRayInsideBoundingBox(const ray_t & Ray);

        /**
         * Find the center of the 3D BoundBox.
         *
         * \return
         */
        glm::vec3 Center();

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
        virtual void calBoundBox();
        /**
         * .
         *
         * \param points
         */
        virtual void setVertices(std::shared_ptr<std::vector<float>>points);
        /**
         * .
         *
         * \return
         */
        float maxX();
        float minX();
        float maxY();
        float minY();
        float maxZ();
        float minZ();

        float Xlength();
        float Ylength();
        float Zlength();

    protected:

        float m_minX; //Min X value of the BoundBox
        float m_maxX; //Max X value of the BoundBox
        float m_minY; //Min Y value of the BoundBox
        float m_maxY; //Max Y value of the BoundBox
        float m_minZ; //Min Z value of the BoundBox
        float m_maxZ; //Max Z value of the BoundBox

        float m_Xlength;
        float m_Ylength;
        float m_Zlength;

        float m_DiagonalLength;
        std::shared_ptr<std::vector<float>>m_points;

    private:
        glm::vec3 m_center;
        bool m_boxType;
    };
}
#endif