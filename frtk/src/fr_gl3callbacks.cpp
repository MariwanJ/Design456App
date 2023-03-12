#include <frtk.h>
#include <FR.h>

#include <Fr_GL3Window.h>
#include "fr_gl3callbacks.h"

void mnuFileNew_cb(void* widget, void* Data)
{
    std::cout << "File new callback\n";
}

void mnuFileOpen_cb(void* widget, void* Data)
{
    std::cout << "File open callback\n";
}

void mnuFileClose_cb(void* widget, void* Data)
{
    std::cout << "File close callback\n";
}

void mnuFileSave_cb(void* widget, void* Data)
{
    std::cout << "File save callback\n";
}

void mnuFileSaveAs_cb(void* widget, void* Data)
{
    std::cout << "File save as callback\n";
}

void mnuFileExport_cb(void* widget, void* Data)
{
    std::cout << "File export callback\n";
}

void mnuFileImport_cb(void* widget, void* Data)
{
    std::cout << "File import callback\n";
}

void mnuFileExit_cb(void*widget, void* Data){
    FR::globalP_pWindow->Exit();
}
