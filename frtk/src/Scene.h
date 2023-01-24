/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef SCENE_H
#define SCENE_H
//#include<frtk.h>
#include<Fr_Core.h>
#include <Group.h>
/**
 * The scene root
 */
typedef struct {
    float r;
    float g;
    float b;
    float a; //alpha
} bkgC;

class Scene : public Group {
public:
    /**
     * Default Constructor
     */
    Scene();
    /**
     * Sets the background color
     */ 
    void SetBackgroud(float r, float g, float b);
    void SetBackgroud(float r, float g, float b, float alfa);

    /**
     * Renders the scene
     * Throws runtime_error if there's no camera
     */
    virtual void RenderScene();
    static GLFWwindow*linkToglfw;

private:
    bkgC  background_;
};

#endif

