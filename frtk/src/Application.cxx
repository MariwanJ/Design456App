// generated by Fast Light User Interface Designer (fluid) version 1,0400

#include "Application.h"
#include <iconImages.h>


/*

    GLFW CALLBACKS
*/



/* Scene and engine*/
static Scene* scene = nullptr;


void Fr_GL3Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (s_GladInitialized && s_GLFWInitialized) {
        glViewport(0, 0, _wGl, _hGl);
    }
}

void Fr_GL3Window::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

void Fr_GL3Window::cursor_position_callback(GLFWwindow* win, double xpos, double ypos)
{
    /*
        if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            return;
        }
     */
    int button;
    if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_LEFT){
        button = 0;//TODO FIDME
    }
    else if (FR::glfw_MouseButton == GLFW_MOUSE_BUTTON_RIGHT)
    {
        button = 1;//TODO FIDME
        FR::glfw_MouseButton = -1;
    }
    else {
        button = -1;
        FR::glfw_MouseButton = -1;
    }
    double cposx, cposy;
    glfwGetCursorPos(win, &cposx, &cposy);
    FR::glfw_e_x = cposx;
    FR::glfw_e_y = cposy;
    if (button == 0 || button == 1)
        if (win != nullptr) {
            FR::globalP_pWindow->cameras[FR::globalP_pWindow->curr_camera].manipulator->GLFWMouse(button,FR::glfw_MouseClicked,cposx, cposy);
            FR::globalP_pWindow->cameras[FR::globalP_pWindow->curr_camera].manipulator->GLFWMotion(cposx, cposy);
            FR::globalP_pWindow->scene->RenderScene();
            button = -1;
        }
}

void Fr_GL3Window::cursor_enter_callback(GLFWwindow*, int entered)
{
}

void Fr_GL3Window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
    if (GLFW_PRESS == action) {
        FR::glfw_MouseClicked = 0; //Pressed
    }
    else if(GLFW_RELEASE == action){
        FR::glfw_MouseClicked = 1; //Released
    }
    FR::glfw_MouseButton = button;
}

void Fr_GL3Window::scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
    if (win != nullptr) {
        FR::globalP_pWindow->cameras[FR::globalP_pWindow->curr_camera].manipulator->GLFWMouse(2, FR::glfw_MouseClicked, xoffset, yoffset);
        FR::globalP_pWindow->scene->RenderScene();
    }
}

void Fr_GL3Window::joystick_callback(int jid, int events)
{

}


//Icon image definitions
static Fl_Image* image_Point() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Point, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Cylinder() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Cylinder, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Sphere() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Sphere, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Cone() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Cone, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Torus() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Torus, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Tube() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Tube, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Paraboloid() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Paraboloid, 46, 46, 4, 0);
    return image;
}
static Fl_Image* image_AlignToPlane() {
    static Fl_Image* image = new Fl_RGB_Image(idata_AlignToPlane, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Square() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Square, 46, 46, 4, 0);
    return image;
}
static Fl_Image* image_Line() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Line, 46, 46, 4, 0);
    return image;
}
static Fl_Image* image_Triangle() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Triangle, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Polygon() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Polygon, 46, 46, 4, 0);
    return image;
}

static void cb_btnBox(Fl_Button*, void*) {

}

static Fl_Image* image_Box() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Box, 46, 46, 4, 0);
    return image;
}

static Fl_Image* image_Extract() {
    static Fl_Image* image = new Fl_RGB_Image(idata_Extract, 46, 46, 4, 0);
    return image;
}


Fl_Menu_Item menu_[] = {
 {"&File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&New                               ", 0x4006e,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Open                              ", 0x4006f,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Close                             ", 0x4ffc1,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Save &As                           ", 0x50073,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Import                             ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Export                            ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"E&xit                              ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"&Edit", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Undo                              ", 0x4007a,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Redo                              ", 0x40079,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Copy                              ", 0x40063,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Cut                               ", 0x40078,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Paste                             ", 0x40076,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Douplicate                         ", 0x40064,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Preferences                       ", 0x9006f,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"&View                              ", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Show                              ", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Show Ground Plane                  ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Show Active Plane", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"&Toolbar                          ", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Main Toolbar                       ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Selection Toolbar                  ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"View Option Toolbar                ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Orthographic View                  ", 0x6f,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Isometric View                     ", 0x76,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Reset View                         ", 0x72,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&Camera Setting                    ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"&Select                             ", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&All Faces                          ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Vertical faces                      ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Horizontal faces                    ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Top Faces                           ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Bottom faces                        ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"&Window                             ", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"&All                                ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Vertical faces                      ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Horizontal faces                    ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Top Faces                           ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Bottom faces                        ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"&Help                               ", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Help                                ", 0xffbe,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"About                               ", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};


Application::Application(int x, int y, int w, int h, const char* l) :Fr_GL3Window(x,y,w,h,l) {
    begin(); {
        barMenu = new Fl_Menu_Bar(0, 0, 1540, 30);
        //barMenu->menu(menu_);
        barStatus = new Fl_Menu_Bar(0, 767, 1536, 25);
        tabToolbars = new Fl_Tabs(0, 30, 1540, 121);
        tabToolbars->labelsize(10);
        tabToolbars->begin(); {
            grp2DPrimatives = new Fl_Group(0, 55, 1539, 90, "2D Primitives");
            grp2DPrimatives->labelsize(12);
            grp2DPrimatives->hide();
            grp2DPrimatives->begin(); {
                btnPoint = new Fl_Button(5, 57, 46, 46);
                btnPoint->image(image_Point());
                btnPoint->callback((Fl_Callback*)createPoint_cb);

                btnPoint->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));
                btnLine = new Fl_Button(51, 57, 46, 46);
                btnLine->image(image_Line());
                btnLine->callback((Fl_Callback*)createLine_cb);
                btnLine->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnTriangle = new Fl_Button(97, 57, 46, 46);
                btnTriangle->image(image_Triangle());
                btnTriangle->callback((Fl_Callback*)createTriangle_cb);
                btnTriangle->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnSquare = new Fl_Button(144, 57, 46, 46);
                btnSquare->image(image_Square());
                btnSquare->callback((Fl_Callback*)createSquare_cb);
                btnSquare->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnPolygon = new Fl_Button(191, 57, 46, 46);
                btnPolygon->image(image_Polygon());
                btnPolygon->callback((Fl_Callback*)createPolygon_cb);
                btnPolygon->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));
                //TODO:: FIXME :: ADD MORE BUTTONS HERE
            }
            grp2DPrimatives->end();

            grpBasic = new Fl_Group(0, 55, 1539, 96, "Basic");
            grpBasic->labelsize(12);
            grpBasic->hide();
            grpBasic->begin();
            {
                btnBox = new Fl_Button(5, 57, 46, 46);
                btnBox->image(image_Box());
                btnBox->callback((Fl_Callback*)cb_btnBox);
                btnBox->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnCylinder = new Fl_Button(51, 57, 46, 46);
                btnCylinder->image(image_Cylinder());
                btnCylinder->callback((Fl_Callback*)createCylinder_cb);
                btnCylinder->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnSphere = new Fl_Button(97, 57, 46, 46);
                btnSphere->image(image_Sphere());
                btnSphere->callback((Fl_Callback*)createSphere_cb);
                btnSphere->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnCone = new Fl_Button(143, 57, 46, 46);
                btnCone->image(image_Cone());
                btnCone->callback((Fl_Callback*)createCone_cb);
                btnCone->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnTours = new Fl_Button(189, 57, 46, 46);
                btnTours->image(image_Torus());
                btnTours->callback((Fl_Callback*)createTours_cb);
                btnTours->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                btnTours = new Fl_Button(235, 57, 46, 46);
                btnTours->image(image_Tube());
                btnTours->callback((Fl_Callback*)createTours_cb);
                btnTours->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));
                //TODO:: FIXME :: ADD MORE BUTTONS HERE
            }
            grpBasic->end();

            grpAdvanced = new Fl_Group(0, 55, 1539, 90, "Advanced");
            grpAdvanced->labelsize(12);
            grpAdvanced->hide();
            grpAdvanced->begin();
            {
                btnParaboloid = new Fl_Button(5, 57, 46, 46);
                btnParaboloid->image(image_Paraboloid());
                btnParaboloid->callback((Fl_Callback*)createParaboloid_cb);
                btnParaboloid->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));
                //TODO:: FIXME :: ADD MORE BUTTONS HERE
            }
            grpAdvanced->end();

            grpAlignment = new Fl_Group(0, 55, 1539, 90, "Alignment");
            grpAlignment->labelsize(12);
            grpAlignment->hide();
            grpAlignment->begin();
            {
                btnAlignToPlane = new Fl_Button(5, 57, 46, 46);
                btnAlignToPlane->image(image_AlignToPlane());
                btnAlignToPlane->callback((Fl_Callback*)AlignToPlane_cb);
                btnAlignToPlane->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));

                //TODO:: FIXME :: ADD MORE BUTTONS HERE
            }
            grpAlignment->end();

            grpOperations = new Fl_Group(0, 55, 1539, 90, "Operations");
            grpOperations->labelsize(12);
            grpOperations->begin();
            {
                btnExtract = new Fl_Button(5, 57, 46, 46);
                btnExtract->image(image_Extract());
                btnExtract->callback((Fl_Callback*)Extract_cb);
                btnExtract->align(Fl_Align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE));
                //TODO:: FIXME :: ADD MORE BUTTONS HERE
            }
            grpOperations->end();
        }
        tabToolbars->end();

        tilMainWindow = new Fl_Tile(0, 151, 1529, 617);
        tilGToolBars = new Fl_Group(0, 151, 265, 617);
        tilGToolBars->begin();
        {
            Fl_Button t(0, 151, 265, 625, "");
            //TODO .: aDD HERE WIDGET TOOLS LIKE IN THE WORKBENCH
        }
        tilGToolBars->end();

        tilGglfw = new Fl_Group(265, 151, 1264, 617);
        tilGglfw->box(FL_DOWN_BOX);
        tilGglfw->begin();
        {
            setOpenGLWinowSize(tilGglfw->x()+68, tilGglfw->y()+39, tilGglfw->w()+313, tilGglfw->h()+149);
        }
        tilGglfw->end();
        tilMainWindow->resizable(tilGglfw);
        tilMainWindow->end();

        resizable(this);
    }
    end();
}

Application::~Application() {
}

int Application::run(int argc, char** argv)
{
    return 0;
}

void Application::CreateScene()
{
    Fr_GL3Window::CreateScene();
}

void createBox_cb() {
    printf("BOX!\n");
}

void createCylinder_cb() {
    printf("Cylinder!\n");
}

void createSphere_cb() {
    printf("Sphere!\n");
}

void createCone_cb() {
    printf("Cone!\n");
}

void createTours_cb() {
    printf("Tours!\n");
}

void createPoint_cb() {
    printf("Point!\n");
}

void createLine_cb() {
    printf("Line!\n");
}

void createTriangle_cb() {
    printf("Triangle!\n");
}

void createSquare_cb() {
    printf("Square!\n");
}

void createPolygon_cb() {
    printf("Polygon!\n");
}

void createParaboloid_cb() {
    printf("Polygon!\n");
}

void Application::createBox_cb(Fl_Button*, void*)
{
}

void Application::createCylinder_cb(Fl_Button*, void*)
{
}

void Application::createSphere_cb(Fl_Button*, void*)
{
}

void Application::createCone_cb(Fl_Button*, void*)
{
}

void Application::createTours_cb(Fl_Button*, void*)
{
}

void Application::createPoint_cb(Fl_Button*, void*)
{
}

void Application::createLine_cb(Fl_Button*, void*)
{
}

void Application::createTriangle_cb(Fl_Button*, void*)
{
}

void Application::createSquare_cb(Fl_Button*, void*)
{
}

void Application::createPolygon_cb(Fl_Button*, void*)
{
}

void Application::createParaboloid_cb(Fl_Button*, void*)
{
}

void Application::AlignToPlane_cb(Fl_Button*, void*)
{
}

void Application::Extract_cb(Fl_Button*, void*)
{
}
