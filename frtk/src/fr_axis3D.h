//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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
#include <fr_primativeShader.h>

namespace FR {
	class FRTK_API Axis3D :public Node
	{
	public:
		/**
		 * class constructor.
		 *
		 */

		Axis3D();

		~Axis3D();
		// Copy constructor
		Axis3D(const Axis3D& other)
			:  ZstepSize_(other.ZstepSize_), stepWidth_(other.stepWidth_)
		{
			// Copy the shared pointers if they are not NULL
			m_Red = (other.m_Red != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_Red) : nullptr;
			m_Green = (other.m_Green != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_Green) : nullptr;
			m_Blue = (other.m_Blue != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_Blue) : nullptr;
			m_ZBlue = (other.m_ZBlue != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_ZBlue) : nullptr;
		}


		// Assignment operator
		Axis3D& operator=(const Axis3D& other)
		{
			if (this != &other) // self-assignment check
			{
				Node::operator=(other); // call the base class assignment operator

				// Copy the simple members
				ZstepSize_ = other.ZstepSize_;
				stepWidth_ = other.stepWidth_;

				// Copy the shared pointers if they are not NULL
				m_Red = (other.m_Red != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_Red) : nullptr;
				m_Green = (other.m_Green != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_Green) : nullptr;
				m_Blue = (other.m_Blue != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_Blue) : nullptr;
				m_ZBlue = (other.m_ZBlue != nullptr) ? std::make_shared<Fr_PrimaitiveShader>(*other.m_ZBlue) : nullptr;
			}
			return *this;
		}

		// Move constructor
		Axis3D(Axis3D&& other) noexcept
			:  ZstepSize_(std::exchange(other.ZstepSize_, 0.0f)),
			stepWidth_(std::exchange(other.stepWidth_, 0.0f)),
			m_Red(std::move(other.m_Red)),
			m_Green(std::move(other.m_Green)),
			m_Blue(std::move(other.m_Blue)),
			m_ZBlue(std::move(other.m_ZBlue))
		{
			// Set the moved-from pointers to null or default values as needed
			other.m_Red = nullptr;
			other.m_Green = nullptr;
			other.m_Blue = nullptr;
			other.m_ZBlue = nullptr;
		}

		/**
		 * .
		 */
		std::shared_ptr<Fr_PrimaitiveShader> getRed();
		std::shared_ptr<Fr_PrimaitiveShader> getBlue();
		std::shared_ptr<Fr_PrimaitiveShader> getGreen();
		std::shared_ptr<Fr_PrimaitiveShader> getZBlue();

		void CreateAxis3D();

		/**
		 * Sets the grid visibility.
		 *
		 * \param status boolean variable. If true: Grids shown, if false: Grid is not visible
		 */
		void setVisible(bool status);
		/**
		 * Sets grid size. This is the distance between each line in both axis
		 */
		void setAxisZstepSize(float sizeINmm);
		float getAxisZstepSize(void) const;

		void setStepWidth(float sec);
		float getStepWidth(void) const;

		/**
		 * Create the Grid vertices.
		 *
		 * \return pointer to the created grid
		 */

	private:

		float ZstepSize_;
		float stepWidth_;
		std::shared_ptr<Fr_PrimaitiveShader> m_Red;
		std::shared_ptr<Fr_PrimaitiveShader> m_Green;
		std::shared_ptr<Fr_PrimaitiveShader> m_Blue;
		std::shared_ptr<Fr_PrimaitiveShader> m_ZBlue; //small lines
	};
}
#endif