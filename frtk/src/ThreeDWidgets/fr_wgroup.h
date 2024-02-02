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

#ifndef FR_WGROUP_H
#define FR_WGROUP_H

#include<../src/ThreeDWidgets/fr_widget.h>
namespace FR {
    class FRTK_API Fr_WGroup : public Fr_Widget {
    public:
        Fr_WGroup(glm::vec3 position, std::shared_ptr<std::vector <float>> verticies, std::shared_ptr<std::vector <unsigned int>> indicies, std::string label);
        Fr_WGroup() = delete;
        ~Fr_WGroup();

    protected:
        void draw();
        void draw_children();
        void draw_lbl_children();
        void update_child(std::shared_ptr <Fr_Widget> wd);

    public:
        /**
         * Something happened to the widget and it needs to be redrawn immediately
         *
         */
        void redraw() override;
        /**
         * Handle is a very important function that take care of all events happen (mouse, keyboard or between widgets).
         * Whenever a widget consumes the events, it should return 0. FR_NO_EVENTS means that there is no more events left.
         * But if a widget uses the event but want to return the event to the system, it should return Fr_WGroup::handle(e).
         * or if the widget didn't care about the event, it should also return either 1 or Fr_WGroup::handle(e).
         *
         * \param events
         * \return
         */
        int handle(int events) override;

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
        virtual int find(std::shared_ptr<Fr_Widget>& wd) const;
        /**
         * Add new widget to the group.
         *
         * \param wid : shared pointer to a widget that will be added
         */
        virtual void addWidget(std::shared_ptr <Fr_Widget> wid);

        /**
         * Insert the widget at a specific position in the vector.
         *
         * \param wd shared pointer to a widget that will be added
         * \param index_before Position where the widget will be inserted (added)
         * \return
         */
        virtual int insert(std::shared_ptr <Fr_Widget> wd, int index_before);
        /**
         * Remove a widget from the group by getting a shared pointer to the widget.
         *
         * \param wid Shared pointer to the widget
         * \return
         */
        virtual int removeWidget(std::shared_ptr <Fr_Widget> wid);
        /**
         * Remove a widget by it's position int the vector.
         *
         * \param index
         * \return
         */
        virtual int removeWidget(int index);
        /**
         * Return the tab information of the widget which determines how TAB key move focus from a widg to another.
         *
         * \param wid Shared pointer to a widget
         * \return
         */
    private:
        std::vector < std::shared_ptr <Fr_Widget>> m_children;
    };
}
#endif