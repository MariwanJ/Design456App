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

#ifndef FR_Fr_Axis3D_H
#define FR_Fr_Axis3D_H
#include <frtk.h>
#include <fr_core.h>
#include <fr_transform.h>

#include <halfedge/fr_shape.h>
#include <fr_widget.h>
#include <fr_light.h>
#include <grid/fr_primatives.h>
#include <grid/fr_grid_shader.h>

namespace FR {
    class FRTK_API Fr_Axis3D :public Fr_Widget
    {
    public:
        /**
         * class constructor.
         *
         */

        Fr_Axis3D();

        ~Fr_Axis3D();
        std::shared_ptr<Fr_GridShader> getRed();
        std::shared_ptr<Fr_GridShader> getBlue();
        std::shared_ptr<Fr_GridShader> getGreen();
        std::shared_ptr<Fr_GridShader> getZBlue();

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
        void setAxisZstepSize(int sizeINmm);
        int getAxisZstepSize(void) const;

        void setStepWidth(int sec);
        int getStepWidth(void) const;
        

    private:

        int ZstepSize_;
        int stepWidth_;
        std::shared_ptr<Fr_GridShader> m_Red;
        std::shared_ptr<Fr_GridShader> m_Green;
        std::shared_ptr<Fr_GridShader> m_Blue;
        std::shared_ptr<Fr_GridShader> m_ZBlue; //small lines
    };
}
#endif