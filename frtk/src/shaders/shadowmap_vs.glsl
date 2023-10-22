/**
 * SHADOWMAP VS 
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 430 core

layout (location = 0) in vec3 position;

layout (location = 0) out vec4 gl_Position;

uniform mat4 mvp;

void main () {
    gl_Position = mvp * vec4(position, 1.0);
}

