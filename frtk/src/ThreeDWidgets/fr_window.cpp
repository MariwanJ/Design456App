#include "fr_window.h"
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

/**
 *
 * This object is a container for the FR_WIDGETS. It has important widget method, property and is their parent :
 * 1- Deliver events
 * 2- Keep track of widgets, add, remove,
 * 3- Layer responsible for the whole FR_WIDGET system (ONLY ONE LAYER AT THE MOMENT, THIS IS A DESIGN QUESTION THAT DONT KNOW KNOW
 * .
 */
namespace FR {
    Fr_Window::Fr_Window(glm::vec3 position, std::shared_ptr<std::vector<float>> verticies,
                         std::shared_ptr<std::vector<float>> indicies, std::string label) : 
                        Fr_WGroup(position,verticies,indicies,label),
                        m_layer(std::make_shared<Fr_ImGuiLayer>())
    {
    }
    /**
     * Default constructor required by Fr_GL3Window.
     * 
     */
    Fr_Window::Fr_Window() :Fr_WGroup(glm::vec3(0.f,0.f,0.f),NULL,NULL,"")
    {

    }

    Fr_Window::~Fr_Window()
    {
    }

    void Fr_Window::show()
    {
        m_layer->Visible(true);
    }

    void Fr_Window::hide()
    {
        m_layer->Visible(false);
    }
    bool Fr_Window::SetupCamera(glm::mat4& projection, glm::mat4& modelview)
    {
        if (m_layer)
            return Fr_WGroup::SetupCamera(projection, modelview);
        else
            return false;
    }
    void Fr_Window::SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights)
    {
        if (m_layer)
            Fr_WGroup::SetupLight(modelview, lights);   //Only if the layer is active
    }
    void Fr_Window::Render(RenderInfo& info, const glm::mat4& modelview)
    {
        if (m_layer)
            Fr_WGroup::Render(info, modelview);   //Only if the layer is active
    }
}