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
typedef struct {
    //TODO : FIXME: This is just a dummy construction. this should be changed later 
    union {
        std::string str;
        int val;
    };

} userData;

class FRTK_API Fr_Widget : public Node {
    
    /** Abstract Base class used to create all Widget.
        You need to subclass this object
        to be able to create any widget,
        and you should always have a Fr_Group
        widget which acts like a container for the widgets.
        */
    friend class Fl_Group;
public:

    /** unimplemented copy ctor */
    Fr_Widget(const Fr_Widget&);
    
    /** unimplemented assignment operator */
    Fr_Widget& operator=(const Fr_Widget&);

    Fr_Widget() =delete;
    Fr_Widget(glm::vec3 position,  std::vector<glm::vec3> verticies, std::vector<glm::vec3> indicies, std::string label);

    /**
     * Virtual destructor
     */
    virtual ~Fr_Widget();
protected:
    void do_callback();

// Node functions - donot touch let it be there only and should be subclassed.
public: 
    /**
     * Sets the camera
     * Returns true if the camera has been set
     * Returns the camera info by reference
     */
    virtual bool SetupCamera(glm::mat4& projection, glm::mat4& modelview);

    /**
     * Sets the lights
     * Returns the light info by reference
     */
    virtual void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

    /**
     * Sets the shadow map
     */
    virtual bool SetupShadowMap(ShadowMapInfo& info);

    /**
     * Renders the shadow map
     */
    virtual void RenderShadowMap(ShadowMapInfo& info, const glm::mat4& modelview);

    /**
     * Renders the node
     */
    virtual void Render(RenderInfo& info, const glm::mat4& modelview);

            //Fr_Widget functions
public:
    /**
     * main draw function .
     */
    virtual void draw();
    
    /**
     * label draw function.
     */
    virtual void lbl_draw();

    /**
     * .
     */
    void label(std::string& lbl);
    
    std::string label() const;

    void font(std::string &forntName);

    std::string font() const;

    void fontSize(int size_);

    virtual void resize(std::vector<glm::vec3>& verticies, std::vector<glm::vec3>& indicies);

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


private:
    std::vector<glm::vec3>& m_verticies;
    std::vector<glm::vec3>& m_indicies;
    std::string m_label;
    std::string m_fontName;
    int m_fontSize;
    bool m_active;
    bool m_visible;


};