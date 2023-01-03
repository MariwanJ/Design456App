/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                *
 Copyright (C) 2023                                                     *
                                                                    *
 This library is free software; you can redistribute it and/or          *
 modify it under the terms of the GNU Lesser General Public             *
 License as published by the Free Software Foundation; either           *
 version 2 of the License, or (at your option) any later version.       *
                                                                *
 This library is distributed in the hope that it will be useful,        *
 but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 Lesser General Public License for more details.                        *
                                                                *
 You should have received a copy of the GNU Lesser General Public       *
 License along with this library; if not, If not, see                   *
 <http://www.gnu.org/licenses/>										*
 .																*                                                                       *
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                        *
*/

#ifndef FR_GL3WINDOW_H
#define FR_GL3WINDOW_H


#include <frtk.h>
#include<Fr_Core.h>

class FRTK_API Fr_GL3Window : public Fl_Window {
public:
    Fr_GL3Window(int x, int y, int w, int h, const char* l);
    Fr_GL3Window(int x, int y, int w, int h);
    Fr_GL3Window(int w, int h, const char* l);
    Fr_GL3Window(int w, int h);
    virtual ~Fr_GL3Window();

    virtual void reset(void);
    virtual void resizeGlWindow(int x, int y, int w, int h);
    void resize(int x, int y, int w, int h) override;

    virtual void draw() override;
    virtual void redraw();
    virtual void show() override;
    virtual void gladEvents(int events);
    virtual int handle(int event) override;

protected:
    int  createGLFWwindow();
    int updateGLFWWindow();
private:
    bool overlay;
    //Let FLTK draw over GLFW
    void setOverlay();
    /* Don't draw over GLFW -
    Warning the object will still try to draw but
    it will not be visible */
    void removeOverlya();

    GLuint shaderProgram;
    GLuint vertexArrayObject;
    GLuint vertexBuffer;
    GLint positionUniform;
    GLint colourAttribute;
    GLint positionAttribute;

    int gl_version_major;
    int gl_version_minor;

    static GLFWwindow* pWindow;
    static Fl_Window* FlglWindow;

    HWND glfwHND;
    static bool s_GLFWInitialized;
    static bool s_GladInitialized;

    int _xGl;
    int _yGl;
    int _wGl;
    int _hGl;
};

#endif