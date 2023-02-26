#include <frtk.h>
#include <FR.h>

#include <Fr_GL3Window.h>

void mnuFileNew_cb(void* widget, void* Data)
{
    //Temporary code just for debugging
    CameraList camtype = FR::globalP_pWindow->getCameraType();
    if (camtype == CameraList::BACK)
        camtype = CameraList::PERSPECTIVE;
    else
        camtype = (CameraList)((int)(camtype) + 1);
    if (int(camtype) >= 6)
        camtype = CameraList::PERSPECTIVE;
    FR::globalP_pWindow->setCameraType(camtype);
    printf("camera changed\n");
}

void mnuFileOpen_cb(void* widget, void* Data)
{
}

void mnuFileClose_cb(void* widget, void* Data)
{
}

void mnuFileSave_cb(void* widget, void* Data)
{
}

void mnuFileSaveAs_cb(void* widget, void* Data)
{
}

void mnuFileExport_cb(void* widget, void* Data)
{
}

void mnuFileImport_cb(void* widget, void* Data)
{
}
