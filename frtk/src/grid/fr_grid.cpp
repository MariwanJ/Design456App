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

#include <grid/fr_grid.h>
#include <grid/fr_grid_shader.h>
//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FR {
	Fr_Grid::Fr_Grid() :Fr_Widget(NULL, NULL, ""), gridShader(0)
	{
		setGridParam();//default values. Otherwise you have to use setGridParam
		type(NODETYPE::FR_GRID);
	}
	/**
	 * .
	 *
	 * \param sections No of line sections. default = 50
	 * \param gridWidth Distance between each line. default = 1mm
	 * \param pos Center of the grid. Default is the origin (0,0,0)
	 * \param scale Scale of the grid - default is (1.0f,1.0f,1.0f)
	 */

	void Fr_Grid::setGridParam(unsigned int sections,
		unsigned int gridWidth,
		glm::vec3 pos,
		glm::vec3 scale) {
		sections_ = sections;
		gridWidth_ = gridWidth;
		scale_ = scale;
		centerPos_ = pos;
		gridColor_ = glm::vec4(FR_DESIGN456_GRID);// (glm::vec4)FR_RED;
	}

	Fr_Grid::~Fr_Grid()
	{
	}

	void Fr_Grid::setCenterPosition(glm::vec3 pos)
	{
		centerPos_ = pos;
	}

	void Fr_Grid::setAngle(float Angle)
	{
		gridRotation_[3] = glm::radians(Angle);
	}

	void Fr_Grid::setRotation(glm::vec4 rotation)
	{
		gridRotation_ = rotation;
	}

	glm::vec4 Fr_Grid::getRotation(void) {
		return gridRotation_;
	}

	void Fr_Grid::setVisible(bool status)
	{
		m_active = status;
	}

	void Fr_Grid::setgridWidth(unsigned int sizeINmm)
	{
		gridWidth_ = sizeINmm;
	}

	unsigned int Fr_Grid::getgridWidth(void) const
	{
		return gridWidth_;
	}
	std::shared_ptr<Fr_GridShader> Fr_Grid::getGridShader() {
		return gridShader;
	}
	void Fr_Grid::CreateGrid()
	{
		std::vector<float> vertices;
		float x, y, z;
		x = y = z = 0;
		float totalLength = gridWidth_ * sections_;
		glm::vec3 limmitValue = glm::vec3(centerPos_[0] - (totalLength / 2), centerPos_[1] - (totalLength / 2), centerPos_[2]);
		//First lines
		for (int i = 0; i <= (sections_); i++) {
			for (int j = 0; j <= sections_; j += sections_) {
				x = limmitValue[0] + i * gridWidth_;
				y = limmitValue[1] + (float)j * gridWidth_;
				z = limmitValue[2];
				if ((x == 0 && y == 0) ||
					(x == 0 && z == 0) ||
					(y == 0 && z == 0)) {
					//We don't draw the axis line as we draw them separately
					continue;
				}
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}
		//Second lines to create the squre plane
		for (int i = 0; i <= (sections_); i++) {
			for (int j = 0; j <= sections_; j += sections_) {
				x = limmitValue[0] + (float)j * gridWidth_;
				y = limmitValue[1] + (float)i * gridWidth_;
				z = limmitValue[2];
				if ((x == 0 && y == 0) ||
					(x == 0 && z == 0) ||
					(y == 0 && z == 0)) {
					//We don't draw the axis line as we draw them separately
					continue;
				}
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}

		std::vector<unsigned int> indices;
		for (int i = 0; i <= vertices.size(); i++) {
			indices.push_back(i);
		}
		std::shared_ptr<Fr_Primatives> primative = std::make_shared<Fr_Primatives>();
		primative->SetVertexes(vertices, indices);
		gridShader = std::make_shared<Fr_GridShader>(); //  color and
		gridShader->SetColor(gridColor_);
		gridShader->SetPrimative(primative);
	}
}