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

#include<../src/ThreeDWidgets/fr_widget.h>
#include<../src/ThreeDWidgets/fr_draw.h>

namespace FR {
    class FRTK_API Fr_Group : public Fr_Widget {
    public:
        Fr_Group(glm::vec3 position, std::vector<glm::vec3> verticies, std::vector<float> indicies, std::string label);
        Fr_Group() = delete;
        ~Fr_Group();

    protected:
        void draw();
        void draw_children();
        void draw_lbl_children();
        void update_child(std::unique_ptr <Fr_Widget> wd);
    
    public:
        void redraw() override;
        int handel(int events) override;

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
        /**
         * Find a widget and return it's index number.
         */
        virtual int find(std::unique_ptr<Fr_Widget>& wd) const;

        virtual void addWidget(std::unique_ptr <Fr_Widget> wid);
        virtual int insert(std::unique_ptr <Fr_Widget> wd, int index_before);

        virtual int removeWidget(std::unique_ptr <Fr_Widget> wid);
        virtual int removeWidget(int index);

        virtual int tabIndex(std::unique_ptr <Fr_Widget>& wid);
        virtual void tabIndex(std::unique_ptr <Fr_Widget>& wid, int tabIndex);

        virtual void addResizable(std::unique_ptr <Fr_Widget> wd);
        virtual bool Resizable(std::unique_ptr <Fr_Widget>wd);

        std::vector<std::unique_ptr <Fr_Widget>> m_risizable;

    private:

        std::vector < std::unique_ptr <Fr_Widget>> m_children;
    
    
    };
}