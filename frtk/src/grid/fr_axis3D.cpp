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

#include <grid/fr_grid_shader.h>
//Temporary code to have something to show.

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "fr_axis3D.h"
namespace FR {
	Fr_Axis3D::Fr_Axis3D() :Fr_Widget(NULL, NULL, ""), ZstepSize_(10), stepWidth_(10)
	{
	}

	Fr_Axis3D::~Fr_Axis3D()
	{
	}
	std::shared_ptr<Fr_GridShader> Fr_Axis3D::getRed()
	{
		return m_Red;
	}
	std::shared_ptr<Fr_GridShader> Fr_Axis3D::getBlue()
	{
		return m_Blue;
	}
	std::shared_ptr<Fr_GridShader> Fr_Axis3D::getGreen()
	{
		return m_Green;
	}
	std::shared_ptr<Fr_GridShader> Fr_Axis3D::getZBlue()
	{
		return m_ZBlue;
	}

	void Fr_Axis3D::CreateAxis3D()
	{
		float start = 2000.0f;
		float end = -2000.0f;
		float arrow1 = start - 5.0f;
		float arrow2 = 5.0f;
		float zBlueSize = 10.0f;   //The small lines on the Z axis

		std::vector<float> verticesRed;
		std::vector<float> verticesGreen;
		std::vector<float> verticesBlue;
		std::vector<float> verticesZBlue;
		float x, y, z;
		x = y = z = 0;

		glm::vec3 lightColorX(1.0, 0.0, 0.0); // red x

		verticesRed = {
			 end,    0.0f,     0.0f,
			 start,  0.0f,     0.0f,

			 start,  0.0f,     0.0f,
			 arrow1, arrow2,   0.0f,
			 start,  0.0f,     0.0f,
			 arrow1, -arrow2,  0.0f
		};

		glm::vec3 lightColorY(0.0, 1.0, 0.0); // green y

		verticesGreen = {
			0.0f,   end,     0.0f,
			0.0f,   start,   0.0f,

			0.0f,    start,  0.0f,
			arrow2,   arrow1, 0.0f,
			0.0f,    start,  0.0f,
		   -arrow2,  arrow1,  0.0f
		};

		// z
		glm::vec3 lightColorZ(0.0, 0.0, 1.0); // blue z

		verticesBlue = {
			0.0f,  0.0f,    end,
			0.0f,  0.0f,    start,

			0.0f,  0.0f,    start,
			0.0f,  arrow2,  arrow1,
			0.0f,  0.0f,    start,
			0.0f, -arrow2,  arrow1
		};

		std::vector<unsigned int> indicesRed;

		for (int i = 0; i <= verticesRed.size(); i++) {
			indicesRed.push_back(i);
		}
		std::vector<unsigned int> indicesGreen;

		for (int i = 0; i <= verticesGreen.size(); i++) {
			indicesGreen.push_back(i);
		}
		std::vector<unsigned int> indicesBlue;

		std::vector<unsigned int> indicesZBlue;
		//Parallel lines
		for (int i = -500; i <= 500; i = i + ZstepSize_) {
			verticesZBlue.push_back(0.0f);
			verticesZBlue.push_back(float(-zBlueSize / 2));
			verticesZBlue.push_back(float(i));
			verticesZBlue.push_back(0.0f);
			verticesZBlue.push_back(float(zBlueSize / 2));
			verticesZBlue.push_back(float(i));
		}
		for (int i = 0; i <= verticesZBlue.size(); i++) {
			indicesZBlue.push_back(i);
		}

		for (int i = 0; i <= verticesBlue.size(); i++) {
			indicesBlue.push_back(i);
		}

		//For the blue, we add also the vertical line
		auto primativeR = std::make_shared<Fr_Primatives>();
		primativeR->SetVertexes(verticesRed, indicesRed);
		primativeR->lineWidth(5); //THICKER LINE
		m_Red = std::make_shared<Fr_GridShader>(); //  color and
		m_Red->SetColor(glm::vec4(FR_RED));
		m_Red->SetPrimative(primativeR);

		std::shared_ptr <Fr_Primatives>primativeG = std::shared_ptr<Fr_Primatives>(new Fr_Primatives());
		primativeG->SetVertexes(verticesGreen, indicesGreen);
		primativeG->lineWidth(5); //THICKER LINE
		m_Green = std::make_shared<Fr_GridShader>(); //  color and
		m_Green->SetColor(glm::vec4(FR_GREEN));
		m_Green->SetPrimative(primativeG);

		auto primativeB = std::make_shared<Fr_Primatives>();
		primativeB->SetVertexes(verticesBlue, indicesBlue);
		primativeB->lineWidth(5); //THICKER LINE
		m_Blue = std::make_shared<Fr_GridShader>(); //  color and
		m_Blue->SetColor(glm::vec4(FR_BLUE));
		m_Blue->SetPrimative(primativeB);

		auto primativeZB = std::make_shared<Fr_Primatives>();
		primativeZB->SetVertexes(verticesZBlue, indicesZBlue);
		primativeZB->lineWidth(2);
		m_ZBlue = std::make_shared<Fr_GridShader>(); //  color and
		m_ZBlue->SetColor(glm::vec4(FR_YELLOW));
		m_ZBlue->SetPrimative(primativeZB);
	}

	void Fr_Axis3D::setVisible(bool status)
	{
		m_active = status;
	}

	void Fr_Axis3D::setAxisZstepSize(int sizeINmm)
	{
		ZstepSize_ = (int)sizeINmm;
	}

	int Fr_Axis3D::getAxisZstepSize(void) const
	{
		return ZstepSize_;
	}

	void Fr_Axis3D::setStepWidth(int sec)
	{
		stepWidth_ = sec;
	}

	int Fr_Axis3D::getStepWidth(void) const
	{
		return stepWidth_;
	}
}