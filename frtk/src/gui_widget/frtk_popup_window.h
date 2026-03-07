#ifndef FRTK_POPUP_WINDOW_H
#define FRTK_POPUP_WINDOW_H

#include <frtk.h>
#include <fr_core.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <nanovg_gl.h> // for OpenGL 3 backend
#include <gui_widget/frtk_grpwidget.h>

namespace FR{
class Frtk_Popup_Window : public Frtk_GrpWidget{
    public:
        Frtk_Popup_Window(int X, int Y, int W, int H, std::string lbl, BOX_TYPE b = FRTK_UP_BOX);
        void setlinkToMain(Fr_Window* window);
        virtual void redraw() override;
        virtual void show() override;
        virtual void hide();
        virtual void resize(float X, float Y, float W, float H);
        virtual void position(float X, float Y) override;
        virtual void setDecorated(GLFWwindow* w, bool decorated);
        int run(void);

    protected:
        virtual int handle(int ev) override;
        virtual void draw() override;
        GLFWwindow *m_glfwWindow;
        int gl_version_major;
        int gl_version_minor;
        Fr_Window* m_linkToMainWindow;

};
}
#endif //FRTK_POPUP_WINDOW_H