/**
 * SILHOUETTE VS
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 460 core


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (location=0) out vec4 gl_Position;

uniform float silhouette;
uniform mat4 mvp;

void main () {
	vec3 Xnormal= normal * vec3(0.0f,0.0f,0.0f);  //Experemental code - normal is not correct for Shape class. Check it
    gl_Position = mvp * vec4(position + silhouette * Xnormal, 1.0);
}

