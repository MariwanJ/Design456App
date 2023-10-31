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

#ifndef FR_GRID_H
#define FR_GRID_H

#include<frtk.h>
#include<fr_core.h>
#include <fr_transform.h>
#include <fr_mesh.h>
#include<halfEdge/fr_new_mesh.h>
#include <fr_node.h>
#include <fr_light.h>
#include <fr_primatives.h>

//Temporary code - just for debuggin
std::shared_ptr<Transform>bunny();
//End Temporary code

class Grid :public Node
{
public:
    /**
     * class constructor.
     *
     */
    Grid();

    void setGridParam(unsigned int sections = 100, unsigned int gridWidth = 10, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(0.0f, 0.0f, 0.0f));
    /**
     * Class destructor.
     *
     */
    ~Grid();
    /**
     * Sets the position of the grid.
     *
     * \param pos Vertext that is the center of the grid
     */
    void setCenterPosition(glm::vec3 pos);
    /**
     * Sets Angle of rotation and the axis of rotation.
     *
     * \param axis 3 floats - Axis of rotation
     * \param angle Angle of rotation in degrees
     */
    void setAngle(float Angle);

    /**
     * Set Grid rotation.
     *
     * \param rotation 4 float : axis and an angle
     */
    void setRotation(glm::vec4 rotation);
    /**
     * Get rotation axis and angle in radians.
     *
     * \return
     */
    glm::vec4 getRotation(void);
    /**
     * Sets the grid visibility.
     *
     * \param status boolean variable. If ture: Grids shown, if false: Grid is not visible
     */
    void setVisible(bool status);
    /**
     * Sets grid size. This is the distance between each line in both axis
     */
    void setgridWidth(unsigned int sizeINmm);
    /**
     * Returns the grid size.
     *
     * \return gird size defined previously
     */
    unsigned int getgridWidth(void) const;

    /**
     * Create the Grid verticies.
     *
     * \return pointer to the created grid
     */
    std::shared_ptr<Transform>CreateGrid();
private:

    int sections_; //No of lines in both directions
    int gridWidth_; //Distance between each line in mm. This will be affected by the scale
    glm::vec3 scale_; //Scale the whole grid - Be careful this affects the distance value.
    glm::vec3 centerPos_;//Center of the grid
    glm::vec4 gridRotation_; //(Axis, angle) 4 float values
    glm::vec4 gridColor_;
};

#endif