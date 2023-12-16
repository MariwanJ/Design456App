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
#ifndef FR_WINDOW_H
#define FR_WINDOW_H
#include <ThreeDWidgets/fr_wgroup.h>

#include <fr_ImGuiLayer.h>
namespace FR {
    class Fr_Window : public Fr_WGroup {
        friend Fr_GL3Window;
    public:
        /**
         * Class constructor for main dummy window object that holds the FR_WIDGET system objects and their properities.
         */

        Fr_Window(glm::vec3 position, std::shared_ptr<std::vector <float>> verticies, std::shared_ptr<std::vector <float>> indicies, std::string label);
        Fr_Window();
/**
 * Class deconstructor.
 */
        ~Fr_Window();
        /**
         * Show the window and it's children by enabling the layer.
         * 
         */
        void show();
        /**
         * Hide the window and it's children by disabling the layer.
         * 
         */
        void hide();

        /**
         * Sets the camera
         * Returns true if the camera has been set
         * Returns the camera info by reference
         */
        virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview) override;

        /**
         * Sets the lights
         * Returns the light info by reference
         */
        virtual void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) override;

        /**
         * Renders the node
         */
        virtual void Render(RenderInfo& info, const glm::mat4& modelview) override;
        
    protected:

        Fr_GL3Window* linkToMainWindow;  //Row pointer otherwise we will not be able to set

    private:
        std::shared_ptr<Fr_ImGuiLayer> m_layer;
    };
}

#endif // !FR_WINDOW_H
