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

#include <../src/FR.h>
#include <../src/Fr_Core.h>
#include <../src/fr_node.h>
#include<../src/ThreeDWidgets/fr_draw.h>
#include <stdexcept>
namespace FR {
    typedef struct {
        //TODO : FIXME: This is just a dummy construction. this should be changed later
        union {
            std::string str;
            int val;
        };
    } userData;

    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException() : std::logic_error{ "not implemented." } {}
    };

    class Fr_Widget;
    class Fr_Group;
    class ShaderProgram;
    class Shape;

    /** Default callback type definition for all fltk widgets (by far the most used) */
    typedef void (Fr_Callback)(Fr_Widget*, void*);

    /** Default callback type pointer definition for all fltk widgets */
    typedef Fr_Callback* Fr_Callback_p;

    /** One parameter callback type definition passing only the widget */
    typedef void (Fr_Callback0)(Fr_Widget*);

    /** Callback type definition passing the widget and a long data value */
    typedef void (Fr_Callback1)(Fr_Widget*, long);

    class FRTK_API Fr_Widget : public Node {
        /** Abstract Base class used to create all Widget.
            You need to subclass this object
            to be able to create any widget,
            and you should always have a Fr_Group
            widget which acts like a container for the widgets.
            */
        friend class Fl_Group;
    public:
        /** Copy constructor */
        Fr_Widget(const Fr_Widget&);

        //Default constructor is disallowed
        Fr_Widget() = delete;
        Fr_Widget(glm::vec3 position, std::vector<glm::vec3> verticies, std::vector<float> indicies, std::string label);

        /**
         * Virtual destructor
         */
        virtual ~Fr_Widget();

        // Node functions - donot touch let it be there only and should be subclassed.
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
         * Sets the shadow map
         */
        virtual bool SetupShadowMap(ShadowMapInfo& info) override;

        /**
         * Renders the shadow map
         */
        virtual void RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview) override;

        /**
         * Renders the node
         */
        virtual void Render(RenderInfo& info, const glm::mat4& modelview) override;

        //Fr_Widget functions
        /**
         * main draw function .
         */
        virtual void draw();
        virtual void redraw();

        /**
         * label draw function.
         */
        virtual void lbl_draw();

        virtual void lbl_redraw();
        /**
         *
         */
        void label(std::string& lbl);

        std::string label() const;

        void font(std::string& forntName);

        std::string font() const;

        void fontSize(int size_);

        virtual void resize(std::vector<glm::vec3>& verticies, std::vector<float>& indicies);

        bool active();

        void activate(bool value);

        bool has_focus();

        void has_focus(bool value);

        void visible(bool value);

        bool visible(void);

        /**
        *   Handle events - must be subclassed
        */
        virtual int handel(int handel);

        virtual void show();

        virtual void hide();

        /** Gets the current callback function for the widget.
         Each widget has a single callback.
         \return current callback
      */
        Fr_Callback_p callback() const;

        glm::vec3 getPosition() const;

        //From shader

        virtual  void WidgetShader(glm::vec4 color = glm::vec4(FR_WHITE), float silhouette = 0.005);

        /**
         * Sets the color
         */
        void SetColor(glm::vec4 c);

        /**
         * Sets the opacity
         */
        void SetOpacity(float alpha);

        virtual GLuint getCurrentTexturer(void);

    protected:
        virtual void do_callback();

    private:
        //From shader
        /**
         * Sets the uniform light data
         */
        virtual void LoadLights(ShaderProgram* program, const std::vector<LightInfo>& lights);

        Fr_Callback* m_callback_;
        std::vector <glm::vec3> m_verticies;    //This has 3 float which is the xyz values
        std::vector<float> m_indicies;     // We don´t use glm::vec3 but we can even so use it for Triangle drawing. Decide that by the drawing type.
        glm::vec3 m_position;
        std::string m_label;
        std::string m_fontName;
        int m_fontSize;
        bool m_active;
        bool m_visible;
        bool m_focus;
        int m_type;   //widget type

        static    ShaderProgram* widget_program;

        // Attributes
        glm::vec4 m_color;
        float m_silhouette;
        GLuint m_texture; //used to return the texture for imgui rendering inside window.
    };
}
