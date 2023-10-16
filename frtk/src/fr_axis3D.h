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

#ifndef FR_AXIS3D_H
#define FR_AXIS3D_H

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

typedef struct vert{
	std::shared_ptr<Transform> Red;
	std::shared_ptr<Transform> Green;
	std::shared_ptr<Transform> Blue;
	std::shared_ptr<Transform> ZBlue; //small lines
};

class Axis3D :public Node
{
public:
/**
 * class constructor.
 *
 */

	Axis3D();

	~Axis3D();
	/**
	 * .
	 */

	vert CreateAxis3D();

	/**
	 * Sets the grid visibility.
	 *
	 * \param status boolean variable. If true: Grids shown, if false: Grid is not visible
	 */
	void setVisible(bool status);
	/**
	 * Sets grid size. This is the distance between each line in both axis
	 */
	void setAxisZstepSize( float sizeINmm);
	float getAxisZstepSize(void) const;


	void setStepWidth(float sec);
	float getStepWidth(void) const;

	/**
	 * Create the Grid verticies.
	 *
	 * \return pointer to the created grid
	 */

private:

	float ZstepSize_;
	glm::vec4 axis3DColor_;
	float stepWidth_;
};

#endif