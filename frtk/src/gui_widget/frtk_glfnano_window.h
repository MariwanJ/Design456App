#ifndef FRTK_GLFWNANO_WINDOW_H
#define FRTK_GLFWNANO_WINDOW_H

#include <frtk.h>
#include <fr_core.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <nanovg_gl.h> // for OpenGL 3 backend

namespace FR{
class Frtk_GlfwNano_Window {
    public:
        Frtk_GlfwNano_Window(int X, int Y, int W, int H, std::string lbl);
        void setlinkToMain(Fr_Window* window);
        virtual void draw();
        virtual void redraw();
        virtual void show();
        virtual void hide();
        int x();
        int y();
        int w();
        int h();
        void x(int X);
        void y(int Y);
        void w(int W);
        void h(int H);

        void resize(int X, int Y, int W, int H);
        void position(int X, int Y);
        void setDecorated(GLFWwindow* w, bool decorated);

        const std::string& label();

        int run(void);

    protected:
        virtual int handle(int ev);
        
        GLFWwindow *m_glfwWindow;
        int gl_version_major;
        int gl_version_minor;

        std::string m_label;
        glm::vec4 m_color;
        glm::vec4 m_bkg_color;
        NVGcontext* m_vg;
        Fr_Window* m_linkToMainWindow;
private:
    int m_x, m_y, m_w, m_h;
};
}
#endif //FRTK_GLFWNANO_WINDOW_H