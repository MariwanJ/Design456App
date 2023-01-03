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


//#include <GLFW/glfw3.h>
//#include <GLFW/glfw3native.h>
#include<Fr_GL3Window.h>


GLuint m_QuadVA, m_QuadVB, m_QuadIB;
bool s_GLFWInitialized;
#define border 60


GLFWwindow* Fr_GL3Window::pWindow = nullptr;
Fl_Window* Fr_GL3Window::FlglWindow = nullptr;

bool Fr_GL3Window::s_GLFWInitialized = false;
bool Fr_GL3Window::s_GladInitialized = false;

Fr_GL3Window::Fr_GL3Window(int w, int h, const char* l) : Fl_Window(0, 0, w, h, l) {}
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h) : Fl_Window(x, y, w, h, "") {}
Fr_GL3Window::Fr_GL3Window(int w, int h) : Fl_Window(0, 0, w, h, "") {}

static int counter = 0;
Fr_GL3Window::Fr_GL3Window(int x, int y, int w, int h, const char* l) : Fl_Window(x, y, w, h, l),overlay(true) {
	/*
	* from https://discourse.glfw.org/t/attach-a-glfwwindow-to-windows-window-client-area/882/5:
	*
	BEFORE you #include your glfw includes, define the native win32 glfw exposure such as:

	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3.h>
	#include <GLFW/glfw3native.h>

	Next, make sure to include the glfw3native.h as shown above. Clean and rebuild and you should then have access to the function �HWND glfwGetWin32Window(GLFWwindow *window)� which returns a HWND handle from your GLFWwindow
	Next, create a static control or dialog to use as the parent.
	Somehwere in your code after both the control/dialog and GLFWwindow have been instanciated get the HWND handle and change its style to be a chiild as follows:

	DWORD style = GetWindowLong(handle, GWL_STYLE); //get the b style
	style &= ~(WS_POPUP | WS_CAPTION); //reset the �caption� and �popup� bits
	style |= WS_CHILD; //set the �child� bit
	SetWindowLong(handle, GWL_STYLE, style); //set the new style of b
	The
	window->SetParent(control);
	window->MoveWindow(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top); //place b at (x,y,w,h) in a
	control->UpdateWindow();
	*/

	//TODO FIXME//

	_xGl = border;
	_yGl = border;
	_wGl = w - border;
	_hGl = h - border;
	gl_version_major = 3;
	gl_version_minor = 3;

	if (!s_GLFWInitialized)
	{
		int success = glfwInit();
		//FRTK_CORE_ASSERT(success, "Could not intialize GLFW!");
		//glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialized = true;
	}
	//Hint to GLFW  - Window is visible, not decorated and gl version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	pWindow = glfwCreateWindow(_wGl, _hGl, "", NULL, NULL);
	//callbacks  https://www.glfw.org/docs/3.3/input_guide.html
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
	glfwSetKeyCallback(pWindow, keyboard_callback);
	glfwSetCursorPosCallback(pWindow, cursor_position_callback);
	glfwSetCursorEnterCallback(pWindow, cursor_enter_callback);
	glfwSetMouseButtonCallback(pWindow, mouse_button_callback);
	glfwSetScrollCallback(pWindow, scroll_callback);
	//glfwSetJoystickCallback(joystick_callback);




	end();
}


Fr_GL3Window::~Fr_GL3Window()
{
    glfwDestroyWindow(pWindow);
    pWindow = nullptr;
    Fl_Window::~Fl_Window();
}

void Fr_GL3Window::draw() {
    if (overlay) {
        Fl_Window::draw();
        updateGLFWWindow();
        //FRTK_CORE_INFO("[DRAW BOTH] {0}");
        printf("overlay%i\n", counter);
        counter++;
    }
    else {
        updateGLFWWindow();
        Fl_Window::draw();
        printf("not overlay%i\n", counter);
        counter++;
    }
}

void Fr_GL3Window::reset() {
	shaderProgram = 0;
	gl_texture_reset();
}

void Fr_GL3Window::resizeGlWindow(int _xG, int _yG, int _wG, int _hG)
{
    if (pWindow != nullptr) {
        glfwSetWindowPos(pWindow, _xG, _yG);
        glfwSetWindowSize(pWindow, _wG, _hG);
        //printf("xgl=%i ygl=%i wgl=%i hgl=%i\n", _xG, _yG, _wG, _hG);
    }
}

int Fr_GL3Window::handle(int event) {
    return Fl_Window::handle(event);
}

int Fr_GL3Window::createGLFWwindow()
{
	//GWLF Window construction
	FlglWindow = this;
	int result = 0;
	if (pWindow != nullptr)  {
		glfwMakeContextCurrent(pWindow);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 1)
			s_GladInitialized = true;
		else
			s_GladInitialized = false;

		if (!s_GladInitialized) {
			std::cout << "Sorry check your code, glad is not initialized\n";
		}
		glfwSwapInterval(1);  // GLFW Update rate - interval
		//GLFW_EXPOSE_NATIVE_WIN32
		HWND glfwHND = glfwGetWin32Window(pWindow);
		HWND hwParentWindow = fl_win32_xid(FlglWindow);

		if (hwParentWindow == 0) {
			printf("Failed to get HWND of the window please debugme!!\n");
			return result;
		}

		DWORD style = GetWindowLong(glfwHND, GWL_STYLE); //get the b style
		style &= ~(WS_POPUP | WS_CAPTION); //reset the �caption� and �popup� bits
		style |= WS_CHILD; //set the �child� bit
		style |= WS_OVERLAPPED;
		SetWindowLong(glfwHND, GWL_STYLE, style); //set the new style of b
		MoveWindow(glfwHND, _xGl, _yGl, _wGl, _hGl, true); //place b at (x,y,w,h) in a
		SetParent(glfwHND, hwParentWindow);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ShowWindow(glfwHND, SW_SHOW);
		glfwGetFramebufferSize(pWindow, &_wGl, &_hGl);
		glViewport(_xGl, _yGl, _wGl, _hGl);
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

	UpdateWindow(glfwHND);
	result = 1;
	}
	return result;
}

int Fr_GL3Window::updateGLFWWindow()
{
    UpdateWindow(glfwHND);
    glfwSwapBuffers(pWindow);
    glfwPollEvents();
    return 0;
}

void Fr_GL3Window::setOverlay()
{
    overlay = true;
}

void Fr_GL3Window::removeOverlya()
{
    overlay = false;
}

void Fr_GL3Window::show() {
    Fl_Window::show();
    //Create the GLFW Window
    if (createGLFWwindow() != 0) {
        unsigned int id = 0;
        glGenVertexArrays(1, &id);
        if (s_GladInitialized == true) {
            glad_glClearColor(0.0, 1.0, 0.0, 1.0);
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            UpdateWindow(glfwHND);
        }
    }
}

void Fr_GL3Window::gladEvents(int events)
{
}

void Fr_GL3Window::resize(int x, int y, int w, int h)
{
    _xGl = border;
    _yGl = border;
    _wGl = w - 2 * border;
    _hGl = h - 2 * border;
    printf("x=%i y=%i w=%i h=%i\n", x, y, w, h);

    resizeGlWindow(_xGl, _yGl, _wGl, _hGl);
    if (s_GladInitialized) {
        glViewport(_xGl, _yGl, _wGl, _hGl);
    }
    Fl_Window::resize(x, y, w, h);
    redraw();
    //updateGLFWWindow();
}

void Fr_GL3Window::redraw()
{
    Fl_Window::damage(FL_DAMAGE_ALL);
    Fl_Window::redraw();
    updateGLFWWindow();
}
