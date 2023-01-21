/**
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include<frtk.h>
#include<Fr_Core.h>

#include <glm/glm.hpp>

class Manipulator {
public:
    /**
     * Constructor
     */
    Manipulator();
    
    /**
     * Accumulates the manipulator matrix
     */
    glm::mat4 GetMatrix(const glm::vec3& look_dir = glm::vec3(0, 0, -1));

    /**
     * Accumulates the inverse of the manipulator matrix
     */
    glm::mat4 GetInverse();

    /**
     * Sets the reference point (world center)
     */
    void SetReferencePoint(float x, float y, float z);

    /**
     * Sets whether each axis is inverted or not
     */
    void SetInvertAxis(bool invertX, bool invertY = false);

    /**
     * Mouse button function
     */
    void GLFWMouse(int button, int state, double x, double y);

    /**
     * Mouse motion function
     */
    void GlutMotion(int x, int y);

private:
    enum class Operation {
        kRotation,  //Mouse click and drag
        kZoom,       //Left mouse and drag
        kNone       //nothing
    };

    const float kZoomScale = 1.0f;

    /** Verifies the k_button state and sets the k_operation */
    template<int k_button, Operation k_operation>
    void SetOperation(int button, int state, double x,double y);

    /** Computes the sphere vector for rotation */
    glm::vec3 computeSphereCoordinates(double x, double y);

    glm::vec3 reference_;
    glm::mat4 matrix_;
    glm::mat4 inv_;
    Operation operation_;
    double x_, y_;
    glm::vec3 v_;
    bool invertX_, invertY_;
};

#endif

